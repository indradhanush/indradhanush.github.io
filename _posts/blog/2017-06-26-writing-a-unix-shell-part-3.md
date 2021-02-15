---
layout: post
title: Writing a Unix Shell - Part III
categories: blog
tags: ['recurse-center', 'unix', 'operating-systems', 'C', 'shell', 'linux']
excerpt: 'Building your own UNIX shell in parts. This post explains
signal handling.'
date: June 26, 2017
author: self

---

Previously, in [Part II](/blog/writing-a-unix-shell-part-2/) we
discussed about running system commands and implementing our own
built-in commands. In Part III, we explore signal handling.

## What are signals?

When driving, one looks out for traffic signals, red or green and
takes a decision based on it: to stop or to keep driving. But the
traffic signals only come up after some intervals at crossroads
and is not present continuously along the road.

We can somewhat apply this analogy to signals in the context of
computers as well. A signal is a _software interrupt_ that is sent out
from an external event to a process. It may be sent to the process by
the kernel, by another process or by itself. A very common example is
`SIGINT`, which is the signal that is sent out when you hit `Ctrl-C`
to exit a program. Before going any further, let us take a look at the
following diagram:

<figure>
    <img src="{{ site.url }}/images/shell-part-3/signals.jpg" alt="signals" />
</figure>

The process executes three instructions and terminatess. However,
after the second instruction, it receives a signal. At this point the
regular execution of the program is interrupted and is passed on to
the _signal handler_. The signal handler is a pre-defined function
which is invoked when the signal is received. It returns the process
to its normal execution flow, where it goes on to execute the third
instruction and exits. However, depending on the code in the signal
handler itself, `instruction 3` might not be executed at all. For eg:
If the signal being sent is `SIGINT (Ctrl-C)`, the program exits.
Also, it is not guaranteed that a signal interrupt will only occur
when a program is between instructions. It may occur when an
instruction is executing and in such a case the instruction _will_ get
interrupted.

~~One important thing to note is that, while the main function runs in
its own thread the signal handler also runs in its own thread. Both
the threads belong to the same process though.~~

Edit: I misunderstood this line from `The Linux Programming
Interface, section 21.1.2`:

> Because a signal handler may asynchronously interrupt the execution
> of a program at any point in time, the main program and the signal
> handler in effect form two independent (althought not concurrent)
> threads of execution within the same process.

I asked around on IRC<sup>[1]</sup> about this and it turns out that,
"in effect" is the keyword here. It does not really create a thread
for the signal handler. However, when a signal is delivered, the
signal handler asynchronously interrupts a thread (in our case the
main thread since we have a single threaded application). Once
interrupted, the signal handler executes its own code, and the thread
may resume execution unless the signal handler exits the program. The
analogy to multiple threads helps to understand the flow of execution.

## Signal handling

Now that we understand signals, let us run the
[code for the shell](/code/shell-part-2/shell_with_builtin.c) we had from
[Part II](/blog/writing-a-unix-shell-part-2/).
If you run the executable and run the command `sleep 10` in the shell
and hit `Ctrl-C` before the command finishes, you will notice that
along with the command, our shell has quit as well.

```
$ gcc -lreadline shell_with_builtin.c && ./a.out
unixsh> sleep 10
^C
$
```

You will notice the same behaviour if you hit `Ctrl-Z` as well, which
generates the `SIGTSTP` signal. This stops the current running
process. Currently, the shell is reacting to the default signal
handlers set up by the operating system. The good news is that we can
customize this behaviour. We can use the function `signal()` defined in
`signal.h`: 

{% highlight c %}
#include <signal.h>

typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);
{% endhighlight %}

The first argument to the function is the signal number. Each signal
has a predefined integer value assigned to it. This number is 2 for
`SIGINT` and 20 for `SIGTSTP`.

The second argument is a pointer to a signal handler. The signal
handler is a function that must accept an `int` as the only parameter
and return `void` as described by the `typedef sighandler_t`.

Let us write a minimal program to handle `SIGINT`:

[<i>sigint.c</i>](/code/shell-part-3/sigint.c)
{% highlight c %}
#include <stdio.h>
#include <signal.h>

void sigint_handler(int signo) {
    printf("Caught SIGINT\n");
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1);                  /* Infinite loop */
}
{% endhighlight %}

We run an infinite `while` loop here on typing `Ctrl-C` you will
notice the text `Caught SIGINT` printed to the terminal, but the
program will continue to run after that. You can stop it with
`Ctrl-Z`. Here's the output from a sample run:

```
$ gcc sigint.c && ./a.out
^CCaught SIGINT
^CCaught SIGINT
^Z
[2]+  Stopped                 ./a.out
```

C provides two very useful macros that can be passed to the `signal`
function:
- `SIG_IGN`: Ignores the signal. Usage: `signal(SIGINT, SIG_IGN)`.
- `SIG_DFL`: Sets the default behaviour for the signal. This is useful
  when you want to reset the behaviour for a signal after having made
  some modifications. Usage: `signal(SIGINT, SIG_DFL)`.

However, it is not possible to ignore, block or setup a custom handler
for `SIGKILL` and `SIGSTOP`. Blocking a signal means that the signal
will not be delivered to the process at all.

We will now use signal handling in our shell and modify our code by
adding a call to `signal()` just before the `while` loop:

{% highlight c %}
...
int main() {
    ...
    signal(SIGINT, SIG_IGN);
    
    while (1) {
    
...
{% endhighlight %}

The modified file is available
[here](/code/shell-part-3/signal_handling_parent.c).  If you compile
and execute the binary and hit `Ctrl-C`, the shell does not quit
anymore. But if you run `sleep 10` in the shell and hit `Ctrl-C`, the
command does not quit as well. The reason behind this is that when a
`fork` is called, apart from duplicating the parent process, it copies
the current signal configurations (also known as the signal
dispositions) as well. Since we are ignoring `SIGINT` in the parent,
the child also inherits the same property for `SIGINT` from its
parent and conveninently ignores the keyboard interrupt (`Ctrl-C`).

To prevent this, we will restore the default behaviour of `SIGINT` in
the child process after `fork`. Note that this must be done before the
call to `execvp` since it will replace the current program with the
program passed in the command.

{% highlight c %}
...
        child_pid = fork();
        ...
        if (child_pid == 0) {
            signal(SIGINT, SIG_DFL);

            /* Never returns if the call is successful */
            if (execvp(command[0], command) < 0) {
...
{% endhighlight %}

The modified file is available [here](/code/shell-part-3/signal_handling_parent_and_child.c).

## Signal masks

Each process has an attribute called the `process signal mask` which
is maintained by the kernel. Any signal that is added to the `signal
mask` gets blocked from being delivered in the future, unless the
signal is removed from it. This is useful when we want to block a
signal based on the application logic.

Now, let's look at the following workflow for an example:

1. A signal is delivered. The signal handler gets invoked and is in
   the middle of executing some instructions.
2. The same signal is delivered again and the signal handler is
   invoked once again. The previous instance of the signal handler
   will get interrupted by a new instance of the signal handler.

This is not very desirable. To prevent the signal handler from
interrupting itself, the original signal that invoked the signal
handler gets added to the signal mask by default. This means that the
same signal will not interrupt the current instance of the signal
handler. And once the signal handler returns, the signal is removed
from the mask.

## Non local jumps

Currently, the shell does not do anything when it encounters a
`Ctrl-C`, while waiting for a command input. We would like to change
this behaviour to restart the `while` loop from the top and print a
newline. Effectively, `Ctrl-C` would mean a soft reset of the command
line. This brings us to the functions `setjmp` and `longjmp`, which
are used to perform a `non local jump`. This is equivalent of using a
`goto` statement to jump across scopes, except that the scope of a
`goto` is restricted to within a function. These functions are defined
in `setjmp.h` and their signatures look like this:

{% highlight c %}
int setjmp(jmp_buf env);
{% endhighlight %}

The `setjmp()` function sets a jump point and takes a buffer of type
`jmp_buf` which is used to store details like the stack pointer and
the instruction pointer. It returns 0 once the jump point has been
set.

{% highlight c %}
void longjmp(jmp_buf env, int val);
{% endhighlight %}

The `longjmp()` function uses the buffer which contains values saved by
`setjmp()` to determine the jump point in the program. Additionally it
takes an integer value, which is returned when the code returns to the
jump point. Here's an example:

[<i>setjmp_longjmp.c</i>](/code/shell-part-3/setjmp_longjmp.c)
{% highlight c linenos %}
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

static jmp_buf env;

void sigint_handler(int signo) {
    longjmp(env, 42);
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1){                  /* Infinite loop */
        if (setjmp(env) == 42) {
            printf("Restart.\n");
        }
        printf("next iteration...\n");
        sleep(2);
    }
}
{% endhighlight %}

A few important things to note about the code above:

1. The call to `signal()` takes a pointer to the `sigint_handler()`
   function instead of `SIG_IGN (line 13)`.
2. When the code reaches `line 15` for the first time, `setjmp()` is
   invoked and returns `0`.
3. After the signal handler has been registered, if we type `Ctrl-C`,
   the `longjmp()` function call is invoked where we pass `42` to it.
   The code jumps to `line 15` and this time `setjmp()` returns the
   value that was passed in `longjmp()` on `line 9`, i.e. `42`. Thus
   the check evaluates to `true`, which signifies that we reached this
   code from a non local jump. This is also referred to as a `fake
   return` by `setjmp()`.

If you compile and execute the binary, the output would be similar to:

```
$ gcc -lreadline -g setjmp_longjmp.c && ./a.out
next iteration...
^CRestart.
next iteration...
^Cnext iteration...
next iteration...
^Z
[6]+  Stopped                 ./a.out
```

But, `Restart` will be printed to the screen only the first time you
hit `Ctrl-C`. The reason behind this is that the first time the signal
handler is invoked for `SIGINT`, it blocks the signal and the call to
`longjmp()` does not unblock the signal since the signal handler never
really returns. As a result, `SIGINT` does not get delivered after the
first time.

To fix this problem, we have `sigsetjmp()` and `siglongjmp()`. The
function signatures are:

{% highlight c %}
int sigsetjmp(sigjmp_buf env, int savesigs);

void siglongjmp(sigjmp_buf env, int val);
{% endhighlight %}

They are similar to `setjmp()` and `longjmp()`, but they accept a buffer
of type `sigjmp_buf` instead of `jmp_buf`. Also, the `sigsetjmp()`
function accepts a flag `savesigs`. If value of this flag is non zero,
then `sigsetjmp()` saves the current process signal mask and restores it
when `siglongjmp()` is invoked. This means, that the signal which
initially gets blocked on invoking the signal handler, gets unblocked
as soon as `siglongjmp()` is invoked.

And here's an example using these functions:

[<i>sigsetjmp_siglongjmp.c</i>](/code/shell-part-3/sigsetjmp_siglongjmp.c)
{% highlight c linenos %}
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

static sigjmp_buf env;

void sigint_handler(int signo) {
    siglongjmp(env, 42);
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1){                  /* Infinite loop */
        if (sigsetjmp(env, 1) == 42) {
            printf("Restart.\n");
        }
        printf("next iteration...\n");
        sleep(2);
    }
}
{% endhighlight %}

Note that the function call to `sigsetjmp()` on `line 15` accepts an
extra parameter for the `savesigs` flag. Also, `env` is of type
`sigjmp_buf`. And if you compile and execute it you will notice that
`Ctrl-C` is accepted more than once, until you stop the program:

```
$ gcc -lreadline -g sigsetjmp_siglongjmp.c && ./a.out
next iteration...
^CRestart.
next iteration...
^CRestart.
next iteration...
^Z
[7]+  Stopped                 ./a.out
```

There's one last catch about this arrangement though. We setup the
signal handler before setting a jump point. But there is no guarantee
that a signal will only be delivered after the jump point has been
set. And if this scenario takes place, our program will crash. To
avoid this we add a global flag that is `false` by default. Once the
jump point has been set, we set the flag to `true` and add a check on
this flag in our signal handler. If the flag is `false`, we skip the
call to `longjmp()` and return from the handler instead. Here's our
updated signal handler and main function:

[<i>sigsetjmp_siglongjmp_with_check.c</i>](/code/shell-part-3/sigsetjmp_siglongjmp_with_check.c)
{% highlight c %}
...
static volatile sig_atomic_t jump_active = 0;

void sigint_handler(int signo) {
    if (!jump_active) {
        return;
    }
    siglongjmp(env, 42);
}

int main() {
    signal(SIGINT, sigint_handler);
    while (1){                  /* Infinite loop */
        if (sigsetjmp(env, 1) == 42) {
            printf("Restart.\n");
        }
        jump_active = 1;        /* Set the flag */
        printf("next iteration...\n");
        sleep(2);
    }
}
{% endhighlight %}

The flag `jump_active` is of type `volatile sig_atomic_t`. This is
essential, since this flag will be accessed asynchronously by multiple
threads of the process, i.e. the main thread and the signal handler
thread. The type guarantees atomic access to the variable across
multiple threads. 

This brings us back to the first example,
[`sigint.c`](/code/shell-part-3/sigint.c) where we used `printf` in
the signal handler. `printf` is an _async unsafe_ function. Which
means, that if the signal handler is invoked while another `printf` is
executing in a different part of the program, the output may be
erratic. We use `printf` only to explain the concept here, and it
should not be used in real life applications.

## A better way for signal handling: sigaction

So far we have used the `signal()` function for setting signal
handlers. However, its implementation differs from system to system
and is generally not recommended to be used directly in application
code since its usage makes portability hard. The alternative is to use
the `sigaction()` function call.

This is also defined in `signal.h`, but before we look at its
signature, lets look at the definition of the `struct sigaction` (yes,
sadly they are both named the same):

{% highlight c %}
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};
{% endhighlight %}

The struct requires:
- `sa_handler`: A pointer to the signal handler.
- `sa_sigaction`: A pointer to a signal handler that can access more
  information regarding the signal. Either one of `sa_handler` or
  `sa_sigaction` should be used.
- `sa_mask`: An optional set of signals which are blocked while the
  signal handler is executing.
- `sa_flags`: A `bitwise OR` of config flags.
- `sa_restorer`: This is for internal use and should not be set.

Now let us look at the signature of the `sigaction()` function:

{% highlight c %}
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
{% endhighlight %}

It accepts the signal number and two `sigaction struct` objects. The
first contains new configuration to be set, while the second is used
to save the current configuration before overwriting it with the new
one.

In our previous code, we replace `signal(SIGINT, signal_handler` by:

{% highlight c %}
    struct sigaction s;
    s.sa_handler = sigint_handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s, NULL);
{% endhighlight %}

The `sigemptyset()` function initializes the `sa_mask` attribute of
the struct with an empty set. We set the `SA_RESTART` flag on the
struct, which implies that if the signal handler is invoked while the
program is in the middle of a system call, the system call will be
restarted after the signal handler has finished its execution. And
finally, we call the `sigaction()` function with the signal and the
`sigaction struct`. We do not care about the previous configuration
for the signal and pass `NULL` instead of another `sigaction struct`
object. The example is available
[here](code/shell-part-3/sigaction.c).


## One last trivia

During this exercise contrary to my belief I realized that on typing
`Ctrl-D` no signal is generated like it does when we type
`Ctrl-C`. Rather it sends the `EOF` character. Since we've changed
`Ctrl-C` to not quit the shell, we implement `Ctrl-D` to do that
instead for us, which is similar to the behaviour of `bash`. The
following snippet helps us do this:

{% highlight c %}
...
        input = readline("rcsh> ");
        if (input == NULL) {  /* Exit on Ctrl-D */
            printf("\n");
            exit(0);
        }
...
{% endhighlight %}
    
The code for the shell with the concepts explained above is available
[here](/code/shell-part-3/shell.c), but it is recommended that
readers try to implement it themselves.

That brings us to the end of part III. All the code examples shown in
this blog post are available
[here](https://github.com/indradhanush/indradhanush.github.io/tree/master/code/shell-part-3/). In
the next blog post we will see how to run background commands and
perform job control. Stay tuned.

## Acknowledgements

Once again thanks to [Dominic Spadacene](https://github.com/domspad)
for pairing with me on this and to
[Saul Pwanson](https://github.com/saulpw) for being patient with my
endless questions.

[1] - Also, thanks to `valdis` and `derRichard` on `#kernelnewbies
(irc.oftc.net)` for helping me understand the asynchronous nature of a
signal handler.

## Resources

- [The Linux Programming Interface - Micahel Kerrisk](http://amzn.to/2sH0xMW)
- [Advanced Programming in the UNIX Environment - Stephens & Rago](http://amzn.to/2sc0p8o)
- [Linux man pages](https://linux.die.net/man/)

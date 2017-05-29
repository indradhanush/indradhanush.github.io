---
layout: post
title: Writing a Unix Shell - Part I
categories: blog
tags: ['recurse-center', 'unix', 'operating-systems', 'C', 'shell']
excerpt: 'Building your own UNIX shell in parts. This post focuses on
the semantics of the fork system call'
date: May 28, 2017
author: self

---

One of the projects that I am exploring at RC, is writing a UNIX
shell. This is the first part of a series of posts that will
eventually follow.

## What is a shell?

A lot has been written about this, so I will not go into too much
detail about the definition. However, in one line -

> A shell is an interface that allows you to interact with the kernel
> of an operating system.

## How does a shell work?

A shell parses commands entered by the user and executes this. To be
able to do this, the workflow of the shell will look like this:

1. Startup the shell
2. Wait for user input
3. Parse user input
4. Execute the command and return the result
5. Go back to `2`.

There is one important piece to all of this though: processes. The
shell is the parent process. This is the `main` thread of our
program which is waiting for user input. However, we cannot execute
the command in the `main` thread itself, because of the following
reasons:

1. An erroneous command will cause the entire shell to stop
   working. We want to avoid this.
2. Independent commands should have their own process blocks. This is
   known as isolation and falls under fault tolerance.

## Fork

To be able to avoid this, we use the system call `fork`. I thought I
understood `fork` until I wrote about four lines of code using it.

`fork` creates a copy of the current process. The copy is known as the
`child` and each process in a system has a unique process id (pid)
associated to it. Let's take a look at the following piece of code:

[<i>fork.c</i>]({{ site.url }}/code/shell-part-1/fork.c)
{% highlight c linenos %}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main() {
    pid_t child_pid = fork();
        
    // The child process
    if (child_pid == 0) {
        printf("### Child ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
    } else {
        printf("### Parent ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
    }
 
    return 0;
}
{% endhighlight %}


The `fork` system call returns twice, once for each process. This
sounds counter intuitive at first. But let's take a look at what goes
underneath the hood.

1. By invoking `fork` we are creating a new branch in our
program. This is not the same as a traditional `if-else`
branch. `fork` creates a copy of the current process and creates a new
one out of it. The resulting system call returns the process id of the
child process.

2. Immediately after the `fork` call has succeeded, both the child and
   the parent process (the main thread of our code) are running
   simultaneously.

To give you a better idea of the program flow, take a look at this
diagram:

<figure>
	<img src="{{ site.url }}/images/fork.jpg" alt="fork" />
</figure>

The `fork()` creates a new child process, but at the same time,
execution of the parent process is not halted. The child process
begins and finishes its execution independent of the parent and vice
versa. 

A quick note before we proceed further, the `getpid` system call
returns the current process id.

If you compile and execute the code, you'd get an output similar to the
following:

```
### Parent ###
Current PID: 85247 and Child PID: 85248
### Child ###
Current PID: 85248 and Child PID: 0
```

In the block under `### Parent ###`, the current process ID is `85247`
and that of the child is `85248`. Note that the pid of the child is
greater than that of the parent, implying that the child was created
after the parent.

In the block under `### Child ###`, the current process ID is `85248`,
which is the same as the pid of the child in the previous
block. However, the child pid here is `0`.

Actual numbers would vary on each execution.

You'd be forgiven for thinking about how can `child_pid` assume two
different values in the same execution flow, when we have clearly
assigned a value to `child_pid` once on `line 9`. However, recall that
invoking `fork` creates a new process, which is identical to the
current one. As a result, in the parent process, `child_pid` is the
actual value of the child process that just got created, and the child
process itself has no child of its own, as a result of which the value
of `child_pid` is `0`.

Thus, the `if-else` block we have defined from lines 12 to 16 is
required to control what code to execute in the child, vs the
parent. When `child_pid` is `0`, the code block will be executed under
the child process, while the else block will be executed under the
parent process instead. The order in which the blocks will be executed
cannot be determined, and depends on the operating system's scheduler.

## Introducing determinism

Let me introduce you to the system call `sleep`. To quote the linux
man pages:

> sleep -- suspend execution for an interval of time

The interval is in seconds.

Let us add a `sleep(1)` call to the parent process, which would be the
`else` block of our code:

[<i>sleep_parent.c</i>]({{ site.url }}/code/shell-part-1/sleep_parent.c)
{% highlight c linenos %}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main() {
    pid_t child_pid = fork();

    // The child process
    if (child_pid == 0) {
        printf("### Child ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
    } else {
        sleep(1); // Sleep for one second
        printf("### Parent ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
    }
 
    return 0;
}
{% endhighlight %}

And when you execute this, the output would be similar to:

```
### Child ###
Current PID: 89743 and Child PID: 0
```

and after a span of 1 second, you would see

```
### Parent ###
Current PID: 89742 and Child PID: 89743
```

And you will see the same behaviour each time you execute the
code. This is because we have made a blocking `sleep` call in the
parent process and the OS scheduler in the meantime finds free CPU
time for the child process to be executed.

Similarly, if you add the `sleep(1)` call to the child process
instead, i.e. the `if` block of our code, you will notice that the
output of the parent block immediately on the console. But you will
also notice that your program has terminated. And the output of the
child block being dumped into `stdout`. It looks like:

```
$ gcc -lreadline blog/sleep_child.c -o sleep_child && ./sleep_child
### Parent ###
Current PID: 23011 and Child PID: 23012
$ ### Child ###
Current PID: 23012 and Child PID: 0
```

The source for this is available in [sleep_child.c]({{ site.url
}}/code/shell-part-1/sleep_child.c).

This is because the parent process has nothing to do after the
`printf` statement, and is terminated. However, the child process is
blocked on the `sleep` call for one second after which the `printf`
statement is executed.

## Determinism done right

However, using `sleep` to control your process execution flow is not
the best approach, because if you make a `sleep` call for `n seconds`:

1. How do you guarantee that whatever it is that you are waiting for will
complete its execution within those `n seconds`. 
2. What if whatever it is that you are waiting for finishes much
   sooner than `n seconds`? In that case you are idling unnecessarily.
   
A better approach here would be using the `wait` system call instead
(or one of the variants). We will use the `waitpid` system call. It
takes the following parameters:

1. Process ID of the process for which you want your program to wait.
2. A variable which will be populated with information on how the
   process was terminated.
3. Options flag, to customize the behaviour of `waitpid`

[<i>wait.c</i>]({{ site.url }}/code/shell-part-1/wait.c)
{% highlight c linenos %}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main() {
    pid_t child_pid;
    pid_t wait_result;
    int stat_loc;

    child_pid = fork();
        
    // The child process
    if (child_pid == 0) {
        printf("### Child ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
        sleep(1); // Sleep for one second
    } else {
        wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
        printf("### Parent ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
    }
 
    return 0;
}
{% endhighlight %}

When you execute this, you will notice that the child block gets
printed immediately and waits for a brief moment (we added the `sleep`
after the `printf` here). The parent process waits for the child to
finish execution after which it is free to execute its own commands. 

That's all for part I. All the code examples shown in this blog post
are available
[here](https://github.com/indradhanush/indradhanush.github.io/tree/master/code/shell-part-1/). In
the next post, we will explore how to take a command as user input and
execute it. Stay tuned.

## Acknowledgements

Thanks to [Saul Pwanson](https://github.com/saulpw) for helping me
understand the behaviour of `fork` and to
[Jaseem Abid](https://github.com/jaseemabid) for reading drafts and
suggesting edits.

## Resources

- [EnthusiastiCon - Stefanie Schirmer “OMG building a shell in 10 minutes”](https://www.youtube.com/watch?v=k6TTj4C0LF0)
- [Linux man pages](https://linux.die.net/man/)

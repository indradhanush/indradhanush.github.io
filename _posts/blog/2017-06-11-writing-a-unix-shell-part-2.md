---
layout: post
title: Writing a Unix Shell - Part II
categories: blog
tags: ['recurse-center', 'unix', 'operating-systems', 'C', 'shell', 'linux']
excerpt: 'Building your own UNIX shell in parts. This post explains
how to execute commands.'
date: June 11, 2017
author: self

---

In [Part I](/blog/writing-a-unix-shell-part-1/) we discussed about the
`fork` system call and its caveats. In this post, we shall explore how
to execute commands.

## Exec

This brings us to the `exec` family of functions. Namely, it has the
following functions:

* `execl`
* `execv`
* `execle`
* `execve`
* `execlp`
* `execvp`

For our needs, we will use `execvp` whose signature looks like this:

{% highlight c %}
int execvp(const char *file, char *const argv[]);
{% endhighlight %}

The `vp` in the name of the function indicates that, it accepts the
name of a file, for which it will search for in the `$PATH` variable
of the system and an array of arguments to be executed.

You may read the [man page for exec](https://linux.die.net/man/3/exec)
for more information on the other functions.

Let us take a look at the following code, which executes the command
`ls -l -h -a`:

[<i>execvp.c</i>](/code/shell-part-2/execvp.c)
{% highlight c linenos %}
#include <unistd.h>

int main() {
    char *argv[] = {"ls", "-l", "-h", "-a", NULL};
    execvp(argv[0], argv);

    return 0;
}
{% endhighlight %}

A few things to note about the `execvp` function:

1. The first argument is the name of the command
2. The second argument consists of the name of the command and the
   arguments passed to the command itself. It must also be terminated
   by `NULL`.
3. It also swaps out the current process image with that of the
   command being executed, but more on that later.
   
If you compile and execute the above, you will see an output similar
to the following:

```
total 32
drwxr-xr-x  5 dhanush  staff   170B Jun 11 11:32 .
drwxr-xr-x  4 dhanush  staff   136B Jun 11 11:30 ..
-rwxr-xr-x  1 dhanush  staff   8.7K Jun 11 11:32 a.out
drwxr-xr-x  3 dhanush  staff   102B Jun 11 11:32 a.out.dSYM
-rw-r--r--  1 dhanush  staff   130B Jun 11 11:32 execvp.c
```

Which is exactly the same if you manually execute `ls -l -h -a` in
your primary shell.

Now that we can execute commands, we need to construct something
useful using the `fork` system call that we learned about in
[part I](/blog/writing-a-unix-shell-part-1/). In effect we will do the
following:

1. Accept the command as user input.
2. Call `fork` to create a child process.
3. Execute the command in the child process while the parent waits for
   the command to complete.
4. Return back to step 1.

Let us take a look at the following function.  which takes a string as
the `input`. We use the library function `strtok` to split the string
by the character `space` and return an array of strings instead. We also
terminate the array by `NULL`.

{% highlight c linenos %}
#include <stdlib.h>
#include <string.h>

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}
{% endhighlight %}

If the `input` to the function is the string `"ls -l -h -a"`, then the
function will create an array of the form
`["ls", "-l", "-h", "-a", NULL]` and return the pointer to this array.

Now in our `main` function, we invoke `readline` to read an input from
the user, and pass it to `get_input` we just defined above. Once the
input has been parsed, we call `fork` and call `execvp` in the child
process. Before we dive into the code, take a look at the following
diagram, to understand the semantics of `execvp` first:

<figure>
    <img src="{{ site.url }}/images/shell-part-2/execvp.jpg" alt="execvp" />
</figure>

When the `fork` command completes, the child is an exact copy of the
parent process. However, when we invoke `execvp`, it replaces the
current program with the program passed to it in the arguments. What
this means is that although the current text, data, heap and stack
segments of the process are replaced, the process id still remains
unchanged, but the program gets overwritten completely. If the
invocation is successful, then `execvp` never returns, and any code in
the child after this will not be executed. And here is the `main` function:

{% highlight c linenos %}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;

    while (1) {
        input = readline("unixsh> ");
        command = get_input(input);

        child_pid = fork();
        if (child_pid == 0) {
            /* Never returns if the call is successful */
            execvp(command[0], command);
            printf("This won't be printed if execvp is successul\n");
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        free(input);
        free(command);
    }

    return 0;
}
{% endhighlight %}

The entire code is available in a single file
[here](/code/shell-part-2/shell.c). If you compile it with `gcc -g
-lreadline shell.c` and execute the binary, you will have a minimal
working shell, and you can use it to run system commands like `pwd`
and `ls -lha`:

```
unixsh> pwd
/Users/dhanush/github.com/indradhanush.github.io/code/shell-part-2
unixsh> ls -lha
total 28K
drwxr-xr-x 6 root root  204 Jun 11 18:27 .
drwxr-xr-x 3 root root 4.0K Jun 11 16:50 ..
-rwxr-xr-x 1 root root  16K Jun 11 18:27 a.out
drwxr-xr-x 3 root root  102 Jun 11 15:32 a.out.dSYM
-rw-r--r-- 1 root root  130 Jun 11 15:38 execvp.c
-rw-r--r-- 1 root root  997 Jun 11 18:25 shell.c
unixsh> 
```

Note that the `fork` is only called after the command has been entered
by the user, which means that the user prompt accepting input from the
user is the parent process.

## Error handling

So far we have assumed that all our commands would work perfectly all
the time and we are not handling the errors. So we will make a few
changes to [shell.c](/code/shell-part-2/shell.c):

* **fork** - If the OS runs out of memory or reaches the maximum
   number of allowed processes, a child process will not be created
   and it will return -1. We add the following to our code:
   
{% highlight c %}
    ...
    while (1) {
        input = readline("unixsh> ");
        command = get_input(input);

        child_pid = fork();
        if (child_pid < 0) {
            perror("Fork failed");
            exit(1);
        }
    ...
{% endhighlight %}


* **execvp** - As explained above, it will never return on a
  successful invocation. However, if it will return -1 if the
  execution has failed. Likewise, we modify our call to `execvp`:
  
{% highlight c %}
    ...
            if (execvp(command[0], command) < 0) {
                perror(command[0]);
                exit(1);
            }
    ...
{% endhighlight %}

Note that, while the `exit` call after `fork` terminates the entire
program, the `exit` call after `execvp` will only terminate the child,
since the code belongs to the child process only.

* **malloc** - It can fail if the OS runs out of memory. We should exit
  the program in such a scenario:

{% highlight c %}
char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    if (command == NULL) {
        perror("malloc failed");
        exit(1);
    }
    ...
{% endhighlight %}

* **Dynamic memory allocation** - Currently our command buffer
  allocates 8 blocks only. If we enter a command which has more than 8
  words, our command will not work as expected. This has been done to
  keep the example easy to understand and has been left as an exercise
  for the reader.

The code with error handling as shown above is available
[here](/code/shell-part-2/shell_with_error_handling.c).

## Builtin commands

If you try to execute the `cd` command, you will get an error that
says:
```
cd: No such file or directory
```

Our shell does not recognize the `cd` command yet. The reason behind
this is that it is not a system program like `ls` or `pwd`. Let us
take a step back and assume for a moment that `cd` is a system program
as well. What do you think the execution flow will be like?  You may
want to think about it before reading further.

The flow proceeds like this:

1. The user sends the input `cd /`.
2. The shell `forks` the current process and executes the command in
   the child.
3. After a successful invocation, the child exits and the control is
   returned to the parent process.
4. The current working directory of the parent has not changed, since
   the command was executed in the child. As a result, the `cd`
   command although successful, did not produce the result that we desired.

Thus, to support `cd` we will have to implement it on our own. We also
need to ensure that, if the command entered by the user is `cd` (or
belongs to a list of pre-defined built-in commands), we will not
`fork` the process at all. Instead, we will execute our implementation
of `cd` (or any other built-in) and move on to wait for the next user
input. For `cd`, thankfully we have the `chdir` function call
available to us and using it is straightforward. It accepts the path
as an argument and returns 0 upon success and -1 upon a failure.  We
define our function:

{% highlight c %}
int cd(char *path) {
    return chdir(path);
}
{% endhighlight %}

And add a check in our `main` function for it:

{% highlight c %}
    while (1) {
        input = readline("unixsh> ");
        command = get_input(input);

        if (strcmp(command[0], "cd") == 0) {
            if (cd(command[1]) < 0) {
                perror(command[1]);
            }

            /* Skip the fork */
            continue;
        }
    ...
{% endhighlight %}

The code with the above changes is available
[here](/code/shell-part-2/shell_with_builtin.c) and if you compile and
execute it, you will be able to run the `cd` command. Here is an
example output:

```
unixsh> pwd
/Users/dhanush/github.com/indradhanush.github.io/code/shell-part-2
unixsh> cd /
unixsh> pwd
/
unixsh> 
```

And that brings us to the end of part II. All the code examples shown
in this blog post are available
[here](https://github.com/indradhanush/indradhanush.github.io/tree/master/code/shell-part-2/). In
the [next blog post](/blog/writing-a-unix-shell-part-3/) we will
explore the topic of signals and implement handling user interrupts
(Ctrl-C). Stay tuned.

## Acknowledgements

Thanks to [Dominic Spadacene](https://github.com/domspad) for pairing
with me on this and to [Saul Pwanson](https://github.com/saulpw) for
helping me solve the weird memory leaks when nothing seemed to be working.

**Update**: Saul mentioned that checking for errors with `< 0` is
conventionally better than `== -1`, since some APIs might return
negative values other than just `-1` and `< 0` helps protect against
those. I've updated the post and the code examples accordingly.

## Resources

- [Advanced Programming in the UNIX Environment - Stephens & Rago](http://amzn.to/2sc0p8o)
- [Linux Systems Programming - Robert Love](http://amzn.to/2sc3TYr)
- [Linux man pages](https://linux.die.net/man/)

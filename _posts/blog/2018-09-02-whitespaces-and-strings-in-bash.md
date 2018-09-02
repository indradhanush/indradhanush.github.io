---
layout: post
title: 'Whitespaces and strings in Bash'
categories: blog
tags: ['programming', 'bash', 'kubernetes', 'kinvolk']
excerpt: 'Yet another bug when manipulating strings in bash and lessons learned from this exercise.'
date:  2 September, 2018
author: self
---

Last week at work I was working on a bash script, part of which needed
to get the status of a Kubernetes node. Specifically I was running
this command:

```
$ kubectl get nodes node-0
```

And if everything looked well, the output would be something similar
to:

```
NAME      STATUS     ROLES     AGE       VERSION
node-0    Ready      <none>    22h       v1.11.1
```

As part of the script I was using `cut` to extract the value of the second column by doing:


{% highlight shell linenos %}
#!/bin/bash

result=$(kubectl get nodes node-0 | tail -n 1)
state=$(echo $result | cut -d ' ' -f2)

echo $state
{% endhighlight %}

Let's break that down:

On line three, I pipe the output of `kubectl get nodes node-0` to
`tail` and store only the second line of the output since the first
line contains the column headings and is not useful in this case.

On line four, I use the `cut` command to split the words by the
character `space`, indicated by the `-d ' '` flag and extract the
value of the second column, indicated by the `-f2` flag. When I ran
the script I saw the output as expected:

```
Ready
```

However, [shellcheck](https://www.shellcheck.net/) complained about
the line number four of the script (it complained about the last line
as well, but that's not relevant to this post):

```
In test.sh line 4:
state=$(echo $result | cut -d ' ' -f2)
             ^-- SC2086: Double quote to prevent globbing and word splitting.
```

## Behold the mighty bug &#x1F41B;

So I fixed the warning by wrapping it around double quotes:

```
state=$(echo "$result" | cut -d ' ' -f2)
```

But to my surprise, all I had now was an empty string as output. To
debug this I printed the value of `$result` by:

```
echo $result
```

Which gave the output:

```
node-0 Ready <none> 3d v1.11.1
```

## Debugging &#x1F52C;

I copied this and ran piped it to `cut -d ' ' -f2` directly on the
bash shell. And I got the expected output -- ```Ready```.

I copied this and ran the code directly on the shell this time:

```
$ result="node-0 Ready <none> 3d v1.11.1"
$ state=$(echo "${result}" | cut -d ' ' -f2)
$ echo $state
Ready
```

I was able to get the desired output this time. I asked in my
company's Slack and eventually found out that if I ran the following
in the shell directly:

```
$ result=$(kubectl get nodes node-0 | tail -n 1)
$ echo "$result"
node-0    Ready     <none>    3d        v1.11.1
```

Versus, if I ran:

```
$ echo $result
node-0 Ready <none> 3d v1.11.1
```

Notice the difference yet? The difference is the presence of double
quotes around `$result`. When we wrap a variable around double quotes
we are forcing bash to print the variable as is and to quote the linux
documentation project:

> Using double quotes the literal value of all characters enclosed is
> preserved, except for the dollar sign, the backticks (backward
> single quotes, ``) and the backslash.

## Lessons learned &#x1F4D6;

I learned two things out of this:

1. The output of `kubectl get nodes` is not separated by a single space character.
2. Bash cleans up extra spaces when writing to `stdout` unless you use
   variable quoting.

Now that the problem had been identified, the solution was easy -- I
needed to squeeze out the extra spacing between the columns before
using `cut` on it:

```
state=$(echo "${result}" | tr -s "[:space:]" | cut -d ' ' -f2)
```

Another important lesson that I learned from this exercise is that
when manipulating strings plain text format isn't the best
option. `kubectl` can output in both `yaml` and `json`. I prefer
`json` as it's easier to parse by the naked eye and I can use
[jq](https://github.com/stedolan/jq) to manipulate `json` output
programmatically. As a result I was able to minimize my script to a
single line:

```
state=$(kubectl get nodes node-0 -o json | jq ".status.conditions[-1])"
```

The filters to `jq` are Kubernetes specific filters.

## Addendum &#x1F4E2;

1. It's generally considered good practice to wrap bash variables
   around `{}`. So instead of `echo "$result"`, using `echo ${result}`
   is safer and can help avoid bugs involving string expansion in
   bash.

2. If you're into Kubernetes, `kubectl` also supports the `-o
jsonpath` that lets you directly specify the json filter and returns
the minimized output instead of the entire json string. I tried using
`jsonpath` but in my case I noticed that negative indexing raised a
`panic`. I haven't yet filed an issue about this on the Kubernetes
project's issue tracker and intend to do so once I've verified this
with the latest Kubernetes components.

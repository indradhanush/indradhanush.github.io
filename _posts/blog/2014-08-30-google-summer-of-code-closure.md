---
layout: post
title: Google Summer of Code - Closure
categories: blog
tags: ['gsoc']
date: August 30, 2014
author: self
---

Its been quite long since my last post. The reason being, post
mid-term my work schedule started to get more and more hectic. Last
week I finished off my GSoC project and successfully cleared final
evaluations. Yay!

So I think I ought to write this post describing my work over the
summer. As described in one of my
[previous](http://indradhanush.github.io/2014/05/21/gsoc-project-preview/)
blog post, the target was to get a sync over ZeroMQ working and add
resume and selective sync support.

But I was only able to implement the sync transport and get a
successful sync working. This was trickier than it seemed initially.
There were challenges, especially in maintaining backwards
compatibility. For this we had to choose a blocking client. I have
written a detailed report about the achievements over the summer, the
challenges faced and the way to look forward. So I am not going to
repeat all that here. You can read it
[here](https://github.com/indradhanush/U1DB-ZeroMQ-Transport/blob/benchmarks/Report.md).

This post is more about the experience I gained over 12 weeks. In
retrospection, I learned more than I could possibly have imagined. I
learned at least 10 times more about software development than I did in
my entire final year.

First off, I learned about
[git-flow](http://nvie.com/posts/a-successful-git-branching-model/).
Now let me stress that this is something that every programmer and
every organisation should follow for their projects. My mentor
recommended me to follow this. And I did, only here I treated my
master as my develop. I know it kind of breaks it but since we don't
have any releases yet so it kind of makes sense. And ofcourse, very
soon I am going to fork off a __develop__ and follow the git-flow in a
more accurate way.

Talking about git, I always had a fear towards `git rebase` and this is
something that I mastered over the summer.

I learned the hard way the importance of writing `unittests`. So much,
that I am never going to do a project without them anymore. I lost a
week hunting bugs in my sync transport. And this was very painful for
me. Especially when I used to be stuck for hours with `pdb` hunting
for that one line of code behaving badly. I'm not sure I am into
[TDD](http://en.wikipedia.org/wiki/Test-driven_development)
completely yet but I am going to write my tests as I develop. Not
after I develop.

It was tough to get my head around
[Mock](http://mock.readthedocs.org/). In fact it took more than a
couple of weeks actually. But once I understood it, I realised the
beauty of it. And especially, my tests that often consist of sending
data over the wire, mocking all that network activity and even mocking
the endpoints became crucial for writing clean tests. Initially I was
not using Mock for my tests, but once I got through it, I have used it
as extensively as possible for my tests. The older tests still need to
be updated to use mock though.

I learned many more things that are difficult to describe. You can
only learn about them by writing code. In technical jargon, I
understood about software paradigms. Why documentation is important.
And how to write code that is easier to understand. Because code is
more often read than written!

My personal recommendation is that every student must participate in
GSoC. It is a program like no other!

Thats it for now. You are welcome to lend us a hand by
contributing towards this. Come say hello at __#leap__ in
[irc.freenode.net](http://webchat.freenode.net/) and ask for _drebs_,
_kaliy_ or me (_dhanush_). We will be very happy to see you there!
Also, you can look up the
[README](https://github.com/indradhanush/U1DB-ZeroMQ-Transport/blob/benchmarks/README.md)
for the project and the
[conclusion report](https://github.com/indradhanush/U1DB-ZeroMQ-Transport/blob/benchmarks/Report.md).

The latest code is in the branch
[benchmarks](https://github.com/indradhanush/U1DB-ZeroMQ-Transport/tree/benchmarks).
Haven't merged it into master yet. I will update the post once we do.
Thanks for reading! Leave your feedback in comments!

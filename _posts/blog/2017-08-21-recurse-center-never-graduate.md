---
layout: post
title: Recurse Center - Never Graduate!
categories: blog
tags: ['recurse-center', 'notes']
excerpt: My final thoughts about my recently concluded batch at the
    Recurse Center
date: August 21, 2017
author: self

---

When I made up my mind to attend the
[Recurse Center](https://recurse.com/) earlier this year I found
myself standing in a crossroads of sorts. I found myself in a
comfortable position at my job in Instamojo, being confident about
most parts of the growing codebase along with having worked on the
infrastructure team. In short, I would hardly flinch when I had to
build something and knew my way around from the get go almost all the
time. But then I had always wanted to work in the area of distributed
systems and after having worked for almost three years as a full time
programmer, I found myself lacking and not much to show for it.

## What I did at the Recurse Center?

The first thing that I wanted to work on at RC was to build a
multiplayer game, followed by implementing a load balancer and if time
permitted build a toy UNIX shell. You can see the pattern here. My
goal was to learn more about distributed systems and operating
systems. I had started reading up on Erlang on the days leading up to
the first day of my batch.

However, more often than not, people come to RC with a different kind
of goal and end up doing something drastically different if not
completely different. The very first project that I started working on
was the UNIX shell, which turns out was the last preference on my
aforementioned list. I did think about the multiplayer game and the
load balancer, but I worked on none of them. I worked on a ray tracer
instead which was something I had never thought I'd work on at RC. The
ray tracer turned out to be very different from the traditional
application development that I was used to. In general, a buggy code
leads can make your application crash. However, in the ray tracer, a
bug means the image itself does not get rendered correctly. The buggy
image looked cool for sure, but I had no clue what was wrong with
it. This was especially harder, since I was not quite sure what the
expected image should look like and it felt like fishing in the dark
to some extent. This meant that I had to learn a different thought
process to debug the ray tracer.

Finally, I resumed learning Erlang at RC, and decided to implement
Raft, the consensus protocol. Learning Erlang turned out to be more
challenging than I had anticipated initially. The main reason was that
this was my first foray into functional programming. The other was
that Raft was completely unknown to me and I was trying to do two
unknowns at the same time. I had ignored the general advice of dealing
with only one unknown at a time. This lead to a few not so productive
weeks during the mid point of my batch (at least it felt so at the
time). I was not writing a lot of code and struggling to grasp
Erlang's ideology when it came to designing fault tolerant systems. In
retrospect, I should have worked on some basic Erlang exercises
and only then attempted to implement Raft once I found my feet in
Erlang's world. This was a hard learned lesson that will stick with me
for a long time. **Only one unknown at a time. Period.**

At RC, once a week interested people gather in a room for what is
called as a *feelings checkins*. Here people can talk about anything they
want without anyone offering a comment. This makes for a non
judgemental environment allowing recursers to feel free and vent out
anything that might be bothering them. When my Erlang wasn't going
anywhere I attended one of the feelings checkins and said that, if I
cannot complete my Raft implementation by the end of my batch, RC
would have been a failed experiment for me.

When my batch ended, I had not completed the implementation but I
attended the feelings checkins and issued an apology. RC is not a
failed experiment for me, even though my implementation is
incomplete. All the projects that I worked on, the UNIX shell, the ray
tracer and the Raft implementation are incomplete. But completion does
not define the success of my batch. It is rather defined by the
experience that I gained being around folks who accept you for who you
are. All the projects are a start. They have some momentum. I had zero
know how about each of the projects before I started working on
them. And RC helped me gain that momentum and now I am confident that
I can carry that on my own and keep working on them by myself over
time.

I was worried that I would spend all my time on Twitter or
Facebook. Instead I am happy that I spent even less time on these
websites during RC than what I was already doing. I think the impostor
syndrome can take a backseat for now. I feel confident that I have the
drive in me to learn new things on my own without a manager having to
set a deadline.

P.S. At RC, I regularly posted on Zulip in the #checkins stream about
my progress. I have collected it from Zulip and published it
[here](/blog/recurse-center-checkins/)

## What next?

My batch ended on August 10, 2017 and I have been doing tourist things
in New York since then and now I am flying back to my home in India.

Looking back, doing a batch of RC was the best decision that I could
have made. My present self thanks my past self. RC is not one of the
best experiences of my life, but the very best experience without a
sliver of doubt and I would love to come back and do another batch in
the future.

But for now, I am looking for a new job. I am open to relocating
anywhere in the world but am also considering the idea of a remote job
(I have previous remote work experience). If you read this far, you
would know about the kind of work that appeals to me and if you think
you have a similar position to fill, please get in touch over
[Twitter](https://twitter.com/@indradhanush92) (my DMs are open) or
via [email](mailto:indradhanush.gupta@gmail.com). You can check out my
resume [here](http://bit.ly/indradhanush_resume). I would love to talk
to you!

Also, if you are someone like me and you think you should do a batch
of RC, you should definitely [apply](https://www.recurse.com/apply)!

Never Graduate!

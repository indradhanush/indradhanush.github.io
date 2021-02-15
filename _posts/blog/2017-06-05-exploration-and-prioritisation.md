---
layout: post
title: Exploration and Prioritisation - Week two of RC
categories: blog
tags: ['recurse-center']
excerpt: 'Summary of the second week at the Recurse Center'
date: June 5, 2017
author: self
image: /images/exploration-and-prioritisation/cover.jpg

---

The second week of RC has rushed by and most of it has been a
blur. This week has been about finding and learning new things, not
all of them technical though.

## Emotional rollercoaster

This week picked up right from where the
[previous one](/blog/uncertainty-intimidation-and-the-stupid-one-in-the-room/)
left off - uncertainty. One of my
[blog posts](/blog/writing-a-unix-shell-part-1/) was trending on
Hacker News and it took me through an emotional roller coaster. I gave
a talk on this at RC on Thursday and published the transcript as a
[blog post](/blog/getting-noticed-on-the-internet-and-what-to-do-about-it/)
as well. Everyone was laughing through most of the talk which was
again something that I was not expecting. This was another first for
me, in being able to keep my audience entertained throughout the
talk. The main reason for which I think was that the talk duration was
five minutes only, as stipulated. One important lesson that I learned
from this entire exercise though, is that if you really want something
to happen, you should stop trying too hard, be natural, and go with
the flow. If it works out how you wanted it, well done! Or else,
there's always a next time.

## Prioritisation

I was also able to identify and prioritise my goals for the first half
of RC, and have set mental goals for my projects. Currently my main
focus is to work on the shell I've been writing. It can execute system
commands now, on which I will write a blog post soon. The next step is
to implement signal handling.

I have been reading the following books in order to accomplish this:
* The C Programming Language - Kernighan & Ritchie
* Advanced Programming in the UNIX Environment - Stevens & Rago
* Linux Systems Programming - Robert Love

## Python to C

Prior to this, I was programming mostly in Python (and a little bit of
Golang) and starting with C felt like suddenly being hit by a wall. I
spent quite some time reading and understanding C (and pointers
ofcourse) to be able to implement something that Python can do in a
single line - split a long string into individual words separated by
space. I had to take care of memory allocation (and reallocation when
my buffer runs out of memory) and parsing the string. This forced me
to understand the inner implementation of something that appears
trivial in a language like Python. Somebody at RC mentioned (I can't
recall who) that:

> C is a very bad high level language but a great assembly language.

[Veit Heller](https://github.com/hellerve) also mentioned that:

> The joy of writing C is in reinventing the wheel.

I've noticed when I keep these in mind while working with C, my
frustrations at having to reinvent the wheel are easier to keep at
bay. Also, I am starting to appreciate how C survived for thirty years
while almost every other piece of software fails at this. One reason
for this is keeping C very simple and clear at its core, even if it
means more trouble for the programmer.

## Getting stuck and seeking help

I'm also happy that I can now use `gdb` to debug my code, which is
something I always wanted to but never paid enough attention towards,
thanks to [Sabelo Mhlambi](https://github.com/sabzo) and
[Trevor Saunders](https://github.com/tbsaunde) who helped me with
this. I also used [Saul Pwanson's](https://github.com/saulpw/) help
with `valgrind` to fix a hard to trace bug.

I realized that it is always a nice idea to ask someone if you are
stuck at something and unable to make any progress at all. An extra
pair of eyes can do wonders!

## Pairing

I paired on the shell with
[Dominic Spadacene](https://github.com/domspad) where he was the
navigator and 
I was the driver and implemented the command parser while also
improving the internal APIs. We also learned why `cd` is not supported
as a system call but as a shell builtin instead. More on that in a
separate blog post. I also paired with
[Jaseem Abid](https://github.com/jaseemabid) to improve the 
code yet again. The pairing exercises turned out to be very fruitful
because I was able to improve my code very early on in the project itself.

I switched roles and became the navigator instead and paired with
[Saul Pwanson](https://github.com/saulpw/) on integrating with the
Github API for [visidata](https://github.com/saulpw/visidata). We also
ended up building a generic client as a side effect which can be
reused for integrating with other APIs.


## More math

I've had a long discussion with
[Hang Lu Su](https://github.com/homeowmorphism) and
[Tim Babb](https://github.com/trbabb) on geometry, shapes and
groups. It was an interesting discussion, although I was able to
retain only parts of it, since most of the discussion was higher level
math than I've done so far. However
[Tim Babb](https://github.com/trbabb) was able to explain a few
concepts very intuitively with real world examples. I always love it
when someone explains a topic with real world context, because it
makes understanding the subject easier and interesting at the same
time.

## Exploration

I've also decided to explore Haskell as my secondary project
here. We've formed a Haskell group where most people are new to the
language and are curious to learn it as well. The group has been
following [the Haskell Book](http://haskellbook.com/). However, I
found it a bit too verbose for my personal taste and I am following
the
[Learn You a Haskell for Great Good!](http://learnyouahaskell.com/)
instead. My reasoning for this is that:

1. Haskell is my side project at RC, and I would not want to give it a
   lot of time at the moment.
2. I read through the first three chapters of Learn You a Haskell, and
   found the book easy to understand while also move at a fast pace.
3. I am okay with having a superficial understanding of Haskell right now
   and will dig deeper when I start using it for a project.

I've explored some Lambda Calculus as part of this exercise, and
admittedly don't understand it too well at the moment. But I've
developed a _feel_ for it now and can relate to the patterns in
Haskell to some extent. So far my Haskell knowledge is about:

* Variables, strings, lists, list comprehensions and tuples
* Infix and Prefix functions
* Type declaration in functions
* Type annotations and type classes

## NYC

I was arriving at RC a little late in the first half of the week,
which I was gladly able to fix during the second half. I've also
managed to bring down my commute time to about 40 minutes from the
usual 50 minutes on the bike. This is probably me getting used to the
long ride added with the fact that I am familiar with the route and I
don't need to stop and check Google maps for directions.

I've taken [Vaibhav Sagar's](https://github.com/vaibhavsagar) advice
on leaving the laptop back at RC overnight. This has two advantages:

1. I have a lighter backpack to carry back on the bike
2. I do not spend time late at night unnecessarily fidgeting on the
 laptop
3. I have an incentive to show up at RC early

Friday is the only exception to this rule though.

I also visited the
[American Museum of Natural History](https://www.amnh.org/) which blew
my mind over. It is huge and visiting all the exhibits in a single day
is not feasible. I saw the space show at the planetarium there, which
was a beautiful experience, after which I spent most of my time in the
Space section and the Hall of Meteorites.

Here are some pictures from the museum:

<figure>
	<img src="{{ site.url }}/images/exploration-and-prioritisation/williamette.jpg" alt="williamette meteorite" />
	<figcaption>The Williamette Meteorite</figcaption>
</figure>

<figure>
	<img src="{{ site.url }}/images/exploration-and-prioritisation/ahnighito.jpg" alt="ahnighito" />
	<figcaption>Ahnighito - Largest meteorite on display in any
	museum; It weights 34 tons and needs special metallic columns for support</figcaption>
</figure>

<figure>
	<img src="{{ site.url }}/images/exploration-and-prioritisation/stibnite.jpg" alt="stibnite" />
	<figcaption>Largest specimen of Stibnite, a mineral in public display</figcaption>
</figure>

<figure>
	<img src="{{ site.url }}/images/exploration-and-prioritisation/blue_whale.jpg" alt="blue_whale" />
	<figcaption>The Blue Whale - the largest animal</figcaption>
</figure>

Looking forward to another fun and exhausting week of RC!

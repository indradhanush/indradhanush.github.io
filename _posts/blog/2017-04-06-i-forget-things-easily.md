---
layout: post
title: I forget things easily
categories: blog
tags: ['introspection', 'trello', 'productivity']
excerpt: "Remembering things doesn't come naturally to me. My thoughts
and attempts on fixing this. What worked and what did not. And a plea
for help."

date: April 6, 2017

author: self

---

Those who have know me personally are aware that I have a hard time
remembering things. This includes things I've worked on and things I am
supposed to do. Up until now I have been saying this to myself and
anyone who's noticed:

> I am not forgetting things. I let my brain clear out anything
> irrelevant. Also what's the point of remembering something when I
> could always look it up?

While I do allow myself to forget the unnecessary details of my day to
day life, I now realize that I forget the important things as well which
I shouldn't be missing out on easily.

To give you a sense of what I'm mean, here are some points that I can
recall (no pun intended):

* I forget things I've worked on in the last week
* I gave a [talk at PyCon](https://www.youtube.com/watch?v=kKDbiibuT7Y)
on working with datetime objects and made the same mistake myself that I
had spoken about, only to be reminded about the talk by my colleague.
* I forget that I worked on a specific component and others tell me you
worked on it.
      
Overall, the theme is that these are relevant details which I should not
be forgetting. A few times I've even incorrectly challenged others that
they are wrong.

# So why now?

You may be thinking as to why am I concerned about this now. Here's a
bit of a backstory (it can get a little technical):

Earlier today, I was updating
[my Emacs configuration](https://github.com/indradhanush/.emacs.d/)
which uses
[emacs-modular-configuration](https://github.com/targzeta/emacs-modular-configuration). This
is a package that merges all the individual `.el` files into a single
`config.el` file, which Emacs can then use to load on startup.

As a result, while you are editing your configuration it is easy to
mistakenly edit the `config.el` instead of your raw `.el` files, and
each time you use `emacs-modular-configuration` to generate the config
file, your changes will get overwritten, because you never made the
change in the raw `.el` file.

While using it for the first time last year, I found this to be an
issue and I
[sent a PR](https://github.com/targzeta/emacs-modular-configuration/pull/2)
that forces the `config.el` to be opened in `read-only` mode. This would
prevent me from making accidental writes to `config.el`.

While I was tweaking my Emacs configuration, I accidentally opened the
`config.el` file itself, wondered why it wouldn't let me write to it,
overrode the read-only mode, made edits and ran the command to
regenerate the file. I kept wondering on how my changes were getting
undone. It took me a few iterations to realize my mistake. Ideally, I
shouldn't have made this mistake at all, when it was me who had
enforced this change in the first place.

So I clearly have a problem here that needs to be fixed but am not sure
how to. Accepting it openly is hopefully the first step towards
this. Thus this blog post. 
  
# How am I fixing this?

## Work
At work I have used
[Trello](https://trello.com/indradhanushgupta/recommend) and applied a mixed approach of the popular
[Kanban](https://en.wikipedia.org/wiki/Kanban_board) technique with
moderate success. I have 3 lists namely:

1. Up Next
2. Currently Working On
3. Done and Dusted

Each Trello card moves from `Up Next -> Currently Working On -> Done and
Dusted`.

The variation here is that I have added more lists like:

1. Infra
2. Product
3. Operations
4. Ad-hoc

And each list is topic specific. Whenever something new comes up that
needs to be taken care of, it goes to the corresponding list. And when
the time is right, it moves to the `Up Next` list and is thereby part of
the pipeline. This has helped me in the following ways:

* I am able to offload things I need to work on from my memory to
  Trello.
* When I start my work day, I have a good mental model of things I am
  working on and it helps me to plan my day accordingly.
* When its time for the weekly engineering meeting, I do not have to
  scratch my head anymore when it is my turn to say what I worked on in
  the previous week.
* I add the smallest of tasks on the board. So even if I forget, the
  board doesn't.
  
Naturally now that I have a board, there is a tendency for things to get
piled up and get ignored for a while. My personal benchmark to deal with
this is that I do not let any list become longer than the visible
desktop area. If the list is touching close to the bottom edge of the
display it is an indicator that the section needs my attention soon. 
The only exception to this rule is the `Done and Dusted` list (the
longer the better in this case).

<div>
  <img src="{{ site.url }}/images/trello-kanban.png" height="1000" width="800"/>
</div>

However, this has not been perfect. Things like Github issues and pull
requests get created and assigned on Github itself. For me to be able to
track them, I have to add them manually on my board as well. This gets a
bit tedious at times, especially when I'm really loaded with things on
my plate.

Occasionally I forget to move the cards around, in effect making the
board not very reliable until I get it upto speed once again.

This approach has worked amazingly well for planning and keeping a track of
ongoing things. But I've still not been able to solve the problem of
being able to remember things from the past very well.

## Personal

It was easier to manage my work life with the help of Trello because the
requirements here were very specific and restricted when compared to my
personal needs. To be fair, I did try to use Trello for this as well but
it has not worked out very well, for the following reasons:

1. It is much harder to map my personal life's TODO's on a board. Both
   over generalization and compartmentalization will kill this approach.
2. At work I have access to my laptop all the time and it is very easy
   to note down things as they come. This is does not stand true for my
   personal life as a result I fail to note important things down on the
   trello board when I do not have access to my laptop.
   

# That's all folks!

This has been my only problem which I have been unable to tackle very
well in the recent past and I fear is becoming my
[Achilles Heel](https://en.wikipedia.org/wiki/Achilles%27_heel). I am
exploring more ideas and approaches to solve this problem and hopefully
will be able to post an update in the future. 

If you've made it this far, please consider leaving a comment with your
thoughts or suggestions on what could I do differently.

I could do with some help here. Hello, World!

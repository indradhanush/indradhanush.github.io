---
layout: post
title: 'TIL: magit-status-here'
categories: blog
tags: ['emacs', 'magit', 'productivity', 'programming', 'til']
excerpt: "TIL that magit-status-here will take the focus to the most recent changes on the current buffer"
date:  10 October, 2024
author: self
---

TIL that `magit-status-here` will open the magit-status buffer with the focus on
the diff of the current file. And more specifically, the diff in the latest
iteration of changes. For example, normally I run `magit-status` through a
keybdinging. Which will open the `magit-status` buffer with the project. When I
run `magit-status` on this blog's repository while writing this post, I get
this:

<figure>
	<img src="{{ site.url }}/images/til-magit-status-here/1.png" alt="" />
</figure>

But when I run `magit-status-here`, I get this:

<figure>
	<img src="{{ site.url }}/images/til-magit-status-here/2.png" alt="" />
</figure>


This utiltity of this may not be evident in a contrived example like this.
However this is particularly useful for larger projects where I'm editing
multiple files and want to quickly see the diff of my changes that I was just
working on.

For example, after writing the above paragraph, I committed my changes, wrote
this line that you're reading and ran `magit-status-here` again. This is what I
get:

<figure>
	<img src="{{ site.url }}/images/til-magit-status-here/3.png" alt="" />
</figure>


I've been using emacs for almost 13 years and magit for a good chunk of that
time and I just found out about it this morning! This is a great utility
function and I will be binding it be my default right away.

**PS:** I made some edits and fixes to the post after I took the screenshots.

**PPS:** I use Emacs in dark mode. But light mode looks better on the blog.

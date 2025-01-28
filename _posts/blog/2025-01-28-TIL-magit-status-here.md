---
layout: post
title: 'TIL: magit-status-here'
categories: blog
tags: ['emacs', 'magit', 'productivity', 'programming', 'til']
excerpt: "TIL that magit-status-here for the current buffer"
date:  10 October, 2024
author: self
---

TIL that `magit-status-here` will open the magit-status buffer with the focus on
the diff of the current file. For example, normally I run `magit-status` through
a keybdinging. Which will open the `magit-status` buffer with the project. When
I do it for my blog while writing this post, I get this:

<insert-screenshot>

But when I run `magit-status-here`, I get this:

<insert-screenshot>

This may not be evident in a contrived example like this. However this is
particularly useful for larger projects where I'm editing multiple files and
want to quickly see the diff of my changes that I was just working on.

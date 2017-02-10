---
layout: post
title: Accepted Into Google Summer of Code 2014
categories: blog
tags: ['gsoc','python','zeromq']
excerpt: 'My first reactions after being selected into Google Summer of Code, 2014. Also a very brief note about my project for the summer.'
date: April 23, 2014
author: self
---

Finally. After trying twice in succession, I made it into [Google Summer of Code 2014](http://www.google-melange.com/gsoc/homepage/google/gsoc2014). Last year I had applied to [Twisted](https://twistedmatrix.com/) which did not get accepted. So learning from my mistakes last year, I applied again this year, but with [LEAP Encryption Access Project](http://leap.se/). And to my delight, when the [results](http://www.google-melange.com/gsoc/projects/list/google/gsoc2014) were announced on April 21, 2014 at 19:00 UTC, my name was in [there](http://www.google-melange.com/gsoc/org2/google/gsoc2014/leap).

Over the past 3 days, I have been congratulated more than I can remember. Thanks to everyone. But at the same time, those who were not aware of what GSoC is, have asked me about it. They have also asked me about my project. So I decided to write a blog post about it.

**Google Summer of Code** is a program by Google, that has the motto - ***"flip bits, not burgers"*** during the summer vacation. The program lets students work on Open Source projects, while getting a healthy stipend (read very healthy for Indian students). The only condition is you must be a student in an accredited insitute. And no. Being a fellow of Computer Science discipline is **NOT** a necessity. Thats it about the program in a few words. You can read more about it [here](http://www.google-melange.com/gsoc/document/show/gsoc_program/google/gsoc2014/about_page) and [here](http://www.google-melange.com/gsoc/document/show/gsoc_program/google/gsoc2014/help_page). 

Now, about my project. I am going to write an "Alternate transport for U1DB sync protocol". [U1DB](https://one.ubuntu.com/developer/data/u1db/index) is a database API that makes it easy to store synchronized databases. That is when the same data should be synced in multiple devices, U1DB comes in really handy. The only problem is that it uses HTTP for communicating between the devices. Now HTTP as we know, is the backbone of the internet, but in some cases, like this one it just isn't ideal. Lets just say its not the best option. 

So, my project over the summer is mainly to provide with an alternate transport to the current HTTP implementation. How do I aim to do it? 

A Message Transport is what I need. And having [worked](http://github.com/indradhanush/file-collection-server) with [ZeroMQ](http://zeromq.org/) a while ago, I knew that ZeroMQ was the perfect alternative. With ZeroMQ I will design a Client-Server architecture thats going to form the core of the new transport that I will write. This is just my project in a nutshell. There's more to it than just this. But then, that's going to end up in another blog post in the coming days.

You can read my proposal [here](http://bit.ly/gsocleap14). 

Lastly, something I've wanted to say for more than a year. **Yes! I am a GSOCer!**

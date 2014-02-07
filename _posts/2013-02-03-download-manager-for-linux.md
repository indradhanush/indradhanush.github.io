---
layout: post
title: Download Manager for Linux
date: February 3, 2013
author: Indradhanush Gupta
---

My college Wi-Fi signal fluctuates frequently and I having been using Linux Mint 13. The problem is that I get logged out automatically. In the absence of the traditional IDM that I had been using while on Windows, downloading large files became difficult. Often the download would stop at close to 90 %. Argh! Annoyed I used to be with the fluctuating signals. But this was something not in my hand. So I decided to do something that was in my hand. I checked out for download managers and came to know that Chrome for Linux didn't support download managers. And after scouring through the net a little came the savior!

    wget

It's a command line utility and the best I've seen so far. To install it you should issue the following command :

    sudo apt-get install wget

Enter Your Password. Wait for the installation to finish.

All you need to do is to obtain the download link and then use this in a terminal to start the download :

    wget -c http://manet.eurecom.fr/das.pdf

Bingo! wget downloads the file for you. Works like a charm! More options can be specified that can be viewed by typing :

    wget -h

One last thing. Although I've not tried it yet. I saw that wget is also available for Windows follow the following link : [http://www.gnu.org/software/wget/](http://www.gnu.org/software/wget/)

Who needs a GUI when command line works best!


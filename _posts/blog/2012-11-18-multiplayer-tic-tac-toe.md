---
layout: post
title: Multiplayer Tic Tac Toe
categories: blog
tags: ['games','network-programming']
excerpt: 'A multiplayer tic tac toe game that can be played over the internet.'
date: November 18, 2012
author: self
---

This one right here is my first post on this blog. This is about my first mini-project which I completed on my own over the last few days. I've developed an Online Tic-Tac-Toe game that can be played by two players sitting at different computers but within the same network.

I implemented the basics of socket programming to employ the reliable Client-Server model. Connecting the two players across the internet is simple. One of the players must decide to play as the server and create a game at the server itself such that the second player may connect to the server's IP address. Yes, the client must be aware of the server's IP address.

I wrote this in C++. Currently the source codes have been compiled for Linux systems. Here's what the server(Player 1) needs to do to set up a game :

    ./server.out

(Yes! That's it!) **server.out** is the compiled output file for creating the server.                                                                              

And connecting to the server is also pretty easy. The client(Player 2) should type in -

    ./client.out 192.0.2.80

**client.out** is the compiled output file for connecting to the server and **192.0.2.80** is the IP address of the server(say). Given a server has already been set up, the client should be able to connect comfortably to the server.

I have uploaded this project at github. And here is the link to the repo :
[https://github.com/indradhanush/Multiplayer-tic-tac-toe.git](https://github.com/indradhanush/Multiplayer-tic-tac-toe.git)

Their are loads of stuff that still needs to be done. I shall list them in decreasing order of my preference:

* Implementing the more modern and better approach of using **getaddrinfo()** to fill out the structures. I've hard coded them manually.
* Extending support to **IPv6** address family.
* Incorporating an **in-game chat** feature that will allow the players to freely interact with each other.
* Compiling the code for **Windows** users.
* Achieving **cross platform** portability.


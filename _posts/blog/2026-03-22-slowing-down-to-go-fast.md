---
layout: post
title: 'Slowing down to go fast'
categories: blog
tags: ['human-behaviour', 'ai', 'debugging', 'learning']
excerpt: "How a debugging session with a coding agent reminded me of the need to learn things with intention"
date: 22 March, 2026
author: self
---

Last week I was troubleshooting some odd connection reset issues at work, which turned out to be (no, not DNS) ARP contention because of a kube-proxy misconfig. While I won't be going into details about that in this post (I may write a separate post about it), this post is instead more "meta" so to ~speak~ write.

Unsurprisingly, I was using a coding agent very heavily to debug this issue. And at one point, it was clear and obvious to me that without realtime packet capture on the worker nodes I wouldn't be getting any more detailed insight than I already had. Now, while I've meant to do this sort of a learning exercise for a really long time, it ended up in the "I'll do this one day" bucket and stayed there, until recently when I needed it to solve a real problem at work.

As I repeatedly fine tuned my packet capture filters, downloading and analysing them between each iteration, at one point the agent took more initiative. It fired off a series of `tcpdump` and `tshark` commands in quick succession and came back with a reasonable sounding explanation that was beginning to indicate what the issue might be. While my intuition of the problem was beginning to align with what the agent was proposing, in all honesty I had zero clue about the gazillion args and the baroque `awk` syntax it used in its analysis.

This was my inflection point. 

I really wanted to rely on my intuition and continue "investigating" (in quotes because it would be the agent doing most of it at this point with small prods from me) the issue. I was about 2 days into this affair and I couldn't wait to wrap this up! But I had to take a step back. I didn't understand what the agent did in the last few steps. And proceeding further would be akin to continuing to climb the Everest[1] in the middle of a snowstorm with no compass or GPS. Consequently, I switched from investigating to learning. I asked the agent to teach me the commands that led to the next step and why it took those decisions. 

What followed in the next couple of hours (or more, I don't quite remember) was me going through these commands, typing them out (yes, typing, not copy-paste) in another terminal. The same commands that the agent had already run and had a refined result waiting for me. If you were sitting next to me, you'd think I had just been rescued from a deserted island and hadn't heard about the AI ~subversion~ revolution at all!

Clearly, one could argue why I did not press forward with the agent's analysis instead. But I really wanted to be able to explain the root cause to another colleague myself. I laboured through the commands, adding and removing a few of them myself using the agent as my guide. And eventually arrived at the same conclusion. Only that the agent's analysis actually made complete sense now. Even better, I knew the shortest path to finding conclusive evidence.

This in itself isn't a novel insight – both Einstein and Feynman (along with countless other people)[2] are known to have said something similar to "If you can't explain it simply, you don't understand it well enough". And it isn't the first or the last time I've had this realisation working with AI. But there's something about a perspective that just can't be "passed on" by reading or listening to someone else. Instead, it has to be felt deep within yourself. By you and only you. 

This was such a moment for me. It reinforced in myself the need to pay closer attention and remember to switch between leading and following even when I'm letting the AI do a lot of the work. Quite like what we'd do if we were pairing with another human (Alas, coding agents are taking away one of the few forms of social interaction for us nerds, but that's a rant for another post).

I can't explain this feeling better even if I were to write another 500 words. But I hope this inspires you to find your own core moment where you can reinforce the need to teach things to yourself _slowly_, and not offload all of your cognition to a machine. 


### Footnotes

- \[1\]: [Man Lost in the Himalayas Tells Horrifying Story](https://www.youtube.com/watch?v=pY-df1FnAWA)
- \[2\]: [Did Einstein say "if you can't explain it simply you don't understand it well enough"?](https://skeptics.stackexchange.com/questions/8742/did-einstein-say-if-you-cant-explain-it-simply-you-dont-understand-it-well-en)
- \[3\]: I didn't use AI to write this post. I use "–" in my own writing frequently and I love it.  

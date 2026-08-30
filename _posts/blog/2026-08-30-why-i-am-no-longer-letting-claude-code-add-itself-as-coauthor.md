---
layout: post
title: "Why I am no longer letting Claude Code add itself as Co-author in my commits"
categories: blog
tags: ['programming', 'ai', 'human-behaviour']
excerpt: "My thoughts on why I do not want claude code as co-author to my git commits"
date: 30 August, 2026
author: self
---

For the last year or maybe more, I've been explicit about adding Claude Code as
co-author for each commit (and also wanted others to do the same) that I used it
for. And my reasoning for it was simple: as a reviewer or anyone else reading
the code, they should know that I used an LLM to build it. 

However, now it's obvious and even expected that using LLMs is the way forward
and you _have_ to use it at work unless you want to go out the door. Side
projects is completely upto you and we have had multiple instances of folks
publicly rejecting its use off-late.

**A carpenter may sign their work. But they don't add the name of the saw they
used to cut wood, do they? Adding the LLM as co-author feels similar.**

And while I'm still very much using LLMs for both work and side-projects I am
not going to add them as co-authors to my commits. My reasoning is quite simple:
if the work is under my name, I assume full responsibility for it. A few years
ago I'd never have added Google or StackOverflow as co-authors. But I would have
added a link to post that helped and I'll continue to do so now.

In my view, adding an LLM as co-author gives you a way for you to shirk
responsibility for mistakes – even if a little bit. You can say, oops sorry this
happened because it did its thing and it was not careful. And that is exactly
the behaviour I want to guard against. If a piece of work is under my name, I
own it. Fully.

To be clear, there have always been bugs. Both before and after LLMs. So our
attitude towards them shouldn't change just because the tool under the hood has
changed. We still need to remain responsible for verifying the work before we
ship it.

However, as with everything there's scope for nuance here as well. It may be
okay and probably better to use LLMs as co-authors or even as the primary
authors for a few of the scenarios that come to mind:

- You're evaluating different models for similar tasks and want to easily
  distinguish between them for comparison
- An LLM is creating the PR and _you_ are the reviewer

What about attributions and disclaimers for AI generated work? If you're
concerned about being transparent to anyone seeing your work, either create an
AI specific account that commits with your name or add a big disclaimer to your
project's readme that this is AI slop and there be dragons. The same way you'd
have done for something of a hack that you haven't fully tested yourself. But
for anything serious, please take full ownership of it.

### Appendix

I woke up this morning and saw [this
post](https://news.ycombinator.com/item?id=49498201) on HackerNews and it
reminded of my own on Bluesky from earlier this week. And I felt strongly that I
needed to get this piece out right away.

<blockquote class="bluesky-embed" data-bluesky-uri="at://did:plc:y5af2lfbc43ssuyn5mozyixz/app.bsky.feed.post/3mts6nqtlg22d" data-bluesky-cid="bafyreib5lpgpihfl65zoykhojwchbs6kgfuzrcylch5drrz7redlwoax5e" data-bluesky-embed-color-mode="light"><p lang="en">Early on I believed we should be adding LLMs as co-authors to commits we make. 

My stance on this has now flipped. I think LLMs as co-authors makes us shirk responsibility for our changes. You wouldn’t have added Google or Stackoverflow as co-author previously. So you shouldn’t do it now.</p>&mdash; Indradhanush Gupta (<a href="https://bsky.app/profile/did:plc:y5af2lfbc43ssuyn5mozyixz?ref_src=embed">@igupta.in</a>) <a href="https://bsky.app/profile/did:plc:y5af2lfbc43ssuyn5mozyixz/post/3mts6nqtlg22d?ref_src=embed">August 23, 2026 at 9:46 PM</a></blockquote><script async src="https://embed.bsky.app/static/embed.js" charset="utf-8"></script>

---
layout: post
title: 'What I have learned being a programmer'
categories: blog
tags: ['programming', 'human-behaviour']
excerpt: 'Lessons learned as a programmer over the last five years'
date:  10 November, 2019
author: self
---

I joined [Loodse](https://loodse.com) last month and I wanted to reflect upon the journey of my programming career so far. And give some thought to what I'd like to improve or change going forward.

## Be a human first, programmer second. 🤓 > 🤖

I feel this is the most important lesson that I have learned and fittingly this should be the first thing on this post. If there's one thing that I would like the readers to take away from this post it's this. And I cannot emphasize this enough.

**Developing empathy for your coworkers is very important**. If someone hasn't been able to accomplish a great deal over the week, instead of following up for an update on the status of the project check with them about their well being. See if there's something in their personal life bothering them and if there's anything you can do to help them. And if it is indeed the task at hand that is slowing them down, offer to pair with them on it.

**Do not assume a person's gender**, especially if you only happen to know them by a "username" on the internet. Most of us are susceptible to using `he` when referring to a user on the internet because of our biases. Use `they/them` first. If you have a Twitter profile put your preferred pronoun on it. When referring to a group of people, prefer not to use `guys`. Use `folks` or `people`. I do not want to argue about why `guys` has been always used as a gender neutral term and thus should continue to be acceptable as such. Using `folks` doesn't hurt anyone.

## Code reviews 🖥

Talking about code reviews, how does one find the right balance between striving for clean and perfect code vs shipping stuff? This is a question that has always bothered me. And while this continues to be an area of improvement for me personally, there are some pointers worth sharing that has helped me along the way.

I try not to block a merge / pull request just because it doesn't match _my_ idea of what perfect code looks like. If it's an improvement on the existing state, I try to approve it. That is unless I spot any bugs. This is especially true for new contributors. Getting your first few PRs merged quickly give you the feeling of getting things done and helps you settle down in a new project / team. And for seasoned contributors it keeps things moving. If there is something that can be improved on the PR but isn't really a deal breaker, I leave a note about the possibility and suggest to do it in a follow up PR. This helps give them responsibility and own that part of the codebase. In my experience the longer a PR lingers and goes back and forth between review and changes, the lesser its chances of getting merged. Sometimes they never get merged. ¯\_(ツ)_/¯

Use emojis in code reviews. The more the better. 🎉 👍.

**Code reviews shouldn't only be about what's wrong.** They should also highlight the good parts. If you spotted a clever design pattern or good documentation or tests, leave a comment. Thank the author. Appreciate them. 🙌

If a PR takes more than one cycle of review, offer to pair on that PR and address the concerns that helps to get it merged. Code reviews needn't always be done passively. They can be done while the changes are being worked on in real time. Admittedly, this is something that I have not been able to do as much as I would have wanted to and would like to fix that in my workflow going forward.

## Programming styles 💻

Don't stick to a specific programming style religiously. Be flexible. For example, I have always preferred spaces over tabs but I recently learned that [tabs are better for accessibility for programmers with visual impairment](https://www.reddit.com/r/javascript/comments/c8drjo/nobody_talks_about_the_real_reason_to_use_tabs/). I intend to move to tabs instead of spaces for projects that allow it.

 ⏎ Never underestimate the power of a newline. Use a newline to separate code blocks with succeeding or preceding blocks of code. For example, look at the following function:

```go
func validateDateTime(input string) (*time.Time, error) {
	val, err := time.Parse("02/Jan/2006:15:04:05 -0700", input)
	if err != nil {
		return nil, fmt.Errorf("Invalid DateTime: %q; error: %v", input, err)
	}
	return &val, nil
}
```

And now look at the same function again:

```go
func validateDateTime(input string) (*time.Time, error) {
	val, err := time.Parse("02/Jan/2006:15:04:05 -0700", input)
	if err != nil {
		return nil, fmt.Errorf("Invalid DateTime: %q; error: %v", input, err)
	}

	return &val, nil
}
```

Does the newline before the return statement make it easier to scan the function at first glance? Now try to imagine a function with 50 lines or so. **Remember that code is more often read than written.** 📖 👓.

If a project uses a specific style, stick to it when contributing to it and do not try to enforce your own style on it.

## Social rules 👮 📢

I continue to look back upon my time at the Recurse Center from more than two years ago as the most influential part of my programming career. Not only did it make me a better programmer, but also a better human being. The Recurse Center is governed by [four social rules](https://www.recurse.com/manual##sub-sec-social-rules) that I feel should be a part of every community. Both in and outside of tech. The page linked does a great job of explaining them so I will not go into detail here. I have also written [quite a few posts](/tags/#recurse-center) on my work and experience there.

When explaining a concept, I try to not use the  words basically and actually. To me, needing to use these words indicates that I am unable to express my thoughts in simpler words (and probably don't understand the concept well enough myself). In addition to this, using these words reads in my head as "what I'm trying to say is simple enough, so you should have already understood it", even though that might not have been the intention.

## Communication 📞

Almost every article that I've read on the topic of "what makes a good programmer/software engineer/\<insert fancy tech job title\>", seemed to have mentioned about the importance of communication. However it wasn't always obvious what one could do to improve upon that. Here's what I feel has helped me.

**When communicating over text, use emojis as much as possible.** The more the better. For example, use the 📢 emoji for an announcement. I don't always feel like I need to use `@here` or `@channel` to convey a message but still feel it is important for my team mates to know. I just don't feel like I want to intrude their thoughts with a notification right away. Using an emoji helps draw attention to it from the wall of text that might have already accumulated on a channel. For a question, I use ❓.

Use 🙂 for ending statements that others may not agree with and 🤔 for something you do not understand. Text is not able to convey emotions. Sometimes words maybe read in a different tone than the one on your mind when they were originally written. An emoji is worth a thousand words. 😉

I try to not use animated GIFs as emojis. Although they can be fun in the right context, I find them distracting for the most part. Something moving in the corner of my vision keeps vying for my attention.

**Communication is more important than your programming skills.** If I have a hard time understanding your question / bug report I am more likely to skip it or file it away as `TODO` for later. Spoiler alert: That is a place where no issue gets looked at again. As there is always new work on the table. 😅

Make your sentences shorter and use paragraphs to separate contexts. Use formatting when available. For example, use backticks for code / technical buzz words. Bold for highlighting important stuff.

If English is not your native language, spend some time on learning comprehension skills in English as that is the most commonly used language for programming. It is easier when others can interpret your thoughts based on your written words without having to read it a few times to understand them. 💭

## Feedback ⤴

Getting timely feedback is important for yourself. But it is also insanely hard. The sooner you get feedback the better. Ask what your colleagues felt about that last feature you worked on. Was there anything that you could have done differently in their view? I've elaborated more on this in the past [here](/blog/how-to-ask-for-feedback/). **When asking for feedback, I try to mention explicitly to not worry about sharing critical feedback and me feeling offended.** It works most of the times. And the critical feedback has been very helpful to me personally.

## Personal productivity 🚀

**Learn to touch type**. I often find myself getting up from my desk and going to another room to get something. In the meantime I've forgotten why I got up from my desk in the first place. Trying to find where that character is on the keyboard interrupts my thought process. And I am better off with my keyboard not interrupting me as well. Additionally, if I'm using the keyboard for eight hours a day, five days a week I would rather be able to use all my ten fingers than just four or five.

It can be hard to quit your old typing habit cold turkey, especially if you already have a day job. One approach that might work is correcting one or two keys at a time. It would still be a struggle but at least your work won't come to a standstill. Start with the home row (`a,s,d,f,g` and `h,j,k,l,;` on QWERTY layouts) and try to get the fingers right for these keys. This is going to be your frame of reference and will help to get the other keys right sooner. Do a few simple typing exercises with those keys when you're waiting for your code to compile (or your cluster to provision rather 😝). And do not stress if you don't get most of them with the right fingers initially. Keep adding a couple of keys every few days and eventually you will have learned to touch type. Also don't worry about the number row initially. Get to it once you feel you have a good command over the alphabets. I used this approach while I was at my first internship back in 2013.

You don't need to have typing speeds of a live note taker. 40-50 wpm is a good point for most programming tasks while 90-110 wpm is awesome. You will get there eventually. If you've gone down this path, try not to quit and go back to your older way of typing. That will only slow you down. If you're a student and not already touch typing, I highly recommend taking time out to learn this skill.

**Learn the keyboard shortcuts of the tools you use.** For example, your editor, browser or terminal. Each time you need to take your hand off the keyboard and look for the mouse to do something, it slows you down. I've found that [vimium](https://addons.mozilla.org/en-US/firefox/addon/vimium-ff/) has helped me to replace most mouse actions on the browser with keyboard shortcuts.

📧 I used to keep my email always open as a pinned tab and had the sync turned on on my phone. This used to make me keep checking for new email and get interrupted whenever there was a new one. I've now turned the sync off on my phone and open email on my browser only when I need it or at the start and end of my day.

Don't feel shy about going offline / turning on DND from your company's chat app to focus on work. Try to schedule no meeting days at work and schedule as many of your meetings back to back as possible.

## Red flags  🔴 ⚠

While being productive is important, it is also important to look out for signs that affect productivity. It is very important to look after my own interests because I am the only person responsible for my career and my life. Not my manager or my colleagues. On that note, here are a few red flags that I keep a lookout for.

**Time spent on Twitter / Facebook / Reddit is inversely proportional to sense of fulfillment at my day job.** That is, the more I've felt detached from my work, the more I've found myself aimlessly scrolling down my Twitter timeline. In hindsight, both the times in my career when I've felt I needed to change my job, my usage of social media has increased significantly.

If you find yourself with a lack of ideas to share as blog posts or talks at meetups, there's a chance that this may mean that the technical tasks you have been working on are not helping you improve as a programmer. They're not making you think and you're working on things that are easy and require less thought. Please note that this does not imply that you must publish blog posts or present technical talks at meetups or conferences. But one should just feel like that they have an idea out of which it might be possible to write a blog post or present a talk with further research.

Try to change your work setting from time to time, especially if you're working remotely. While I prefer to work from my home office on most days, I feel spending too much time in there has a negative effect on me. Stepping out to occasionally work from a cafe helps my productivity. Also this is more fitting on a blog post on remote work, so I will expand on this more if I write one in the future.

**To me writing code is very important.** I do not envision myself in a role where it isn't a part of my job description. When not writing much code for weeks on end, I tend to be cranky and less motivated. And at times like these, even the smallest of bash scripts to automate a tedious task makes me feel good again. For example during one such phase, I wrote a tiny bash script that automated the cleanup of some directories on a bunch of servers based on some filters. It took me under an hour or even less to get it working, but I remember feeling great the rest of the day and the day after. I'm a programmer after all. This does not imply that all I want to do at my job is write code, but I prefer it to be 50-60% of my responsibilities.

**The best environment for me to grow is where I can be the mentor and the mentee simultaneously.** For the same or different people. That is the ideal scenario, but if I am in a room where I don't get to fulfill either of the roles, that is not a place I want to be. There's a beautiful quote that I've come to admire:

> In learning you will teach, and in teaching you will learn.
>
> --- Phil Collins

**Go read** [The Psychopath Code](https://amzn.to/2PZZ4xk). Reading it helped me a lot in being able to look out for myself and spotting early warning signs. The book helped me to spot patterns where someone might intend to or already be using me for their personal gains. Be it a job interview or otherwise. If something feels fishy or unusual to you, talk about it to someone you trust. And then trust your instincts.

## Personal improvement ⏫

I just started a new job and want to create and maintain a [brag document](https://jvns.ca/blog/brag-documents/) to track my progress at work. I do not know if my new colleagues maintain one already, but I intend to find out and encourage others to start one if they haven't already.

So far I've had good exposure to a wide variety of tech stacks, from backend to infrastructure. But I would like to go deeper into one or two subject areas. The ones that immediately come to mind are `TLS` and `iptables`. My current project at work has helped me understand TLS better than I did a few weeks back and I hope I get an opportunity to dig deeper into computer networking.

## Conclusion 🏁

Take everything you see on the internet with a grain of salt. Including this blog post. 😉

There is always another framework / programming language / tool / algorithm to understand. It is a never ending process. Try not to get stressed about the things you're missing out on and focus on learning one thing at a time. As long as you're improving, you are on the right track. Everyone has their own pace. And that's the way it should be.

It has been a good journey over the last five years so far and I am grateful for the opportunities I have had and the people I met along the way. I look forward to the next five.

Is there anything else that comes to your mind? Let me know in the comments below.

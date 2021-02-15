---
layout: post
title: 'No dunst notifications when running picom - a debugging story'
categories: blog
tags: ['linux', 'picom', 'i3', 'dunst', 'debugging']
excerpt: 'How I fixed the problem of no system notifications when I ran picom'
date:  16 February, 2021
author: self
---

🚀 I started using [picom](https://wiki.archlinux.org/index.php/Picom), a
compositor a few days ago as I wanted my inactive windows to be transparent.
This goes a long way into identifying the active window when you're working with
multiple split windows on the same workspace. This has not been a problem for me
previously as I was running [i3wm](https://i3wm.org/) as my window manager and
[i3status-rust](https://github.com/greshake/i3status-rust/) for my status
bar. That meant that each window had a title bar. But I moved to
[i3-gaps](https://github.com/Airblader/i3/) and
[polybar](https://github.com/polybar/polybar/) to make my desktop prettier. And
with `i3-gaps` you need to disable the title bar that `i3` adds on each
window. Thus `picom` as a visual indicator to quickly spot the active window
among a bunch of small windows within a workspace felt like a good
solution. Also it makes your windows prettier! 🤩

⚠️ **Heads up:** If you decide to go down this route, it **will** consume a lot
of your time. A lot more than you would have originally planned. You have been
warned.

🐛 Setting `picom` up was very straightforward, but I ran into an issue very soon:
system notifications stopped showing up completely. And the moment I killed the
`picom` process, all the notifications collected by the notification daemon up to
that point would pop right on screen. This had an unintended effect of becoming
a DND mode. 😛

🔔 The notification daemon I use is
[dunst](https://wiki.archlinux.org/index.php/Dunst) and it has an easy way of
turning on / off notifications on demand. So I didn't necessarily need this side
effect from running `picom`. It definitely came across to me as a bug and not a
feature. Jokes apart. This bugged me for the last five days. I searched the web
but was unable to find anything related to this.

⚙️ In `picom`, the user can set different _opacity_ levels (opposite of
transparency) for different windows. So an opacity level of 0.9 makes a window
only slightly transparent, while an opacity level of 0.1 would make it almost
transparent and barely visible.

🤔 I tried configuring this for dunst windows but to no effect. Finally I tried
to install and run another compositor,
[xcompmgr](https://wiki.archlinux.org/index.php/Xcompmgr) to see if I was able
to reproduce the issue. And unsurprisingly I had the same problem with
`xcompmgr` as well. This helped me with my direction of debugging the issue
immediately. I started feeling that the issue had to be coming out of `dunst`
itself and not `picom`. So I looked up my `dunstrc` (the config file for
`dunst`) and started reading through it. And soon enough I found this setting
there:

```
transparency = 100
```

👀 At first glance I thought it was the right setting. Remember in `picom`
above, a higher number means more opaque. But then I read the `man` pages for
`dunst` where it was clear that a higher number means more transparency (quite
expected by the word itself). I've been using `dunst` for a few years already so
there is a good chance I made that edit at some point as the default value for
this setting is `0`. That is, this was a bug of my own making (like most bugs
anyway!).

So I immediately updated my `dunstrc` file:

```
transparency = 0
```

🎉 Restarted `dunst` and voila! The notifications started showing up when
`picom` was running. And that too without any additional configurations on
`picom`! I can now go back to using DND in `dunst` the way the authors intended. 😅

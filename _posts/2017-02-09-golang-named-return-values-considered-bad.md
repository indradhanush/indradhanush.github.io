---
layout: post
title: Golang named return values considered bad
date: February 9, 2017
author: Indradhanush Gupta
---

I've recently started working on Golang and we use it a little at work. I was writing some custom management scripts when I came across the idea of using named return values in my code.

```golang

func add(x int, y int) (sum int) {
    return x + y
}
```

---
layout: post
title: 'TIL: bash builtin RANDOM'
categories: blog
tags: ['bash', 'cli', 'programming', 'til']
excerpt: "TIL that bash has a builtin RANDOM for generating pseudo random number integers"
date:  17 December, 2025
author: self
---

TIL that bash has a builtin `RANDOM` that can return a random integer between 0 and 32767. This means you can easily simulate printing a random number per second with something like:

```sh
$ while true;  do echo $((RANDOM % 10)); sleep 1; done
```

This is pretty cool because I've frequently used python instead for things like these, which is easy in itself but this is way simpler! 

While reading about this from `man bash`, I also came across `SRANDOM` and turns out that while `RANDOM` is limited to 16 bit ints only and can be seeded, `SRANDOM` can generate 32 bit ints and cannot be seeded. 
This is also very easy to verify. For example:

```
RANDOM=42
for i in 1 2 3; do echo $RANDOM; done
17772
26794
1435
```

This will give you the same output each time you run it after setting `RANDOM=42` for example. But with `SRANDOM` the output will be different each time!

~Another interesting thing I observed is that `SRANDOM` does not work (returns an empty output) on my OSX shell running `GNU bash, version 5.2.37(1)-release (aarch64-apple-darwin24.2.0)`. But I was able to get it to work on a linux box.~

Correction: I use zsh on my terminal and it slipped my mind when I was trying this out. `SRANDOM` does work on OSX too!

```
bash-5.2$ which bash
/opt/homebrew/bin/bash
bash-5.2$ echo $SRANDOM
1190163908
```

Nonetheless, `SRANDOM` does not work on `zsh`, which is interesting because `RANDOM` is not a defined builtin for `zsh`, and that raises the question that why _does_ `RANDOM` work but not `SRANDOM`? Maybe I'll explore that as a follow up.

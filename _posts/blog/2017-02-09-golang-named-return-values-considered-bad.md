---
layout: post
title: Golang named return values considered bad
categories: blog
tags: ['golang']
date: February 9, 2017
published: false
author: self
---

I've recently started playing around with Golang and was writing some custom management scripts when I came across the idea of using named return values in my code.

You can skip to the [next section](#next-section) if you already know what named return values mean. Read on otherwise.

Consider the following function:

```golang
func filterOddAndEvenNumbers(nums []int) (oddNums []int, evenNums []int) {
	for _, n := range nums {
		if n%2 == 0 {
			evenNums = append(evenNums, n)
		} else {
			oddNums = append(oddNums, n)
		}
	}
	return
}
```

`filterOddAndEvenNumbers` is a function that takes a slice of integers and returns two slices containing odd numbers and even numbers respectively.
The return signature of the function looks like this `(oddNums []int, evenNums []int)`; This explicitly names and initializes the return arguments as `oddNums` and `evenNums`. And a simple `return` statement at the end of the function ensures that the variables `oddNums` and `evenNums` are returned respectively.

Although this looks like a great way to minimize the code you write, especially if your function has multiple return statements, it introduces a few easy to miss bugs.

```golang
func removeSSHKeys(unixUsername string) (err error) {
	unixUser, err := user.Lookup(unixUsername)
	if err != nil {
		return
	}

	sshDir := unixUser.HomeDir + "/.ssh"
	path := sshDir + "/authorized_keys.d"

	_, err = os.Stat(path)
	if !os.IsNotExist(err) {
		err = os.RemoveAll(path)
		if err != nil {
			log.WithError(err).Errorf("Error in deleting %s", path)
			return
		}

		err = os.MkdirAll(path, os.ModeDir)
		if err != nil {
			log.WithError(err).Errorf("Error in re-creating directory %s", path)
			return
		}

		path = sshDir + "/authorized_keys"
		err = os.Remove(path)
		if err != nil {
			log.WithError(err).Errorf("Error in deleting %s", path)
			return
		}
	}
	return
}
```


* Example 1 - Why bad
* Example 2 - Why bad
* Example 3 - Where good
* Conclusion


come after a long place

# [Next section](#next-section)

[create an anchor](#anchors-in-markdown)

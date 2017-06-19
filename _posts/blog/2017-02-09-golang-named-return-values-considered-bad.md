---
layout: post
title: Golang named return values considered bad
categories: blog
tags: ['golang']
excerpt: 'Named return values in golang help in reducing redundant return statements, but it might be the reason behind a bug creeping into your code without you realizing'

date: February 11, 2017

author: self
---

I've recently started playing around with Golang and was writing some custom management scripts when I came across the idea of using named return values in my code.

Consider the following function to filter odd and even numbers from a slice:

{% highlight golang linenos %}
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
{% endhighlight %}

* `filterOddAndEvenNumbers` takes a slice of integers and returns two slices containing odd numbers and even numbers respectively.
* The return signature of the function is `(oddNums []int, evenNums []int)` which explicitly names and initializes the return arguments as `oddNums` and `evenNums`.
* The `return` statement at the end of the function ensures that the two variables `oddNums` and `evenNums` are returned.

This language construct is useful in long functions with multiple return statements. However, it can also introduce a few easy to miss bugs. Now consider the following function to delete all files at a given path:

{% highlight golang linenos %}
func removeFiles(path string) (err error) {
	_, err := os.Stat(path) // Check if the path is valid
	if !os.IsNotExist(err) {
		err = os.RemoveAll(path)
		if err != nil {
			return
		}
	}
	return
}
{% endhighlight %}

* `removeFiles` takes `path` as input and returns an `error`
* On line 2, we check if the path exists at all. `os.Stat` returns an
  `os.FileInfo` and an `error` object.
* If the path is invalid, `err` will be of type `*os.PathError` and we check if i

* Consequently we check if the `err` indicates that the path does not exist. If the path exists we go ahead and delete it.
* We have another customary check on line 6 to see if the operation succeeded. The `return` statement will return `err` if there is one.

If the operation succeeds the code execution reaches line 9, and the `return` statement is equivalent to `return nil`. However, if the `os.Stat` failed, `err` is not nil




* Example 3 - Where good
* Conclusion
  * go stdlib

come after a long place

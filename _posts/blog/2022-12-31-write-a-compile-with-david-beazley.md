---
layout: post
title: 'Write a compiler with David Beazley'
categories: blog
tags: ['compilers', 'programming', 'python', 'go']
excerpt: 'My experience of attending the one week course'
date:  31 December, 2022
author: self
---

As the title suggests, I attended David Beazley's course on [writing a
compiler](https://dabeaz.com/compiler.html "The course website") earlier this
year and wanted to write about my experience.

**🏎️️ In a rush? Read the TL;DR at the bottom of this page.**

I won't bore you with the details of the course which you can find on the course
page itself but in one sentence: **A 5 day hands on workshop which will demand
your full attention, energy and then some.**

Now with that out of the way here's what my experience was like.

📖 **Before course start**

David recommended to read the first part of the [Crafting
Interpreters](http://craftinginterpreters.com/contents.html) book (you can read
it online) and also provided some warm up exercises. I had a packed schedule
leading up the course and couldn't get to the warm-up exercises but did read the
first parts of the book. I found it easy to follow the material in the book and
the great wall of compilers in my mind began to crumble one brick at a time.


🤖 **Day 1**

The course kicked off with a discussion on computer instructions and how the
instructions that actually execute on the CPU are much simpler (ADD, SUB, MUL,
LOAD, STORE) than the programs we write. This was a nice refresher of computer
architecture that I had not thought about for years. Working with high level
programming languages is comfortable after all. 🛋️

We had a program simulating a CPU to play with and the goal was to write some
programs against it in order to use the registers, memory and CPU instructions
at a lower level. For the purpose of the course this was a great way to be able
to play around with assembly-like programming in a controlled sandbox. Realizing
how much work goes into a simple program like computing the factorial of a
number has made me appreciate computers and high level programming languages so
much more.

💡 In the process I learned a cool fun fact:

<a href="https://twitter.com/indradhanush92/status/1577478322271162368">
	<img src="{{ site.url }}/images/writing-a-compiler/fun-fact-registers.png" alt="A tweet about a fun fact about computer registers" />
</a>

On day 1, we were introduced to the concept of the Data Model. Consider the
following lines of code:

```
print 42;
print 42.5;
```

The data model is how you'd go about representing a statement like this. You can
have a data model for the print statement. Which can print an integer. Or a
float. Or multiple arguments. The data model is code that knows how to represent
such a statement. It's an API for the compiler to understand what each statement
intends to accomplish. This would form the core of our compiler.

By his own admission, David was running an interesting experiment with our
batch - providing no boilerplate code unlike the previous iterations. He would
spend some time talking about the new concepts and do some live coding and let
us go code it up in our own ways. Spoilers already: This turned out to be a
great decision as I loved being able to approach the problem on a clean slate
while also having some guidance on getting started. The motivation behind this
experiment was to make the course language agnostic. As a result I chose to
start my very own experiment with Go.

However, it became apparent early on that this choice to implement the data
model as the first thing for my eventual compiler would considerably slow me
down. Instead of creating loosely defined abstractions I found myself having to
wrestle with Go's type system. This is not a Go critique post, just that given
the circumstances, I could ill afford to loose much time as I had to keep pace
with the batch.

After a little more than an hour, I abandoned Go and switched to the next best
tool in my arsenal - Python, which also happened to be the language David was
writing his very own version of the compiler alongside us and was also using to
demonstrate the concepts.

The test bed was a set of programs in [wabbit](https://dabeaz.com/wabbit.html),
the target language for which we were writing the compiler - starting from
simple programs that print a single number to simple mathematical expressions to
programs with functions. Using these as a base we were to implement the data
model so that these programs could be represented with this API. There's no
parsing of the program involved yet (this came much later).

 🧗 The hardest challenge here was getting started. You have no code. You have
 an idea. I found myself staring at the screen a lot, writing some code and
 getting rid of it to start again.

As the day ended, I managed to get started but I also found myself lagging
behind where I'd ideally want to be. Maybe a couple of hours of focused coding.
I resisted the temptation to work after hours as a long and intense week was
just getting started and I did not want to burn up too much energy early on.
This was a marathon. Not a sprint.


 🚧 **Day 2**

With my slow start the previous day, I tried to not get bothered too much about
my pace. My goal was to implement the data model to support slightly complicated
programs with `if`, `if-else` and `while` loops. The hardest challenge of the
previous day was getting started, but with that out of the way already I managed
to quickly reach this goal early on day 2. And when I felt like I had enough to
work with for the next step I switched my focus to the formatter.

The goal here was that given a wabbit program can the formatter output the
"ideal" version of the code? A programming language is only as strong as the dev
tools it provides for its users. So I found this little foray into dev tools for
the language you're implementing quite insightful.

🔁 Recursion Recursion and more Recursion. It was the bread and butter of this
project and with the formatter it started getting used quite heavily early on.
By the end of the day I was able to format simpler programs including
mathematical expressions but I was still a little behind the goal. The slow
start on day 1 was proving difficult to catch up with.

🧩 **Day 3**

Day 3 started with a discussion on tokeniser and the parser. A token is
the smallest building block of your programming language. The parser is
responsible for reading the blob of text from your file and generate a stream of
tokens. This building block is then used by anything that wants to understand
and execute your code. 

Most compiler projects from what I've seen in my very limited experience have a
high tendency to start with building the tokeniser and parser. However I still
feel that starting at the data model layer was a great call instead of spending
a ton of time early on fencing around with string patterns and regular
expressions. The data model gave me an early headstart at being able to
comprehend the inner workings of a compiler and what might be the abstractions
that need to be designed. 

I paused my work on the formatter and started out on building the tokeniser and
the parser. This turned out to be both fun and challenging. And when I needed to
bake in operator precedence for mathematical operators it blew my mind away. It
reminded me a lot of my early programming days and data structure lessons in
university. With enough effort I was able to now parse programs that had unary
operators and parenthesis like:

```
print -(2.0+3.0);
```

It was mind boggling how much code had to be written for seemingly such a simple
line of code! Although they each had their own role, I was now also able to see
a distinct pattern emerging from the code and a similarity between the
tokeniser, the parser and the formatter.

Their was a temptation to try to DRY the code but the end goal here was to get
stuff working first and try to make them efficient later. David would keep
reminding us of maybe not trying too hard to make the code pretty early on. And
I took this advice for the most part in order to stay on track.

The output from sending this line of code into the parser was a data model. And
the data model itself was composed of tokens! It felt very satisfying to start
tying the different pieces together.

By this time I had also started coding after hours a bit as it became clear to
me that I really needed to push myself more and engage in the after burners this
week.

🖥️ **Day 4**

This day was all about the interpreter. But I was still working on my parser as
I wanted to be able to have operator precedence working correctly. I knocked off
some bugs instead from the parser and made some more progress to be able to
support `if-else` and `while` loops. I realised I needed to see some tangible
output and started focusing on the interpreter.

Somewhere around mid-day I had a parser and interpreter in place that could
correctly execute print statements with simple mathematical operations. This was
also the moment that I remember fondly. One that gave me great joy and reminded
me how much I loved and enjoyed programming! I also finally got why some of my
close friends have always wanted to write their own compiler and have done so
whenever they got a chance. I only wished I had started sooner, but here I was.
Better late than never! 💪🏽

🏘️ **Day 5**

By this time I was almost a full day behind the batch's current milestone. The
day started with a discussion on virtual machines and generating machine code
from your input program. The goal was to compile the program against a target
VM. While I didn't do this myself that day, listening to David talk about this
did pique my curiosity.

I spent the rest of the day working on my parser and the interpreter so that I
could execute more complicated programs than simple math expressions. I did
eventually get operator precedence working though. But it did require a
significant rewrite of my parser logic as my initial approach was a bit flawed. 😅

Writing a compiler in a week is a herculean effort. This course was not a
competition. And each programmer in the batch had their own free choice in which
direction they wanted to push more as their is plenty to do on any of the
domains at any given point. It was interesting to keep making these decisions at
almost every juncture. 

Overall I am happy I took this course and would do so again if I had the chance
and maybe I'll go further along this time. 🥂

**🧑🏽‍💻 Talk is cheap; show me the code?**

Example wabit programs were available in a private repository for us and we used
those as a milestone to iteratively build each component out. Sadly it's hard
for me to share any of the code without also giving away those example programs.
😔

And since this was a paid course it would feel ethically wrong to share them out
in public. But if you're curious and would like to find out more about my
compiler (more like an interpreter since I manage to write code that compiles it
technically), I'd be happy to chat or pair program and maybe revisit some of the
concepts! Send me a DM on
[Twitter](https://twitter.com/indradhanush92 "My
twitter profile") or an email.

👀 **TL;DR**

1. Does the word `compiler` make your brain shut down completely and anything
   that follows it just does not make sense at all?
1. Do you want a hands on experience instead of going through a full fledged
   theoretical university or MOOC course?
1. Do you want to understand what is a compiler and how you can start writing one yourself but don't yet?

If you answered **yes** to at least one of the above questions, you should find
out a course date that works for you and do it! David is an awesome technical
educator and a master of drilling down complex topics in an approachable way.

Hint: I was answering **yes** to all of those questions up until a few months ago. 😉

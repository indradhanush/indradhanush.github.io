---
layout: post
title: Recurse Center - Checkins
categories: blog
tags: ['recurse-center']
excerpt: 'My almost daily checkins during my RC batch'
date: August 21, 2017
author: self

---

During my batch I would post regular updates on Zulip about what I had
been working on. Over the course of my batch this became a nice
timeline of sorts. I am publishing it here in case anyone is curious.

#### May 24

First checkin here!

**Progress so far**

Researched a bunch of resources as a starting point for my load
balancer project.  Worked through
[Load balancing and the power of hashing](https://jeremykun.com/2015/12/28/load-balancing-and-the-power-of-hashing/),
a nice blog post. Turned out to have some serious math, deeper than I
expected. `@Katrina Evtimova (S1'17)` helped out a lot throughout
yesterday and today. Thank you so much!

**Going forward**
1. Read through other resources on load balancing, which includes a
   few papers.
2. Start working on getting more familiar with Erlang, which is what I
   want to use for this project
3. Maintain a healthy balance between 1 & 2

P.S.: Feels nice to have been able to checkin finally with something
concrete.

P.P.S: The blog has an amazing collection of posts related
to Math & CS combined together. Anyone interested should totally check
it out.

#### May 26

**Yesterday and day before**
- Spoke to `@Nicole Orchard (SP2'17)` about bikes in depth. And picked
  up quite a few tips on how to buy one. Thank you so much!
- Discussed my project ideas with `@Saul Pwanson (SP2'17)`. The load
  balancer seems a bit abstract at the moment. It is a better idea to
  start off with a UNIX shell instead, considering that I want to be
  doing systems programming here.
- Started reading up about shell, and wrote about 4 lines of code in
  C.
- `@Joe Ardent (SP1'17)` helped over Zulip for the linker errors I was
  facing on OSX.

**Today**
- Make some real progress on the UNIX shell
- Pair with others on C, Python or anything else.

#### May 29

**Friday and weekend**
- Paired with `@Jaseem Abid (S1'17)` on LLVM code generation for a block
  of C. Turned out to be a fun and educating exercise. Will do this
  more here.
- Read and understood about fork better than I thought I did. Thanks
  to `@Saul Pwanson (SP2'17)` for helping me understand the
  concepts. [Wrote a blog post](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/)
  on that, which seems to have gone viral on Hackernews.
- Discussed about the slab allocator with `@Tim Babb (S1'17)` and
  `@Jaseem Abid (S1'17)`. I was the lurker for most parts of the
  conversation.
- [Wrote another blog post](https://indradhanush.github.io/blog/uncertainty-intimidation-and-the-stupid-one-in-the-room/)
  on week 1 of RC.

**Today and the week ahead**
- Implement command execution for the shell that I am building
- Pair with `@Tim Babb (S1'17)` & `@Jaseem Abid (S1'17)` on the slab
  allocator sometime this week
- Join the Haskell group. Work through the first five chapters of the
  Haskell book before the meetup
- Work through the first chapter of Programming Pearls by Jon
  Bentley. This will be a weekly exercise. If anyone wants to join,
  you are most welcome.

#### May 30

**Yesterday**
- Realized that a language like Python makes you forget the nitty
  gritty details that goes on under the hood.
- Implemented the command line parser for the shell, which is
  effectively `string.strip().split(" ")` in Python.
- Learned about dynamic memory allocation in C (more like recalled the
  forgotten)
- Ran into seg faults. Fixed them

**Today**
- Get command execution to work. Currently facing another seg fault
  (no surprises there!)
- Read up on slab allocator so that I can contribute on that more
  effectively while pairing
- Attend "Best Programming Talks at 7pm"

#### May 31

**Yesterday**
- Fixed bugs in the parser.
- Paired with `@Dominic Michael Spadacene (SP2'17)` on the shell. Fixed
  bugs and cleaned up the code. We now have an idea of how much memory
  this will use. Brainstormed on why `cd` wouldn't work out of the box
  like `ls` and `pwd`. Turns out it is a shell builtin, and we'll have to
  implement this on our own. To be done later.
- Pushed to github: [https://github.com/indradhanush/rc-shell](https://github.com/indradhanush/rc-shell)
- Paired with `@Jaseem Abid (S1'17)` on improving the C functions to
  accept pointers instead. Code started seg faulting again. Used
  `valgrind` to see if program is leaking memory. Turns out it is
  leaking quite a bit. Will get back to this later in the week.
- Attended the Best Programmin Talks event. Watched `States and Nomads`.

**Today**
- Take a break from the shell.
- Pair with `@Saul Pwanson (SP2'17)` on visidata.
- Start going through `the Haskell Book` and `Learn you a Haskell for
  Great Good` to be on the same page as everyone for the Haskell event
  later this week.
- Do whatever it takes to arrive at RC earlier tomorrow onwards. Have
  been reaching late for the last 2 days.

#### June 01

**Yesterday**
- Paired with `@Saul Pwanson (SP2'17)` to implement Github API as a
  browsable sheet. We also ended up with a generic client design that
  can be reused for other APIs.
- Read through the first chapter of `Learn You a Haskell for Great Good`
  and mid way through the first chapter on lambda calculus of the
  `Haskell Book`.

**Today**
- Reached RC earlier than before. Yay! Would like to keep pushing this
  towards 9 AM.
- Read more of Haskell Book
- Prepare for a presentation
- Maybe read up on some C if time permits

#### June 02

**Yesterday**
- Read more of "Learn You a Haskell for Great Good". Specifically, I
  am familiar with Haskell's syntax, declaring variables, functions
  with type declarations (is that the correct term?), lists, strings,
  list comprehensions, tuples, type classes and type annotations.
- Finally felt like I understood Lambda Calculus, thanks to
  brainstorming with `@Tim Babb (S1'17)`, `@Stefan Lesser (S1'17)` and
  `@Jaseem Abid (S1'17)` multiple times.
- Prepared and gave a talk at RC presentations on "Getting noticed on
  the Internet and what to do about it".
- Took `@Vaibhav Sagar (F1'16)`'s advice on leaving the laptop at
  RC. This sounds like a great thing to do, plus my backpack is much
  lighter.

**Today**
- Managed to bring down my commute time on the bike from ~50 minutes
  to ~40 minutes, mostly because I'm now more used to the ride and the
  route. Bringing this further down to ~35 minutes is a challenge.
- Publish the transcript of my talk from yesterday as a blog post
- Read about pointers in C in depth and refactor the existing code of
  the shell I was working on.
- Read about `PTS/TTY` and signal handling and start implementing it in
  the shell

#### June 03

**Yesterday**
- Published
  [Getting noticed on the Internet and what to do about it]((https://indradhanush.github.io/blog/getting-noticed-on-the-internet-and-what-to-do-about-it/))
- Read up about pointers. Refactored my shell to use pointers.
- The refactoring added some bugs; Fixing them required me to learn
  `gdb`. Thanks to both `@Trevor Saunders (S1'17)` and `@Sabelo Mhlambi
  (S1'17)` for helping me get familiar with gdb. This turned out to be
  much faster, than digging through the manual myself.
- More bugs. Got sucked into a rabbit hole. Reminds me of this poem:
- 99 little bugs to fix, 99 little bugs to fix, take one out, and
  patch it around, 117 little bugs to fix!
- `@Saul Pwanson (SP2'17)` suggested to use `valgrind` for one of the
  weird segmentation fault related bugs. Thank you! Using `valgrind` is
  also faster than using `printf` for debugging. Will use more of this.
- Attended the Haskell study group meet up. Suggested ways to proceed
  further by maybe forming groups where people have similar projects in
  mind to implement in Haskell. This could be useful for people for whom
  Haskell is the side project and not the priority. That would help save
  time for everyone in this group while making some pet project out of
  Haskell.

**Today**
- Slogged a bit (It was a long week, but it came and went, and I
  didn't realise)
- Started reading `Linux Systems Programming` by Robert Love. Read
  through the introduction chapter which talks about linux
  fundamentals. I knew a few things already, while learned a few new
  things along the way.
- Read about signal handling as well, and started playing around. More
  reading on signal handling is required before I can incorporate it
  into my shell.

#### June 05

**Yesterday**
- Had my mind blown over at the American Museum of Natural History
- Wrote a blog post -
  [Exploration and Prioritisation - Week two of RC](https://indradhanush.github.io/blog/exploration-and-prioritisation/)

**Today**
- Read up on signal handling from Linux System Programming and
  implement it in the shell

#### June 06

**Yesterday**
- Paired with `@Dominic Michael Spadacene (SP2'17)` to implement
  `Control-C` handling in the shell. Came up with a hacky way to do this
  such that `Control-C` does not kill the shell, but only the command
  running in the shell instead.
- Wasn't happy with hack. Researched for other ways and spoke to
  `@Saul Pwanson (SP2'17)` about this. That's when we realised that
  the hack was probably the way to implement it, unless I want to dig
  into `pts/tty` handling. Opening a pts should make handling `control-c`
  better.
- Started reading up on pts.

**Today**
- More reading up on `pts` and implement it in the shell. This sounds
  like fun and painful at the same time.

#### June 07

**Yesterday**
- Dug deep to read through the chapters on Process control and Signals
  from `Advanced Programming in the UNIX Environment`
- Figured out a clean solution of handling keyboard interrupt. We can
  use `sigaction` to get the parent to ignore the interrupt and set it
  as the default action on the child process. This makes me happy
  because it is not a hack anymore.
- Explained this to `@Saul Pwanson (SP2'17)` and `@Dominic Michael
  Spadacene` (SP2'17) one by one. This helped me to find the blind
  spots in my own understanding. I digged into them and cleared those
  as well. Writing a blog post will reveal if there are more of those.
- Realised that generally a typical day at RC rarely goes as
  planned. Which seems to be a nice thing.
- Overall feels like a productive day even though I wrote < 20 lines
  of code.

**Today**
- Stop using printf in the signal handler since it is not
  async-safe. Read up on alternatives and implement that.
- Start implementing job control. I will have to implement the `bg` and
  `fg` as builtin commands as a part of this exercise
- Go to the concert at Prospect park in the evening.

#### June 08

**Yesterday**
- Completed the clean handling of Ctrl-C in the shell
- Started working on supporting atleast one builtin command
- Attended Beginner's Club: Design Patterns by `@Andrea Law (SP2'17)` ;
  An interesting discussion followed. I digressed a bit from the topic
  and spoke about McCabe's complexity and why everyone should use it
  right from the start of the project. Connected it back to the topic
  by saying that by keeping your code complexity low from the start,
  it can help to pick simpler design patterns instead of using
  something that sounds cool but is probably an overkill for a problem
- Attended session on taking care of our hands by `@Naomi Saphra
  (SP2'17)` ; Really helpful that in case I ever develop symptoms I'll
  be able to notice them before it gets bad.
- Had a fun time at the prospect park concert

**Today**
- Finish builtins
- Start working on job control

#### June 09

**Yesterday**
- Implemented the builtin command `cd`; The code for this is very adhoc
  and could definitely do with some improvements. I will get back to
  this later.
- Was struggling with breaking the single `main.c` into a modular
  structure. Paired with `@Trent Gill (SP2'17)`, who explained the ideas
  behind `.h` vs `.c` files. Blog posts on the internet and answers on
  stack overflow on this were conflicting. Also improved the `Makefile`
  along the way.
- The shell can now run background commands if you append an `&` at the
  end of a command. There is no job control yet.
- Fixed memory leaks and bugs that kept cropping up.
- More code cleanup
- Attended `@Tim Babb (S1'17)`'s session on Automatic
  Differentiation. Key takeaway: Just because something has a fancy
  name doesn't mean it is rocket science. It turned out to be very
  simple instead.
- It was the first day where I wrote code for most part of the day
  instead of reading. I feel happy again.

**Today**
- Take a break from the shell for now
- Mock algorithm interview
- Work through first chapter of Programming Pearls.

#### June 10

**Yesterday**
- Worked through the first two chapters of Programming Pearls. Also
  thought about few of the problems given at the end of each chapter.
- Gave a mock interview on algorithms. Realised how rusty I've become
  on that.
- Worked through the first chapter and its exercises of Algorithms by
  S.Dasgupta

**Today**
- Got myself an NYPL card
- More algorithms

#### June 12

**Saturday & Sunday**
- Read through a little more of Algorithms by S.Dasgupta
- Finished reading `Distributed Systems for Fun and Profit`. This was
  lying half read for quite some time. Key takeaway: It's a good book
  if you want to get started in distributed systems but don't know
  how. The book touches on all the topics in a light manner without
  going into too much detail. Now I know what things I need to pick up
  and start digging deeper into, and most importantly in what
  order. Recommended reading for beginners in this field.
- Wrote and published
  [Writing a UNIX shell - Part II](https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/)
  ; Polishing a blog post is a lot of more work. Phew.

**Today**
- Implement job control ( the shell can already run background tasks
  commands if you suffix them with `&`

#### June 13

**Yesterday**
- Got sucked into the world of pts in my quest to understand job
  control. I probably don't need this yet. On the positive side, I
  think I probably understand what I need now.
- Refactored the code for builtins with a cleaner interface with `@Saul
  Pwanson (SP2'17)`

**Today**
- Conquer job control (hopefully)

#### June 14

**Yesterday**
- Helped `@Seth Schori (SP2'17)` with a circular import issue he was
  facing on his flask app.
- Spoke to `@Andrea Law (SP2'17)` about docker. She was stuck on the
  exercises from a docker tutorial because they were for linux, and
  she's on OSX instead. Showed her how she could spin up a docker
  container with linux to work on the tutorial instead.
- Some reading and tinkering with job control. Overall not a very
  productive day.
- Fat Cat game night. That was fun!

**Today**
- Late start to the day. Skipping RC in favour of working out of NYPL
  instead.

#### June 15

**Yesterday**
- Was able to make some headway in terms of code for job control

**Today**
- Finished the implementation of job control on the shell. Processes
  clean up after themselves if they run in the background or are
  interrupted in between. Was stuck on this for quite some time and
  badgered `@Saul Pwanson (SP2'17)` to help me on this. Thank you so
  much!
- The shell now runs directly under a terminal emulator, instead of
  having to first open bash and then run the executable. This is the
  biggest win after struggling with job control for all of this week.
- Haven't felt this happy about making something in a long time.
- Discovered an interesting bug regarding the handling of
  SIGTTOU. Need to explore this. Also will implement the job
  completion message tomorrow.

#### June 19

**Since Friday upto now**
- Investigated into the bug related to SIGTTOU. Did some online reading
  and experimented around, but to no avail. I have an idea why the bug
  (might be a feature), but I'm not convinced yet.
- Read through Jeff Bonwick's paper on `The Slab Allocator`.
- Read a bunch of blog posts.
- Wrote a draft cover letter (more like the answer to Tell us about
  yourself?)
- Also started a survey to understand what is an optimal length for a
  cover letter to receive a positive response ([Survey Here](https://docs.google.com/forms/d/e/1FAIpQLSfrGf3doP7nrBCajDxOV51oSVxuOI-HYKrntRBkQQZ0lF0mrg/viewform?usp=fb_send_twt)) ; Would be
  great if you could take it. It has 4 questions only.

**Today**
- Read up on asyncio
- Spend some more time on the SIGTTOU bug
- Maybe work on the slab allocator

#### June 20

**Yesterday**
- Started reading up about Python internals. Read a blog post on
  symbol tables.
- Did a rubber duck explanation to `@Dan Luu (W'13)` of the shell and
  the bug with SIGTTOU in the hope of having an "aha" moment. That
  never came unfortunately. However, we used `strace` and we know that
  SIGTTOU is being emitted for a foreground process when it attempts
  to write to the terminal. However we noticed a similar behaviour in
  bash, which verifies that it is not unexpected. But the man pages
  say SIGTTOU is emitted when a background process attempts to write
  to the terminal. There is most certainly something that I have
  missed out. My next step to figure this out is to create a minimal
  reproducible test case and post on Stackoverflow for help.
- Read about asyncio

**Today**
- Pair with `@Ethan Raymond (S1'17)` on his collaborative editor. We
  will use asyncio.
- Read about Python's data model.
- Maybe create a reproducible test case for the shell bug if I feel
  like it.

#### June 21

**Yesterday**
- Paired with `@Ethan Raymond (S1'17)` to use asyncio for the editor. We
  hit a dead end, since none of us had worked with asyncio
  previously. Turns out you can't do asynchronous input from stdin
  using asyncio yet. Or the resources that I stumbled upon, weren't
  very clear.
- Another dead end: Wanted to integrate the shell into yehos. Realised
  it doesn't ship with libc yet, which is a fair amount of work at
  this point.
- Finalised my second project at RC. I will implement RAFT in
  Erlang. Both of these are unknown to me, so I will be reading up on
  RAFT while working through Learn You Some Erlang at the same
  time. Will be some time before I get started with the actual
  implementation.
- Went through Jason Eisner's `How to Read a Technical
  Paper`(https://www.cs.jhu.edu/~jason/advice/how-to-read-a-paper.html)
  as recommended by `@Naomi Saphra (SP2'17)`.
- Started reading through the original RAFT paper. I'm taking
  extensive notes while reading it, as recommended by `@Naomi Saphra
  (SP2'17)`. It surely helps in staying focussed while understanding
  better instead of just skimming the paper. 33% through the paper at
  the moment. But the thick of the material starts about now, so it
  will only take longer as I go deeper into the paper.

**Today**
- Continue working on the RAFT paper.
- Switch to `Learn You Some Erlang` in between.
- Also read up on Python internals
- This looks to be my daily routine, at least for the next few days.
- I will also have to read Leslie Lamport's paper on vector
  clocks. Probably won't start on it today. But surely before I start
  working on the RAFT implementation.

#### June 22

**Yesterday**
- RAFT: Worked through the section on log replication.
- Went through the first 5 chapters of Learn You Some Erlang. More
  like brushing up, since I had done those just before coming to RC.
- Realised that I'll have to work through most of that book before
  implementing RAFT.

**Today**
- Read more of Learn You Some Erlang.
- Let what I've learned so far about RAFT and Erlang sink in.
- Read up on Python internals

#### June 23

**Yesterday**
- Worked through two chapters of LYSE: Higher Order Functions and
  Errors and Exceptions.

**Today**
- Woke up pretty late.
- Go see MOMA today at 4.

#### June 26

**Friday, Weekend and upto now**
- Saw Van Gogh and Picasso's works at MOMA. Surreal.
- Shell keeps calling me
  back. [Wrote Writing a UNIX Shell - Part III](https://indradhanush.github.io/blog/writing-a-unix-shell-part-3/). Took
  quite some time. Also I learned a few more things about
  signal handling while writing the blog post itself.
- `@Saul Pwanson (SP2'17)` pointed out a statement from the blog post
  that turned out to be incorrect. Digged deeper to understand that
  and updated the post.
- Saw the #NYCPrideParade. Awesome thing. Lucky I got to see it.

**Today**
- I want to work on the shell more.
- But I also want to do Erlang.
- Toss a coin and decide between the two?

#### June 30

**Since last checkin (26th June)**
- Paired with `@Kate Murphy (S1'17)`on her shell. We understood pipes
  and when to close the file descriptors. I was also able to validate
  my understanding of fork().
- Paired with `@Rudi Chen (S1'17)`to implement load balancing on his
  stressed syllables app. Learned a few things about the Elixir which
  will help me with my own study of Erlang. Elixir definitely has a
  better syntax.
- Read the internals of Python and gotchas. Specifically the Python
  data model, variable scoping. I don't think I understand all of the
  data model yet. Will probably have to read that a dozen times until
  I get it.
- Read some other topics: ALB vs ELB. HTTP/2. Docker service
  discovery. VPC.

**Today and the week ahead**
- Try to flip the body clock back to saner timings. Currently it
  starts at 1 in the afternoon and ends at around 5 in the
  morning. Would like to change this to end by 1 AM instead.
- Get back to Erlang + RAFT. Pick up speed on this.
- Pair some more.

#### July 03

**Weekend**
- Wrote a [blog post](https://indradhanush.github.io/blog/half-time/)
  on the RC experience so far.
- Attended my first EDM concert at Central Park.
- Flipped body clock back to regular timings. \m/

**Today**
- Erlang!

#### July 04

**Yesterday**
- Worked through chapters 8,9 and 10 of Learn You Some
  Erlang. (Functionally solving problems, A short visit to common data
  structures, The hitchhiker's guide to concurrency)
- Terrible dinner at Yiwanmen. (No wonder this was the only empty
  space while everywhere else was crowded for dinner)

**Today**
- More Erlang. Didn't do enough yesterday. Need to do more.
- Revise through my notes on the RAFT paper, upto what I've read so
  far.

#### July 05

**Yesterday**
- Revised through my notes on RAFT and in the process found a few
  incorrect assumptions. Also managed to file them in neatly in a more
  organised way digitally.
- Made some more progress on reading the RAFT paper.
- Gave a mock system design interview to `@Veit Heller (S1'17)`and
  `@Rudi Chen (S1'17).` Thanks a lot to both of you for taking out time
  for this!
- Saw the fireworks on the east side. Pretty amazing.
- Sadly not enough time for Erlang yesterday.
- Made peace with the fact that my estimation skills are terribly out
  of mark and I end up underestimating the time required for most
  things all the time. I do want to get better at this, but this is
  probably one of those things that come with time maybe?
- Set more goals for the rest of the week

**Today**
- Summer 2's in the house! yay!
- Participate in the panel on "Choosing and scoping projects"
- Read RAFT (Hopefully finish it?)

#### July 06

**Yesterday**
- Sat on the panel for "Choosing and Scoping Projects"
- Gave a presentation on the shell I built in my first half of RC
- Surprisingly had a reasonably productive time and was able to finish
  the RAFT paper. Have a few blind spots in my understanding though.

**Today**
- Discuss the RAFT paper with `@Rudi Chen (S1'17)`
- Pair with `@Rudi Chen (S1'17)`on his stressed syllables project. We
  will work on caching the syllables across servers.
- Squeeze in Erlang in between all of this.

#### July 07

**Yesterday**
- Paired with `@Rudi Chen (S1'17)`to implement caching on the stressed
  syllables app.
- Paired with `@Elizabeth Rosenzweig (S2'17)`to refactor a very messy
  code base. This is only getting started. It is a lot of work.
- Paired with `@Veit Heller (S1'17)`to pick up some ideas on how to
  better refactor C code. Specifically learned about macros.
- Worked through 2 chapters of Learn You Some Erlang.

**Today**
- More Erlang.
- More pairing.

#### July 09

**Yesterday**
- Paired with `@Anna Taberski (S2'17)`on understanding a bug in her
  HTTP server. Learned a few things along the way about golang's
  `Conn` object. This took a couple of hours somehow. Found a
  workaround that let's Anna not get blocked on this. The workaround
  is hackish but also feels
- The bug managed to spike my curiosity, I did some research after the
  pairing and suggested her a few more approaches.
- Interestingly, as Anna found, the bug only appears on Chrome and not
  on Safari.
- Felt tired, probably because of the long week.
- Slogged through a couple of chapters of Learn You Some Erlang and
  started reading the chapter on concurrent programming from Joe
  Armstrong's Programming Erlang as well.
- I feel more or less okay to get started implementing RAFT now. Don't
  want to get bogged down to just specialising over Erlang without
  building anything concrete. Just going through the tutorials gives a
  feeling of not having accomplished anything.
- Some discussion on the perception of art and literature to end the
  day.

**Today**
- Watched Harry Potter and the Deathly Hallows (Part II) and
  simultaneously echoed the dialogues and waved my arm around when the
  characters cast spells. :D
- Resumed reading Hackers & Painters. I had stopped midway for some
  abrupt reason before starting my RC batch. Finishing the book is one
  of the goals I set before coming to RC.
- Took the Staten Island Ferry and back. Highly recommended. This was
  something different and much needed as my stay in New York was
  starting to feel a bit monotonous. Oh, in case you didn't know, the
  ferry service runs 24x7 and is free. \m/ ; And it is recommended to
  take it during the non rush hours.

#### July 10

**Yesterday**
- Worked through
  [https://rustbyexample.com/](https://rustbyexample.com/) upto
  section 8. I had always wanted to feel what Rust is all about and I
  really wanted to work on something completely new. Offers some fresh
  perspective. I like the syntax of Rust and it also has pattern
  matching. That makes me excited about trying this out in the
  future. But for now, it will have to wait.

**Today**
- More Erlang - specifically read about the Erlang OTP, gen_server and
  gen_fsm. I have to accept this is all a bit too intense and taking
  longer than I thought.
- I am close to get started with implementing RAFT (I thought it would
  be today)
- Spent some time in the evening thinking about my implementation,
  i.e. what would be the best approach to get started.
- Hopefully, tomorrow we can begin! :airplane_departure:

#### July 12

**Yesterday**
- Spent most of the day toiling away with gen\_fsm in Erlang. Was able
  to get started with structuring out the skeleton.
- Midway through this, I realised that gen_fsm has been deprecated in
  favour of gen\_statem. Started reading the man pages for gen\_statem
  instead as a result.
- Can't call this progress, but still better than what I've been able
  to do recently. There's still a long road ahead before I can start
  writing code smoothly for this project.
- Had a nice conversation to wrap up the day with `@Kenneth Alexander
  Durril (S2'17)` on "Why are we at RC" and got a few insights into
  his work/struggles with his project on PDFs so far.

**Today**
- Keep hitting at the proverbial wall of Erlang until it starts
  breaking down.
- Rinse. Repeat.

#### July 13

**Yesterday**
- Paired with `@Jaseem Abid (S1'17)`. He helped me understand Erlang's
  gen_statem that I will need to implement Raft
- Concepts seem clear now but when I attempted to translate it into
  code, I was still stuck. So that will require more effort.
- Attended `@Victoria Kirst (S2'17)'`s session on CSS. Key takeaway: I
  won't be as intimidated the next time I have to fix my blog's
  layout.
- Browsed through `@Anna Taberski (S2'17)`code on the HTTP server that
  she wrote. Suggested a few improvements that she could do along with
  more stuff that she could add (like tests). But I found the code to
  be well structured and organized.

**Today**
- Started working on a library to store large files in memcached just
  for fun; memcached has a max key size of 1MB. Storing files larger
  than that requires some black magic under the hood, that my library
  will do.
- Attended `@Tim Babb (S1'17)`session on ray tracers. I am going to
  start working on one.
- Shared my initial structure of the memcached chunker library with
`@Jaseem Abid (S1'17)`; Made some improvements based on the discussion
and there's more to follow in the coming days.
- Proud owner of a Kinesis Advantage 2 from today onwards. But it
  feels like I never learned to type. I am giving myself two weeks to
  be back at my 100% proficiency. Enjoying the keyboard by each
  passing keystroke. <3
- Paired with `@Kate Ray (S2'17)`on how to manager her specific git
  repo. I provided her with my thoughts on what might be the best
  approach even if it does not align with git best practices. One of
  those scenarios where not following the best practice makes life
  easier instead.

#### July 15

**Today**
- Worked a bit more on the memcached chunker. It has a set\_file and
  get\_file api now. It also stores sha1 hash of each chunk and
  verifies the hash during the get\_file operation to ensure that the
  file was not corrupted since the last time set\_file was used. The
  code is here if anyone is interested:
  https://github.com/indradhanush/memcached-chunker/tree/feature/improvements

- Have a few more ideas to implement in this: Use hashes as the keys
  instead of incremental keys. This would mean duplicate files can be
  stored under the same key. But it would also have to maintain a
  reference to the number of files currently referring to that key so
  that the content is only deleted when none of the files refer to the
  stored piece anymore. Other things include, benchmarking the sha1
  hashing to see what are the limits of the system and to find an
  optimal number of rounds of hashing to be used. I should also
  benchmark sha256 at least if not sha512 as well. Current codebase is
  in python2.7; Should port this to python3.6 instead. Will be
  interesting to understand how the string manipulation changes since in
  python 3 everything is unicode by default. So my current model of
  memory calculation will probably not work. Overall this turned out to
  be an interesting project to pursue, but also something I am
  reasonably confident about pulling it off. So this becomes my goto
  project when nothing else seems to be working. Thus pausing work on
  this for the next few days. But I don't mind getting back to this if
  anyone wants to pair on it or is just curious. **Key lesson: fallback
  projects are nice and work amazingly well to boost your confidence.**
- Started researching about the ray tracer project. I am going to do
  this in Python even though it is not the most performant. Reason
  being learning C++ right now along with implementing ray tracing
  will be too much to handle for me. **Key lesson: Know thy limits.**
- Bugged `@Tim Babb (S1'17)`for help understanding the ray tracer
  basics. An intense drill down session followed where he explained the
  concepts amazingly well. Turns out I had also forgotten some basic
  math like what happens when you multiply a negative number with a
  vector. :( But with Tim's amazing explanation without giving away too
  much and the right amount of prodding meant I was able to come up with
  the answer myself: It flips the direction to the opposite side. Also I
  am glad I asked him for help, because I realised that I was wrong
  footed right from the beginning and had I started working without
  asking him, I'd be working on something completely different and not
  even remotely close to a ray tracer. **Key lesson: Ask for help when you
  need it.**
- A bit comfortable on the Kinesis. But still a long way to go.

#### July 17

**Weekend**
- Started working on the ray tracer. Wrote some code to determine rays
  that intersect a sphere.
- The end result was an all white image with black borders. `@Tim Babb
  (S1'17)` helped to figure out the errors in the code.
- While everything looked fine, there was still one last bug in the
  form of a missing bracket around a mathematical operation that
  `@Wesley Aptekar-Cassels (S2'17)`helped to figure out.
- Thanks to all this I have something, but far from perfect.

**Today**
- My mapping of the world co-ordinates vs screen co-ordinates is
  obviously wrong. Understand and fix this.
- Make more progress on the ray tracer to start accounting for a light
  source.

#### July 18

**Yesterday**
- Fixed the coordinate transformation in the ray tracer. I can
  generate a black and white image of a sphere at varying distances
  now.
- Changed my data structure to handle RGB. I was only handling single
  color values so far. And some basic project management to structure
  the codebase nicely.
- Started reading Designing Data-Intensive Applications. Read through
  half of chapter 1. I'm taking notes as I read. So this will take
  longer.

**Today**
- Started reading What I talk about when I talk about running by
  Haruki Murakami in the subway. I'm enjoying the read and can
  resonate with a lot of the author's feelings about running in
  general already. This is going to be a nice read!
- Read more of Designing Data-Intensive Applications.
- Understand how a light source affects the image and implement it in
  the ray tracer.

#### July 19

**Yesterday**
- Understood the concept of the surface normal and determining the
  color of each point using it with a lot of help from `@Tim Babb
  (S1'17)`
- Implemented it and I have a somewhat buggy image of the surface
  normal.
- RC birthday celebrations
- Finished Chapter 1 of Designing Data-Intensive Applications
- Skimmed through the paper on DynamoDB.

**Today**
- Start reading Chapter 2 of Designing Data-Intensive Applications
- Find the bug in my surface normal image. I could use some help on
  this if anyone would be interested.
- Start reading the DynamoDB paper for real.


#### July 20

**Yesterday**
- Spoke to `@Jinny Cho (S2'17)`and helped her understand the
  differences between DyanmoDB, MongoDB and Postgres. The discussion
  revolved around trying to find out the best database for her use
  case.
- Fixed bugs in the ray tracer. The surface normal image looks a bit
  saner but is far from correct. I have this . `@Sukanya Aneja (S1'17)
`  helped find a bug where I was taking just the absolute value of the
  co-ordinates instead of rescaling my range.
- Helped `@Hang Lu Su (S1'17)`understand operating system processes and
  why cd is not a sys call but a shell builtin.

**Today**
- Start reading the DyanmoDB paper.
- Attend the ray tracer workshop.
- Maybe pair with someone on the ray tracer. I've tried a bunch of
  things to debug and am virtually out of ideas now.


#### July 21

**Yesterday**
- Attended the ray tracer workshop. Had a few doubts answered and a
  revelation afterwards. I'm not sure what changed, but I was using
  python's PIL to save the image and switched to scipy.misc.imsave
  instead. End result I have images that look more like the surface
  normal image. There are subtle variations as I increase the size of
  the image. Also changed hardcoded sphere values to depend on the
  width of the image instead. This makes testing at various sizes
  trivial. Here's the result for a 500 * 500 image. Personally I am
  happy with the result.
- Read upto section 4.2 of the Dynamo paper.

**Today**
- Had an early start to the day but something else needed my
  attention. Ended up missing the jobs workshop. :(
- Continue reading the paper.
- Get back to my Erlang project. I feel mentally prepared for this
  now.
- It has also been a week on the Kinesis, and I feel reasonably
  comfortable. Definitely more than my 50% of usual proficiency on the
  keyboard but I get slightly off when it comes to keyboard shortcuts
  that I had setup previously. It also takes me sometime to adjust to
  my older muscle memory when I go back to typing on the internal
  keyboard.


#### July 22

**Yesterday**
- Discussed about consistent hashing and replication with `@Nikhith
  Naidu (S2'17)`
- Started digging into gen_statem for my Raft implementation once
  again.
- Not a very productive day overall, but a great dinner with `@Naomi
  Saphra (SP2'17)`, `@Stefan Lesser (S1'17)`and `@Jaseem Abid
  (S1'17)` where we discussed from Fahrenheit vs Celsius to is it
  worth blowing a lot of money on an iPhone instead of an high end
  android for half the money to why does Apple have such an
  unapproachable image in the public eye.

**Today**
- Good amount of walking around 42nd street. Saw the UN headquarters
  from outside.
- More Erlang.
- Commentated movie night.

#### July 24

**Weekend**
- Skipped commentate movie night since I felt productive at that time
  and didn't want to break the flow.
- Read the design principles of gen_statem. I don't understand all the
  things but I am beginning to develop a feel for it.
- Started building a skeleton for the leader election phase
- Filed my notes on RAFT from notebook to a text file.

**Today**
- Had a Skype call with `@Joseph George Yiasemides (SP1'17)`. I showed
  him my in progress skeleton code of the leader election phase. Asked
  him about my doubts. He shared a few helpful links to understand OTP
  better. Thanks `@James J. Porter (S'13)` for connecting me with him.
- Go through those links.
- Start Grokking Algorithms

#### July 25

**Yesterday**
- Read through the chapter on Dynamic Programming from Grokking
  Algorithms. Loved it.
- Started reading the articles that `@Joseph George Yiasemides (SP1'17)`
  shared with me on understanding OTP.

**Today**
- Continue reading the articles.
- Hans Zimmer concert.

#### July 27

**Yesterday**
- The wall of Erlang has started to give way.
- Discussed my ideas with `@Jaseem Abid (S1'17)`on the leader election
  phase before getting writing code. We churned out a few obvious
  design issues that I didn't quite know the best "erlang" way.
- Paired with him later to implement a very minimal states where the
  nodes start as "followers" and then one of them becomes a
  "candidate" and starts an election requesting for votes. The
  followers oblige and grant votes.
- This is far from perfect. But definitely a start. I feel motivated
  again. :victory_hand:

**Today**
- Paired with `@Joseph George Yiasemides (SP1'17)` and showed him what I
  had. I had a few more doubts that had cropped up when I was playing
  around with the statem further. We debugged the program and found
  out the best approach to go forward while discussing alternatives.
- The current approach of using state\_function mode of callback
  appears just right. This helps me to move forward. I was fumbling
  with the alternative of using the handle\_event\_function mode and it
  appears to add a generic interface for handling events. Rather
  explicitly writing code to handle the events that we want is a
  better approach.
- Continue building the statem.
- Discussion on Career Progression
- RC Presentations
- Job fair

#### July 31

**Friday and weekend**
- Made some good progress on the leader election. Started cutting down
  edge cases. This is fun.
- Paired with `@Rudi Chen (S1'17)`on more leader election work. Learned
  a few techniques of building better APIs in Erlang. I can see how
  thinking in a FP is significantly different than an imperative
  language.
- Started reading Chapter 2 of Designing Data Intensive Applications.
- Started digging into writing tests in Erlang. Now is a good time to
  do that in parallel.
- Commentated movie night. Geeked out on philosophy while watching The
  Matrix.

**Today**
- Write more code and tests.
- Read a bit.

#### August 01

**Yesterday**
- Wrote tests for the follower state and fixed bugs along the way.
- Had a few erlang design pattern related questions in mind that I got
  answered via IRC.
- A quick pairing session with `@Jaseem Abid (S1'17)`to do things the
  Erlang way. I was using pattern matching for my tests and although
  it made writing them easy, failure messages were painful to
  parse. We worked around this by wrapping the pattern matching
  statements around assert statements instead.

**Today**
- Rinse. Repeat.

#### August 02

**Yesterday**
- Wrote a whole bunch of tests for the candidate and leader states of
  the leader election phase. This helped find bugs along the way while
  I also implemented a few more features.
- After not running my code for a couple of days, I was relying on my
  tests to get my code to work, I finally ran the leader election for
  real. I found more bugs as a result that my tests did not. With
  three nodes I have smooth leader election and reelections. When I
  have five nodes, I see a weird pattern and a split vote almost all
  the time.

**Today**
- Find the source of the annoyance above and fix it. I hope to have
  ironed out issues in the leader election protocol by EOD.
- Update: Found the weird bug that was causing the cluster to fail
with five nodes. It was a hardcoded list of three
nodes. :neutral_face: ** That was quick though. I was fearing
something much more brutal. :laughing:

#### August 03

**Yesterday**
- Sorted out leader election. Fixed a couple of bugs and incorrect
  implementations along with writing tests.
- Did some unrelated reading.
- Took my foot off the pedal for the day. Chilled out.

**Today**
- I resumed reading the Dynamo paper yesterday and will continue to do
  that.
- Start playing around with ideas for implementing log replication.

#### August 05

**Thursday**
- Read the dynamo paper on the subway (a small part of it)
- Didn't really work on my project much but went around talking to
  others
- Spoke to `@Kate Ray (S2'17)`about managing her git repo which has a
  few special requirements. This was a follow up to a discussion we
  had had a few weeks ago. I told her about the idea of orphan
  branches, which now appear to be a closer fit as compared to
  maintaining multiple parallel branches or multiple folders within
  the same branch.
- Helped `@Hang Lu Su (S1'17)`with python's mock library. Mock is
  tricky to understand and I recalled my own painful struggles with
  trying to understand mock back in the day. But it is powerful at the
  same time once you understand it.
- Job fair
- A lot of fun and random discussions in Babbage with fellow
  recursers.

**Friday**
- Continued reading the dynamo paper on the subway.
- Had a fruitful pairing session with `@Sagar Shah (S2'17)`on
  understanding supervisors. Learned about a few tricky spots while
  pairing that will come in helpful when I have to deal with them
  myself.
- Helped `@Jinny Cho (S2'17)`get started on her django project while
  explaining to her the difference between a virtualenv installation
  and a postgres installation.
- `@Elizabeth Rosenzweig (S2'17)`told me about floobits, which is a
  collaborative editor with native extensions for emacs, vim, sublime
  and atom along with a browser interface. I set this up on my system
  and then tested it out with her. It was a lot of fun to type
  together but from the comfort of my own editor. I think this will
  become my preferred mode of pairing remotely after my batch ends.
- Helped `@Hang Lu Su (S1'17)`with understanding python packages and
  modules which was followed up with a rather lengthy conversation
  about structuring packages. I need to learn how to get my point
  across in a more precise manner in a short span of time.
- Showed my code on leader election to `@Veit Heller (S1'17)`and
  explained to him my design considerations.

#### August 08

**Yesterday**
- Had a Skype call with `@Joseph George Yiasemides (SP1'17)` and
  discussed about tools and libraries used in Erlang for production
  code. He shared a bunch of resources and well known Erlang projects
  for reference.
- Got started with log replication. I've been writing tests as I go
  very strictly, which makes the time to build a feature longer but it
  is totally worth it, since testing this in the shell manually is
  annoying.
- Paired with `@Jaseem Abid (S1'17)`later in the evening and figured
  out a better way to make tests deterministic. We can test the
  cluster at different states on intent. Which is a great
  thing. Learned a bunch from him!

**Today**
- Continuing from where I left off yesterday.

#### August 10

Last checkin here. Will move to the #alumni-checkins.

**Yesterday**
- Wrote some code, nothing concrete.
- Lunch with `@Sonali Sridhar`
- Lockpicking workshop.
- Wonderful dinner at the Japanese Kimchi place we'd gone on our first
  week at RC. Seems only fitting that RC ends with that as well.
- Long conversations late into the night.

**Today**
- Not write code.
- Feelings checkin.
- End of batch picnic.
- `return 0`.

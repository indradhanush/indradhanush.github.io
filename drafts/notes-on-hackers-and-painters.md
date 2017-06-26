#Hackers & Painters
Hackers & Painters is an insider's perspective on the programming
fraternity told by Paul Graham. Following are my notes and thoughts
on the book along with a few phrases picked verbatim from it. These
reflect my understanding of the book. The material is a bit dated
though, so take it with a pinch of salt.

A lot of the material sounds obvious if you are reading the book now,
but keep in mind that the book came out in 2004. Facebook was just
launched and was available only within Harvard's networks. iPhone
didn't exist yet.  More than a decade has passed since then and
computers & technology has grown by leaps & bounds. Let that not stop
you from reading the book though. I recommend you read it
anyhow. There's still a thing or two (and possibly more) that can be
learned.

# What this is not
- A review of the book.
- A comprehensive summary of the book. I've possibly missed out whole
  sections in between.

### Why Nerds Are Unpopular

### Hackers And Painters
* Creative work: Keep the low hanging fruits for times when you lack
  motivation. Good work comes in cycles of motivation and the lack of
  it. Backing off is important.
* Collaboration: Ensure that you break down the project into well
  defined modules. Each module should be worked upon by one person at
  a time.
* Designing Software: Think about how painters make drawings. Think
  about the APIs you make from the user's perspective. You are making
  software for a human audience.
* Software: Your user will not read the manual before they use
  it. Software should be obvious. It should do what the user guesses
  it does.

### What You Can't Say
* The Conformist Test: Odds are that we think what we are told.
* Trouble: People will get mad at you if what you say does have a
  chance to be true.
* Heresy: A part of our brain already knows a few things, we just
  haven't realized it yet.
* Time and Space: If an idea is accepted at a different part of the
  world and/or time, and is considered as a taboo in ours, in that
  case we are probably mistaken about that.
* Prigs: We raise our kids with the taboos we believe in. We inject
  those into their heads as they grow up.
* Mechanism: Wars are made out to be about conflicting ideas between
  groups. The group that wins is seen as the one with the eternal
  truth. And the losing side quickly gets vilified.
* Why: Question assumptions. Do not take anything at face
  value. Question the weirdest of theories. Doing this keeps your
  brain alive.
* Pensieri Stretti: Pick your battles wisely. There's no point in
  arguing with an idiot. It does not add any value to you. But only
  distracts you from the more important things. You do not need to
  talk publicly about all the things that goes in your head. Instead,
  find a few good friends with whom you can talk about the most
  outrageous and weirdest of ideas and not get judged for it.
* Viso Sciolto?: If you must engage actively with a zealot, engage
  them from distance. Use abstractions. Attack the theme of the
  zealotry. Also attempt to use humor. Zealots can't handle humor
  well.
* Always be questioning: Learn to watch a mob from distance. Look out
  for ideas being suppressed. Learn to watch your own emotions from a
  distance. From a different perspective.
  
### Good Bad Attitude
* Hacker: For the non technical audience, the word means someone who
  breaks into others' computers. But within the technical community it
  refers to someone skillful enough to get a computer to do what they
  want.
* Hack: It means when someone breaks the current set of rules and does
  something out of the box. It can be an ugly solution. But both
  creative and useful at the same time. Indians would be familiar with
  the term [_jugaad_](https://en.wikipedia.org/wiki/Jugaad). It means
  _a hack_.
* Innovation: Tell a hacker that they can't do something, and their
  first thought is how they can prove you wrong. This is inherent in
  their nature - challenging assumptions.

> It's odd that people think of programming as precise and
> methodical. _Computers_ are precise and methodical. Hacking is
> something you do with a gleeful laugh.

### The Other Road Ahead
* Earlier, software was built with desktops in mind, where you;d have
  to install it on your system. To do just that, you were expected to
  understand computers. How they work. And their internals. And be
  able to fix it if something went wrong.
* People started leveraging the power of the browser to simplify the
  pre-requisites for using software. And using a computer became more
  convenient than ever.
* In the case of desktop software, you have to write it in the
  language of the operating system. For a web based software you can
  choose anything, because the software runs on your server, which you
  control.
* Making releases for server side applications is easy. You can make
  tiny, incremental changes overa period of time. You control how and
  when the updates are rollled out to the end users. In desktop
  software, you tend to release a bunch of updates combined
  together. You have no control over the update. The end user may or
  may not chose to update their appication.
* Bugs: Reproducing bugs on a server side app is trivial. Whereeas,
  you have no clue what could be going on in a desktop app.
* Compound bugs: These are bugs that are caused by a sequence of
  specific steps combined together. These are rare and hard to
  reproduce. These can be minimized if you use functional programming.
* Being able to release faster, adds up as motivation for the future.
* Ideas are dime a dozen. An idea leads to a bunch of other ideas and
  so on. Its an endless rabbit hole unless you start shipping out
  those ideas. Or atleast some of them. If you are shelving your
  ideas, it acts as a negative feedback loop that inhibits your
  ability to come up with more ideas. Because now you are thinking
  about the overflowing shelf of ideas and you don't have the mental
  space to accomodate new ones.
* It is okay to not have a concrete roadmap as long as you have a
  general idea about the direction in which you want to proceed. If
  you knew the next winning idea, you would have implemented it
  already. This applies to all fields of life. Not just technology.

> I may have given the impression that we just blithely plowed forward
> writing code. We did go fast, but we thought very carefully before
> we released software ontho those servers. And paying attention is
> more important to reliability than moving slowly. Because he pays
> close attention, a Navy pilot can land a 40,000 lb. aircraft at 140
> miles per hour on a pitching carrier deck, at night, more safely
> than the average teenager can cut a bagel.

* This generally works well for smaller software teams.
* Small teams are more efficient than bigger ones. Adding an extra
  pair of hands to a project generally slows it down.
* In smaller teams, programmers have to fill the role of system
  administrators as well. Generally the programmers (who wrote the
  software) have enough domain knowledge to be able to bring your
  servers back up at 3 AM.
* Web based software is a constant evolving process. You have to
  always be on the top of things.
* Server side applications give you the liberty to be associated with
  your users more closely. You can observe how they expect the
  software to behave vs how you made the software to behave. You don't
  need artificial benchmarks, because your _users_ are your
  benchmark. However, you must respect your users' privacy as well.
* Software pricing should be subscription based, instead of charging
  users for additional features and upgrades.
  
> If something is hard to buy, people will change their mind about
> whether they wanted it. And vice versa: you'll sell more of
> something when it's easy to buy.
> Users should not have to do much more than enter a credit card
> number. (Make them do more at your peril.)

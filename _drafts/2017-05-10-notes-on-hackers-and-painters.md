---
layout: post
title: Notes on Hackers & Painters
categories: blog
tags: ['books', 'notes']
excerpt: "My understanding of Paul Graham's book - Hackers & Painters
along with excerpts from the book."
date: May 05, 2017

author: self

---

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

* Large companies tend to buy expensive solutions even though cheaper
  ones are available. An expensive solution costs more to sell. When
  finding potential customers, go for the smaller ones first. The
  bigger ones will follow in time.
* With the advent of the desktop computer, writing software became
  more accessible. It became cheaper to produce software compared to
  when you needed a mainframe to write code.
* Microsoft was able to exploit this and beat IBM. But Microsoft might
  get dealt a similar hand, because now computing is moving away from
  the desktop and Microsoft is trying hard to hold on to it, quite
  like how IBM tried to hold on to mainframe computing.
* The idea of starting up became easier with desktops. As the years
  have gone by, startups have become more and more informal and more
  stressful. Since web based applications are never quite finished,
  you can never really say: _Now that we've finisished our product we
  can all pack our bags and go take a vacation for a week_. You work
  more than your competition because you can. Because startups demand
  it.
* Hackers think about starting up all the time. But they don't because
  they are thinking that they don't know how to run a business and are
  mostly afraid of competition.
  
> There are only two things you have to know about business: build
> something users love, and make more than you spend. If you get these
> two right, you'll be ahead of most startups. You can figure out the
> rest as you go.

* In the early days you will probably not earn more than your
  spends. But if you are closing the gap fast, things will turn out
  well.
* Release an initial version of your product first and listen to your
  customers. They will tell you what can be simplified. And what new
  features can be added.

> The best thing software can be is easy, but the way to do this is to
> get the defaults right, not to limit users' choices. Don't get
> complacent if your competitors' software is lame; the standard to
> compare your software to is what it could be, not what your current
> competitors happen to have. Use your software yourself, all the
> time.

* Big companies are scared of startups because they can't move as fast
  as a startup. Bureaucracy.

### How to Make Wealth

* You are more productive at a startup by an order of magnitude. You
  can work more for a fewer number of years, but with greater
  intensity. 
* You can get more done with less at a startup.
* But startups are not easy. If it were so, everyone would do it.

> There is a conservation law at work here: if you want to make a
> million dollars, you have to endure a million dollars' worth of
> pain.

* Make something that people want. 
* Money is not the same as wealth. Although they are used
  interchangeably, but they are not the same.
* Money is used as an intermediate step. You use it to get what you
  want. What you want is known as wealth. Think of the barter system
  and the problems it had. You can't exchange a sack of rice with a
  cobbler if he wants a bag of leather. Instead you use money to get
  what you want, i.e. wealth. Money _creates_ wealth by making it
  possible to give others what they want.
* Wealth can be created out of nothing. By adding _value_ to something
  you are creating wealth.
* A job is a group of people working together trying to build
  something people want.
* A company must earn money to survive. This can only be done if it is
  building something that people want.
* Your efforts at your job get averaged by a lot of other people's
  work.
* Measuring performance for a salesperson is easy. It is hard to do
  the same for others. The designer. The hacker. The marketer. Success
  of a product is a combined effort of all of these combined. But
  there is no way to measure the impact of each group for their
  efforts. As a result, the performance gets averaged out.
* Smaller groups can be measured with greater accuracy. It is easy to
  spot the lazy one among a small group of 10 than it is to spot them
  in a group of 1000.
* A startup is a group of people like you who are willing to work
  harder. Its a group of ambitious people who already know each other
  personally and by reputation.
  
> Steve Jobs once said that the success or failure of a startup
> depends on the first ten employees. I agree. If anything, it's more
> like the first five. Being small is not, in itself, what makes
> startups kick butt, but rather that small groups can be select. You
> don't want small in the sense of a village, but small in the sense
> of an all-start team.

* In a larger group, the average person is an average of the
  population. A hard working person in a large group is getting
  averaged out by average members of the team.
* At decision points, choose the harder problem. It is more
  challenging for a big company to solve a hard problem. By choosing
  the harder problem, you are putting more distance between yourself
  and your competitors. The greater the distance, the safer you are.
* Startups are inherently risky. You would work 30x as hard. But the
  payoff could be anything between zero and thousand times. Chances of
  the payout being zero are much greater.
* Its easy to sell an established startup, because it looks safer
  compared to an early stage one.
* Selling a startup is a good idea. It also allows you to diversify.

> Potential buyers will always delay if they can. The hard part about
> getting bought is getting them to act. For most people, the most
> powerful motivator is not the hope of gain, but the fear of
> loss. For potential acquirers, the most powerful motivator is the
> propsect that one of their competitors will buy you...The second
> biggest is the worry that, if they don't buy you now, you'll
> continue to grow rapidly and will cost more to acquire later, or
> even become a competitor.

* Don't just solve cool tech problems. Solve problems that impacts the
  users. Build products that users want. Not the other way around.
* A startup is an optimization problem: Performance is measured by the
  number of users. This is the only metric that matters.
* But you cannot optimize unless you measure: Ship an initial version,
  get some users and optimize based on the results. There is no point
  in optimizing in the dark. (Premature optimization)
* If you take away the incentive of wealth, innovation grinds to a
  halt. Some governents have done this in the past and continue to do
  so.

### Mind the Gap

* Making money is a specialized skill similar to that of playing a
  game of chess at the highest level.
* But the society is trained to complain when someone outperforms
  everyone else in the skill of making money, while specializing on
  how to play chess seems perfectly normal.
* As kids we think that money is something that is handed down.
* Wealth is not money. Money is a medium used to exchange wealth.
* Wealth needs to be generated.
* A more productive person is paid more for their skills. The more
  wealth that you can generate, the higher salary you can command.

> How much someone's work is worth is not a policy question. It's
> something the market already determines...It may seem unlikely in
> principle that one individual could really generate so much more
> wealth than another. The key to this mystery is to revisit that
> question, are they really worth 100 of us? _Would_ a basketball team
> trade one of their players for 100 random people? What would Apple's
> next product look like if you replaced Steve Jobs with a committee
> of 100 random people? These things don't scale linearly. Perhaps the
> CEO or the professional athlete has only ten times (whatever that
> means) the skill and determination of an ordinary person. But it
> makes all the difference that it's concentrated in one individual.

* Prices are determined by what a buyer wants, and how much s/he is
  willing to pay for it.
* As kids, we are dependent on parents for money which gives us an
  impression from a very early age that wealth is something that is
  distributed rather than created. But our parents had to do an
  equivalent amount of work in exchange for the money that they
  earned. They had to generate value for someone which translated back
  in terms of money in return.
* Wealth is not a zero sum game. You can generate wealth without
  stealing from someone.
* Technnology will increase the gap between the productive and the
  unproductive which is the exact problem it aims to solve - to be
  more efficient.


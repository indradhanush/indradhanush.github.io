---
layout: post
title: Design and Unit Testing
date: November June 2, 2014
author: Indradhanush Gupta
---

<u>
_This post describes my progress into my GSoC project at the end of
the second week. It does not describe the aim of the project. To read
about what I will accomplish over the summer, read this
[previous](http://indradhanush.github.io/2014/05/21/gsoc-project-preview/)
post describing the project._
</u>

Somewhere in a blog post that contained tips on how to apply for GSoC,
I had read that _twelve_ weeks run out fast. Then I had thought that
it must not be necessary. But, this time, _two_ out of _twelve_ weeks
have passed quicker than I had thought they would. Although there have
been exams and some other interruptions in between I have managed to
stick close to my timeline. 

In the last two weeks, I worked out the design pattern with my mentor. 

<div>
    <img src="{{ site.url }}/assets/img/system_design.jpg" height="80%" width="80%"/>
</div>

<br>
What we've done is, separated the entire application into three tiers.

* __Tier 1:__ This is the Application tier. It comprises of
  application logic along with the Database, which is CouchDB here.
* __Tier 2:__ This is the Server, which is the component actually
  exposed to the clients. Thus, any client will only see __Tier 2__
  and not Tier 1. The server sends update messages to __Tier 1__ and
  also receives updates from it. For eg: If a client sends in new sync
  updates, the server sends it to the application tier where it is
  applied or ignored as the case may be. Now when the application has
  some fresh updates, it will send these to the server at __Tier 2__
  along with a list of relevant clients to send it to and finally
  these updates will be sent to the respective clients.
* __Tier 3:__ This is the Client. I don't think there's much to say
  about what it should do. :)

<br>
### Communication Among Tiers ###

* __Tier 1 - Tier 2:__ This is a logical separation for now. That is,
  these will be two independent processes probably on the same system.
  For now, the transport between the two is a DEALER socket at the
  Application/Tier 1 end and a ROUTER socket at the Server/Tier 2 end
  . After asking around in the ZMQ community, a DEALER-ROUTER
  combination felt like the right thing at the moment. It uses the
  _tcp://_ transport for now and might replace it with _ipc://_ in the
  future. Another point I think I should make is that maybe a
  PUSH-PULL combo could come in the long term when there are more than
  one PUSH or PULL sockets. But then there will become a need of
  maintaining separate PUSH-PULL channels for both upstream and
  downstream updates.

* __Tier 2 - Tier 3:__ This is a physical separation and always will
  be. There are two channels at present.
  + __PUB/SUB:__ When the server has fresh updates, it will PUBLISH it
    to all the SUBSCRIBED clients. For this to work, the respective
    clients must subscribe to updates. This is a one way
    communication. Clients cannot talk back in this channel and must
    accept or ignore anything that the server chooses to send to them.
    One problem with this is the __Slow-Joiner-Syndeome__, i.e. for
    clients that join once the server has started publishing updates
    or are slower than the speed at which the server is sending
    updates are bound to miss out on some updates. Thus some of the
    clients will eventually be out of sync. This can be solved with
    the help of the second channel, i.e. the __DEALER/ROUTER__
    channel.
  + __DEALER/ROUTER:__ This channel serves the purpose of direct
    communiation with the server. Here, the DEALER socket sits at the
    client side and the ROUTER socket is at the server side. When the
    client has fresh updates of its own, it will send them via the
    DEALER to the ROUTER at the server. Now coming to the problem
    described in the previous channel. For dealing with slow-joiners,
    when a client misses out on an update, it will send "update
    request" to the server via the DEALER specifying the last update
    that it got correctly. Now the server will send it updates from
    this last point back to the DEALER via the ROUTER at its own end
    thus bringing it up to sync with other clients.

That's it so far related to the design. And, well this is the part
which I have already implemented. 

<br>
### Unit Testing ###

I am not going to write another tutorial on unit testing. The next
lines will be just about my experiences with it:

Prior to this project, I had never written unit tests and I saw it as
something very difficult to get across. This was a mindset thing for
some reason. But now that I had working code and this being a full
fledged open source project, none of the code really stands without
their own unit tests. Thus, I started looking into unittest tutorials
and the documentation at
[http://docs.python.org](http://docs.python.org) ; And surprisingly,
this time it didn't feel so tough or complicated. I wrote basic tests
for starting each instance of the client, server and application and
tests for communicating between each channel.

Honestly, what I had read about in my __Software Engineering__ paper
during the 6th semester, I understood now. I now realized the
difference between unit testing and integration testing. I know what a
stub is. Back then, I had only memorized the definition and blurted it
out on the answer sheet. Practicals have always been a neglected part
of our education system. Anyways, this won't become another blog post
critcizing the Indian Education System. Coming back, unit testing is
fun and now I think I'm going to keep writing tests at every step.

I read at a lot of places that we should first write our tests then
shape our code according to our tests, but I don't think I'm yet ready
for that. That will take some more time honestly. Because I think
being able to do that needs one to be really comfortable with writing
tests and the specifics must be laid out clean as crystal. Neither of
them holds true for me now. So my approach for now will be that I'm
going to add a functionality, write its test and improve it until the
constraints are satisfied.

The tests I have written aren't the most ideal, but I'm happy with
them since this is my first effort. I expect them to improve over
time. One important point I must mention is that tests like sending and
receiving data tend to take a lot of time. And it isn't ideal to
always setup a receiver side before sending some real data for unit
tests. Well, that's the point of unit testing. Each test must be
independent of other modules or functionalities. Also, the entire
testing module should take as less time as possible. This accelerates
development each time we run the tests. Although for now I did have to
set up some stubs for testing receive calls and similar such calls
that tend to depend upon some other components. But, I will most
certainly replace them by using Mock. Mock is a very handy testing library,
that comes with the standard library Python 3.3 onwards. I'm on Python
2.7 so I simply did:

    pip install mock

It lets you mock certain instances and function calls instead of
instantiating real objects and real function calls. This saves the
time taken by that function call and also returns the simulated
results. I took a dab at this, but it wasn't working out yet. Probably
I need to dig in deep with this. But in the coming weeks. In short,
this feels like the right way to move forward with the tests in my project.

It's been fun working on this and am really looking forward to the
coming weeks. Once again, all my code is hosted
[here](https://github.com/indradhanush/U1DB-ZeroMQ-Transport/tree/zmq_architecture).
You are welcome to check it out! :)
    

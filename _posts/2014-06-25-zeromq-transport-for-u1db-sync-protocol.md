---
layout: post
title: ZeroMQ transport for U1DB sync protocol
date: June 25, 2014
author: Indradhanush Gupta
---

In my previous post I had described the architecture of the system I
had designed to implement my sync transport. However, in the past
couple of weeks, there have been some changes to that. Mainly because
there were some hurdles in between and some more hurdles to go around.

The most important one was maintaining backwards compatibility. In a
typical __HTTP__ request, the response is paired to that request. That is,
say we do a __GET__ request, the response is returned immediately by the
server right. Whatever may be the status. __A 200. 404. 500.__ It could be
any of it, but at least the component making the request knows that it
worked or not. It passed or failed. Now the problem (read: advantage)
with __ZeroMQ__ is that request-replies are not paired up like in their
__HTTP__ counterparts. At least that's not the way non-blocking sockets
work. This is the very reason they are of so much use.

The problem I was staring at was the methods that invoked requests
returned some response. My mind instantly went towards __deferreds__. Yes.
Twisted guys make some noise. I asked around but it appears, ZMQ
doesn't yet have anything like that. I mean there are definitely
callback handlers you can attach to your receive and send functions,
but the flow goes a different way in a callback right. When a send is
done, the callback takes over. Quite naturally the method in which the
send occurred has also returned. Now getting that method to
return a __deferred__ would be one way. Such that once the response is
received, the __deferred__ gets fired and my method returns what it
needs to. But again, no such thing in ZMQ yet. Yeah I know. If you are
suggesting to try out __Twisted bindings for ZeroMQ__, I already have that on my
mind. But that's not a priority now. I just want my sync to work out of the
box first. After then I'm going to try and improve it from the inside.

So, reluctantly I had to switch my __DEALER__ in the client for a blocking
__REQ__. Yes you read it right. I chose a blocking socket. As bad as it
sounds, but its actually a much more fitting choice to our scenario.
We needed a lock-step protocol. Now, with the blocking __REQ__ socket, it
will do my job quite simply. Make a request, a very specific one and
wait for a very specific reply. Everything else is silently dropped
and goes into the gutter.

Thus, I now have replaced my DEALER in the client with a __REQ__ socket.
The __ROUTER__ at the server stays. Quite obviously, I don't want my
server to block on every incoming request. ;)

At this point, I would just like to point out, that I am not
considering the PUB/SUB channel of my architecture. Once again, the idea is to
first get the sync working over ZMQ and we can fine tune the semantics
later on. So on we go.

In this post, I will describe the actual sync protocol. Thus, here is
a breakdown of the lock-step sync protocol, but before that, I would
like to tell my readers about some terminologies that are extensively
used:

<br>

### Terminologies ###

* __Source:__ The component initiating a sync is referred to as source.

* __Target:__ The component against which the sync has been initiated is
referred to as the target.

But, for the sake of simplicity, we will consider the __Client__ as
the __Source__ and the __Server__ as the __Target__. Also, __SOLEDAD__
implementation allows sync to be initiated only from the __Client__
end. Thus this approach keeps it simple.

Now, moving on to the sync protocol.

<br>

### The Protocol ###

1. When the __Source__ initiates a sync, it must know when was the
   last time it had synced up with the __Target__, such that the
   source knows exactly the point after which the target has no
   information about.

    For example:

    _Say, the source has documents A, B, and C at generations 5, 8 and
    3 respectively. Lets just say the target has already synced with
    the source at this point._

    Now, if documents A and B move up to generations 9 and 10
    respectively at the source and it now initiates a sync against the
    target. The target will let the source know that the last
    information about these documents it has at generations 5, 8 and 3
    respectively.

    The source will know compare this information against its own
    replica database, and know that it needs to send generations 6
    through 9 for document A and generations 9 through 10 for document
    B, while there is no need to send any information about document C
    as it has not changed at all since their last sync.

    This operation is known as __get\_sync\_info__, The actual
    interchange of information is a little different and in terms of a
    transaction id and generation. But the above example just helps to
    clear out the picture a bit I hope.

    Here, the Source sends a __GetSyncInfoRequest__ message and the
    target replies with all the information packed in a
    __GetSyncInfoResponse__ message.


2. Once the __get\_sync\_info__ operation is completed, the source must
   now send the documents that have changed at the target since their
   last sync.

    Now, in the HTTP based protocol, at this step, all the data was
    added up together as a big stream and sent in one huge POST
    request. Now, this is where the ZMQ implementation differs than
    the one in HTTP. In our implementation, we are splitting up this
    stream into individual documents. Thus once the underlying
    implementation has figured out the documents that need to be sent,
    it will take each document separately and send it as a separate
    request. Only when the target has replied that the document was
    successfully received, will the source send the next document in
    queue. So yes. The documents are sent sequentially now. Although
    there are plans to parallelize this part by sending the documents
    in parallel but for now, we are just focusing on getting the sync
    to work via ZMQ, and focus on that later on.

    This operation is known as __send\_doc\_info__. The source sends
    the documents packed up in a __SendDocumentRequest__ message and
    the target replies with confirmation of inserting that document
    into the underlying database in a __SendDocumentResponse__ message.


3. After all the documents are sent, the source will know request for
   documents that have changed at the target.

    Let us add to our previous example:

    _Say, while docs A and B moved up to generations 9 and 10
    respectively at the source, say another source synced up with the
    target and added a new document D and moved document C from
    generations 3 through 5. Thus this change must also be
    communicated with the first source._

    We can forget about the second source and come back to the first
    source again.
    Rest of the process is similar to that in 2. The source, will now
    send a request to fetch the documents that were changed at the
    target in the meantime. Again, in the HTTP implementation, the
    target prepared a big stream of all the data together and sent in
    a very large POST request. Quite obviously, again in our ZMQ
    implementation we are going to send one document at a time.

    This, once step 2, completes, the target sends a list of documents
    that it is about to send to the source and source will now request
    each of these in independent requests.

    This operation is known as __get\_doc\_at\_target__. But, before
    this operation goes underway, as the source is finished up with
    sending documents and has no more docs to send, it kind-of
    __PINGS__ the target, and lets it know that it has no more
    documents to send. The target __ACKS__ this ping to let the source
    know that it is now ready to send documents, that were changed at
    the target itself, to the source. Along with this __ACK__ signal,
    it also sends a list of the documents paired with their doc_id and
    the doc_generation to the source. Thus the source knows
    beforehand, about the documents that are going to arrive. This
    will come especially handy in case the sync is interrupted in
    between and the source will know exactly which of the documents
    are missing and can recover accordingly. So once this intermediate
    sort-of agreement is established, the source sends a
    __GetDocumentRequest__ message for each of the document in the
    list it received previously and the target replies with the
    contents of the document along with its id, generation etc. packed
    up nicely in a __GetDocumentResponse__ message.

4. Finally, the source records its latest sync state with the target
so that the next time they sync up, the target wont send the docs it
just did.

This operation is known as __record\_sync\_info__. In this operation,
the source sends its sync state in a __PutSyncInfoRequest__ message
and the target confirms the storage of the source sync state by
sending a, you might have guessed by now,  __PutSyncInfoResponse__.

And that concludes the entire lock-step sync protocol. The
__get\_sync\_info__ and the __get\_doc\_at\_target__ comprise of the
part known as the __sync\_exchange__. I'm currently working on this
part of the sync protocol. But typing in all the details of the
protocol kind-of just clears it more in my head.

This blog post will be incomplete without mentioning __Protobuf__. Yup.
I'm using for creating all the message structures I wrote about above.
And one more thing, ZMQ, has this very special socket option, the
__ZMQ\_REQ\_CORRELATE__. What it does is, it forces the REQ socket to pin an
id on every outgoing request. As a result, any response that does not
match the id of the just concluded request, is silently dropped and it
forces the overall semantics to something like a lock-step process in
which every request is locked in a state until the correct response to
it arrives.

That's it for this one. As always,
[here](https://github.com/indradhanush/U1DB-ZeroMQ-Transport/tree/zmq_architecture).
is the code. Go check it out!


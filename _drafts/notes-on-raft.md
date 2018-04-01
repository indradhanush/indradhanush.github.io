---
layout: post
title: "Notes on Raft, the consensus protocol"
categories: blog
tags: ['recurse-center', 'notes']
excerpt: ''
author: self

---

Following are my notes from reading the paper
[In Search of an Understandable Consensus Algorithm](https://www.usenix.org/system/files/conference/atc14/atc14-paper-ongaro.pdf). This
is a paper on Raft, the distributed consensus protocol. Some points
might repeat themselves, but that is okay.

## Introduction ##

* __Strong leader__ - Log entries only flow from leader to other
  servers.
* __Leader election__ - Randomized timers to elect leaders.
* __Membership changes__ - Joint consensus is used.
  
## Replicated State Machines (RSM) ##

* State machines create identical copies on a cluster of servers.
* Systems with a single leader (GFS, HDFS, RAMCloud) use a separate
  RSM for managing leader elections and storing configurations
  (Zookeeper).
* A replicated log is used to build RSM.
* Servers store a log of commands in order. This is the same log that
  is stored on each server. Thus the machines can remain
  consistent and arrive at the same state. This is possible since the
  state machines are deterministic.
* The replicated log __must__ remain consistent. This is the job of
  the consensus algorithm.
  
### Consensus Algorithms ###

* Each node receives commands that get added to the replicated log.
* Each node talks to the other nodes to ensure that the log remains
  consistent (eventually) even if some nodes have failed.
* When the commands have been replicated in the log, the state machine
  in each server runs the command in the _log order_.
* The output of running the commands is returned to the server by the
  algorithm module.
  
### Properties of systems using the consensus algorithm ###

* __Safety__ is ensured. Never returns an incorrect result under
  [non-byzantine conditions](https://en.wikipedia.org/wiki/Byzantine_fault_tolerance).
* The system remains functional as log as the majority of the servers
  are up. For \\( N \\) servers, at \\( N/2 + 1 \\) servers must remain up.
* Servers fail if they,
  - stop.
  - cannot communicate with the other nodes or clients.
* Servers __do not__ depend on timing to ensure log consistency.
* A command is consdered to e complete if the majority of the servers
  have responded. This means that the slower nodes do not impact the
  system's (cluster) performance.

## Raft consensus algorithm  ##

* It elects a leader as the first thing before everything else.
* The leader has full responsibility to manage the replicated log.
* Client sends log entries to the leader. The leader replicates it to
  the other servers.
* The leader tells the server when it is safe to apply the log entires
  ot their state machines.
* Leader decides the position fo a log entry without having to ask
  anyone else.
* A leader can fail or get disconnected from other servers.
* As a result the current *term* ends, a new one begins and a new
  leader is elected.

### Three independent subproblems ###

* __Leader Election__ - Must elect on if the current leader has
  failed.
* __Log replication__ - The leader must accept entries from clients
  and replicate it to the servers. It should also force its decision
  on the servers.
* __State machine safety__ - If *any* server has applied a log entry
  to its state machine, then all the servers must also apply the same
  log entry for that log index.

Raft guarantees that the following properties are true at all times:

* __Election safety__ - There can only be one leader elected for a
  given term. A term is a phase between elections and is valid until a
  leader fails.
* __Leader Append-Only__ - A leader will never overwrite or delete
  entries. It can only append new entries to the log.
* __Log matching__ - If two logs contain an entry with the same
  _index_ and _term_, they are identical for all the entries from the
  _beginning_ and up to that index.
* __Leader completeness__ - If a log entry has been committed in a
  given term, then that particular entry will be present in the logs
  of the leaders for all subsequent terms.

### Raft basics ###

* Typically 5 servers are used.
* A server can have on of the following states:
  - __Leader__: Handles all client requests. If a client sends a
    request to a follower, it forwards the request to the leader.
  - __Follower__: Passive. Only responds to the leader's and
    candidate's requests or forwards client requests to the leader.
  - __Candidate__: A potential leader.
* __Term__ - This is a sequentially increasing integer and exists for
  an arbitrary amount of time. Each term beings with an election and a
  leader is elected. Post which, the leader remains the "leader" for
  the rest of the term. If there is a tie in the election, the term
  ends with no leader and anew term begins.
  
### Flow ###
{% highlight asciidoc %}
                                  System starts
                         +------------------------------+
                         |          Candidates          |
                         |  C1    C2    C3    C4    C5  |
                         +--------------+---------------+
                                        |
                                        |
                                        v
                                    Term starts (T1)
                               Leader Election begins
                                        +
                                        |
                                        |
                                        v
                         +------------------------------+
                         |            Nodes             |
                         |  F1    F2    L3    F4    F5  |
                         +--------------+---------------+
                                        |
                                        |
                                        v
                                 Normal operation
                          (Accept client requests, update log,
                            apply log, respond to request)
                                        +
                                        |
                                        |
                                        v
                                Leader (L3) fails
                                        +
                                        |
                                        |
                                        v
                                   Term 1 ends
                                        +
                                        |
                                        |
                                        v
                                New Term starts (T2)
                               Leader Election begins
                                        +
                                        |
                                        |
                                        v
                         +------------------------------+
                         |            Nodes             |
                         |  C1    C2    --    C4    C5  |
                         +------------------------------+
                                        +
                                        |
                                        |
                                        v
                               Repeat Normal Operation
                            once leader has been elected
{% endhighlight %}


This does not consider a tie during a leader election.

* A term is a logical clock.
* Terms are not constant for all servers. Different servers may switch
  terms at different times.
* Or a server may not participate in an election at all or may remain
  inactive throughout one or more terms as a whole.
* Servers will store the current term number. The term number is
  exchanged whenever servers communicate.
* If a server sees its term lower than another server, it updates to
  the maximum value, i.e. \\( T = max(T1, T2) \\)
* If a leader discovers that its term is out of date, it will __step
  down__ immediately and become a _follower_.
* If a server receives a request with a stale term number, the request
  is rejected.
  
  
### Leader Election ###

* When a server starts up, it is in the _follower_ state by default.
* There are two kinds of RPC:
  - `AppendEntries`
  - `RequestForVote`
* __Heartbeats__ - This is an `AppendEntries` RPC, with an empty body
  (no log entries). The leader is responsible for sending heartbeats
  to all followers to remain the leader.
* A server remains a follower as long as it receives valid RPCs from a
  leader or a candidate.
* __Election timeout__ - If a follower does not receive any request for
  this time duration, it assumes that there are no leaders in the
  cluster, and begins a leader election phase. This is generally set
  to 150-300 ms.

#### Starting an Election ####

* A follower increments its current term and becomes a candidate.
* It votes for itself and requests votes from all the servers
  (`RequestForVote`) in parallel.
* At this point, one of the three outcomes are possible:
  - The candidate wins the election and becomes the leader.
  - A different candidate wins the election instead.
  - There is a tie with no clear winner.

#### Voting ####

* A candidate needs majority of the votes.
* Each server can vote for only one candidate in a specific term. The
  vote goes to the first `RequestForVote` issuer (first come, first served).
* While waiting for votes, a server may receive an `AppendEntries` RPC
  from another server claiming to be the leader. This can happen in a
  network partition.
* If the leader's term, \\( T_l\\) is at least greater than equal to
  the candidate's term, \\(T_c\\) then the candidate steps down to
  become a follower and the leader continues, i.e. \\( T_l \ge T_c \\)
* This situation can arise when two candidates initiate a new term,
  but one of them gets majority of votes before the other.
* If \\( T_l < T_c \\), then the `AppendEntries` RPC is rejected by
  the server.
* Split votes can occur if too many followers become candidates for
  the same term. This means none of the candidates were able to secure
  a majority vote.
* In such a scenario, the candidates will time out and start a new
  election.
* \\(T_c \\) is incremented by `1` and fresh `RequestForVote` RPCs are
  issued.
* However, split votes can keep repeating indefinitely. To avoid this,
  random election timeouts are used. 
* This implies, that the candidates will have a different random
  election timeout, generally between `150-300 ms`. The candidate with
  the smallest value will timeout before the others have timed out,
  and will be able to issue a new `RequestForVote` RPC.

## Log Replication ##

* When a leader is elected, it starts sending `AppendEntries` RPC
  calls.
* When there is consensus on the entry, it applies the log to its
  state machine and responds to the client with the result.
* __Logs__: Each log entry has a term number and a state command. They
  also have an index to identify the position of the entry in the log.
* The leader decides when it is safe to apply a log entry. The log
  entry when applied is said to be _committed_.
* Committed entries are durable and will _eventually_ be applied by
  all the servers in their respective state machines.
* A log entry is committed when the leader has replicated it to a
  majority of the servers. This also commits all previous entries in
  the leader's log (including all entries created by the previous
  leaders).
* The leader tracks the highest known index that was committed.
* This index is sent in all future `AppendEntries` calls and
  heartbeats. Thus any slow server will eventually find out about
  newly committed entries.
* When a follower sees a committed entry in the log, it applies it to
  its own state machine.

### Log matching property ###

* A leader creates only one entry for a given index in a given term.
* The log entries are never changed or deleted. Their position is also
  never altered.
* This implies, that if two entries in two different logs have the
  same index and term, they will have the same command.

### Consistency check for AppendEntries ###

* When sending a request, the term and the index of the previous log
  entry is also sent by the leader.
* If the follower does not find an entry in its log for the
  corresponding term and index already, it rejects the request.
* An acknowledge by a follower indicates that its log matches with
  that of the leader.

### Conflict resolution ###

* In normal operation mode, the logs stay consistent across the
  cluster.
* However, if a leader crashes and a new leader has emerged, the logs
  may become inconsistent. Followers might be missing entries from the
  leader and have extra entries that are not present on the leader.
* Or if there is a network partition with a leader in each partition
  along with their own set of followers.
* To fix this, the leader always forces the followers to accept its
  log entries. Conflicts in the followers are overwritten with entries
  from the leader's log.
* The leader maintains a `nextIndex` for each follower. This is the
  index of the log entry that the leader will send to that follower.
* When a leader is elected, it sets the `nextIndex` as the index after
  the last log entry in its own log, i.e. this value is same for all
  the followers at the start of the term.
* If a follower's log is inconsistent, the leader decrements the
  `nextIndex` for that follower and tries again. This is repeated
  until a matching log entry is found. The index of this log entry is
  the value of `nextIndex` for that follower.
* The worst case scenario is that the entire log of the follower is
  incorrect and it is reset to an empty one.
* When the conflict is resolved, all the subsequent log entries from
  the leader are appended to the follower's log.
* The log will remain consistent throughout the current term.
* When a leader is elected, it starts normal operations right away,
  and all the logs in the followers converge over time if the
  `AppendEntries` RPC fails in the consistency checks.


## Safety

* If a follower is unavailable during a term, \\(T_n \\) and the
  current leader goes ahead with several committed log entries.
* In such a scenario, if the follower becomes the new leader in term,
  \\(T_n+1 \\), it will accept new writes and force the leader of the
  previous term to erase its log entries. This means some committed
  log entries will be overwritten.

### Election restriction

* To fix this problem, we ensure that a leader for any given term must
  contain all the entries committed from all previous terms.
* Raft ensures that all committed entries from previous terms are
  already present on the new leader from the moment of its election
  without having to send them to the leader after it has been elected.
* During the voting period, if a candidate does not have all the
  committed entries, then servers do not vote for it.
* The `RequestVotes` RPC adds this restriction and includes the latest
  log entry. The voter then compares this log entry with its own and
  only issues a vote if the log entry in the `RequestVotes` RPC is at
  least as new as the latest log entry of the voter's state machine.
* If the term of the logs is different, then the log with
  the latest term is considered to be the most up-to-date. But if the
  term is the same, then the longer log is considered as the more
  up-to-date one.`


### Committing entries from previous terms

* If an entry from the current term is replicated on a majority of
  servers, the leader marks it as committed.
* If a leader crashes before committing an entry, future leaders will
  attempt to finish replicating that entry. But a new leader cannot
  assume that an entry from a previous term is committed even if it is
  stored in a majority of servers. The previous leader might have
  crashed after replicating it to the majority but before committing
  it.
* The leader will only commit log entries from the current term by
  checking if the entry has been replicated in majority of the
  servers. As a result all prior entries are also considered to be
  committed. This is the log matching property.

### Safety argument

Let us assume that the Leader completeness is a false property and we
have term, \\( T \\) and leader, \\( L_T \\), which commits a log
entry \\( E \\) but does not get replicated to a node that is also a
leader in a future term.

For the nearest term after \\( T \\) such that \\( U > T \\) and
leader, \\( L_U \\) that does not have the entry \\( E \\).

But, \\( L_T \\) replicated the entry to a majority of the servers and
\\( L_U \\) received votes from the majority of nodes to be elected a
leader.

This implies, that there exists at least one server that received the
entry \\( E \\) and voted for \\( L_U \\) as well.

Also the voter received entry \\( E \\) first and then made the vote
to \\( L_U \\). \\( E \\) has term \\( T \\) as defined above and if
it received entry \\( E \\) after casting the vote, the entry \\( E
\\) should have term \\( U \\) instead. As a result the entry would
have been rejected since \\( U > T \\).

Thus we can safely conclude, that the voter has stored entry \\( E \\)
and if the voter voted in favor of \\( L_U \\), the leader must have
had its log at least as new as that of the voter (log matching
property).

Also, if \\( L_U \\) had the last element of the voter in its log, it
implies that, the length of the log of \\( L_U \\) \ge length of the
log of the voter.

which means that log of \\( L_U \\) has all the elements that are
in the log of the voter.


But, the voter already has the entry \\( E \\), which means \\( L_U
\\) also has \\( E \\). However we assumed that the leader \\( L_U \\)
does not have the entry \\( E \\). This is a contradiction and thus an
incorrect assumption.

And finally, if the last log entry of \\( L_U \\) has a term greater
than that of the voter, it implies that the term of the last log entry
of \\( L_U \\) is greater than \\( T \\) since the voter at least
contained the term \\( T \\)


### Follower and candidate crashes

* If a follower or candidate crashes then the leader retries the
  `RequestVotes` and the `AppendEntries` RPCs indefinitely. This
  implies that if the crashed server recovers, the RPC calls will
  succeed.
* If the server crashes after completing the RPC but before responding
  back to the leader it will receive the applied RPC again when it
  restarts (since the leader will retry indefinitely).
* However RPC calls are idempotent, that is they can be safely
  repeated without any side effects. If a server receives an
  `AppendEntries` RPC which it has already completed in the past, it
  will ignore this. This is possible since the log entry is already
  present in its own log, which can which can be identified by the
  index and the term of the corresponding log entry.

### Timing and availability

* If message exchanges take longer than the time between server
  crashes, we will never be able to elect a leader.
* The following is a timing requirement for Raft to function:
  \\[ broadcastTime \\ \< \< \\ electionTimeout \\ \< \< \\ MTBF \\]
* `broadcastTime`: Average time required for the servers to send RPCs
  in parallel to all the servers in the cluster and receive their
  responses.
* `electionTimeout`: Time for which a server waits for a leader to be
  elected. If no leader is elected within this time, the server starts
  a new term and a new election is initiated.
* `Mean time between failures (MTBF)`: Average time between failures
  for a single server.
* `broadastTime` should be an order of magnitude lesser than the
  `electionTimeout`.
* This implies that servers can send heartbeats and RPCs before a node
  times out and initiates an election. This also minimizes the chance
  of a split vote.
* The `electionTimeout` should be an order of magnitude lesser than
  the `MTBF` for the system to work.
* If the leader crashes, the system becomes unavailable for
  approximately the election timeout, since at this point no client
  requests can be safely processed in the absence of a leader.
* The `broadcastTime` and `MTBF` are derived properties of the system
  while the `electionTimeout` should be determined by us.

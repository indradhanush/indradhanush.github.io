---
layout: post
title: 'A Helm debugging story'
categories: blog
tags: ['programming', 'kubernetes', 'helm', 'kinvolk']
excerpt: 'A description about an annoying bug and the lessons learned from it'
date:  19 April, 2018
author: self
---

I've been working on a Kubernetes service broker at work, specifically
the [Habitat service
broker](https://github.com/kinvolk/habitat-service-broker/). To put it
mildly without diving deep into the details, the Habitat service
broker is an
[OSB](https://github.com/openservicebrokerapi/servicebroker) compliant
piece of software whose job is to run apps built with
[Habitat](https://www.habitat.sh/) in a
[Kubernetes](https://kubernetes.io) cluster. The service broker is
deployed via [Helm](https://github.com/kubernetes/helm/), which is a
package manager for Kubernetes. What each of these are built for is
not exactly important as is the debugging story that I'm about to
describe. Let's reserve that for a future post(s).

I had reached a checkpoint of sorts where I was able to successfully
create and apply a custom configuration on a redis instance that was
provisioned via the broker in the Kubernetes cluster. Once the [pull
request](https://github.com/kinvolk/habitat-service-broker/pull/7/)
was merged, I started working on another feature that was to undo this
custom configuration. This required me to tinker with the
[RBAC](https://kubernetes.io/docs/admin/authorization/rbac/) rules,
which is an authorization mode available in Kubernetes. I had to add
new rules for accessing additional API endpoints. After writing the
code for this and trying to apply the change on my cluster for the first
time, I started seeing an error that looked like this:

```
Error: release habitat-service-broker failed: clusterroles.rbac.authorization.k8s.io "habitat-service-broker-habitat-service-broker" already exists
make: *** [Makefile:35: deploy-helm] Error 1
```

Even if someone has no experience in Kubernetes, it should be
relatively straightforward to understand this error at a higher level,
which is that my code is trying to create a resource named
"habitat-service-broker-habitat-service-broker" and failed since it
already exists in the cluster. To elaborate on the error a little, I
am trying to create a new `clusterrole` object via Helm, our protagonist
of this story.

My first instinct was that there was something stale lying around on
my Kubernetes cluster from my previous testing and starting on a fresh
cluster would fix it. No surprises there that starting a new cluster
did not fix the bug. I was running my cluster via
[minikube](https://github.com/kubernetes/minikube), which is a tool to
run Kubernetes clusters locally. After a lot of tinkering and without
any success I shared a set of instructions to reproduce the bug with
my colleagues. But surprisingly the code was working fine for them
without any signs of the bug. At this point I thought that there was
something wrong with my minikube setup or that it had some other
configurations that I didn't know about. 

I decided to use [kube-spawn](https://github.com/kinvolk/kube-spawn)
which is another tool to quickly setup a Kubernetes cluster but with
some differences than minikube (you can read more about it
[here](https://kinvolk.io/blog/2017/08/introducing-kube-spawn-a-tool-to-create-local-multi-node-kubernetes-clusters/)). However
this bug seemed to be omnipresent and it showed up on the kube-spawn
cluster as well. By this point I had spent more than two days on this
bug and was beginning to be think that this was something sillier than
expected.

Helm, like we mentioned previously is a package manager for Kubernetes
and uses "charts" for defining services and their properties. The RBAC
related changes are also part of the charts and is defined using
`yaml` files.

Not knowing where to look next, I asked my colleagues Iago and Lorenzo
to pair with me on this and I set upon to reproduce the bug from
scratch. During the pairing session, they asked to look at the file
that contained the `clusterrole` definition.

Here's what the corresponding directory looked like:<sup>[1]</sup>

{% highlight shell %}
$ tree $PROJECT_ROOT/charts/habitat-service-broker/templates/
charts/habitat-service-broker/templates/
├── broker-deployment.yaml
├── broker-service.yaml
├── broker.yaml
├── clusterrolebinding.yaml
├── #clusterrole.yaml#
├── clusterrole.yaml
├── _helpers.tpl
└── serviceaccount.yaml

0 directories, 8 files
{% endhighlight %}

Notice the odd file starting and ending with a `#`? That's an Emacs
buffer for the original file named `clusterrole.yaml`. It turns out
that Helm, picks up all files that "look like" yaml from the charts
directory. As a result it was first applying the contents of
`clusterrole.yaml` and then those of `#clusterrole.yaml#`, or the
other way round. Either way, when it got to the second file that's
when the command would fail. Emacs buffers normally get deleted when a
file is saved, and this might have been leftaround from a crashed
Emacs session. Deleting this buffer fixed the bug.

I felt a mixture of emotions at this point: anger, stupidity,
agitation, happiness and relief. It took me sometime to get back to my
original problem statement though.

<a href="https://twitter.com/indradhanush92/status/986186213001490434">
    <img src="{{ site.url }}/images/a-helm-debugging-story/tweet-debugging.png" />
</a>


I was stuck with this for more than two days and was eventually able
to fix it over a ten minute video call thanks to my colleagues. Even
though I found Helm's approach to dealing with template files a bit
silly, I learned (and relearned) the following things out of this
experience:

- I should configure my editor to store buffers outside my working
  directory.
- An extra pair of eyes is always a great idea.
- If you're stuck seeing the same error for a long enough time, ask
  for help sooner rather than later. Although a different error from
  your last one can be thought of as progress. This is especially
  relevant if you're worried about asking for help "too much".
- If an error cannot be reproduced on someone else's machine it
  becomes much harder for others to help you unless you invite them
  over to your machine.
- If a bug sounds like a simple oversight somewhere rather than
  something obscure and non trivial, it probably is.

That's all for now, thanks for reading and I'll let you enjoy this
xkcd comic for now:

<img src="https://imgs.xkcd.com/comics/debugging.png" />


<br>
<sup>Footnotes:</sup>
<br>
<sup>[1]: I used Emacs for navigating the directory, but I used tree
here for better representation.</sup>

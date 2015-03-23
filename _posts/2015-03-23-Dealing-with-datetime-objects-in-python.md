---
layout: post
title: Dealing with datetime objects in a Python + Postgres environment
date: March 23, 2015
author: Indradhanush Gupta
redirect_from: "/2015/03/23/Dealing-with-datetime-objects-in-python/"
---

I've been wanting to roll out this post for quite some time but it
kept evading me. In fact I had bulk of this post written out a long
time back, just finishing it up was missing.

So, in this post I will be talking about how to deal with datetime
objects in `Python` and how to interact with them when you are storing
it in `Postgres`. The aim of this post is to avoid all error
prone methods of timezone conversion of datetime objects as well as
those of storing them.

Datetime objects are probably one of the most used in any application.
One obvious thing you'd need when designing a model, is probably the
date of creation field. It actually gets trickier to tackle them as
your models mutate<sup>1</sup> after a while, and as surprising as it
may sound, it is also fairly easy to miscalculate your datetimes,
especially when you are handling multiple timezones. Ignoring this
**will** bite you back hard someday.

<br>
## **So what's so complicated about a simple datetime?** ##

First a little bit of background before we dive in. Their are two
kinds of `datetime` objects. **Timezone aware** and **Timezone
unaware** or **Naive** objects. You can skip this part if you know the
difference between the two.

A **timezone aware** object is one which has a timezone information
associated to it. That is, looking at such an instance, we will be
able to find out the corresponding time in another time zone. Also, at
any given moment in time, we can look this object up and identify
which exact moment in time *(seconds since epoch<sup>2</sup>)* does it
represent.

On the other hand, a **timezone unaware** or a **naive** object has no
clue what moment in time it represents.

So if I am in India and say that the time is **10 AM**, the person sitting
next to me will know that it is 10 in the morning here in India. S/He
can correctly identify it because they are also in India along with
me. But if I say the same thing to a friend over the phone and ask them
to second guess my location, s/he will surely be not able to answer my
question. However, if I say that the current time is **10 AM, IST**, my
friend should be able to identify that I am somewhere in India,
precisely from the timezone information I supplied. The analogy should
be clear by now. I advise to read this section again if it isn't.


<br>
## **What does Postgres want?** ##

Postgres will store any timezone aware datetime in **UTC** but will
display it in the time zone of the server, session or the user.

You can inspect the `timezone` setting for **postgres** by logging
into the `psql` shell and running the following command:

```
dhanush=# show timezone;
   TimeZone
--------------
 Asia/Kolkata
(1 row)
```

To set a custom timezone, use the following command:

```
dhanush=# set timezone='UTC';
SET

dhanush=# show timezone;
 TimeZone
----------
 UTC
(1 row)
```

Here's the same set of records in both `IST` and `UTC` respectively.

**IST**

```
dhanush=# select created_at from users;
            created_at
----------------------------------
 2014-09-11 12:14:33.867216+05:30
 2014-09-15 12:23:27.384904+05:30
 2014-09-15 12:24:29.668802+05:30
 2014-09-19 18:27:27.426808+05:30
 2014-09-23 18:18:37.022816+05:30
 2014-09-25 13:04:04.779181+05:30
 2014-10-16 18:30:14.939262+05:30
(7 rows)
```

**UTC**

```
dhanush=# select created_at from users;
          created_at
-------------------------------
 2014-09-11 06:44:33.867216+00
 2014-09-15 06:53:27.384904+00
 2014-09-15 06:54:29.668802+00
 2014-09-19 12:57:27.426808+00
 2014-09-23 12:48:37.022816+00
 2014-09-25 07:34:04.779181+00
 2014-10-16 13:00:14.939262+00
(7 rows)
```

So it is clear that postgres shows you any timezone aware datetime in
the timezone that is set.

**At this point, I would like to make it clear that I did NOT research
about timezone unaware datetime entries in postgres.**


<br>
## **Okay, so what does Python want?** ##

Python supports both `naive` objects as well as `timezone aware`
objects. But, it is advised to **never** use timezone naive datetime
objects. The reason being, that a naive datetime object gives the end
user no information about the moment in time that it represents.
Datetime objects become more useful when they contain a timezone.

<br>
### **Hello pytz, bye bye errors!** ###

[pytz](http://pytz.sourceforge.net/) is an incredibly useful library
for handling timezones in `python`. It does most of the work for you.

<br>
### **I have a naive datetime object. Please help me!** ###

Take a look at the snippet below and the error that it produces:

```
In [13]: import pytz

In [14]: from datetime import datetime

In [15]: now = datetime.now()

In [16]: now
Out[16]: datetime.datetime(2014, 10, 16, 14, 17, 51, 720507)

In [17]: ist = pytz.timezone('Asia/Kolkata')

In [18]: ist.localize(now)
Out[18]: datetime.datetime(2014, 10, 16, 14, 17, 51, 720507, tzinfo=<DstTzInfo 'Asia/Kolkata' IST+5:30:00 STD>)

In [19]: now.astimezone(ist)
---------------------------------------------------------------------------
ValueError                                Traceback (most recent call last)
<ipython-input-19-6bce1c9dbf37> in <module>()
----> 1 now.astimezone(ist)

ValueError: astimezone() cannot be applied to a naive datetime
```

In the last command you can see that `astimezone` works on `aware`
objects where as `localize` works on `naive` objects. The error
message is self explanatory so I wouldn't go any deeper into this.

<br>
### **So, why don't you use datetime.datetime.replace instead?** ###

One common error in converting `naive` objects to `aware` ones is the
use of `datetime.datetime.replace`. Here's a short example
demonstrating why it isn't ideal.

```
In [38]: ist
Out[38]: <DstTzInfo 'Asia/Kolkata' LMT+5:53:00 STD>

In [39]: stupid_utc_now = datetime.utcnow()

In [40]: stupid_utc_now
Out[40]: datetime.datetime(2014, 10, 16, 14, 26, 57, 150167)

In [41]: stupid_utc_now.replace(tzinfo=ist).utcoffset()
Out[41]: datetime.timedelta(0, 21180)
```

If you look carefully, the information about `ist` is `LMT+5:53:00
STD` which you might think is incorrect as the offset of `IST` from
`UTC` is `+5:30` and not `5:53`. Bug? Not really. Initially `IST` was
declared to be `+5:53` ahead of `UTC` which was corrected later on to
be `+5:30`. But `replace` doesn't really know about this and thus you
can see the offset as `21180` seconds instead of `19800` seconds.

Now take a look at the following snippet:

```
In [42]: intelligent_utc_now = datetime.utcnow()

In [43]: ist.localize(intelligent_utc_now).utcoffset()
Out[43]: datetime.timedelta(0, 19800)

In [44]: old_days = datetime(1700, 6, 18)

In [45]: old_days
Out[45]: datetime.datetime(1700, 6, 18, 0, 0)

In [46]: ist.localize(old_days)
Out[46]: datetime.datetime(1700, 6, 18, 0, 0, tzinfo=<DstTzInfo 'Asia/Kolkata' LMT+5:53:00 STD>)
```

Now carefully note the two offsets of `intelligent_utc_now`. You can
see the correct offset this time. Whereas, for `old_days`, when
localized to **IST**, the offset is `5:53`. That's the wonder of `pytz`.
Depending on the time, it returns the offset accordingly. `+5:53` for
a really old date and `+5:30` for a date after the time that the
offset for **IST** was corrected.

Finally, if you want to work with the current time as a timezone aware
object, which once again I highly advise you to use instead of a naive
timezone object, you should do the following:

```
In [47]: datetime.now(pytz.timezone('Asia/Kolkata'))
Out[47]: datetime.datetime(2014, 10, 20, 13, 25, 14, 121485, tzinfo=<DstTzInfo 'Asia/Kolkata' IST+5:30:00 STD>)
```

And, if you need the current time in **UTC**,

```
In [48]: datetime.now(pytz.utc)
Out[48]: datetime.datetime(2014, 10, 20, 7, 55, 17, 817783, tzinfo=<UTC>)
```

or,

```
In [49]: pytz.utc.localize(datetime.utcnow())
Out[49]: datetime.datetime(2014, 10, 20, 7, 55, 23, 25311, tzinfo=<UTC>)
```

But in my opinion the first approach looks way more clean. For fans of
`datetime.datetime.replace`, you can still use it for creating a
`datetime` object in **UTC** without any problems.

<br>
### **TL;DR** ###

**Dos**

* Always use `aware` datetime objects.
* When dealing with `naive` objects, use `localize` to add timezone
* When you are converting timezones use `astimezone`.

**Donts**

* Create `naive` datetime objects.
* Use `datetime.datetime.replace` for adding or manipulating timezone
  information on a `datetime` object. Except when you use it to
  instantiate a datetime object in **UTC**.


<br>
### **Footnotes** ###

**[1]**
Read
[this](https://medium.com/@landongn/12-years-later-what-i-ve-learned-about-being-a-software-engineer-d6e334d6e8a3)
post here if you want to know why I say your models mutate instead of
change.

**[2]** [http://en.wikipedia.org/wiki/Unix_time](http://en.wikipedia.org/wiki/Unix_time)

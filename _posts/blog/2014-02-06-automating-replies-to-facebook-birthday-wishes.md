---
layout: post
title: Automating Replies to Facebook Birthday Wishes
categories: blog
tags: ['python', 'regex', 'facebook']
excerpt: 'Using regular expressions to detect happy birthday wishes while factoring in sms language variants.'
date: February 7, 2014
author: self
---

So, on my birthday this year I was expecting a lot of wishes on facebook. I mean who doesnt right? And I wanted to automate the replies instead of going through them manually. So I started looking up the facebook graph api and fql, both of which, now that I have had a brief interaction with, totally rock!

It was easy right. I only needed to go through two steps:

* **GET** all the posts on my wall between **00:00 hours** to **23:59 hours** on **1st February 2014**.
* Scan through each of them, if it was a birthday wish, **POST** a generous thank you.

Now, this is where it was a little tricky. So this post will focus on how I did the second step. For the rest, you can consult the [Facebook API Documentation](https://developers.facebook.com/docs/reference/apis/) or check out my code [here](https://github.com/indradhanush/birthday-thanks).

My friends, some of them, aren't really used to forming complete words, leave apart sentences. So the challenge was not just to form a regular expression for "Happy Birthday" but also for all possible short forms of Happy Birthday. Ones like these:

  * Hpy Bday!
  * Hhhhppppyyyyy Bddaeee...

This list could be anything that sounds marginally close to a birthday wish. Oh and not to forget, a couple of variants like:

  * Many many happy returns of the day.
  * Best wishes.

Hell! I even got a **HBD** in one of the posts! Intensifies my reason to hate sms language even more. But then, thats what programmers should do right? Fix the problems (read bugs) at hand right?

And with a comprehensive [data set](http://bpaste.net/show/176299/) at my disposal, I set off.

So I broke down the problem into smaller ones. Initially I only focussed on forming a regex for **Happy** and needless to say also for any other sms variant of the word. And with python, my favourite and most powerful weapon in my arsenal yet, I formed the following regex:

    (h+a*p+i*y*e*)

Which means:

* **h+** - One or more occurrences of **h**.
* **a*** - Zero or more occurrences of **a**.
* **p+** - One or more occurrences of **p**. Eg: happppyyy
* **i*** - Zero or more occurrences of **i**. Eg: hppiiiii!!
* **y*** - Zero or more occurrences of **y**. Eg: hppyyy..
* **e*** - Zero or more occurrences of **e**. Eg; haappeeee..

And I ran it against the data set. It failed to catch the following wishes:

    many many happy returns of the day sensai.

    many many happy returns of the day

    many happy returns of the day :)

    many many happy returns of the day buddy

    hbd..sensei..

    many happy return`s  of the day

    netcamp wishes you a happy wala birthday

    wishes

    wish u many many happy returns of the day


The reason was quite clear. **Happy** may not be the first word. And it failed for such cases. So all I had to do was add a little **".*"** before the regex, which essentially means anything before the regex. Thus I got this:

    (.*h+a*p+i*y*e*)

And this time it only missed out for the following:

    hbd..sensei..

    wishes

But I couldn't possibly rely on just this regex. Although my posts all but contained wishes only, it may not be the case always. There could be a post from a friend which could say:

    Thanks for recommending Happy Days. Awesome watch!

Got the point right?

So I wrote one for **Birthday** and all other possible variants. It was:

    (.*b([irthday]|'|(u*(d+(a+e+|a+y+|y+)))))

What the hell is that! Wait I can explain it.

* **.*** - For anything before that regex.
* **b** - Match for the character **b**.
* **[irthday]** - To match **birthday**"
* **|'** - The pipe indicates an OR. So after **b** it will either look for **irthday** or **'**.
* **(u*(d+(a+e+|a+y+|y+)))** - I will break this down further:
  * **u*** - Zero or more instances of **"u"**. Eg: buuddddayyy!
  * **d+** - At least one instance of **"d"**. 
  * **(a+e+|a+y+|y+)** - Any one of the following:
    * **a+e+** - One or more occurrence of **"a"** and one or more occurrence of **"e"**. Eg: bdae.
    * **a+y+** - One or more occurrence of **"a"** and one or more occurrence of **"y**. Eg: bday.
    * **y+**- One or more occurrence of **"y"**
    
I ran only this regex against the data set and it failed for these:

    many many happy returns of the day sensai.

    many many happy returns of the day

    happy b.day......

    many happy returns of the day :)

    many happy return`s  of the day

    wishes

    wish u many many happy returns of the day


So it missed out for **"happy returns of the day"** type wishes with one exception. The third one - **"happy b.day......"**
So before moving on, I modified it to expect one of **'** or **.** after **b**. Although you can skip this, a **"."** between **"b"** and **"day"** is actually rare. But I felt like doing it at the time. So for "birthday" I ended up with this:

    (.*b([irthday]|['.]|(u*(d+(a+e+|a+y+|y+)))))
   
Now I wrote another regex for "returns", which is very simple:

    (.*return(s|'s))

Now I combined the above three regular expressions to form one that logically looked like this:

    [Match "happy" and then look for either "birthday" or "returns"]

Thus the end product:

    (.*h+a*pi*y*e*(.*b([irthday]|['.]|(u*(d+(a+e+|a+y+|y+))))|(.*return(s|'s))))

Now I ran this against my data set one last time and it missed out the following:

    hbd..sensei..

    many happy return`s  of the day

    wishes

So I kept a manual override switch in my code for expressions for which my regex failed. Just a failsafe so I could manually force my code to comment a generous **Thanks** if it indeed was a birthday wish that my regex failed to match. Note the second one contains a back tick (`) and not a single quotation mark.

I am sure there is still some scope of refining the regex even futher for some corner case I may missed because in the end my tests are only limited by the data set I have. Please do let me know if you spot one! Until then, Happy Coding!


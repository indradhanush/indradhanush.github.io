* Erlang `atoms` are not garbage collected. Never create `atoms`
  dynamically. Its a tool for the developer. Not the program. This
  also implies that generating atoms dynamically via code is a bad
  idea, since you do not have complete control over how many atoms are
  going to be present in your program.

* If you have a function with different arity, say `foo/2` and
  `foo/3`, instead of terminating the final declaration of `foo/2`
  with a `semicolon (;)`, terminate it with a `dot (.)`. Not doing
  this results in a `head mismatch error`. This seems to be a very
  common mistake for beginners, going by this StackOverlow question:
  http://stackoverflow.com/questions/1802680/what-does-the-head-mismatch-compiler-error-mean#1802900
  
* Erlang isn't the best at string handling. That's how you write the
  string "ABC":

``` Erlang
1> [65, 66, 67].
"ABC"
```

* A binary string is more efficien than a string constructed above. A
  binary string is like an array in C, while the above string is like
  a linked list. Syntax: `<<"hello, world!">

* A built-in function (BIF) like `hd` or `tl`, which return the head
  and the tail of a list respectively, are not implemented in pure
  Erlang. Instead they are written in C. This was done either to
  improve performance, or it was not possible to implement them in
  native Erlang.
  
* Improper vs proper lists: `[1 | 2, 3]` is an improper list. While
  `[1, 2, 3]` is a proper list. Both are valid syntax. But an improper
  list won't work when used with standard Erlang functions like
  `length()`.
  
* Guards: `, and ;` mean `andalso` and `orelse` respectively. But they
  are different. Eg:
  - `X >= N; N >= 0` => If the `X >= N` has an error, the second part
  can still be evaluated. (`andalso`)
  - `X >= N orelse N >= 0` => If the `X >= N` throws an error, the
    second part will be skipped.

* Only `andalso` and `orelse` can be used for nesting in *guards*.

* `if` must have one `true` branch, since everything in Erlang must
  return. This applies to `if` as well.

    

  

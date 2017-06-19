* Erlang `atoms` are not garbage collected. Never create `atoms`
  dynamically. Its a tool for the developer. Not the program.

* If you have a function with different arity, say `foo/2` and
  `foo/3`, instead of terminating the final declaration of `foo/2`
  with a `semicolon (;)`, terminate it with a `dot (.)`. Not doing
  this results in a `head mismatch error`. This seems to be a very
  common mistake for beginners, going by this StackOverlow question:
  http://stackoverflow.com/questions/1802680/what-does-the-head-mismatch-compiler-error-mean#1802900
  

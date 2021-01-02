# Init capture (capture-by-move)

The containers, as well as other tools of the Standard Template library are expensive to copy, but cheap to move. C++14 offers us a chance to move these objects into the lambda's closures. If we can avoid unncessary copies, then we rather move these type of objects.

With the help of init captures, we have the power to specify:

1) "**the name of a data member** in the closure class generated from the lambda and

2) **an expression** initializing that data member"

A init capture looks like the following:

``` c++
[<variable> = <expression>] {...}
// for example: 
[pw = std::move (pw)] {...}
```

Inside the initialization capture syntax, the scope of the left operand is different from the scope of the right operand. The scope of the left is the same as the scope of the closure class, while the scope of the right is the same as the scope where the lambda is defined.

If a local variable is defined just so it can be passed to a lambda, then it is unnecessary, since C++14 can initialize that variable, and limit its scope to the lambda's closure.

``` c++
[pw = std::make_unique<T> ()] {...}
```

### Up next:

*Writing init capture in c++11, where it is not supported directly in the lambda syntax.*

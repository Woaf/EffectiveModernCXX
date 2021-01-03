# Init capture (capture-by-move)

## Init capture in C++14

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

## Generalized lambda capture C++11

Since C++11 does not support init captures, we have to use other ways to achieve this.

Lmabda expressions are in fact just *syntactical candies* for **functors**. In C++, *functors are just classes with an overloaded `operator ()` (function call operator)*. (The real definition of functors can be found in the field of category theory and as a programming term it is mainly used in functional programming - they are operations on an object.)

As a consequence, we can create our own *init capture* in C++11 with functor classes.

## Emulating move capture in C++11

Move capture can be emulated in C++11 by:

1) **moving the object to be captured into a functionobject produced by `std::bind`** and

2) **giving the lambda a regerence to the "captured" object**

```c++
// C++11 use std::bind for move capture in lambdas
auto func11 = std::bind ([] (const std::vector<double>& data) {
    // use data ...
}, std::move (data));
```

`std::bind` produces function objects (or "bind objects" by Scott Meyers). The first argument of `std::bind` is a functor (callable object). Further arguments are parameters that will be passed to that function object. The object returnd by `std::bind` **contain copies of the values that are passed into it**. Lvalue arguments are copy constructed inside the bind object, while rvalue arguments are move constructed.

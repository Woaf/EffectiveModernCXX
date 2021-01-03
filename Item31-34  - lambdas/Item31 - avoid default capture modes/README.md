# Lambda variable caputre modes

## Catpure by reference

### Default caputre `[&] () {}`

Capturing local variables by reference invokes the possibility of having dangling references. The closure (functor) object will contain references to the local variables declared inside the scope of the lambda function. If the lambda function works on an object which fall outisde of this scope, then the references to those local variables will be outdated right after the lambda returns.

### Explicit caputre `[&<variable>] () {}`

Explicitly capturing variables does not elliminate the previously described problem, however it makes it easier to see which variables the lambda expression depends on. It alsoreminds us on-the-fly that the lifetime of the explicitly decalred variable exceeds that of the lambda's colsures.

### Immediately used lambdas

There are cases when the previously described problem won't exist - such as immediately used closures. Under such circumstances, the lambda will not live longer than the captured variable and using default capture-by-referece mode is safe. **However**, code is meant to be read by humans, and therefore if someone may find such a lambda expression to be useful somewhere else, then the *copy-pasted* code might not meet these criteria. **"There is nothing in the capture clause to specifically remind [us] to perform lifetime analysis on the [catured variables].**

**Simply put, its just better practice to explicitly declare captured variables in lambda expressions.**

## Capture by value `[=] () {}` and `[<value>] () {}`

Capturing local variables (or whatever, that is inside the scope of the lambda expresion) mean that these variables will be copied into new local variables inside the body of the lambda's closure - exactly like a function taking a *non-reference* parameter.

First, it may seem tempting to use this capture mode to overcoem the problem with the dangling references, but it will not help the case if the captured variable is a pointer (especially `this`).

A bigger problem arises from using `static` variables. **Static variables are not captured by lambdas**, and therefore the `[=]` notation might be very misleading. In other words, default by-value caputre might falsely suggest that lambdas are self-contained.

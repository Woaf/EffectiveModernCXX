# Capture by reference

## Default caputre `[&] () {}`

Capturing local variables by reference invokes the possibility of having dangling references. The closure (functor) object will contain references to the local variables declared inside the scope of the lambda function. If the lambda function works on an object which fall outisde of this scope, then the references to those local variables will be outdated right after the lambda returns.

## Explicit caputre `[&<variable>] () {}`

Explicitly capturing variables does not elliminate the previously described problem, however it makes it easier to see which variables the lambda expression depends on. It alsoreminds us on-the-fly that the lifetime of the explicitly decalred variable exceeds that of the lambda's colsures.

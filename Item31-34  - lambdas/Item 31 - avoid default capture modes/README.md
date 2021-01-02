# By-reference capture

Capturing local variables by reference invokes the possibility of having dangling references. The closure (functor) object will contain references to the local variables declared inside the scope of the lambda function. If the lambda function works on an object which fall outisde of this scope, then the references to those local variables will be outdated right after the lambda returns.

# Prefer lambdas over `std::bind`

In the previous sections we saw how we can facilitate `std::bind` to achieve *capture-by-move* in C++11. In this section, we outline why using lambda expressions is more pragmatic.

The first reason is code clarity. Lambdas are easier to read than `std::bind` object definitions.

As we can see in the example code in `main.cpp`, the parameter declaration of the bind object is confusing and not evident. Furthermore, neight it is correct. In the case of the lambda expression, `stead_clock::now ()` will be evaluated when `SetAlarm` is called. However, in the latter case this is evaluated when `std::bind` is called. The difference between the argument beiing evaluated when `SetAlarm` or when `std::bind` is called, is... well, alarming.

To avoid this problem, we can play around with the parameters, so they are not evaluated immediately. However, the syntax just makes everything more confusing.

``` c++
using namespace std::chrono;
using namespace std::literals;
// using lambda
auto setSoundL = [] (Sound s) {

    SetAlarm (steady_clock::now () + 1h, 
              s, 
              30s);
}; 

// VS.

// type parameter may be ommitted from std::plus in this case
using namespace std::placeholders;
auto SetSoundB = std::bind (SetAlarm), 
                            std::bind (std::plus<steady_clock::time_point> (), steady_clock::now (), 1h),
                            _1, 
                            30s);
```

Things get even more interesting when the `SetAlarm` function is overloaded. Suppose we overload `SetAlarm` with an extra parameter. The lambda would still work by resolving the three parameter definition of `SetAlarm`. Using `std::bind` on the other hand would fail to compile, because the bind does not have anything other than the function name, which became ambiguous. To make it work, we could introduce a type alias to the signature of the three-parameter SetAlarm function, and `static_cast` the first parameter that is passed to `std::bind`.

``` c++
using namespace std::chrono;
using namespace std::literals;
// using lambda (same as before)
auto setSoundL = [] (Sound s) {

    SetAlarm (steady_clock::now () + 1h, 
              s, 
              30s);
}; 

// VS.

// type parameter may be ommitted from std::plus in this case
using namespace std::placeholders;
using SetAlarm3ParamType = void (*) (Time t, Sound s, Duration d);
auto SetSoundB = std::bind (static_case<SetAlarm3ParamType> (SetAlarm)), 
                            std::bind (std::plus<steady_clock::time_point> (), steady_clock::now (), 1h),
                            _1, 
                            30s);
```

Things are getting pretty ugly, just to force `std::bind` to work.

When we are using lambdas, the function invocation of `SetAlarm` inside the lambda closure is a simple function call, which may very well be inlined by the compiler. This is *not* the case when we use `std::bind`, since the function is called through a function pointer. **Compilers may generate faster code with lambdas than using`std::bind`.**

More examples of how lambdas can be much more comfortable:

``` c++
// using lambda
auto betweenL = [lowVal, highVal] (int val) {
    return lowVal <= val && val <= highVal;
};

// VS. using std::bind
auto betweenB = std::bind (std::logical_and<bool> (), 
                           std::bind (std::less_equal<int> (), lowVal, _1), 
                           std::bind (std::less_equal<int> (), _1, highVal));
```

Further problem emerge with the semantics of `std::placeholders`. How are the passed to a function - by-value of by-reference? By default they are passed by value, and we have to indicate pass-by-reference by writing `std::ref (...)` if we want it to be passed by reference. With lambdas, we can clearly indicate the capture mode, but this is not stand true for placeholders.

## "Compared to lambdas, then, code using std::bind is less readable, less expressive, and possibly less efficient. In C++14, there are no reasonable use cases for std::bind."

In C++11, however, std::bind can be justified in two constrained situations:

1) move-capture

2) Polymorphic functors

## Polymorphic functors

Since calling the `operator ()` of a bind object uses `std::forward`, it can accept arguments of any type.

## As a final note **"lambda support to C++11 rendered std::bind all but obsolete, however, and as of C++14, there are just no good use cases for it."**

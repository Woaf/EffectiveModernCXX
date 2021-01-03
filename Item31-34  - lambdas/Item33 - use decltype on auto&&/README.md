# Use `decltype` on `auto&&` parameters to `std::forward` them

C++14 introduced *generic lambdas*, lambdas that use `auto` in their parameter specifications. Inside the lambda closue class this is a template function call operator.

``` c++
auto f = [] (auto x) { ... };
```

Manually, we would write this as the following:

``` c++
class C {
public: 
    template<typename T>
    auto operator () (T x) const {
        // ...
    }
};
```

To `std::forward` our arguments inside the lambda function to other methods, we should specify our lambda parameters as `auto&&`. However, *`std::forward<???>` needs a type parameter*, which we do not possess - unless we use **`decltype (param)`**. Our new code should look like the following:

``` c++
auto f = [] (auto&&... params) {
        return someFunction (std::forward<decltype (params)> (params)...);
    };
```

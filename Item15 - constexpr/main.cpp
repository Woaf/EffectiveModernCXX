#include <array>
#include <iostream>
#include <cmath>

// I. 'constexpr' variables are not only constant, but
// they are compile-time constant!

// II. 'constexpr' functions do not necessarily return 
// a const, but they can be evaluated compile-time.
// They produce compile time constants IF they are used
// with compile time constants.

// III. 'constexpr' objects are const, and their 
// values are known compile time.

// constexpr values are priviliged, they are placed in 
// read-only memory

// constexpr values can be used in contexts where
// c++ expects a const expression, i.e.: std::array size

int f () { return 4; } // 
constexpr int f2 () { return 10; }

constexpr int g (int x, int y) {
    return x * y;
}

// IV. in c++11, constexpr functions can only have one single-line expression.
constexpr float getExp (float base) { return base*base; }

// V. in c++14, constepxr functions can have as many lines of expressions as needed.
// the restriction is that only literal types may be given as parameters. 
// (all built-in types are literal types BUT user defined types may be literals as well
// given that they have a constexpr constructor)

class Point2D 
{
public: 
    constexpr Point2D (double x = 0.0, double y = 0.0) noexcept : x (x), y (y) {}

    constexpr double GetX () const noexcept { return x; }
    constexpr double GetY () const noexcept { return y; }

    // in c++14, set functions can also be 'constexpr'
    void constexpr SetX (double x) noexcept { this->x = x; }
    void constexpr SetY (double y) noexcept { this->y = y; }

private:
    double x;
    double y;
};

constexpr Point2D GetMidpoint (const Point2D& point) noexcept
{
    return Point2D (point.GetX () / 2.0, point.GetY () / 2.0);
}

constexpr Point2D LimitPoint (const Point2D& point) noexcept 
{
    Point2D ret (point);

    if (point.GetX () > 3.0 && point.GetY () > 3.0) {
        ret.SetX (3.0);
        ret.SetY (3.0);
    } else if (point.GetX () > 3.0) {
        ret.SetX (3.0);
    } else if (point.GetY () > 3.0) {
        ret.SetY (3.0);
    }

    return ret;
}

int main () 
{
    // error! f () is not declared constexpr
    // and therefore will not return a compile-time 
    // const value, but a runtime value
    // std::array <int, f()> intarr;
    std::array <int, f2()> intarr2; // ok, size is determined during compile-time.

    // https://godbolt.org/z/F-7yu-
    int p = g (2, 4); // ok, g is evalueated during compile-time

    int x, y;
    std::cin >> x; std::cin >> y;
    int q = g (x, y); // also ok, g is not used in a compile-time context, can return a runtime value

    // V.
    constexpr Point2D point (4.3, 6.5); // ok
    constexpr Point2D point2 = GetMidpoint (point); // ok

    // constexpr Point2D point3 (x, y); // error, parameters are not determined compile-time
    Point2D point4 (x, y); // ok, constructor will return a runtime value.

    constexpr Point2D underLimitPoint (1.2, 2.1);
    constexpr Point2D modifiedPoint = LimitPoint (point); // ok
    std::cout << "{" << modifiedPoint.GetX () << ", " << modifiedPoint.GetY () << "}" << std::endl;
    constexpr Point2D modifiedPoint2 = LimitPoint (underLimitPoint); // ok
    std::cout << "{" << modifiedPoint2.GetX () << ", " << modifiedPoint2.GetY () << "}" << std::endl;

    return 0;
}
#include <memory>
#include <type_traits>

#include "classes.hpp"

enum class Selector {
    Stock, 
    Bond, 
    RealEstate
};

template <typename E>
constexpr std::underlying_type_t<E> toUnderlyingType (E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>> (enumerator);
}

std::unique_ptr<Investment> makeInvestment (const Selector& selector) 
{
    switch (toUnderlyingType (selector)) {
        case (toUnderlyingType (Selector::Stock)):      return std::make_unique<Stock>      (1, "stock");       break;
        case (toUnderlyingType (Selector::Bond)):       return std::make_unique<Bond>       (2, "bond");        break;
        case (toUnderlyingType (Selector::RealEstate)): return std::make_unique<RealEstate> (3, "real estate"); break;
        default: return nullptr; break;
    }
}

/*
However, we may also feed custom deestructors to the std::unique_ptr, when it comes for the 
object to be freed.
*/
auto delInvmt = [] (Investment* pInvestment) {
    std::cout << "Custom destructor for the investment object is running..." << std::endl;
    delete pInvestment;
};
std::unique_ptr<Investment, decltype (delInvmt)> makeInvmtWithCustomDestructor (const Selector& selector)
{
    std::unique_ptr<Investment, decltype (delInvmt)> pInv (nullptr, delInvmt);

    switch (toUnderlyingType (selector)) {
        case (toUnderlyingType (Selector::Stock)): pInv.reset (new Stock (1, "Stock")); break;
        case (toUnderlyingType (Selector::Bond)):  pInv.reset (new Bond (2, "Bond")); break;
        case (toUnderlyingType (Selector::RealEstate)): pInv.reset (new RealEstate (3, "RealEstate")); break;
        default: break;
    }

    return pInv;
}

static void UseInvestmentFactoryTest () 
{
    /*
    std::unique_ptrs are used for handling exclusive ownership of a dynamically
    allocated object. (exclusive ownership semantics. for this reason, this type of
    pointer cannot be copied but only moved. In other words, the std::unique_ptr is a
    move-only type.)

    Unique pointers work with very little overhead as compared to raw pointers,
    and most of the operations (i.e. dereferencing) execute the same instructions.

    The destructor of the std::unique_ptr is responsible for desstroying the pointed
    object (if it is not nullptr). It is done so by applying 'delete' on the raw pointer
    that is wrapped.
    */
    auto pStock = makeInvestment (Selector::Stock);
    pStock->printName ();

    auto pBond = makeInvestment (Selector::Bond);
    pBond->printName ();

    auto pRE = makeInvestment (Selector::RealEstate);
    pRE->printName ();
}

void TestUniquePtrsWithCustomDestructor () 
{
    {
        auto pStock = makeInvmtWithCustomDestructor (Selector::Stock);
    } // custom destructor runs

    {
        auto pBond = makeInvmtWithCustomDestructor (Selector::Bond);
    } // custom destructor runs

    {
        auto pRE = makeInvmtWithCustomDestructor (Selector::RealEstate);
    } // custom destructor runs
}

int main () 
{
    UseInvestmentFactoryTest ();
    TestUniquePtrsWithCustomDestructor ();

    return 0;
}
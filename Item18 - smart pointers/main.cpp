#include <iostream>
#include <memory>
#include <type_traits>

class Investment {
public:
    Investment (int id, const std::string& name) : id (id), name (name) {}

    virtual void printName () const noexcept { std::cout << name << std::endl; }
protected:
    int id;
    std::string name;
};

class Stock : public Investment 
{
public:
    Stock (int id, const std::string& name) : Investment (id, name) {}
};

class Bond : public Investment 
{
public:
    Bond (int id, const std::string& name) : Investment (id, name) {}
};

class RealEstate : public Investment
{
public: 
    RealEstate (int id, const std::string& name) : Investment (id, name) {}
};

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

int main () 
{
    UseInvestmentFactoryTest ();

    return 0;
}
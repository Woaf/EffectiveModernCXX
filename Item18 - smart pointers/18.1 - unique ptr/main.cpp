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

std::unique_ptr<Investment> makeInvestment (const Selector& selector, int id, const std::string& name) 
{
    switch (toUnderlyingType (selector)) {
        case (toUnderlyingType (Selector::Stock)):      return std::make_unique<Stock>      (id, name); break;
        case (toUnderlyingType (Selector::Bond)):       return std::make_unique<Bond>       (id, name); break;
        case (toUnderlyingType (Selector::RealEstate)): return std::make_unique<RealEstate> (id, name); break;
        default: return nullptr; break;
    }
}

/*
However, we may also feed custom deestructors to the std::unique_ptr, when it comes for the 
object to be freed.

All custom deletion functions accept a rea pointer to the obejct to be destroyed.

The type of the custom deleter function must be specified inside the type arguments 
of the std::unique_ptr.

It is important to note that the size of a unique_ptr is only the same as a raw pointer, 
when it does not have a custom destructor. Custom destructors are stored as function pointers, 
therefore the size of an std::unique_ptr doubles. If the deleter fucntion is a function object
(aka functor; lambda; a nameless object with a callable () operator), then the size of the 
unique_ptr depends on how much state is stored in the function object.
"Stateless function objects (from lambda expressions with no captures) incur no size penalty."
If a custrom destructor function can be implemented as either a function or a captureless lambda 
expression, then the lambda is preferred.
*/
template<typename... Ts>
auto makeInvmtWithCustomDestructor (const Selector& selector, Ts&&... args)
{
    auto delInvmt = [] (Investment* pInvestment) {
        std::cout << "Custom destructor for the investment object is running..." << std::endl;
        delete pInvestment; 
    };

    std::unique_ptr<Investment, decltype (delInvmt)> pInv (nullptr, delInvmt);

    switch (toUnderlyingType (selector)) {
        case (toUnderlyingType (Selector::Stock)):      pInv.reset (new Stock (std::forward<Ts>(args)...));      break;
        case (toUnderlyingType (Selector::Bond)):       pInv.reset (new Bond (std::forward<Ts> (args)...));      break;
        case (toUnderlyingType (Selector::RealEstate)): pInv.reset (new RealEstate (std::forward<Ts> (args)...)); break;
        default: break;
    }

    return pInv;
}

// --------- Custom deleters as stateless lambda and as a function pointer
auto delInvmnt1 = [] (Investment* pInvestment) {
    std::cout << "Deleting: ";
    pInvestment->printName ();
    std::cout << std::endl;

    delete pInvestment;
};

// the factory method sepcifies the custom deleter function of the unique pointer with the deduced type of the lambda
template<typename... Ts>
std::unique_ptr<Investment, decltype (delInvmnt1)> makeInvWithCustomDeleter2 (const Selector& selector, Ts&&... args) {

    std::unique_ptr<Investment, decltype (delInvmnt1)> pInv (nullptr, delInvmnt1);
    
    switch (toUnderlyingType (selector)) {
        case (toUnderlyingType (Selector::Stock)):          pInv.reset (new Stock       (std::forward<Ts> (args)...)); break;
            case (toUnderlyingType (Selector::Bond)):       pInv.reset (new Bond        (std::forward<Ts> (args)...)); break;
            case (toUnderlyingType (Selector::RealEstate)): pInv.reset (new RealEstate  (std::forward<Ts> (args)...)); break;
            default: break;
    }

    return pInv;
}

// custom deleter as a function
void delInvmnt2 (Investment* pwInvestment) {
    std::cout << "Deleting... ";
    pwInvestment->printName ();
    std::cout << std::endl;

    delete pwInvestment;
}

// the factory method specifies custom deleter function of the unique pointer to be a function pointer
template<typename... Ts>
std::unique_ptr<Investment, void (*)(Investment*)> makeInvWithCustomDeleter3 (const Selector& selector, Ts&&... args)
{
    std::unique_ptr<Investment, void (*)(Investment*)> pInv (nullptr, delInvmnt2);

    switch (toUnderlyingType (selector)) {
        case (toUnderlyingType (Selector::Stock)):      pInv.reset (new Stock (std::forward<Ts> (args)...)); break;
        case (toUnderlyingType (Selector::Bond)):       pInv.reset (new Bond (std::forward<Ts> (args)...)); break;
        case (toUnderlyingType (Selector::RealEstate)): pInv.reset (new RealEstate (std::forward<Ts> (args)...)); break;
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
    auto pStock = makeInvestment (Selector::Stock, 1, "First stock");
    pStock->printName ();

    auto pBond = makeInvestment (Selector::Bond, 2, "First bond");
    pBond->printName ();

    auto pRE = makeInvestment (Selector::RealEstate, 3, "First real estate");
    pRE->printName ();
}

void TestUniquePtrsWithCustomDestructor ()
{
    {
        auto pStock = makeInvmtWithCustomDestructor (Selector::Stock, 1, "Stock");
    } // custom destructor runs

    {
        auto pBond = makeInvmtWithCustomDestructor (Selector::Bond, 2, "Bond");
    } // custom destructor runs

    {
        auto pRE = makeInvmtWithCustomDestructor (Selector::RealEstate, 3, "Real Estate");
    } // custom destructor runs
}

void TestUnqPtrsWtihCDesctructor2 ()
{
    {
        std::cout << "Creating stock with a custom lambda deleter..." << std::endl;
        auto stock = makeInvWithCustomDeleter2 (Selector::Stock, 1, "Stock");
    }

    {
        std::cout << "Creating bond with a custom lambda deleter..." << std::endl;
        auto bond = makeInvWithCustomDeleter2 (Selector::Bond, 2, "Bond");
    }

    {
        std::cout << "Creating real estate with a custom lambda deleter..." << std::endl;
        auto realEstate = makeInvWithCustomDeleter2 (Selector::RealEstate, 3, "RE");
    }
}

void TestUnqPtrsWtihCDesctructor3 ()
{
    {
        std::cout << "Creating stock with a custom function pointer deleter..." << std::endl;
        auto stock = makeInvWithCustomDeleter3 (Selector::Stock, 1, "Stock");
    }

    {
        std::cout << "Creating bond with a custom function pointer deleter..." << std::endl;
        auto stock = makeInvWithCustomDeleter3 (Selector::Bond, 2, "Bond");
    }

    {
        std::cout << "Creating real estate with a custom function pointer deleter..." << std::endl;
        auto stock = makeInvWithCustomDeleter3 (Selector::RealEstate, 3, "Real Estate");
    }
}

void TestDocument () {
    Document d ("book.pdf");
    std::cout << d << std::endl;
}

int main () 
{
    UseInvestmentFactoryTest ();
    TestUniquePtrsWithCustomDestructor ();
    TestUnqPtrsWtihCDesctructor2 ();
    TestUnqPtrsWtihCDesctructor3 ();

    {
        // The unique_ptr can be converted to a shared pointer, which is a very useful feature
        std::shared_ptr<Investment> shPtr = makeInvWithCustomDeleter2 (Selector::Stock, 44, "shared stock");
    }

    TestDocument ();

    return 0;
}
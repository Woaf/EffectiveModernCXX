#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using FilterContainer = std::vector<std::function<bool (int)>>;

int CalculateValue (int x, int y) {
    return x + y;
}

void AddDivisorFilter (FilterContainer& fc) {
    auto base = 71;
    auto operand = 13;

    auto divisor = CalculateValue (base, operand);

    fc.emplace_back ([&divisor](int value) {
        return value % divisor == 0;
    });
}

int main ()
{
    FilterContainer fc;
    AddDivisorFilter (fc);

    return 0;
}

#include "flow.hpp"
using namespace fw;

#define FNT2(x, y, fn) [](auto x, auto y) { return fn; }

int main() {
    auto sum = [](auto x, auto y) { return x + y; };
    auto concat = [](auto x, auto y) { return "{}{}" | Format(x, y); };

    range(1, 20) | ZipWith(range(11, 15), sum) | Write(); // [12, 14, 16, 18]

    zipwith(range(1, 5), range(11, 20), concat) | Write(); // [111, 212, 313, 414]

    //junta dois char em uma string
    auto fnjoin = [](auto x, auto y) { return std::string{x, y}; };

    "ABCDEF"s | ZipWith("abcdef"s, fnjoin) | Write(); // [Aa, Bb, Cc, Dd, Ee, Ff]

    zipwith(range(10), "pterodactilo"s, concat) | Write(); // [0p, 1t, 2e, 3r, 4o, 5d, 6a, 7c, 8t, 9i]

    range(10) | ZipWith(range(10), sum) | Write(); // [0, 2, 4, 6, 8, 10, 12, 14, 16, 18]
}

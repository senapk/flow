#include "flow.hpp"

using namespace fw;
int main() {

    std::vector<int> a {1, 3, 2, 5};

    for (auto [i, x] : a | fw::Enumerate()) {
        format("({}:{})", i, x) | Write(""); 
        // (0:1)(1:3)(2:2)(3:5)
    }
    write("");

    fw::enumerate(a) | Join() | Write();  
    // (0, 1), (1, 3), (2, 2), (3, 5)

    "banana"s | Enumerate() | Join(", ") | Text("[{}]") | Write(); 
    // [(0, b), (1, a), (2, n), (3, a), (4, n), (5, a)]

    std::vector<double> d = {1.2, 2.1, 5.3, 6.7, 9.34};
    d   | Enumerate() 
        | Map([](auto p){ return format("{:_^5}:{%.2f}", p.first, p.second); })
        | Join("\n")
        | Write();

    // __0__:1.20
    // __1__:2.10
    // __2__:5.30
    // __3__:6.70
    // __4__:9.34
}

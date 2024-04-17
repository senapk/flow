#include "flow.hpp"

using namespace fw;

int main() {
    range(1, 5) 
        | Zip(range(10, 20)) 
        | Write(); // [(1, 10), (2, 11), (3, 12), (4, 13)]

    zip(range(10, 20), range(1, 5))
        | Write(); // [(10, 1), (11, 2), (12, 3), (13, 4)]

    "banana"s 
        | Zip(range(1, 10)) 
        | Write(); // [(b, 1), (a, 2), (n, 3), (a, 4), (n, 5), (a, 6)]
}

#include "flow.hpp"
using namespace fw;

int main() {
    "5:6:7"
        | Unpack<int, int, int>(':') 
        | Write(); // (5, 6, 7)

    "banana-5.68-8-c" 
        | Unpack<std::string, double, int, char>('-')
        | Write(); // (banana, 5.68, 8, c)
}

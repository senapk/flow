#include "flow.hpp"
#include <list>
#include <array>
using namespace fw;

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    v | Join(", ") | Write(); // 1, 2, 3, 4, 5
    v | Join("")   | Write(); // 12345
    v | Join("-")  | Text("( {} )") | Write(); // ( 1-2-3-4-5 )


    std::array<int, 3> a = {1, 2, 3};
    a | Join() | Write(); // 1, 2, 3

    std::list<int> {1, 2, 3, 4, 5}
        | Join(", ") 
        | Write(); // 1, 2, 3, 4, 5

    "abced"s | Join(", ") | Write(); // a, b, c, e, d

    std::make_tuple("ovo", 1, 1.3) 
        | Join(", ")
        | Write(); // ovo, 1, 1.3

     std::make_pair("ovo", 1)
         | Join(":")
         | Write(); // ovo:1
}

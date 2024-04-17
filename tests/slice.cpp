#include <map>
#include <list>

#define EXTRA //Sort
#include "flow.hpp"
using namespace fw;

int main() {
    range(1, 10) | Slice(2, 5)   | Write(); // [3, 4, 5]
    range(10)    | Slice(2, 5)   | Write(); // [2, 3, 4]
    range(10)    | Slice(1)      | Write(); // [1, 2, 3, 4, 5, 6, 7, 8, 9]
    range(10)    | Slice(-1)     | Write(); // [9]
    range(10)    | Slice(-2)     | Write(); // [8, 9]
    range(10)    | Slice(-3, -1) | Write(); // [7, 8]
    range(10)    | Slice()       | Write(); // [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    range(10)    | Slice(0, 0)   | Write(); // []
    range(10)    | Slice(0, 1)   | Write(); // [0]
    range(10)    | Slice(5, 2)   | Write(); // []
    range(10)    | Slice(5, -2)  | Write(); // [5, 6, 7]

    std::string("banana") | Slice(2, 5) | Write(); // nan

    "abcdef" | Text() | Slice(2)     | Write(); // cdef
    "abcdef" | Text() | Slice(2, -1) | Write(); // cde
    "abcdef" | Text() | Slice(3, -4) | Write(); // 

    std::list<int> {1, 2, 3, 4} | Slice(2, 5) | Write(); // [3, 4]

    std::map<std::string, int> m = {{"jose", 5}, {"bianca", 6}, {"maria"s, 7}};
    m   | Slice(0, 2)
        | Map([](auto x) { return x.first; })
        | Sort()
        | Write(); 
    // [bianca, jose]

    std::vector<int> v = std::list<int> {1, 2, 3, 4} | Slice();
    //-transforma em vetor

    std::map<std::string, int> {{"c", 1}, {"a", 2}}
        | Slice()
        | Write(); 
    // [(a, 2), (c, 1)]

    range(1, 5) 
        | Slice(0, 10) 
        | Write(); // [1, 2, 3, 4]
}

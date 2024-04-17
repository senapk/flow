#define EXTRA
#include "flow.hpp"
#include <list>
#include <map>
#include <set>
#include <array>
#include <unordered_set>
#include <unordered_map>

using namespace fw;
int main() {

    5.6123 | Text("%.2f")      | Write(); // 5.61
    std::vector<int> {1, 2, 3} | Write(); // [1, 2, 3]
    std::pair<int, int> {1, 2} | Text("%03d") | Write(); // (001, 002)
    "banana"                   | Write(); // banana
    "banana"s                  | Write(); // banana

    //-números
    5.6123 | Text("%.2f")     | Write(); // 5.61
    5      | Text("%02d")     | Write(); // 05

    //-alinhamento de string
    "banana"  | Text("<8")   | Write(); // banana  
    "banana"  | Text(">8")   | Write(); //   banana

    //-containers
    //-a função Write já chama a função Text para não primitivos
    std::vector<int> {1, 2, 3}   | Write(); // [1, 2, 3]
    std::list<int> {1, 2, 3}     | Write(); // [1, 2, 3]
    std::array<int, 3> {1, 2, 3} | Write(); // [1, 2, 3]

    //-pair
    std::pair<int, int> {1, 2}   | Write(); // (1, 2)

    //-tuples
    std::make_tuple(1, 5.42, "banana") | Write(); // (1, 5.42, banana)

    //-estruturas aninhadas
    std::make_pair(std::make_pair(4, "ovo"), "chiclete") | Write(); // ((4, ovo), chiclete)

    //-formatação recursiva
    std::make_tuple(1, 2, 3) 
         | Text("%03d")
         | Write(); // (001, 002, 003)

    std::make_pair(std::vector<int>{1,2,3}, std::vector<int>{4,5,6}) 
         | Text("%03d")
         | Write(); // ([001, 002, 003], [004, 005, 006])

    //-mapas
    std::map<int, int>{{1, 2}, {3, 4}} | Write(); // {(1, 2), (3, 4)}
    std::map<std::string, int>{{"c", 1}, {"a", 2}} | Write(); // {(a, 2), (c, 1)}
    std::unordered_map<int, int>{{1, 2}, {3, 4}} 
        | Write(); // {(3, 4), (1, 2)}
    std::unordered_map<std::string, int>{{"c", 1}, {"a", 2}} | Write(); 
    // {(a, 2), (c, 1)}

    //-sets
    std::set<int> {1, 2, 3}                   | Write(); // {1, 2, 3}
    std::unordered_set<int>{1, 2, 3}          | Write(); // {3, 2, 1}
    std::unordered_set<std::string>{"c", "a"} | Write(); // {a, c}
}


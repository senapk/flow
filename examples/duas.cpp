#include <iostream>
#include <vector>
#include "flow.hpp"

using namespace fw;

int main() {
    std::vector<int> vet {1, 2, 3, 4};
    
    //modo função
    write(join(range(5))); //imprime [01, 02, 03, 04]
    
    //modo pipeline
    range(5) | Join("[{, }]") | Write(); //imprime [0, 1, 2, 3, 4]
}
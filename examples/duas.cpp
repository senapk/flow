#include <iostream>
#include <vector>
#include "flow.hpp"

using namespace fw;

int main() {
    std::vector<int> vet {1, 2, 3, 4};
    
    //modo função
    write(range(5)); //imprime [0, 1, 2, 3, 4]
    
    //modo pipeline
    range(5) | Write(); //imprime [0, 1, 2, 3, 4]
}

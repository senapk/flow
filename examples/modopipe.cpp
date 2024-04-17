#include "flow.hpp"
using namespace fw;
int main() {
    std::stringstream ss("1 2 3 4 5 6 7");
    input(ss)
        | Split()                               // quebra em palavras ["1", "2", "3", "4", "5", "6", "7"]
        | Slice(1, -1)                          // excluir primeiro e último ["2", "3", "4", "5", "6"]
        | Map(Parse<int>())                     // converter para int [2, 3, 4, 5, 6]
        | Filter([](auto x){return x % 2 == 1;})// pegar apenas os impares [3, 5]
        | Write();                              // imprimir
    // [3, 5]
}

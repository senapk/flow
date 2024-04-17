#include <iostream>
#include "fn.hpp"
using namespace fn;
int main() {
    // 1 2 3 4 5 6 7
    input() | split()                   // quebra em palavras ["1", "2", "3", "4", "5", "6", "7"]
            | slice(1, -1)              // excluir primeiro e último ["2", "3", "4", "5", "6"]
            | map(FNT(x, _strto<int>(x)))// converter para int [2, 3, 4, 5, 6]
            | filter(FNT(x, x % 2 == 1))// pegar apenas os impares [3, 5]
            | write();                  // imprimir
    // [3, 5]
}

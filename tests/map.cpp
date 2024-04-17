#include "flow.hpp"
using namespace fw;

struct Pessoa {
    std::string nome;
    int idade;

    Pessoa(std::string nome = "", int idade = 0): nome{nome}, idade{idade} {}
};

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
        v   | Map([](auto x) {return x + 1;}) 
            | Write(); // [2, 3, 4, 5, 6]

        std::vector<Pessoa> vp = {{"Joao", 20}, {"Maria", 30}};
        vp  | Map([](auto p) {return p.idade + 1;}) 
            | Write(); // [21, 31]

        "abcde"s
            | Map([](char c) -> char {return c + 1;}) 
            | Write(); // [b, c, d, e, f]
}

#include "flow.hpp"
using namespace fw;
struct Pessoa {
    std::string nome;
    int idade;
    Pessoa(std::string nome, int idade) : nome(nome), idade(idade) {}
};

std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
    return os << p.nome << ":" << p.idade;
}

int main() {
    range(0, 10) | Filter([](auto x) { return x % 2 == 0;}) | Write(); 
    // [0, 2, 4, 6, 8]
    "banana"s    | Filter([](auto x) { return x == 'a';})   | Write(); 
    // aaa
    "banana"s    | Filter([](auto x) { return x != 'a';})   | Write();
    // bnn

    std::vector<int> {1, 2, 3, 4, 5}
        | Filter([](auto x) { return x % 2 == 0;})
        | Write(); 
    // [2, 4]

    std::vector<Pessoa>{{"Joao", 20}, {"Maria", 30}}
        | Filter([](auto p) {return p.idade > 20;}) 
        | Write(); 
    // [Maria:30]

}

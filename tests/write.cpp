#include "flow.hpp"
using namespace fw;

struct Pessoa {
    std::string nome;
    int idade;
public:
    Pessoa(std::string nome, int idade) : nome(nome), idade(idade) {}
};

//obrigatório para imprimir objetos diretamente via Write, Text
std::ostream& operator<<(std::ostream& os, Pessoa p) {
    return os << p.nome << ":" << p.idade;
}

int main() {
    //-funciona com primitivos
    5   | Write(); // 5
    4.5 | Write(); // 4.5

    //-e quaisquer combinação de containers e tipos primitivos
    std::vector<int>{1,2,3}         | Write(); // [1, 2, 3]
    std::list<float>{1.5,2.5, 3.5}  | Write(); // [1.5, 2.5, 3.5]
    std::make_pair("ovo", "queijo") | Write(); // (ovo, queijo)
    std::make_tuple(1,2.3,"tres")   | Write(); // (1, 2.3, tres)

    //-após impressão, ele devolve o valor original
    //-dá pra mudar o fim de linha passando um argumento
    write("sem quebrar linha", "");
    write(" ou mudando a quebra de linha", ".\n");
    // sem quebrar linha ou mudando a quebra de linha.

    //-para imprimir classes, é necessário sobrecarregar a função operator <<
    std::vector<Pessoa> pessoas {{"Joao", 5}, {"Maria", 6}};
    
    pessoas | Write(); 
    // [Joao:5, Maria:6]
}

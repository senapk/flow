#include "flow.hpp"
#include <map>
#include <list>
#include <set>

using namespace fw;
int main() {

    format("O valores sao {} e {}.", 5, 7) | Write();
    // O valores sao 5 e 7.

    "O valores sao {} e {}." | Format(5, 7) | Write();
    // O valores sao 5 e 7.

    std::vector<int> vet {1, 2, 3};
    "O primeiro elemento de {} eh {}." | Format(vet, vet[0])  | Write();
    // O primeiro elemento de [1, 2, 3] eh 1.

    "O primeiro elemento de {} eh {}."
      | Format( vet, vet[0]) 
      | Write();
    // O primeiro elemento de [1, 2, 3] eh 1.
    
    "O primeiro elemento de {} eh {}." 
      | Format(
        vet | Join("-") | Text("({})"),
        vet[0]
        )
      | Write(); 
    // O primeiro elemento de (1-2-3) eh 1.

    "{}{}" | Format("bana", "nada")  | Write();
    // bananada

    "{{ Dobre para poder inserir chaves. }}" | Format()  | Write();
    // { Dobre para poder inserir chaves. }

    //-números
    "Formate com printf assim {%.2f}." | Format(5.6123)  | Write();
    // Formate com printf assim 5.61.
    
    "Ou completando com zeros {%02d}" | Format(5) | Write();
        // Ou completando com zeros 05

    "Hora {%02d}:{%02d}:{%02d}" | Format(5, 6, 7) | Write();
        // Hora 05:06:07

    //-alinhamento de string definindo o tamanho
    "Usando <10 para alinhar [{<10}]." | Format("banana") | Write();
    // Usando <10 para alinhar [banana    ].
    "Usando >10 para alinhar [{>10}]." | Format("banana") | Write();
    // Usando >10 para alinhar [    banana].
    "Usando ^10 para alinhar [{^10}]." | Format("banana") | Write();
    // Usando ^10 para alinhar [  banana  ].

    //-alinhamento de string mudando o pad

    ":[char] muda o char de pad {:_<10}." | Format("banana") | Write();
    // :[char] muda o char de pad banana____.
    ":[char] muda o char de pad {:=>10}." | Format("banana") | Write();
    // :[char] muda o char de pad ====banana.
    ":[char] muda o char de pad {:*^10}." | Format("banana") | Write();
    // :[char] muda o char de pad **banana**.

    //-containers
    //-use o join(container) ou container | Join() para formatar um container como string
    "{:_>6}: {}" | Format("vector", std::vector<int> {1, 2, 3})   | Write();
    // vector: [1, 2, 3]
    "{:_>6}: {}" | Format("list",   std::list<int> {1, 2, 3})     | Write();
    // __list: [1, 2, 3]
    "{:_>6}: {}" | Format("array",  std::array<int, 3> {1, 2, 3}) | Write();
    // _array: [1, 2, 3]

    //-use o joinwith(container) ou container | JoinWith() para aplicar formatação ao seu container
    "{:_>6}: {}" | Format("vector", std::vector<int> {1, 2, 3})   | Write();; 
    // vector: [1, 2, 3]
    "{:_>6}: {}" | Format("list",   std::list<int> {1, 2, 3})     | Write();; 
    // __list: [1, 2, 3]
    "{:_>6}: {}" | Format("array",  std::array<int, 3> {1, 2, 3}) | Write();; 
    // _array: [1, 2, 3]
    
    //-pair e tuplas
    //-pair são sobrecarregados para impressão com (, )
    "pair {}"  | Format(std::make_pair(1, 2))     | Write();;
    // pair (1, 2)
    "tuple {}" | Format(std::make_tuple(1, 2, 3)) | Write();;
    // tuple (1, 2, 3)


    //-quaisquer estruturas aninhadas funcionam como esperado
    format("pair {}", std::make_pair(1.7, std::make_pair("ovo", 3))) | Write();; 
    // pair (1.7, (ovo, 3))

    //-se uma formatação for aplicada a um container, ela será aplicada a todos os elementos
    //-formatação recursiva
    format("{%.2f}", std::vector<double> {1.7, 2.3, 3.4}) | Write();; 
    // [1.70, 2.30, 3.40]

    //-4 espaços, completa com 0 pra ter 2 digitos, faz o pad usando _
    format("{:_^4%02d}", std::make_pair(std::vector<int>{1,2,3}, std::vector<int>{4,5,6})) | Write();;
    // ([_01_, _02_, _03_], [_04_, _05_, _06_])

    //-map e unordered_maps são impressos entre {} e separados por , 
    //-cada elemento eh um par
    format("map {}", std::map<int, int>{{1, 2}, {3, 4}}) | Write();; 
    // map {(1, 2), (3, 4)}
    format("map {}", std::map<std::string, int>{{"casa", 1}, {"ave", 2}}) | Write();; 
    // map {(ave, 2), (casa, 1)}

    format("set {}", std::set<int>{1, 2, 3}) | Write();;
    // set {1, 2, 3}
}

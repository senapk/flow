# FAKEFN for c++

<!-- toc -->
- [Requisitos](#requisitos)
- [Instalação no sistema](#instalação-no-sistema)
- [Usando como arquivo local do projeto](#usando-como-arquivo-local-do-projeto)
- [Duas opções de funções](#duas-opções-de-funções)
- [Resumo das funções](#resumo-das-funções)
- [Documentação](#documentação)
  - [String e Operador +](#string-e-operador-)
  - [WRITE](#write)
  - [TEXT](#text)
  - [FORMAT](#format)
  - [INPUT](#input)
  - [JOIN](#join)
  - [RANGE](#range)
  - [SLICE](#slice)
  - [FILTER](#filter)
  - [MAP](#map)
  - [SPLIT](#split)
  - [UNPACK](#unpack)
  - [ZIP](#zip)
  - [ZIPWITH](#zipwith)
  - [ENUMERATE](#enumerate)
<!-- toc -->

## Requisitos

- Você precisa do GCC 7.3 ou superior para compilar o código.
- Quando for compilar, utilize a flag `-std=c++17`.

## Instalação no sistema

- Copie o arquivo para uma pasta de includes do sistema e use no seu código como `#include <flow.hpp>`.
  - Windows: Copie a biblioteca para dentro da pasta MinGW\include.
  - Linux: Copie a biblioteca para dentro da pasta /usr/local/include.

    ```bash
    sudo curl https://raw.githubusercontent.com/senapk/flow/master/flow.hpp -o /usr/local/include/flow.hpp
    ```

```cpp
//main.cpp
#include <flow.hpp>

int main() {
    fw::write("ola mundo");
}

```

## Usando como arquivo local do projeto

- Copie o arquivo para a pasta do seu projeto e inclua no seu código como `#include "flow.hpp"`.

```bash
curl https://raw.githubusercontent.com/senapk/flow/master/flow.hpp -o flow.hpp
```

```cpp
//main.cpp
#include "flow.hpp"

int main() {
    fw::write("ola mundo");
}

```

## Duas opções de funções

- As funções estão no namespace fw.
  - Para utilizar, basta incluir o arquivo flow.hpp e usar o namespace flow.
- As funções estão disponibilizadas em dois formatos:
  - Formato de função normal, escrita em minúsculo, com parênteses e argumentos.
  - Formato de função em pipeline, escrita em com a primeira letra em maiúsculo, onde o primeiro argumento da função é passado pelo pipe.
- Exemplo:
  - A função `text(data)` transforma um dado passado em uma string.
    - Modo função: `text(data, cfmt)`.
    - Modo pipeline: `data | Text(cfmt)`.
    - Um parâmetro opcional é a formatação a ser aplicada utilizando o padrão printf.
  - A função `write()` imprime um dado passado no fluxo de saída padrão.
    - Modo função: `write(data)`.
    - Modo pipeline: `data | Write())`.

<!-- load examples/duas.cpp fenced -->

```cpp
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
```

<!-- load -->

## Resumo das funções

```js



//----------------------------------------------------------
//                       IMPRIMINDO 
//----------------------------------------------------------

write(data: DATA, end = "\n")        -> DATA   // imprime um conteúdo convertido pelo tostr

//----------------------------------------------------------
//                       AÇUCAR SINTÁTICO
//----------------------------------------------------------

input(fluxo = cin)                   -> str    // lê linha inteira
operator+(token: str)                -> double // transforma string em double
"nome"s                              -> str    // transforma raw string em string
range(end: int)                      -> [int]  // vetor de [0, end[, não inclui o end
range(init: int, end: int, step = 1) -> [int]  // vetor de [init, end[, não inclui o end

//----------------------------------------------------------
//                   PARA STRINGS
//----------------------------------------------------------

text      (data: DATA, cfmt = "")            -> str   // converte qualquer coisa para string e formata
format    (fmt: str, Args ...args)           -> str   // formata uma string usando {} e printf
join      (container, fmt = "[{, }]")        -> str   // concatena os elementos de um container 

//----------------------------------------------------------
//                  DE STRINGS
//----------------------------------------------------------

parse <TYPE> (value: str)                    -> TYPE                // dado tipo, converte string para esse tipo
unpack<TS...>(line: str, delimiter: char)    -> std::tuple<TS...>;  // dado tipos e delimitador, separa em uma tupla 
split        (content: str, fmt = " ")       -> [str]               // dado um delimitador, separa em vetor de strings

//----------------------------------------------------------
//             filter, map, slice  
//----------------------------------------------------------

filter (container<a>, fn: (a -> bool))      -> [a]       // filtra os elementos que satisfazem a função
map    (container<a>, fn: (a -> b   ))      -> [b]       // aplica uma função em todos os elementos
foreach(container<a>, fn: (a)        )      -> void      // aplica uma função em todos os elementos
slice  (container<a>, begin = 0)            -> [a]       // copia de begin até o final
slice  (container<a>, begin: int, end: int) -> [a]       // copia de [begin, end[

//----------------------------------------------------------
//             ZIP
//----------------------------------------------------------
enumerate(container<a>)                -> [(int,a)] // enumera os elementos
zip    (cont<a>, cont<b>)              -> [(a,b)]   // zipa dois containers em um cont de pares
zipwith(cont<a>, cont<b>, fn: (a,b->c) -> [c]       // zipa dois containers usando uma função


```

## Documentação

### String e Operador +

No C++11, foi introduzido o suporte a `string literals`, que permite criar strings de forma mais simples e legível.
Esse modo já está habilitado na biblioteca, mas pode ser inserido manualmente utilizando `using namespace std::string_literals;` no seu código.

Outra função útil para manipulação de strings foi inspirada no operator + do javascript, que permite converter uma string em um double.

<!-- load examples/str.cpp fenced -->

```cpp
#include <iostream>
#include "flow.hpp"
using namespace fw;
int main() {
    auto a = "aa";              //const char *
    auto b = std::string("bb"); //std::string
    auto c = "cc"s;             //std::string

    auto d = +"23.556"s;        //double
    auto e = (int) +"23.556"s;  //int (cast)

    std::cout << a <<  " " << b << " " << c << " " << d << " " << e << std::endl;
    //aa bb cc 23.556 23
}
```

<!-- load -->

### WRITE

<!-- load flow.hpp fenced=cpp:extract=write -->

```cpp
/**
 * @note #### `write(T data, str end = "\n") -> T`
 * @note #### `T data| Write(str end = "\n") -> T`
 * 
 * @note - Envia o dado para o `std::cout` quebrando a linha.
 * @note - Se o dado não for uma `string`, será convertido pela função `text`.
 * 
 * @note #### Parâmetros
 * @note `param: data` Dado a ser transformado e impresso.
 * @note `param: end` (opcional) String a ser inserida no final da linha.
 * @note `return` O dado original recebido.
 * 
 * @note #### Exemplos
 * @note `vector<int> {1, 2, 3} | Join() | Write(); // [1, 2, 3]`
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#write
 */
template <typename PRINTABLE> 
const PRINTABLE& write(const PRINTABLE& data, std::string end = "\n") 
```

<!-- load -->

<!-- load tests/write.cpp fenced=cpp -->

```cpp
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
```

<!-- load -->

### TEXT

<!-- load flow.hpp fenced=cpp:extract=text -->

```cpp
/**
 * @note #### `text(T data,  str cfmt = "") -> str`
 * @note #### `T data | Text(str cfmt = "") -> str`
 * @note - Converte o dado passado em string.
 * 
 * @note #### Parâmetros
 * @note `param: data` Dado a ser convertido.
 * @note `param: cfmt`: parâmetro de formatação tal qual printf como "%.2f"
 * @note `param: cfmt`: modo de formatação usando braces para substituição "antes {%2f} depois"
 * @note `return` String com o dado convertido.
 * 
 * @note #### Funcionamento para tipos primitivos
 * @note - Converte o dado em string.
 * @note - Se `cfmt` for passado, o dado será formatado usando o modelo do `printf`.
 * @note - Se não tiver `cfmt`, o dado será convertido diretamente para string usando operator<<
 * @note `text(1.2) | Write(); // "1.2"
 * @note `text(1.2, "%.4f") | Write(); // "1.2000"
 * @note `1.2 | Text("%.4f") | Write(); // "1.2000"
 * @note `text(1.2, "%.4f") | Write(); // "1.2000"`
 * 
 * @note #### Utilizando {} como placeholder
 * @note - O {} pode ser utilizado como o local onde a variável será inserida.
 * @note - O conteúdo do {} será formatado de acordo com o `cfmt`.
 * @note "domingo" | Text("Hoje é {}.") | Write(); // "Hoje é domingo."
 * @note 3.1415 | Text("O valor de pi é {%.2f}.") | Write(); // "O valor de pi é 3.14."
 * 
 * @note #### Funcionamento para pair e tuple
 * @note - Para pair e tuple, o texto é gerado com os elementos separados por vírgula.
 * @note `text(std::pair<int, int>(2, 1)) | Write(); // "(2, 1)"`
 * 
 * @note #### Padding e alinhamento
 * @note - O alinhamento pode ser feito com <, > ou ^.
 * @note - O tamanho do campo pode ser definido com um número.
 * @note - O padding pode ser feito com qualquer caractere e definido pelo símbolo :.
 * @note `text(1.2, "<10:_") | Write(); // "1.2_______"`
 * @note `text(1.2, ">10:_") | Write(); // "_______1.2"`
 * @note `text(1.2, "^10:_") | Write(); // "___1.2____"`
 * @note `text(1.2, "<10:0") | Write(); // "1.20000000"`
 * @note `"amigo" | Text("Meu {^10:0}.") | Write(); // "Meu 00amigo000."`
 * 
 * @note  #### Mais exemplos em https://github.com/senapk/flow#text
 */
template <typename T>
inline std::string text(const T& data, const std::string& cfmt)
```

<!-- load -->

<!-- load tests/text.cpp fenced=cpp -->

```cpp
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

```

<!-- load -->

### FORMAT

<!-- load flow.hpp fenced=cpp:extract=format -->

```cpp
/**
 * @note #### `format(str fmt, Args ...args ) -> str`
 * @note #### `str fmt| FORMAT(Args ...args ) -> str`
 * 
 * @note - Formata uma string com base nos argumentos passados.
 * @note - A função `text` é chamada para cada argumento {}
 * @note - Utilizando um modelo de chaves para posicionar os argumentos.
 * @note - Se dentro da chave, houver um string de formatação, o dado será formatado com base nela.
 * @note - Não primitivos são formatados de acordo com a função `text`
 * 
 * @note #### Parâmetros
 * @note `param: fmt` O texto com os {} para substituir pelos argumentos.
 * @note `param: args` Os argumentos a serem substituídos.
 * @note `return` O texto formatado.
 * 
 * @note #### Exemplos
 * @note `format("O {} é {%0.2f}.", "pi", 3.141592653) | Write(); //o pi e 3.14.`
 * @note `"O {} é {%0.2f}." | Format("pi", 3.141592653) | Write(); //o pi e 3.14.`
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#format
 * 
 */
template<typename... Args>
std::string format(std::string fmt, Args ...args) 
```

<!-- load -->

<!-- load tests/format.cpp fenced=cpp -->

```cpp
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
```

<!-- load -->

### INPUT

<!-- load flow.hpp fenced=cpp:extract=input -->

```cpp
/**
 * @note #### `input(istream source = std::cin) -> str`
 * 
 * @note - Extrai uma linha inteira e retorna como string.
 * @note - O padrão é o std::cin, mas pode ser um fluxo ou arquivo.
 * @note - Se não houver mais linhas, lança uma exceção.
 * 
 * @note #### Parâmetros
 * @note `param: source` Origem da linha.
 * @note `return` Linha lida.
 * @note `throws: std::runtime_error` Caso não haja mais linhas.
 * 
 * @note #### Exemplos
 * @note `auto line = input();`
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#input
 */
inline std::string input(std::istream & is = std::cin)
```

<!-- load -->

<!-- load tests/input.cpp fenced=cpp -->

```cpp
#include "flow.hpp"
using namespace fw;

int main() {
    auto line = input();
    line | Write();
}
```

<!-- load -->

### JOIN

<!-- load flow.hpp fenced=cpp:extract=join -->

```cpp
/**
 * @note #### `join(T container, str separator = ", ", str cfmt = "") -> str`
 * @note #### `T container| Join(str separator = ", ", str cfmt = "") -> str`
 * 
 * @note - Transforma um container, par ou tupla em string.
 * @note - Se os elementos não forem strings, eles serão transformados pela função `text`.
 * 
 * @note #### Parâmetros
 * @note `param: container` Container a ser transformado em string.
 * @note `param: separtor` demilitador utilizado para juntar os elementos.
 * @note `param: cfmt` fortação a ser aplicada em cada elemento do container.
 * @note `return` String com os elementos concatenados.
 * 
 * @note  #### Exemplos
 * @note `join(vector<int>{1, 2, 3}, " ") | Write(); // "1 2 3"`
 * @note `vector<int>{1, 2, 3} | Join("=") | Write(); // "1=2=3"`
 * @note `vector<int>{1, 2, 3} | Join("; ") | Text("[{}]") | Write(); // "[1; 2; 3]"`
 * @note `vector<int>{1, 2, 3} | Join("; ", "%02d") | Text("[{}]") | Write(); // "[01; 02; 03]"`
 * 
 * @note  #### Mais exemplos em https://github.com/senapk/flow#join
 */
template <typename T>
std::string join(const T& container, const std::string& separator = ", ", const std::string& cfmt = "")
```

<!-- load -->

<!-- load tests/join.cpp fenced=cpp -->

```cpp
#include "flow.hpp"
#include <list>
#include <array>
using namespace fw;

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    v | Join(", ") | Write(); // 1, 2, 3, 4, 5
    v | Join("")   | Write(); // 12345
    v | Join("-")  | Text("( {} )") | Write(); // ( 1-2-3-4-5 )


    std::array<int, 3> a = {1, 2, 3};
    a | Join() | Write(); // 1, 2, 3

    std::list<int> {1, 2, 3, 4, 5}
        | Join(", ") 
        | Write(); // 1, 2, 3, 4, 5

    "abced"s | Join(", ") | Write(); // a, b, c, e, d

    std::make_tuple("ovo", 1, 1.3) 
        | Join(", ")
        | Write(); // ovo, 1, 1.3

     std::make_pair("ovo", 1)
         | Join(":")
         | Write(); // ovo:1
}
```

<!-- load -->

### RANGE

<!-- load flow.hpp fenced=cpp:extract=range -->

```cpp
/**
 * @note #### `range(int init, int end, int step = 1) -> vector<int>`
 * 
 * @note - Gera um vetor de inteiros de init até end, mas não incluindo end, com passo step.
 * 
 * @note #### Parâmetros
 * @note `param: init` início.
 * @note `param: end` limite superior.
 * @note `param: step` passo do incremento.
 * @note `return` vetor de inteiros.
 * 
 * @note #### Exemplos
 * @note `range(0, 10) | Join() | Write(); // [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]`
 * @note `range(0, 10, 2) | Join() | Write(); // [0, 2, 4, 6, 8]`
 * 
 * @note #### Veja  mais exemplos em https://github.com/senapk/flow#range
 */
inline std::vector<int> range(int init, int end, int step = 1)
```

<!-- load -->

<!-- load tests/range.cpp fenced=cpp -->

```cpp
#include "flow.hpp"

using namespace fw;

int main() {
  range(0, 10)     | Write(); // [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  range(0, 10, 2)  | Write(); // [0, 2, 4, 6, 8]
  range(10, 0, -1) | Write(); // [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]

  range(1, 5) | Write(); // [1, 2, 3, 4]
  range(5)    | Write(); // [0, 1, 2, 3, 4]
  range(10, -1, -2) | Write(); // [10, 8, 6, 4, 2, 0]

  range(26)
        | Map([](int x) -> char {return 'a' + x;})
        | Write()  // [a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]
        | Join("") // abcdefghijklmnopqrstuvwxyz
        | Write();

  range(10, -1, -2) | Write(); // [10, 8, 6, 4, 2, 0]

  5 | Range() | Write(); // [0, 1, 2, 3, 4]

  range(-10, 10, 2) | Write(); // [-10, -8, -6, -4, -2, 0, 2, 4, 6, 8]
  range(10, 0, -1)  | Write(); // [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]

  auto tochar = [](int x) -> char {return 'a' + x;};
  range(26) 
    | Map(tochar)  
    | Join("") 
    | Write(); // abcdefghijklmnopqrstuvwxyz

  range(25, -1,  -1)
    | Map(tochar)
    | Join("")
    | Write(); // zyxwvutsrqponmlkjihgfedcba
}
```

<!-- load -->

### SLICE

<!-- load flow.hpp fenced=cpp:extract=slice -->

```cpp

```

<!-- load -->

<!-- load tests/slice.cpp fenced=cpp -->

```cpp
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
```

<!-- load -->

### FILTER

<!-- load flow.hpp fenced=cpp:extract=filter -->

```cpp
/**
 * @note #### `filter(CONTAINER<T> container, FUNCTION fn) -> vector<T>`
 * @note #### `CONTAINER<T> container| FILTER(FUNCTION fn) -> vector<T>`
 * 
 * @note - Retorna um vetor com os elementos do container que satisfazem a função predicado fn.
 * 
 * @note #### Parâmetros
 * @note `param: container` Container a ser filtrado.
 * @note `param: fn` Função predicado.
 * @note `return` Vector com os elementos que satisfazem a função predicado.
 * 
 * @note #### Exemplos
 * @note `vector<int> vet {1, 2, 3};`
 * @note `filter(vet, [](int x) {return x % 2 == 0;}) | Join() | Write(); // [2]`
 * @note `vet| Filter([](int x) {return x % 2 == 0;}) | Join() | Write(); // [2]`
 * 
 * @note #### Veja  mais exemplos em https://github.com/senapk/flow#filter
 * 
 */
template<typename CONTAINER, typename FUNCTION>
auto filter(const CONTAINER& container, FUNCTION fn)
```

<!-- load -->

<!-- load tests/filter.cpp fenced=cpp -->

```cpp
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
```

<!-- load -->

### MAP

<!-- load flow.hpp fenced=cpp:extract=map -->

```cpp
/**
 * @note #### `map(CONTAINER<T> container, FUNCTION fn) -> vector<fn(T)>`
 * @note #### `CONTAINER<T> container| Map(FUNCTION fn) -> vector<fn(T)>`
 * 
 * @note - Retorna um vetor com o resultado da aplicação da função fn para cada elemento do container.
 * 
 * @note #### Parâmetros
 * @note `param: container` Container a ser mapeado.
 * @note `param: fn` Função a ser aplicada em cada elemento do container.
 * @note `return` Vector com os elementos resultantes da aplicação da função.
 * 
 * @note #### Exemplos
 * @note `vector<int> vet {1, 2, 3};`
 * @note `map(vet, [](int x) {return x * x;}) | Join() | Write(); // [1, 4, 9]`
 * @note `vet| Map([](int x) {return x * x;}) | Join() | Write(); // [1, 4, 9]`
 * 
 * @note #### Veja  mais exemplos em https://github.com/senapk/flow#map
 */
template<typename CONTAINER, typename FUNCTION>
auto map(const CONTAINER& container, FUNCTION fn)
```

<!-- load -->

<!-- load tests/map.cpp fenced=cpp -->

```cpp
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
```

<!-- load -->

### SPLIT

<!-- load flow.hpp fenced=cpp:extract=split -->

```cpp
/**
 * @note #### `split(str content, char delimiter = " ") -> vector<str>`
 * @note #### `str content| Split(char delimiter = " ") -> vector<str>`
 * 
 * @note - Transforma uma string em um vetor de strings, separando pelo delimitador.
 * 
 * @note #### Parâmetros
 * @note `param: content` String a ser separada.
 * @note `param: delimiter` (opcional) Caractere delimitador.
 * @note `return` Vetor de strings.
 *
 * @note #### Exemplos
 * @note `split("a,b,c", ",") | Join() | Write(); // [a, b, c]`
 * @note `"a,b,c"| Split(",") | Join() | Write(); // [a, b, c]`
 * @note `"a, b, c"| Split(", ") | Join() | Write(); // [a, b, c]`
 * @note `split("a b c") | Join() | Write(); // [a, b, c]`
 * @note `"a b c"|Split()| Join() | Write(); // [a, b, c]`
 *  
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#split
 */
inline std::vector<std::string> split(std::string content, std::string delimiter = " ")
```

<!-- load -->

<!-- load tests/split.cpp fenced=cpp -->

```cpp
#include "flow.hpp"
using namespace fw;

int main() {

    split("eu gosto de comer banana", " ")    | Write();
    // [eu, gosto, de, comer, banana]
    split("a,b,c", ",")                       | Write();
    // [a, b, c]
    split("eu gosto de comer banana", " ")    | Write();
    // [eu, gosto, de, comer, banana]
    split("eu gosto de comer    banana", " ") | Write();
    // [eu, gosto, de, comer, , , , banana]
}
```

<!-- load -->

### UNPACK

<!-- load flow.hpp fenced=cpp:extract=unpack -->

```cpp
/**
 * @note #### `unpack<...TS>(str value, char delimiter) -> tuple<TS...>`
 * @note #### `str value| UNPACK<...TS>(char delimiter) -> tuple<TS...>`
 * 
 * @note - Transforma de string para tupla dados os tipos de cada elemento e o char separador.
 * 
 * @note #### Parâmetros
 * @note `param: TS...` Tipos a serem extraídos.
 * @note `param: value` String a ser convertida.
 * @note `param: delimiter` Caractere separador entre os elementos.
 * @note `return` Tupla com os elementos convertidos.
 * 
 * @note #### Exemplos
 * @note unpack<int, double, std::string>("1:2.4:uva", ':') | Write(); // (1, 2.4, "uva") 
 * @note "1:2.4:uva"| UNPACK<int, double, std::string>(':') | Write(); // (1, 2.4, "uva")
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#unpack
 * 
 */
template <typename... TS>
std::tuple<TS...> unpack(const std::string& line, char delimiter)
```

<!-- load -->

<!-- load tests/unpack.cpp fenced=cpp -->

```cpp
#include "flow.hpp"
using namespace fw;

int main() {
    "5:6:7"
        | Unpack<int, int, int>(':') 
        | Write(); // (5, 6, 7)

    "banana-5.68-8-c" 
        | Unpack<std::string, double, int, char>('-')
        | Write(); // (banana, 5.68, 8, c)
}
```

<!-- load -->

### ZIP

<!-- load flow.hpp fenced=cpp:extract=zip -->

```cpp
/**
 * @note #### `zip(CONTAINER_A<T> container_a, CONTAINER_B<K> container_b) -> vector<pair<T, K>>`
 * @note #### `CONTAINER_A<T> container_a| ZIP(CONTAINER_B<K> container_b) -> vector<pair<T, K>>`
 * 
 * @note - Une dois containers em um vetor de pares limitado ao menor tamanho dos dois containers.
 * 
 * @note #### Parâmetros
 * @note `param: container_a` Primeiro container.
 * @note `param: container_b` Segundo container.
 * @note `return` Vetor de pares.
 * 
 * @note #### Exemplos
 * @note `zip(vector<int>{1, 2, 3}, string("pterodactilo")) | Join() | Write(); //[(1, p), (2, t), (3, e)]`
 * @note `vector<int>{1, 2, 3}| ZIP(string("pterodactilo")) | Join() | Write(); //[(1, p), (2, t), (3, e)]`
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#zip
 */
template<typename CONTAINER_A, typename CONTAINER_B>
auto zip(const CONTAINER_A& A, const CONTAINER_B& B)
```

<!-- load -->

<!-- load tests/zip.cpp fenced=cpp -->

```cpp
#include "flow.hpp"

using namespace fw;

int main() {
    range(1, 5) 
        | Zip(range(10, 20)) 
        | Write(); // [(1, 10), (2, 11), (3, 12), (4, 13)]

    zip(range(10, 20), range(1, 5))
        | Write(); // [(10, 1), (11, 2), (12, 3), (13, 4)]

    "banana"s 
        | Zip(range(1, 10)) 
        | Write(); // [(b, 1), (a, 2), (n, 3), (a, 4), (n, 5), (a, 6)]
}
```

<!-- load -->

### ZIPWITH

<!-- load flow.hpp fenced=cpp:extract=zipwith -->

```cpp
/**
 * @note #### `zipwith(CONTAINER<T> container_a, CONTAINER<K> container_b, FUNCTION fnjoin) -> vector<fnjoin(T, K)>`
 * @note #### `CONTAINER<T> container_a| ZIPWITH(CONTAINER<K> container_b, FUNCTION fnjoin) -> vector<fnjoin(T, K)>`
 * 
 * @note - Une dois containers através da aplicação da função fnjoin em cada par limitado ao menor tamanho dos dois containers.
 * 
 * @note #### Parâmetros
 * @note `param: container_a` Primeiro container.
 * @note `param: container_b` Segundo container.
 * @note `param: fnjoin` Função a ser aplicada em cada par.
 * @note `return` Vetor com os resultados.
 * 
 * @note #### Exemplos
 * @note `auto concat = [](auto x, auto y) { return text(x) + y; };`
 * @note `zipwith(vector<int>{1, 2, 3}, string("pterodactilo"), concat) | Join() | Write(); // ["1p", "2t", "3e"]`
 * @note `zipwith(range(10), "pterodactilo"s, concat) | Join() | Write(); // ["0p", "1t", "2e", "3r", "4o", "5d", "6a", "7c", "8t", "9i"]`
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#zipwith
 * 
 */
template<typename CONTAINER_A, typename CONTAINER_B, typename FNJOIN>
auto zipwith(const CONTAINER_A& A, const CONTAINER_B& B, FNJOIN fnjoin)
```

<!-- load -->

<!-- load tests/zipwith.cpp fenced=cpp -->

```cpp
#include "flow.hpp"
using namespace fw;

int main() {
    auto sum = [](auto x, auto y) { return x + y; };
    auto concat = [](auto x, auto y) { return "{}{}" | Format(x, y); };

    range(1, 20) | ZipWith(range(11, 15), sum) | Write(); // [12, 14, 16, 18]

    zipwith(range(1, 5), range(11, 20), concat) | Write(); // [111, 212, 313, 414]

    //junta dois char em uma string
    auto fnjoin = [](auto x, auto y) { return std::string{x, y}; };

    "ABCDEF"s | ZipWith("abcdef"s, fnjoin) | Write(); // [Aa, Bb, Cc, Dd, Ee, Ff]

    zipwith(range(10), "pterodactilo"s, concat) | Write(); // [0p, 1t, 2e, 3r, 4o, 5d, 6a, 7c, 8t, 9i]

    range(10) | ZipWith(range(10), sum) | Write(); // [0, 2, 4, 6, 8, 10, 12, 14, 16, 18]
}
```

<!-- load -->

### ENUMERATE

<!-- load flow.hpp fenced=cpp:extract=enumerate -->

```cpp

/**
 * @note #### `enumerate(CONTAINER<T> container) -> vector<pair<int, T>>`
 * @note #### `CONTAINER<T> container|Enumerate()-> vector<pair<int, T>>`
 * 
 * @note - Retorna um vetor de pares com os indices seguidos dos elementos originais do vetor.
 * 
 * @note #### Parâmetros
 * @note `param: container` Container a ser enumerado.
 * @note `return` Vector com os pares.
 * 
 * @note #### Exemplos
 * @note `vector<int> vet {1, 2, 3};`
 * @note `enumerate(vet) | Join() | Write(); // [(0, 1), (1, 2), (2, 3)]`
 * @note `vet|Enumerate()| Join() | Write(); // [(0, 1), (1, 2), (2, 3)]`
 * 
 * @note #### Veja  mais exemplos em https://github.com/senapk/flow#enumerate
 */
template<typename CONTAINER>
auto enumerate(const CONTAINER& container)
```

<!-- load -->

<!-- load tests/enumerate.cpp fenced=cpp -->

```cpp
#include "flow.hpp"

using namespace fw;
int main() {

    std::vector<int> a {1, 3, 2, 5};

    for (auto [i, x] : a | fw::Enumerate()) {
        format("({}:{})", i, x) | Write(""); 
        // (0:1)(1:3)(2:2)(3:5)
    }
    write("");

    fw::enumerate(a) | Join() | Write();  
    // (0, 1), (1, 3), (2, 2), (3, 5)

    "banana"s | Enumerate() | Join(", ") | Text("[{}]") | Write(); 
    // [(0, b), (1, a), (2, n), (3, a), (4, n), (5, a)]

    std::vector<double> d = {1.2, 2.1, 5.3, 6.7, 9.34};
    d   | Enumerate() 
        | Map([](auto p){ return format("{:_^5}:{%.2f}", p.first, p.second); })
        | Join("\n")
        | Write();

    // __0__:1.20
    // __1__:2.10
    // __2__:5.30
    // __3__:6.70
    // __4__:9.34
}
```

<!-- load -->

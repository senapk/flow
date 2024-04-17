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

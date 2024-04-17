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

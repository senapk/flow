

/**
 * @note #### `slice(CONTAINER<T> container, int begin, int end) -> vector<T>`
 * @note #### `CONTAINER<T> container| Slice(int begin, int end) -> vector<T>`
 * @note #### `slice(string container, int begin, int end) -> string`
 * @note #### `string container| Slice(int begin, int end) -> string`
 * 
 * @note - Fatia um container retornando um `vector` com os elementos copiados.
 * @note - Funciona como a função `slice` do Python ou do Javascript. 
 * @note - Os índices podem ser negativos para indicar que a contagem deve ser feita a partir do final.
 * @note - Se o container for uma string, retorna uma string.
 * 
 * @note #### Parâmetros
 * @note `param: container` container a ser fatiado.
 * @note `param: begin` índice inicial.
 * @note `param: end` índice final.
 * @note `return` vector com os elementos copiados.
 * 
 * @note #### Exemplos
 * @note `vector<int> vet {1, 2, 3, 4, 5};`
 * @note `slice(vet, 1, -1) | Join() | Write(); // [2, 3, 4]`
 * @note `vet| Slice(1, -1) | Join() | Write(); // [2, 3, 4]`
 * 
 * @note #### Veja  mais exemplos em https://github.com/senapk/flow#slice
 */

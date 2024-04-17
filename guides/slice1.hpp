
/**
 * @note #### `slice(CONTAINER<T> container, int begin = 0) -> vector<T>`
 * @note #### `slice(      string container, int begin = 0) -> string`

 * @note #### `CONTAINER<T> container| Slice(int begin = 0) -> vector<T>`
 * @note #### `      string container| Slice(int begin = 0) -> string`
 * 
 * @note - Fatia um container retornando um `vector` com os elementos copiados.
 * @note - Funciona como a função `slice` do Python ou do Javascript.
 * @note - Se não passado nenhum parâmetro, copia todos os elementos.
 * @note - Os índices podem ser negativos para contar a partir final.
 * @note - Se o container for uma string, retorna uma string.
 * @note - Se o container for qualquer outro como vetor, set, map, list, array, retorna um vetor.
 * 
 * @note #### Parâmetros
 * @note `param: container` container a ser fatiado.
 * @note `param: begin` (opcional) índice inicial.
 * @note `return` vector com os elementos copiados.
 * 
 * @note #### Exemplos
 * @note `vector<int> vet {1, 2, 3, 4, 5};`
 * @note `slice(vet, 1)  | Join() | Write(); // [2, 3, 4, 5]`
 * @note `slice(vet, -2) | Join() | Write(); // [4, 5]`
 * @note `vet | Slice(1) | Join() | Write(); // [2, 3, 4, 5]`
 * 
 * @note #### Veja  mais exemplos em https://github.com/senapk/flow#slice
 */


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

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

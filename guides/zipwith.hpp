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

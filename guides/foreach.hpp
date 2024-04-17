/**
 * @note #### `foreach(CONTAINER container, FUNCTION fn) -> void`
 * @note #### `CONTAINER container| Foreach(FUNCTION fn) -> void`
 * 
 * @note - Aplica a função fn em cada elemento do container.
 * 
 * @note #### Parâmetros
 * @note `param: container` Container a ser iterado.
 * @note `param: fn` Função a ser aplicada em cada elemento.
 * 
 * @note #### Exemplos
 * std::vector<int>{1, 2, 3, 4} | Foreach([&](int x) { std::cout << x; });
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#zipwith
 */

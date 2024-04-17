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

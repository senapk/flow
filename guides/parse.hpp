/**
 * @note #### `parse<READABLE>(str value) -> READABLE`
 * @note #### `str value|STRTO<READABLE>()-> READABLE`
 * 
 * @note - Transforma de string para o tipo solicitado utilizando o operador de extração de stream.
 * @note - Dispara uma exceção caso a conversão não seja possível.
 * 
 * @note #### Parâmetros
 * @note `param: READABLE` Tipo a ser convertido.
 * @note `param: value` String a ser convertida.
 * @note `return` Valor convertido.
 * @note `throws: std::runtime_error` Caso a conversão não seja possível.
 * 
 * @note #### Exemplos
 * @note `parse<int>("1") | Write(); // 1`
 * @note `parse<double>("1.2") | Write(); // 1.2`
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#parse
 * 
*/

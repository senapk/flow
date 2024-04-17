/**
 * @note #### `unpack<...TS>(str value, char delimiter) -> tuple<TS...>`
 * @note #### `str value| UNPACK<...TS>(char delimiter) -> tuple<TS...>`
 * 
 * @note - Transforma de string para tupla dados os tipos de cada elemento e o char separador.
 * 
 * @note #### Parâmetros
 * @note `param: TS...` Tipos a serem extraídos.
 * @note `param: value` String a ser convertida.
 * @note `param: delimiter` Caractere separador entre os elementos.
 * @note `return` Tupla com os elementos convertidos.
 * 
 * @note #### Exemplos
 * @note unpack<int, double, std::string>("1:2.4:uva", ':') | Write(); // (1, 2.4, "uva") 
 * @note "1:2.4:uva"| UNPACK<int, double, std::string>(':') | Write(); // (1, 2.4, "uva")
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#unpack
 * 
 */

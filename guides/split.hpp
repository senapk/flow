/**
 * @note #### `split(str content, char delimiter = " ") -> vector<str>`
 * @note #### `str content| Split(char delimiter = " ") -> vector<str>`
 * 
 * @note - Transforma uma string em um vetor de strings, separando pelo delimitador.
 * 
 * @note #### Parâmetros
 * @note `param: content` String a ser separada.
 * @note `param: delimiter` (opcional) Caractere delimitador.
 * @note `return` Vetor de strings.
 *
 * @note #### Exemplos
 * @note `split("a,b,c", ",") | Join() | Write(); // [a, b, c]`
 * @note `"a,b,c"| Split(",") | Join() | Write(); // [a, b, c]`
 * @note `"a, b, c"| Split(", ") | Join() | Write(); // [a, b, c]`
 * @note `split("a b c") | Join() | Write(); // [a, b, c]`
 * @note `"a b c"|Split()| Join() | Write(); // [a, b, c]`
 *  
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#split
 */

/**
 * @note #### `join(T container, str separator = ", ", str cfmt = "") -> str`
 * @note #### `T container| Join(str separator = ", ", str cfmt = "") -> str`
 * 
 * @note - Transforma um container, par ou tupla em string.
 * @note - Se os elementos não forem strings, eles serão transformados pela função `text`.
 * 
 * @note #### Parâmetros
 * @note `param: container` Container a ser transformado em string.
 * @note `param: separtor` demilitador utilizado para juntar os elementos.
 * @note `param: cfmt` fortação a ser aplicada em cada elemento do container.
 * @note `return` String com os elementos concatenados.
 * 
 * @note  #### Exemplos
 * @note `join(vector<int>{1, 2, 3}, " ") | Write(); // "1 2 3"`
 * @note `vector<int>{1, 2, 3} | Join("=") | Write(); // "1=2=3"`
 * @note `vector<int>{1, 2, 3} | Join("; ") | Text("[{}]") | Write(); // "[1; 2; 3]"`
 * @note `vector<int>{1, 2, 3} | Join("; ", "%02d") | Text("[{}]") | Write(); // "[01; 02; 03]"`
 * 
 * @note  #### Mais exemplos em https://github.com/senapk/flow#join
 */

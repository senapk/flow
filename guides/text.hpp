/**
 * @note #### `text(T data,  str cfmt = "") -> str`
 * @note #### `T data | Text(str cfmt = "") -> str`
 * @note - Converte o dado passado em string.
 * 
 * @note #### Parâmetros
 * @note `param: data` Dado a ser convertido.
 * @note `param: cfmt`: parâmetro de formatação tal qual printf como "%.2f"
 * @note `param: cfmt`: modo de formatação usando braces para substituição "antes {%2f} depois"
 * @note `return` String com o dado convertido.
 * 
 * @note #### Funcionamento para tipos primitivos
 * @note - Converte o dado em string.
 * @note - Se `cfmt` for passado, o dado será formatado usando o modelo do `printf`.
 * @note - Se não tiver `cfmt`, o dado será convertido diretamente para string usando operator<<
 * @note `text(1.2) | Write(); // "1.2"
 * @note `text(1.2, "%.4f") | Write(); // "1.2000"
 * @note `1.2 | Text("%.4f") | Write(); // "1.2000"
 * @note `text(1.2, "%.4f") | Write(); // "1.2000"`
 * 
 * @note #### Utilizando {} como placeholder
 * @note - O {} pode ser utilizado como o local onde a variável será inserida.
 * @note - O conteúdo do {} será formatado de acordo com o `cfmt`.
 * @note "domingo" | Text("Hoje é {}.") | Write(); // "Hoje é domingo."
 * @note 3.1415 | Text("O valor de pi é {%.2f}.") | Write(); // "O valor de pi é 3.14."
 * 
 * @note #### Funcionamento para pair e tuple
 * @note - Para pair e tuple, o texto é gerado com os elementos separados por vírgula.
 * @note `text(std::pair<int, int>(2, 1)) | Write(); // "(2, 1)"`
 * 
 * @note #### Padding e alinhamento
 * @note - O alinhamento pode ser feito com <, > ou ^.
 * @note - O tamanho do campo pode ser definido com um número.
 * @note - O padding pode ser feito com qualquer caractere e definido pelo símbolo :.
 * @note `text(1.2, "<10:_") | Write(); // "1.2_______"`
 * @note `text(1.2, ">10:_") | Write(); // "_______1.2"`
 * @note `text(1.2, "^10:_") | Write(); // "___1.2____"`
 * @note `text(1.2, "<10:0") | Write(); // "1.20000000"`
 * @note `"amigo" | Text("Meu {^10:0}.") | Write(); // "Meu 00amigo000."`
 * 
 * @note  #### Mais exemplos em https://github.com/senapk/flow#text
 */

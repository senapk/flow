/**
 * @note #### `format(str fmt, Args ...args ) -> str`
 * @note #### `str fmt| FORMAT(Args ...args ) -> str`
 * 
 * @note - Formata uma string com base nos argumentos passados.
 * @note - A função `text` é chamada para cada argumento {}
 * @note - Utilizando um modelo de chaves para posicionar os argumentos.
 * @note - Se dentro da chave, houver um string de formatação, o dado será formatado com base nela.
 * @note - Não primitivos são formatados de acordo com a função `text`
 * 
 * @note #### Parâmetros
 * @note `param: fmt` O texto com os {} para substituir pelos argumentos.
 * @note `param: args` Os argumentos a serem substituídos.
 * @note `return` O texto formatado.
 * 
 * @note #### Exemplos
 * @note `format("O {} é {%0.2f}.", "pi", 3.141592653) | Write(); //o pi e 3.14.`
 * @note `"O {} é {%0.2f}." | Format("pi", 3.141592653) | Write(); //o pi e 3.14.`
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#format
 * 
 */

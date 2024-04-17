
#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <array>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <memory>

//--------------------------------------------------------
// BIBLIOTECA HEADER ONLY PARA C++ 
//     MANIPULAÇÃO DE TEXTO
//         FORMAT, TOSTR, PRINT, WRITE, split, JOIN
//     E PROGRAMAÇÃO FUNCIONAL
//         MAP, filter, SLICE, enumerate
//     EM MODO FUNÇÃO E MODO PIPELINE
//--------------------------------------------------------
//  VERSÃO 1.0.0
//  https://github.com/senapk/cppaux
//--------------------------------------------------------

/*

/*
composite
    Align
    CFMT


    serial

    posso fazer o format com cfmt e deixar só o serial aqui


    posso manter o show aqui pra fazer o papel que era do write
pipelines
    o join daqui é private para ser chamado recursivamente

    vet<double> | serial("%.2f") | write();

*/



namespace text {

using str_view = std::string_view;

//--------------------------------------------------------
//-------------------- ALIGN -------------- --------------
//--------------------------------------------------------

class Align {
    char align_mode { 0 }; //< > or ^, default is center
    int  align_size { 0 }; //size of the field
    char pad_char   { ' ' }; //char used to pad the field
    std::string format { "" }; //filtered format string

    bool extract_align() {
        std::string align_str_size;

        size_t i {0}, j {0};
        for (i = 0; i < format.size(); ++i) {
            if (format[i] == '<' || format[i] == '>' || format[i] == '^') { //achei o alinhamento
                this->align_mode = format[i];

                for (j = i + 1; j < format.size(); ++j) { //extraindo o tamanho do alinhamento
                    if (format[j] >= '0' && format[j] <= '9') {
                        align_str_size += format[j];
                    } else { // terminou o tamanho
                        break;
                    }
                }
                if (align_str_size.empty()) {
                    this->align_size = 0;
                    std::cout << "fail: format symbol `" << format[i] << "` must be followed by a size\n";
                    exit(1);
                }
                this->align_size = std::stoi(align_str_size);
                this->format.erase(i, j - i);
                return true;
            }
        }
        return false;
    }

    void extract_pad() {
        //search for : char in format, if exists and is followed by a char, then use that char as padding, and remove both from string
        auto pos = this->format.find(':');
        if (pos != std::string::npos) {
            if (pos + 1 < format.size()) {
                this->pad_char = format[pos + 1];
                this->format.erase(pos, 2);
            } else {
                std::cout << "fail: format symbol `:` must be followed by a padding char\n";
                exit(1);
            }
        }
    }
public:

    Align(str_view format) {
        this->format = format;
        this->extract_pad();
        this->extract_align();
    }

    std::string align_text(const std::string& str) {
        int len = str.length();
        if(this->align_mode == 0 || this->align_size < len) { 
            return str; 
        }
        int diff = this->align_size - len;
        
        //default is center
        int padleft = diff/2;
        int padright = diff - padleft;
        if(this->align_mode == '>') {
            padleft = diff;
            padright = 0;
        }
        else if(this->align_mode == '<') {
            padleft = 0;
            padright = diff;
        }
        return std::string(padleft, this->pad_char) + str + std::string(padright, this->pad_char);
    }

    const std::string& get_filtered_format() {
        return this->format;
    }
    int get_align_size() {
        return this->align_size;
    }
    char get_pad_char() {
        return this->pad_char;
    }
    char get_align_mode() {
        return this->align_mode;
    }
};

//--------------------------------------------------------
//-------------------- CFMT  -----------------------------
//--------------------------------------------------------

class CFMT {

    //transformation using sprintf
    template <typename T>
    static std::string c_transform(const T& data, const str_view& format) {
        std::string fmt(format);
        auto size = std::snprintf(nullptr, 0, fmt.c_str(), data);
        std::string output(size + 1, '\0');
        std::sprintf(&output[0], fmt.c_str(), data);
        if (output.back() == '\0') 
            output.pop_back();
        return output;
    }

    //conversion to string using stringstream
    template <typename T>
    static std::string sstream_transform(const T& data) {
        std::stringstream ss;
        ss << data;
        return ss.str();
    }


    template <typename T>
    static std::string process(const T& data, const str_view& format) 
    {
        if (format == "%s" || format == "") {
            return sstream_transform(data);
        }
        if (format.size() > 0 && format.find("%s") != std::string::npos) {//formatting a non string with %s
            return process(sstream_transform(data), format);
        }
        return c_transform(data, format);
    }

    //validate if the format is correct for a string
    static std::string process(const std::string& data, const str_view& format) 
    {
        return process(data.c_str(), format);
    }
    
    //validate if the format is correct for a const char *
    //write specialization for const char *
    static std::string process(const char* const& data, const str_view& format) 
    {
        if (format == "%s" || format == "") {
            return data;
        }
        return CFMT::c_transform(data, format);
    };

    
public:

    template <typename T>
    static std::string format(const T& data, const str_view& format) 
    {
        Align align(format);
        std::string filtered = align.get_filtered_format();
        return align.align_text(process(data, filtered));
    }
};

//--------------------------------------------------------
//-------------------- TOSTR PROTOTYPE -------------------
//--------------------------------------------------------

template <typename T> std::string tostr(const T& t     , const str_view& format = "");

//--------------------------------------------------------
//-------------------- JOIN  -----------------------------
//--------------------------------------------------------

namespace hide {
template <typename CONTAINER> 
std::string __join(const CONTAINER& container, const str_view& separator, const str_view& cfmt) 
{ 
    std::stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it == container.begin() ? "" : separator);
        ss << tostr(*it, cfmt);
    }
    return ss.str();
}

template <typename... Ts>
std::string __join(std::tuple<Ts...> const &the_tuple, const str_view& separator, const str_view& cfmt)
{
    std::stringstream ss;
    std::apply( [&](Ts const &...tuple_args) {
            std::size_t n{0};
            ((ss << tostr(tuple_args, cfmt) << (++n != sizeof...(Ts) ? separator : "")), ...);
        }, the_tuple);
    return ss.str();
}

template <typename T1, typename T2>
std::string __join(const std::pair<T1, T2>& the_pair, const str_view& separator, const str_view& cfmt)
{
    std::stringstream ss;
    ss << tostr(the_pair.first, cfmt) << separator << tostr(the_pair.second, cfmt);
    return ss.str();
}
}
template <typename T>
std::string join(const T& container, const str_view& separator = "", const str_view& cfmt = "") 
//[[join]]
{
    return hide::__join(container, separator, cfmt);
}

//class
struct JOIN {
    str_view delimiter;
    str_view cfmt;

//__guide join
/**
 * @note #### `join(T container, str separator = "", str cfmt = "") -> str`
 * @note #### `T container| JOIN(str separator = "", str cfmt = "") -> str`
 * 
 * @note - Transforma um container, par ou tupla em string.
 * @note - Se os elementos não forem strings, eles serão transformados pela função `tostr`.
 * 
 * @note #### Parâmetros
 * @note `param: container` Container a ser transformado em string.
 * @note `param: separator` Separador entre os elementos.
 * @note `param: cfmt` String de formatação.
 * @note `return` String com os elementos concatenados.
 * 
 * @note  #### Exemplos
 * @note `join(vector<int>{1, 2, 3}, " ") | WRITE(); // "1 2 3"`
 * @note `vector<int>{1, 2, 3} | JOIN("=") | WRITE(); // "1=2=3"`
 * @note `vector<int>{1, 2, 3} | JOIN("=", "%02d") | WRITE(); // "01=02=03"`
 * 
 * @note  #### Mais exemplos em https://github.com/senapk/flow#join
 */
    JOIN(const str_view& delimiter = "", const str_view& cfmt = "") : delimiter(delimiter), cfmt(cfmt) {}
    template <typename CONTAINER> std::string operator()(const CONTAINER& v) const { return join(v, delimiter, cfmt); }
    template <typename T> friend std::string operator|(const T& v, const JOIN& obj) { return obj(v); }
};

//--------------------------------------------------------
//-------------------- TOSTR -----------------------------
//--------------------------------------------------------

namespace hide {
template <typename T>             inline std::string __tostr(const T& t                      , const str_view& format) { return CFMT::format(t, format); }
                                  inline std::string __tostr(int i                           , const str_view& format) { return CFMT::format(i, format); }
                                  inline std::string __tostr(bool b                          , const str_view& format) { (void) format; return b ? "true" : "false"; }
                                  inline std::string __tostr(const char* s                   , const str_view& format) { return CFMT::format(s, format); }
                                  inline std::string __tostr(const std::string& s            , const str_view& format) { return CFMT::format(s, format); }
                                  inline std::string __tostr(const str_view& s               , const str_view& format) { return CFMT::format(s, format); }
template <typename A, typename B> inline std::string __tostr(const std::pair<A,B>& p         , const str_view& format) { return "(" + tostr(p.first, format) + ", " + tostr(p.second, format) + ")"; }
template <typename T>             inline std::string __tostr(const std::list<T>& t           , const str_view& format) { return "[" + join(t, ", ", format) + "]"; }
template <typename T>             inline std::string __tostr(const std::vector<T>& t         , const str_view& format) { return "[" + join(t, ", ", format) + "]"; }
template <typename ...Ts>         inline std::string __tostr(const std::tuple<Ts...>& t      , const str_view& format) { return "(" + join(t, ", ", format) + ")"; }
template <typename T, size_t N>   inline std::string __tostr(const std::array<T, N>& t       , const str_view& format) { return "[" + join(t, ", ", format) + "]"; }
template <typename T>             inline std::string __tostr(const std::set<T>& t            , const str_view& format) { return "{" + join(t, ", ", format) + "}"; }
template <typename K, typename T> inline std::string __tostr(const std::map<K,T>& t          , const str_view& format) { return "{" + join(t, ", ", format) + "}"; }
template <typename T>             inline std::string __tostr(const std::unordered_set<T>& t  , const str_view& format) { return "{" + join(t, ", ", format) + "}"; }
template <typename K, typename T> inline std::string __tostr(const std::unordered_map<K,T>& t, const str_view& format) { return "{" + join(t, ", ", format) + "}"; }
template <typename T>             inline std::string __tostr(const std::shared_ptr<T>& t     , const str_view& format) { return t == nullptr ? "null" : tostr(*t, format); }

}

template <typename T> std::string tostr(const T& data     , const str_view& cfmt) 
{ 
    return hide::__tostr(data, cfmt); 
}

//class
struct TOSTR {
    str_view cfmt;

//__guide tostr
/**
 * @note #### `tostr(T data, str cfmt = "") -> str`
 * @note #### `T data| TOSTR(str cfmt = "") -> str`
 * @note - Converte o dado passado em string.
 * 
 * @note #### Parâmetros
 * @note `param: data` Dado a ser convertido.
 * @note `param: cfmt` Parâmetro de formatação no modo printf.
 * @note `return` String com o dado convertido.
 * 
 * @note #### Funcionamento para tipos primitivos
 * @note - Converte o dado em string.
 * @note - Se `cfmt` for passado, o dado será formatado usando o modelo do `printf`.
 * @note `tostr(1.2) | WRITE(); // "1.2"`
 * @note `tostr(1.2, "%.4f") | WRITE(); // "1.2000"`
 * 
 * @note #### Funcionamento para containers
 * @note - Elementos são impressos usando vírgulas como separador.
 * @note `vector`, `list` e `array` são impressos entre colchetes. 
 * @note `map` e `set` são impressos entre chaves. 
 * @note `pair` e `tuple` são impressos entre parênteses.
 * @note - O parâmetro de formatação é aplicado em todos os elementos do container recursivamente.
 * @note `tostr(list<int>{1,2,3}, "%02d") | WRITE(); //[01, 02, 03]`
 * 
 * @note #### Formatação personalizada
 * @note - Veja a função `join`.
 * @note `std::vector<int> vet {1, 2, 3};`
 * @note `join(vet, " - ", "%02d") | WRITE(); // "01 - 02 - 03"`
 * 
 * @note #### Funcionamento para tipos do usuário
 * @note - Basta implementar a função de saída
 * @note `ostream& operador <<(ostream& os, TIPO tipo)`.
 * 
 * @note  #### Exemplos
 * @note `tostr(std::list<int>{1,2,3}, "%02d") | WRITE(); //[01, 02, 03]`
 * @note `std::pair<int, int>(2, 1) | TOSTR() | WRITE(); //(2, 1)`
 * 
 * @note  #### Mais exemplos em https://github.com/senapk/flow#tostr
 */
    TOSTR(const str_view& cfmt = "") : cfmt(cfmt) {}

    template <typename T> std::string operator()(const T& t) const { return tostr(t, cfmt); }
    template <typename T> friend std::string operator|(const T& v, const TOSTR& obj) { return obj(v); }
};

//--------------------------------------------------------
//-------------------- FORMAT ----------------------------
//--------------------------------------------------------






//--------------------------------------------------------
//-------------------- PRINT------------------------------
//--------------------------------------------------------

template<typename... Args> std::string print(std::string fmt, Args ...args)
{ 
    auto result = FORMAT<Args...>(args...)(fmt);
    std::cout << result;
    return result;
}
//class
template<typename... Args> 
struct PRINT {
    std::tuple<Args...> args;

    PRINT(Args ...args): args(std::forward<Args>(args)...) { }
    std::string operator()(std::string fmt) { return print(fmt, args); }
    friend std::string operator|(std::string fmt, PRINT<Args...> obj) { return obj(fmt); }
};

//--------------------------------------------------------
//-------------------- WRITE -----------------------------
//--------------------------------------------------------


template <typename PRINTABLE> const PRINTABLE& write(const PRINTABLE& data, str_view end = "\n") 
//[[write]]
{
    std::cout << tostr(data) << end;
    return data;
}

//class
struct WRITE {
    str_view end;

//__guide write
/**
 * @note #### `write(T data, str end = "\n") -> T`
 * @note #### `T data| WRITE(str end = "\n") -> T`
 * 
 * @note - Envia o dado para o `std::cout` quebrando a linha.
 * @note - Se o dado não for uma `string`, será convertido pela função `tostr`.
 * @note - O modo pipe é `| WRITE()`.
 * 
 * @note #### Parâmetros
 * @note `param: data` Dado a ser transformado e impresso.
 * @note `param: end` (opcional) String a ser inserida no final da linha.
 * @note `return` O dado original recebido.
 * 
 * @note #### Exemplos
 * @note `write(vector<int> {1, 2, 3}); // [1, 2, 3]`
 * @note `vector<int> {1, 2, 3} | WRITE(); // [1, 2, 3]`
 * 
 * @note #### Veja mais exemplos em https://github.com/senapk/flow#write
 */
    WRITE(str_view end = "\n"): end(end) { }

    template <typename PRINTABLE>        const PRINTABLE& operator()(const PRINTABLE& data           ) { return write(data, end); }
    template <typename PRINTABLE> friend const PRINTABLE& operator| (const PRINTABLE& data, WRITE obj) { return obj(data); }
};

}
#include <iostream>
#include "fn.hpp"
using namespace fn;
int main() {
    auto a = "aa";              //const char *
    auto b = std::string("bb"); //std::string
    auto c = "cc"s;             //std::string

    auto d = +"23.556"s;        //double
    auto e = (int) +"23.556"s;  //int (cast)

    std::cout << a <<  " " << b << " " << c << " " << d << " " << e << std::endl;
    //aa bb cc 23.556 23
}

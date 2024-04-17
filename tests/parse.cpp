#include "flow.hpp"

int main() {
    double a {fw::parse<double>("1.234")};
    std::cout << a << std::endl;
    // 1.234

    double b {"1.234" | fw::Parse<double>()};
    std::cout << b << std::endl;
    // 1.234
}

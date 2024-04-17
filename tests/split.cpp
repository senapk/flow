#include "flow.hpp"
using namespace fw;

int main() {

    split("eu gosto de comer banana", " ")    | Write();
    // [eu, gosto, de, comer, banana]
    split("a,b,c", ",")                       | Write();
    // [a, b, c]
    split("eu gosto de comer banana", " ")    | Write();
    // [eu, gosto, de, comer, banana]
    split("eu gosto de comer    banana", " ") | Write();
    // [eu, gosto, de, comer, , , , banana]
}

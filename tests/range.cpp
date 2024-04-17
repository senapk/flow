#include "flow.hpp"

using namespace fw;

int main() {
  range(0, 10)     | Write(); // [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  range(0, 10, 2)  | Write(); // [0, 2, 4, 6, 8]
  range(10, 0, -1) | Write(); // [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]

  range(1, 5) | Write(); // [1, 2, 3, 4]
  range(5)    | Write(); // [0, 1, 2, 3, 4]
  range(10, -1, -2) | Write(); // [10, 8, 6, 4, 2, 0]

  range(26)
        | Map([](int x) -> char {return 'a' + x;})
        | Write()  // [a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]
        | Join("") // abcdefghijklmnopqrstuvwxyz
        | Write();

  range(10, -1, -2) | Write(); // [10, 8, 6, 4, 2, 0]

  5 | Range() | Write(); // [0, 1, 2, 3, 4]

  range(-10, 10, 2) | Write(); // [-10, -8, -6, -4, -2, 0, 2, 4, 6, 8]
  range(10, 0, -1)  | Write(); // [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]

  auto tochar = [](int x) -> char {return 'a' + x;};
  range(26) 
    | Map(tochar)  
    | Join("") 
    | Write(); // abcdefghijklmnopqrstuvwxyz

  range(25, -1,  -1)
    | Map(tochar)
    | Join("")
    | Write(); // zyxwvutsrqponmlkjihgfedcba
}

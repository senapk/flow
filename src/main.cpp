#include <iostream>
#include <vector>
//#include "source.hpp"

//-------------------- PIPE -----------------------------
//--------------------------------------------------------
//--------------------------------------------------------

template <typename FN_ONE>
class Pipe {
    FN_ONE fn;
public:
    Pipe(FN_ONE fn): fn(fn) {}
    template <typename T>        auto operator()(T data) const            { return fn(data); }
    template <typename T> friend auto operator| (T data, const Pipe& obj) { return obj(data); }
};

template<typename CONTAINER, typename FUNCTION>
auto map(const CONTAINER& container, FUNCTION fn)
//[[map]]
{
    std::vector<decltype(fn(*container.begin()))> aux;
    for (const auto& item : container)
        aux.push_back(fn(item));
    return aux;
}

template <typename FUNCTION>
inline auto map(FUNCTION fn) {
    return Pipe([&](auto container) {
        return map(container, fn);
    });
};


int main()
{
    std::vector<int> v = {1, 2, 3};
    {
        auto x = map(v, [](auto x) { return x + 1; });
        for (int elem : x) {
            std::cout << elem << '\n';
        }
    }
    {
        auto x = v | map([](auto x) { return x + 1; });
        for (int elem : x) {
            std::cout << elem << '\n';
        }
    }
}


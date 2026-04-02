#include <vector>
template <int T> struct Factorial {
    static constexpr int value = T * Factorial<T - 1>::value;
};

template <> struct Factorial<0> {
    static constexpr int value = 1;
};

int main(){
}
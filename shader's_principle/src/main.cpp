#include <iostream>

#include "../include/Screen.hpp"

int main() {
    Screen test_s(100, 10, 'x');
    test_s.display();
    test_s.clean();
    test_s.display();
    return 0;
}

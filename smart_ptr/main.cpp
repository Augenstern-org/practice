#include <iostream>
#include <memory>
#include "sm_ptr.hpp"

int main() {
    std::shared_ptr<int> s1(new int(10));
    auto s2 = s1;
    std::cout << "s1 use_count: " << s1.use_count() << std::endl;
    std::cout << "s2 use_count: " << s2.use_count() << std::endl;
    s1.reset();
    std::cout << "s1 use_count: " << s1.use_count() << std::endl;
    // std::cout << "s1 location: " << s1 << std::endl;
    std::cout << "s2 use_count: " << s2.use_count() << std::endl;

    sm_ptr<int> p1(new int(1));
    auto p2 = p1;
    std::cout << "p1: " << *p1 << std::endl;
    std::cout << "p1 use_count: " << p1.use_count() << std::endl;
    std::cout << "p2 use_count: " << p2.use_count() << std::endl;

    return 0;
}
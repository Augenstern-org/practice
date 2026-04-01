#include "letter.hpp"
#include "mailbox.hpp"
#include "postman.hpp"

#include <string>
#include <vector>
#include <memory>
#include <iostream>


int main(){
    auto letter = std::make_unique<Letter>("test_user", "Hello TEST_USER!");
    Mailbox test_box("test_user");
    Postman postman;

    std::cout << "已生成邮件" << std::endl;

    postman.receiveLetter(std::move(letter));

    std::cout << "已移交邮递员" << std::endl;

    test_box.receiveLetter(postman.deliverLetter());

    std::cout << "邮箱已处理" << std::endl;
}


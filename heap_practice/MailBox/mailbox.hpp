#ifndef MAILBOX_HPP

#define MAILBOX_HPP
#include "letter.hpp"
#include <string>
// #include <vector>
#include <memory>

class Mailbox{

    std::string address;
    std::unique_ptr<Letter> letter_;

    void processLetter(){
        letter_ -> read();
    }

public:

    Mailbox(std::string a):address(a){}
    ~Mailbox() = default;

    void receiveLetter(std::unique_ptr<Letter> letter){
        letter_ = std::move(letter);
        processLetter();
    }

    const std::string getAddr() const {return address;}

};

#endif
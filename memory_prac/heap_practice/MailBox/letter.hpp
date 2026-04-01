#ifndef LETTER_HPP

#define LETTER_HPP
#include <string>
#include <iostream>

class Letter{

    std::string recipient;
    std::string content;

public:

    Letter(std::string r, std::string c):recipient(r), content(c){}
    ~Letter() = default;

    void read() const{
        std::cout << content << std::endl;
    }

    const std::string getRecipient() const {return recipient;}

};

#endif
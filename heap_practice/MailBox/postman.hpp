#ifndef POSTMAN_HPP

#define POSTMAN_HPP
#include "letter.hpp"
#include "mailbox.hpp"
#include <string>
#include <memory>

class Postman{

    std::unique_ptr<Letter> letter_;

public:

    Postman() = default;
    ~Postman() = default;

    void receiveLetter(std::unique_ptr<Letter> letter){
        letter_ = std::move(letter);
    }

    std::unique_ptr<Letter> deliverLetter(){
        if(letter_){
            return std::move(letter_);
        }
        return nullptr;
    }

};

#endif
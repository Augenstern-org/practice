#include <vector>
#include <iostream>
#include <unistd.h>
#include <cmath>

inline int cal_digit(int in_num){
    int count = 1 + std::log10(in_num);
    return count;
}

void display(std::vector<int> target,int back_num){
    if(target.empty()){
        std::cout << "Target is empty." << std::endl;
        return;
    }
    std::cout << std::endl;
    size_t counter = 0;
    for(; counter != target.size(); ++counter){
        for(size_t i = 0; i != target.size(); ++i){
        std::cout << target[i] << " ";
        }
        std::cout << std::endl;

        for(size_t i = 0; i != target.size(); ++i){
            std::string space(cal_digit(target[i]), ' ');
            if(i == counter){
                std::cout << "^" << space;
            }else{
                std::cout << space << " ";
            }
        }
        std::cout << std::endl;
        usleep(300000);
        if(counter != target.size()-1){
            std::cout << "\033[A\033[K" << "\033[A\033[K";
        }
    }
    sleep(1);
    std::cout << "\033[A\033[K" << "\033[A\033[K";
    for(; counter != back_num-2; --counter){
        for(size_t i = 0; i != target.size(); ++i){
        std::cout << target[i] << " ";
        }
        std::cout << std::endl;

        for(size_t i = 0; i != target.size(); ++i){
            std::string space(cal_digit(target[i]), ' ');
            if(i == counter){
                std::cout << "^" << space;
            }else{
                std::cout << space << " ";
            }
        }
        std::cout << std::endl;
        usleep(300000);
        if(counter != back_num-1){
            std::cout << "\033[A\033[K" << "\033[A\033[K";
        }
    }
    std::cout << std::endl;

}

std::vector<int> generator(int a){
    int b = 1;
    std::vector<int> rVec;
    for(; b != a+1; ++b){
        rVec.push_back(b);
    }
    return rVec;
}

int main(){
    int a = 0;
    int b = 0;
    std::cout << "输入两个数，先大后小：\na: ";
    if(!(std::cin >> a)){
        std::cout << "\n呃呃这对吗" << std::endl;
    }
    std::cout << "b: ";
    if(!(std::cin >> b)){
        std::cout << "\n呃呃这对吗" << std::endl;
    }
    auto vec = generator(a);
    display(vec, a-b);
    std::cout << a << " - " << b << " = " << a-b << std::endl;
    // std::string test1(cal_digit(100), '#');
    // std::cout << cal_digit(100) << test1 << std::endl;
}
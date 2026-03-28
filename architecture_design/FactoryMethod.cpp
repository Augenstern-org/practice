#include <iostream>
#include <memory>
#include <string>

// 抽象产品：信件
class Letter {
  public:
    virtual ~Letter() = default;
    virtual void showType() = 0;
};

// 具体产品A：平信
class OrdinaryLetter : public Letter {
  public:
    void showType() override {
        std::cout << "这是一封【平信】，贴了1元的邮票。\n";
    }
};

// 具体产品B：挂号信
class RegisteredLetter : public Letter {
  public:
    void showType() override {
        std::cout << "这是一封【挂号信】，带有追踪条形码。\n";
    }
};

// 邮局（工厂）
class PostOffice {
  public:
    // 工厂方法：返回基类指针，实际指向派生类
    std::unique_ptr<Letter> createLetter(const std::string &type) {
        if (type == "Ordinary") {
            return std::make_unique<OrdinaryLetter>();
        } else if (type == "Registered") {
            return std::make_unique<RegisteredLetter>();
        }
        return nullptr;
    }
};

int main() {
    PostOffice office;

    // 1. 用户拿到了所有权
    auto myLetter = office.createLetter("Registered");

    if (myLetter) {
        myLetter->showType();
    }
    // 2. 函数结束，myLetter 自动析构
    return 0;
}

/*
    适合批量生产某种产品，同时工厂模式便于扩张
    但日后随着需求逐渐变得成熟与复杂，大多会转向生成器模式或者抽象工厂模式
*/
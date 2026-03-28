#include <iostream>
#include <memory>

// --- 抽象产品族 ---
class BaseLetter {
  public:
    virtual ~BaseLetter() = default;
    virtual void print() = 0;
};
class BaseBox {
  public:
    virtual ~BaseBox() = default;
    virtual void print() = 0;
};

// --- 具体产品：中国系列 ---
class ChinaLetter : public BaseLetter {
    void print() override { std::cout << "中国邮政信封\n"; }
};
class ChinaBox : public BaseBox {
    void print() override { std::cout << "中国邮政纸箱\n"; }
};

// --- 具体产品：美国系列 ---
class USLetter : public BaseLetter {
    void print() override { std::cout << "USPS Envelope\n"; }
};
class USBox : public BaseBox {
    void print() override { std::cout << "USPS Box\n"; }
};

// --- 抽象工厂：定义一个物流标准 ---
class AbstractLogisticsFactory {
  public:
    virtual ~AbstractLogisticsFactory() = default;
    // 同时生产多种配套产品
    virtual std::unique_ptr<BaseLetter> createLetter() = 0;
    virtual std::unique_ptr<BaseBox> createBox() = 0;
};

// --- 具体工厂：中国邮政工厂 ---
class ChinaFactory : public AbstractLogisticsFactory {
  public:
    std::unique_ptr<BaseLetter> createLetter() override {
        return std::make_unique<ChinaLetter>();
    }
    std::unique_ptr<BaseBox> createBox() override {
        return std::make_unique<ChinaBox>();
    }
};

// --- 具体工厂：美国邮政工厂 ---
class USFactory : public AbstractLogisticsFactory {
  public:
    std::unique_ptr<BaseLetter> createLetter() override {
        return std::make_unique<USLetter>();
    }
    std::unique_ptr<BaseBox> createBox() override {
        return std::make_unique<USBox>();
    }
};

int main() {
    // 假设我们要开通中国业务
    std::unique_ptr<AbstractLogisticsFactory> factory =
        std::make_unique<ChinaFactory>();

    // 生产全套配套工具，所有权全部移交给调用者
    auto letter = factory->createLetter();
    auto box = factory->createBox();

    letter->print();
    box->print();

    return 0;
}
/*
    适用于生产一系列产品，并且这些产品必须配套存在
    如果风格不匹配会出现问题
*/
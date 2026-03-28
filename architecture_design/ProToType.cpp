#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 附件类（被邮件包含）
class Attachment {
public:
    std::string fileName;
    Attachment(std::string name) : fileName(name) {}
    // 附件也可以支持克隆
    std::unique_ptr<Attachment> clone() const {
        return std::make_unique<Attachment>(*this);
    }
};

// 抽象原型：邮件基类
class Mail {
public:
    virtual ~Mail() = default;
    virtual std::unique_ptr<Mail> clone() const = 0; // 核心：克隆接口
    virtual void setContent(const std::string& text) = 0;
    virtual void show() const = 0;
};

// 具体原型：营销邮件
class MarketingMail : public Mail {
private:
    std::string content;
    std::unique_ptr<Attachment> attachment; // 邮件带有一个附件

public:
    MarketingMail(std::string text, std::string file) 
        : content(text), attachment(std::make_unique<Attachment>(file)) {}

    // 拷贝构造函数：实现深拷贝的关键
    MarketingMail(const MarketingMail& other) 
        : content(other.content) {
        // 重要：不能直接复制指针，要克隆附件对象本身
        if (other.attachment) {
            this->attachment = other.attachment->clone();
        }
    }

    // 实现克隆接口
    std::unique_ptr<Mail> clone() const override {
        // 调用拷贝构造函数
        return std::make_unique<MarketingMail>(*this);
    }

    void setContent(const std::string& text) override { content = text; }

    void show() const override {
        std::cout << "邮件内容: " << content 
                  << " | 附件: " << (attachment ? attachment->fileName : "无") 
                  << " | 地址: " << this << std::endl;
    }
};

int main() {
    // 1. 创建一个“中秋活动”的邮件原型（母本）
    auto prototype = std::make_unique<MarketingMail>("祝您中秋快乐！", "优惠券.pdf");
    std::cout << "--- 原型已准备好 ---" << std::endl;

    // 2. 模拟批量发送：通过克隆产生新邮件
    std::vector<std::unique_ptr<Mail>> mailBox;

    for (int i = 0; i < 3; ++i) {
        auto copy = prototype->clone(); // 克隆！
        copy->setContent("尊敬的客户" + std::to_string(i) + "，祝您中秋快乐！");
        mailBox.push_back(std::move(copy)); // 所有权移交给容器
    }

    // 3. 展示结果
    for (const auto& m : mailBox) {
        m->show();
    }

    return 0;
}
/*
原型模式适合应用场景
如果你需要复制一些对象， 同时又希望代码独立于这些对象所属的具体类， 可以使用原型模式。
这一点考量通常出现在代码需要处理第三方代码通过接口传递过来的对象时。 
即使不考虑代码耦合的情况， 你的代码也不能依赖这些对象所属的具体类， 因为你不知道它们的具体信息。
原型模式为客户端代码提供一个通用接口， 客户端代码可通过这一接口与所有实现了克隆的对象进行交互， 它也使得客户端代码与其所克隆的对象具体类独立开来。
如果子类的区别仅在于其对象的初始化方式， 那么你可以使用该模式来减少子类的数量。
别人创建这些子类的目的可能是为了创建特定类型的对象。
在原型模式中， 你可以使用一系列预生成的、 各种类型的对象作为原型。
客户端不必根据需求对子类进行实例化， 只需找到合适的原型并对其进行克隆即可。

你可以新建一个工厂类来实现注册表， 或者在原型基类中添加一个获取原型的静态方法。
该方法必须能够根据客户端代码设定的条件进行搜索。 
搜索条件可以是简单的字符串， 或者是一组复杂的搜索参数。 
找到合适的原型后， 注册表应对原型进行克隆， 并将复制生成的对象返回给客户端。
最后还要将对子类构造函数的直接调用替换为对原型注册表工厂方法的调用。
*/
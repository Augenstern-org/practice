#include <iostream>
#include <string>
#include <memory>

class Computer {
public:
    std::string cpu;
    std::string gpu;
    int ram = 0;

    void show() {
        std::cout << "配置：CPU-" << cpu << ", GPU-" << gpu << ", RAM-" << ram << "GB" << std::endl;
    }
};

// 生成器类
class ComputerBuilder {
private:
    std::unique_ptr<Computer> computer;
public:
    ComputerBuilder() { computer = std::make_unique<Computer>(); }

    ComputerBuilder& setCPU(std::string cpu) {
        computer->cpu = cpu;
        return *this;
    }

    ComputerBuilder& setGPU(std::string gpu) {
        computer->gpu = gpu;
        return *this;
    }

    ComputerBuilder& setRAM(int ram) {
        computer->ram = ram;
        return *this;
    }

    // 最终移交 unique_ptr 的所有权
    std::unique_ptr<Computer> build() {
        return std::move(computer); 
    }
};

int main() {
    auto myPC = ComputerBuilder()
                .setCPU("Intel i9")
                .setRAM(64)
                .setGPU("RTX 4090")
                .build();

    myPC->show();
    return 0;
}
/*
    适用于某些大型部件
    例如建造房子会有很多的零部件
    但是如果说一栋房子不需要游泳池或者后院，那么这意味着关于游泳池与后院的参数几乎都是无效的
    所以就需要删掉很多参数来重载一些精简过后的构造函数
    但着无疑仍然非常复杂，并且容易填错参数
    生成器模式就是为此而生，它可以一步步指定参数，最后统一构造
*/
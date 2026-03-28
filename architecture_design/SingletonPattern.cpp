#include <iostream>
#include <string>
#include <mutex>

// 日志管理器：单例类
class Logger {
public:
    // 1. 禁用拷贝构造和赋值操作（关键：防止别人复制出一个副本）
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // 2. 全局访问点
    static Logger& getInstance() {
        // C++11 标准确保了即使在多线程环境下，这里的初始化也只发生一次且线程安全
        static Logger instance; 
        return instance;
    }

    // 业务功能
    void log(const std::string& message) {
        // 在实际开发中，这里通常会加锁保护文件写入
        std::cout << "[日志记录]: " << message << std::endl;
    }

private:
    // 3. 私有化构造函数（关键：外部无法通过 new 或 直接声明来创建）
    Logger() {
        std::cout << "--- 日志系统初始化（仅此一次） ---\n";
    }

    ~Logger() {
        std::cout << "--- 日志系统资源释放 ---\n";
    }
};

int main() {
    // 4. 尝试获取实例
    // 注意：这里拿的是引用，因为单例不能被拷贝给 unique_ptr 或 shared_ptr
    Logger& logger1 = Logger::getInstance();
    logger1.log("用户 A 登录了系统");

    Logger& logger2 = Logger::getInstance();
    logger2.log("用户 B 修改了密码");

    // 验证是否是同一个对象
    if (&logger1 == &logger2) {
        std::cout << "logger1 和 logger2 指向同一个内存地址。" << std::endl;
    }

    return 0;
}
/*
单例模式主要解决的是 “资源共享与冲突” 的问题。特点如下：
    唯一性： 确保一个类只有一个实例。
    全局访问： 提供一个全局访问点，让所有人都能找到这个唯一的实例。
    自行创建： 这个类自己负责创建自己的唯一实例，不允许外部通过 new 来创建。
    控制资源： 通常用于管理共享资源，比如：数据库连接池、日志记录器（Logger）、配置管理器、线程池。

适用情境：想象在开发一个大型系统。
    有 100 个模块都在运行。
    如果每个模块都自己 new 一个 Logger 去写同一个文件，就会发生写入冲突（都抢着往文件里塞数据，导致乱码）。
    单例模式：全系统只有一个 Logger 实例，所有的日志都排队通过这一个口子写出去。

单例模式中，情况变了：
    没有所有权移交： getInstance() 返回的是引用（Logger&）或原始指针（不建议）。
        因为单例的生命周期是跟随整个程序的，调用者不拥有它，也就不能销毁它。
    谁来析构？
        静态变量（static Logger instance）存放在内存的“全局/静态存储区”。当 main 函数结束、程序退出时，操作系统会自动调用析构函数。
    为什么不用智能指针？
        如果返回 unique_ptr，第一个调用的模块把它销毁了，第二个模块就没法用了。
        单例的哲学是“我始终在那儿，你们尽管用，不用管我什么时候噶”。
*/
// 能源站分为4类，分别是基础能源站、快充能源站、效率能源站和高级能源站
// 快充能源站充能速度快，效率能源站加工效率高，高级能源站则兼具两者优点
// 不同的能源站有不同的初始容量、充能转化效率、加工效率和加工等级
// 基础能源站：初始容量500，充能转化效率60%，加工效率80%，加工等级2，建造成本为1、时间为1000 tick
// 快充能源站：初始容量600，充能转化效率80%，加工效率60%，加工等级1，建造成本为2、时间为2000 tick
// 效率能源站：初始容量400，充能转化效率50%，加工效率90%，加工等级3，建造成本为2、时间为3000 tick
// 高级能源站：初始容量700，充能转化效率80%，加工效率90%，加工等级3，建造成本为3、时间为5000 tick
// 能源站可以通过处理矿石来获取能量，不同等级的能源站允许处理不同难度的矿石
// 能源站仅支持加工等级小于等于自身等级的矿石
// 
// 
// 能源站可以通过传递能量来相互充能
// 不同能源站之间可以互相传递能量，但会有一定损耗
// 能量传递损耗率为10%，即直接连接的两个能源站衰减10%
// 快充能源站除外，快充能源站与其他能源站连接时不产生能量损耗
// 高级能源站之间传递能量时损耗率降低为5%
// 
// 
// 不同的矿石有不同的开采难度、储量和加工难度
// 开采难度决定了至少需要多少机器人才能开采该矿石
// 储量决定了开采到该矿石的概率，储量越少概率越低
// 加工难度决定了允许加工该矿石的能源站等级
// 低级矿石：开采难度5，储量60%，加工难度1，含能量10
// 普通矿石：开采难度10，储量40%，加工难度2，含能量15
// 高级矿石：开采难度20，储量20%，加工难度3，含能量20
// 能量矿石：开采难度30，储量5%，加工难度3，含能量30
// 
// 
// 每个机器人执行一次动作固定消耗10点能量
// 机器人可以开采矿石并将其运送到能源站进行加工
// 开采矿石需要消耗机器人的能量，开采难度越高所需的机器人越多
// 机器人开采矿石时会有一定概率失败，失败则消耗能量但无法获得矿石
// 机器人将矿石运送到能源站进行加工时也会消耗能量
// 
// 
// 模拟器按照tick进行时间推进
// 每个tick中，机器人可以执行一次动作（开采、运输、待命）
// 能源站可以在每个tick中处理一定数量的矿石，处理数量取决于能源站的加工效率
// 在控制端可以查看当前能源站的能量状态、加工状态和连接状态
// 也可以查看机器人的能量状态和任务状态
// 同时支持tick连续运行与单步推进两种模式
// 默认情况下，模拟器以每秒10个tick的速度连续运行
// 用户可以通过控制端调整tick的运行速度
// 也可以暂停模拟器并单步推进tick（Debug模式）
// 每个tick结束后，系统会输出当前的状态信息，方便用户进行监控和调整
// 并且会sleep一段时间以免错过指令下达的时间点
// 
// 
// 所有能源站与机器人的数据均保存在本地文件中
// 模拟器启动时会读取这些文件以恢复上次的状态
// 模拟器关闭时会将当前的状态保存到文件中以便下次恢复
// 同时，用户也可以手动保存当前状态到指定文件
// 或从指定文件加载状态
// 
// 可以通过特定指令生成log文件
// log文件记录了每个tick中能源站与机器人的状态变化
// 以及用户的操作指令
// log文件以时间戳命名，方便用户进行回溯与分析
// 用户可以选择开启或关闭log记录功能
// 文件名为"log_YYYYMMDD_HHMMSS.txt"
// 最新的log文件可以通过控制端进行查看
// 默认为“Latest.log”




#include <cmath>
#include <new>
#include <memory>
#include <iostream>
#include <fstream>

// 矿石类型定义
struct Ore{
    // 开采耗能-至少需要多少机器人才能开采
    // 矿石储量-越少开采到的概率越低
    // 加工难度-允许加工的能源站等级
    // 所含能量-矿石所含的原始能量
    int energy = 10;
    double total_storage = 0.4;
    int process_difficult = 2;
};

// 矿石等级
struct Low_Ore : public Ore{
    // 低开采难度，储量大，加工难度低
    int energy = 5;
    double total_storage = 0.6;
};

struct High_Ore : public Ore{
    // 高开采难度，储量少，加工难度大
    int energy = 20;
    double total_storage = 0.2;
};

//矿石具体种类
struct Energy_Ore : public High_Ore{
    // 一种特殊的矿石，能量密度极大
    // 但含量少，且对能源站加工等级有要求
    int energy = 30;
    double total_storage = 0.05;
};

struct Common_Ore : public Low_Ore{
    // 最普遍的矿石，但是等级较低
    double total_storage = 0.8;
};



class PowerCore{
    int power;
    int capacity;
    int lvl;
    int type;
    double retention_rate;
    
    public:
    // 构造函数
    PowerCore() =default;
    PowerCore(int p = 100, int c = 500, int l = 2, int t = 1, double r = 0.8):
        power(p), capacity(c), lvl(l), type(t), retention_rate(r){}

    ~PowerCore(){};
    
    // 获取能源站状态

    /*
    const int getPower() const {return power;}
    const int getCapacity() const {return capacity;}
    const int getLevel() const {return lvl;}
    */
    virtual void showStatus() const {
        std::cout << "[PowerCore]\nPower: " << power 
                  << " / Capacity: " << capacity 
                  << " | Level: " << lvl << std::endl;
    }

    //能源站状态检查
    const int checkLevel() const {
        if(lvl <= 0 || lvl > 3){
            std::cout << "Level is illegal! Set it as ";
            if(lvl <= 0){
                std::cout << "1" << std::endl;
                return -1;
            }
            else{
                std::cout << "3" << std::endl;
                return 1;
            }
        }
        return 0;
    }
    const bool tryProcess(int ore_lvl) const {return lvl >= ore_lvl? true: false;}

    //能源站状态更新
    void updateLevel(int lvl_update_to = 2, int condition = 0){
        if(condition = 0) {lvl = lvl_update_to;}
        if(condition = 1) {lvl = 3;}
        if(condition = -1){lvl = 1;}
        checkLevel();
    }
    virtual void consume(int energy){
        power = std::max(power - energy, 0);
    }
    virtual void recharge(int energy) {
        power = std::min(power + energy, capacity);
    }
    //能源站加工行为
    virtual void process(Ore ore_to_process){
        int final_energy;
        recharge(round(ore_to_process.energy * retention_rate));
    }
};

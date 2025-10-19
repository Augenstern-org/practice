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
    int energy;
};

// 矿石等级
struct Low_Ore : public Ore{
    // 低开采难度，储量大，加工难度低

};

struct High_Ore : public Ore{
    // 高开采难度，储量少，加工难度大
};

//矿石具体种类
struct Energy_Ore : public High_Ore{
    // 一种特殊的矿石，能量密度极大
    // 但含量少，且对能源站加工等级有要求
};

struct Common_Ore : public Low_Ore{
    // 最普遍的矿石，但是等级较低
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

// 矿石生命周期：
// 1.经概率判断后被机器人开采
// 2.被机器人运送到对应的能源站
// 3.被能源站消耗，生命周期结束


#ifndef ORE_HPP

#include <string>
#include <memory>

class Ore{
protected:
    int required_energy;
    double storage;
    int process_lvl;
    int energy_content;

public:
    Ore(int r, double s, int p, int e):
        required_energy(r), storage(s), process_lvl(p), energy_content(e){}
    virtual ~Ore() = default;

    bool tryMine(){}

};

#endif

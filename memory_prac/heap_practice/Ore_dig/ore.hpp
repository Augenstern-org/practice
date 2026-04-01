// 矿石生命周期：
// 1.经概率判断后被机器人开采
// 2.被机器人运送到对应的能源站
// 3.被能源站消耗，生命周期结束


#ifndef ORE_HPP

#include <string>
#include <random>

class Ore{
protected:
    int required_energy;
    double storage;
    int process_lvl;
    int energy_content;
    std::string name;

public:
    Ore(int r, double s, int p, int e):
        required_energy(r), storage(s), process_lvl(p), energy_content(e){
        name = "Ore";
    }
    virtual ~Ore() = default;

    const bool tryMine(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist_real(0.0, 1.0);
        if(dist_real(gen) <= storage){
            return true;
        }
        return false;
    }

    // getter
    const int getProcessLvl() const {return process_lvl;}
    const int getRequiredEnergy() const {return required_energy;}
};

class CommonOre: public Ore{
public:
    CommonOre() : Ore(2, 0.6, 1, 5){
        name = "CommonOre";
    }
};

class Advanced_Ore: public Ore{
public:
    Advanced_Ore(): Ore(6, 0.2, 3, 20){
        name = "Advanced_Ore";
    }
};

class Energy_Ore : public Ore{
public:
    Energy_Ore() : Ore(8, 0.05, 3, 40){
        name = "Energy_Ore";
    }
};
#endif

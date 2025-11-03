#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "ore.hpp"
#include <memory>
#include <vector>

enum robot_status{
    status_free,
    status_digging,
    status_transporting,
    status_handling
};

class Robot{
    int power;
    robot_status status_free;
    std::vector<std::shared_ptr<Ore>> ore_list;

public:
    // 不管成没成功都要消耗能量
    const bool digMine(Ore& ore_to_dig){
        const bool p = (ore_to_dig.getRequiredEnergy() > power)? true : false;
        power -= ore_to_dig.getRequiredEnergy();
        return p;
    }

    template<typename T>
    void getMine(T ore_has_digged){
        if(ore_has_digged.tryMine() && digMine(ore_has_digged)){
            auto temp = std::make_shared<T>();
            ore_list.push_back(temp);
        }
    }
};

#endif

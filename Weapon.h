#ifndef WEAPON_H
#define WEAPON_H

#include<iostream>
#include<string>
#include <sstream>

#include "Tool.h"

class Weapon: public Tool{
    private:
        bool isRanged;
        bool canForceLocks;
    public:
        Weapon()
            : Tool(), isRanged(false), canForceLocks(false){};
        Weapon(std::string n, int useTool, float suspicion, bool r, bool lock)
            : Tool(n, useTool, suspicion), isRanged(r), canForceLocks(lock) {}
        
        bool getIsRanged();
        bool getCanForceLocks();
        std::string use() override;
};

bool Weapon::getIsRanged(){
    return isRanged;
}

bool Weapon::getCanForceLocks(){
    return canForceLocks;
}

std::string Weapon::use(){
    consumeUse(1);
    std::stringstream ss;
    ss << uses;
    if (canForceLocks) {
        return name + ": forzaste la cerradura. Usos restantes: " + ss.str();
    } else {
        return name + ": neutralizaste al guardia. Usos restantes: " + ss.str();
    }
}

#endif

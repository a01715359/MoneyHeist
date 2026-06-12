#ifndef WEAPON_H
#define WEAPON_H

#include "Tool.h"
#include <string>

class Weapon : public Tool {
private:
    bool canForceLocks;

public:
    Weapon()
        : Tool(), canForceLocks(false) {}

    Weapon(const std::string& weaponName,
           int totalUses,
           float suspicion,
           bool forceLocks)
        : Tool(weaponName, totalUses, suspicion),
          canForceLocks(forceLocks) {}

    bool getCanForceLocks() const;

    std::string use() override;
};

bool Weapon::getCanForceLocks() const {
    return canForceLocks;
}

std::string Weapon::use() {
    consumeUse();

    if (canForceLocks) {
        return getName() +
               ": forced the lock. Remaining uses: "
               + std::to_string(getUses());
    }

    return getName() +
           ": neutralized the guard. Remaining uses: "
           + std::to_string(getUses());
}

#endif

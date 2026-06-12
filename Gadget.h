#ifndef GADGET_H
#define GADGET_H

#include "Tool.h"
#include <string>

class Gadget : public Tool {
private:
    bool isElectronic;

public:
    Gadget()
        : Tool(), isElectronic(false) {}

    Gadget(const std::string& gadgetName,
           int useTool,
           float suspicion,
           bool elec)
        : Tool(gadgetName, useTool, suspicion),
          isElectronic(elec) {}

    bool getIsElectronic() const;

    std::string use() override;
};

bool Gadget::getIsElectronic() const {
    return isElectronic;
}

std::string Gadget::use() {
    consumeUse();

    if (isElectronic) {
        return getName() +
               ": incapacitated instantly. Remaining uses: "
               + std::to_string(getUses());
    }

    return getName() +
           ": no trace, no witnesses. Remaining uses: "
           + std::to_string(getUses());
}

#endif

#ifndef GADGET_H
#define GADGET_H

#include <iostream>
#include <string>
#include <sstream>

#include "Tool.h"

class Gadget: public Tool{
    private:
        bool isElectronic;
    
    public:
        Gadget()
            : Tool(), isElectronic(false) {};
        Gadget(std::string n, int useTool, float suspicion, bool elec)
            : Tool(n, useTool, suspicion), isElectronic(elec) {}
        bool getIsElectronic();
        std::string use() override;
};

bool Gadget::getIsElectronic(){
    return isElectronic;
}

std::string Gadget::use(){
    consumeUse(1);
    std::stringstream ss;
    ss << uses;
    if (isElectronic) {
        return name + ": incapacitado instantaneamente. Usos restantes: " + ss.str();
    } else {
        return name + ": sin rastro, sin testigos. Usos restantes: " + ss.str();
    }
}

#endif

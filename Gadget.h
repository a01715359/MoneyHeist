#ifndef GADGET_H
#define GADGET_H

#include <iostream>
#include <string>

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
};

bool Gadget::getIsElectronic(){
    return isElectronic;
}

#endif

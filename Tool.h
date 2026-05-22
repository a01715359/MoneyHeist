#ifndef TOOL_H
#define TOOL_H

#include <iostream>
#include <string>

class Tool{
    protected:
        std::string name;
        int uses;
        float suspicionCost;
    public:
        Tool()
            : name(""), uses(0), suspicionCost(0.0){};
        Tool(std::string nTool, int useTool, float suspicionTool)
            : name(nTool), uses(useTool), suspicionCost(suspicionTool){}
        
        std::string getName();
        int getUses();
        float getSuspicionCost();
        void consumeUse(int amountUse);
        bool hasUses();
};

std::string Tool::getName() {
    return name;
}

int Tool::getUses(){
    return uses;
}

float Tool::getSuspicionCost(){
    return suspicionCost;
}

void Tool::consumeUse(int amountUse){
    uses -= amountUse;
}

bool Tool::hasUses(){
    return uses > 0;
}

#endif

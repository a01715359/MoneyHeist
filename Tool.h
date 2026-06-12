#ifndef TOOL_H
#define TOOL_H

#include <string>

class Tool {
protected:
    std::string name;
    int uses;
    float suspicionCost;

public:
    Tool()
        : name(""), uses(0), suspicionCost(0.0) {}

    Tool(const std::string& nTool, int useTool, float suspicionTool)
        : name(nTool), uses(useTool), suspicionCost(suspicionTool) {}

    std::string getName() const;
    int getUses() const;
    float getSuspicionCost() const;

    virtual void consumeUse();
    virtual void consumeUse(int amountUse);

    bool hasUses() const;

    virtual std::string use() = 0;
};

std::string Tool::getName() const {
    return name;
}

int Tool::getUses() const {
    return uses;
}

float Tool::getSuspicionCost() const {
    return suspicionCost;
}

void Tool::consumeUse() {
    if (uses > 0) {
        uses--;
    }
}

void Tool::consumeUse(int amountUse) {
    if (amountUse > 0 && uses >= amountUse) {
        uses -= amountUse;
    }
}
bool Tool::hasUses() const {
    return uses > 0;
}

#endif

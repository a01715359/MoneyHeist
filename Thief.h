
#ifndef THIEF_H
#define THIEF_H

#include <iostream>
#include <string>
#include <vector>

#include "Tool.h"

class Thief{
    private:
        std::string name;
        int hp;
        float suspicion;
        bool goldenKey;
        std::vector<Tool> inventory;

    public:
        Thief()
            : name(""), hp(0), suspicion(0.0), goldenKey(false){};

        Thief(std::string nThief, int health, float susThief, bool key)
            : name(nThief), hp(health), suspicion(susThief), goldenKey(key) {}
        

        std::string getName();
        int getHp();
        float getSuspicion();
        bool getGoldenKey();

        std::vector<Tool> getInventory();

        void setGoldenKey(bool hasKey);
        void setHp(int health);
        void addToInventory(Tool newTool);
        void removeFromInventory(int index);
        void addSuspicion(float amountSuspicion);
        void takeDamage(int amountDamage);
        bool isAlive();
};

std::string Thief::getName(){
    return name;
}

int Thief::getHp(){
    return hp;
}

float Thief::getSuspicion() {
    return suspicion;
}

bool Thief::getGoldenKey() {
    return goldenKey;
}

std::vector<Tool> Thief::getInventory(){
    return inventory;
}

void Thief::setGoldenKey(bool hasKey){
    goldenKey = hasKey;
}

void Thief::setHp(int health){
    hp = health;
}

void Thief::addToInventory(Tool newTool) {
    if(inventory.size() < 2) {
        inventory.push_back(newTool);
    }
}

void Thief::removeFromInventory(int index) {
    inventory.erase(inventory.begin() + index);
}

void Thief::addSuspicion(float amountSuspicion){
    suspicion += amountSuspicion;
}

void Thief::takeDamage(int amountDamage){
    hp -= amountDamage;
}

bool Thief::isAlive(){
    return hp > 0;
}

#endif

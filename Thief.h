#ifndef THIEF_H
#define THIEF_H

#include <iostream>
#include <string>
#include <vector>

#include "Gadget.h"
#include "Weapon.h"

class Thief {
private:
    std::string name;
    int hp;
    float suspicion;
    bool goldenKey;
    std::vector<Tool*> inventory;

public:
    Thief()
        : name(""), hp(0), suspicion(0.0), goldenKey(false) {}

    Thief(std::string nThief, int hpThief,
          float susThief, bool key)
        : name(nThief),
          hp(hpThief),
          suspicion(susThief),
          goldenKey(key) {}

    std::string getName();
    int getHp();
    float getSuspicion();
    bool getGoldenKey();

    std::vector<Tool*>& getInventory();

    void setGoldenKey(bool hasKey);
    void setHp(int damage);

    void addWeapon(std::string name,
                   int uses,
                   float suspicion,
                   bool extra1);

    void addGadget(std::string name,
                   int uses,
                   float suspicion,
                   bool extra1);

    void removeFromInventory(int index);

    void addSuspicion(float amountSuspicion);

    bool isAlive();
};

std::string Thief::getName() {
    return name;
}

int Thief::getHp() {
    return hp;
}

float Thief::getSuspicion() {
    return suspicion;
}

bool Thief::getGoldenKey() {
    return goldenKey;
}

std::vector<Tool*>& Thief::getInventory() {
    return inventory;
}

void Thief::setGoldenKey(bool hasKey) {
    goldenKey = hasKey;
}

void Thief::addWeapon(std::string name,
                      int uses,
                      float suspicion,
                      bool extra1) {

    if (inventory.size() < 2) {

        Tool* newTool = nullptr;

        newTool = new Weapon(name,
                             uses,
                             suspicion,
                             extra1);

        inventory.push_back(newTool);
    }
}

void Thief::addGadget(std::string name,
                      int uses,
                      float suspicion,
                      bool extra1) {

    if (inventory.size() < 2) {

        Tool* newTool = nullptr;

        newTool = new Gadget(name,
                             uses,
                             suspicion,
                             extra1);

        inventory.push_back(newTool);
    }
}

void Thief::removeFromInventory(int index) {
    delete inventory[index];
    inventory.erase(inventory.begin() + index);
}

void Thief::addSuspicion(float amountSuspicion) {
    suspicion += amountSuspicion;
}

void Thief::setHp(int damage) {
    hp -= damage;
}

bool Thief::isAlive() {
    return hp > 0;
}

#endif

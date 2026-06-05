
#ifndef THIEF_H
#define THIEF_H

#include <iostream>
#include <string>
#include <vector>

#include "Weapon.h"
#include "Gadget.h"

class Thief{
    private:
        std::string name;
        int hp;
        float suspicion;
        bool goldenKey;
        std::vector<Tool*> inventory;

    public:
        Thief()
            : name(""), hp(0), suspicion(0.0), goldenKey(false){};

        Thief(std::string nThief, int health, float susThief, bool key)
            : name(nThief), hp(health), suspicion(susThief), goldenKey(key) {}
        
        std::string getName();
        int getHp();
        float getSuspicion();
        bool getGoldenKey();

        std::vector<Tool*> getInventory();

        void setGoldenKey(bool hasKey);
        void setHp(int health);
        void addWeapon(std::string nombre, int usos, float sospecha, bool extra1, bool extra2);
        void addGadget(std::string nombre, int usos, float sospecha, bool extra1);
        // void addToInventory(int tipo, std::string nombre, int usos, float sospecha, bool extra1, bool extra2);
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

std::vector<Tool*> Thief::getInventory(){
    return inventory;
}

void Thief::setGoldenKey(bool hasKey){
    goldenKey = hasKey;
}

void Thief::setHp(int health){
    hp = health;
}

void Thief::addWeapon(std::string nombre, int usos, float sospecha, bool extra1, bool extra2) {
    if(inventory.size() < 2){
    
        Tool* nueva = nullptr;
        nueva = new Weapon(nombre, usos, sospecha, extra1, extra2);
        inventory.push_back(nueva);
    }
}

void Thief::addGadget(std::string nombre, int usos, float sospecha, bool extra1) {
    if(inventory.size() < 2){
    
        Tool* nueva = nullptr;
        nueva = new Gadget(nombre, usos, sospecha, extra1);
        inventory.push_back(nueva);
    }
}
/*
void Thief::addToInventory(int tipo, std::string nombre, int usos, float sospecha, bool extra1, bool extra2) {
    if(inventory.size() < 2){
    
        Tool* nueva = nullptr;
        
        if(tipo == 1 || tipo == 2){
            nueva = new Weapon(nombre, usos, sospecha, extra1, extra2);
        }
        else{
            nueva = new Gadget(nombre, usos, sospecha, extra1);
        }
            inventory.push_back(nueva);
    }
}
*/

void Thief::removeFromInventory(int index) {
    delete inventory[index];
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

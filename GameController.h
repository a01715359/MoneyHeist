#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include<iostream>
#include<string>
#include "Thief.h"

class GameController{
    private:
        Thief thief;
        int currentPhase;
        bool camaraAlert;
    public:
        GameController()
            : thief(), currentPhase(0), camaraAlert(false) {};
        GameController(Thief t, int phase, bool cam)
    : thief(t), currentPhase(phase), camaraAlert(cam){}
        
        int getCurrentPhase();
        bool getCamaraAlert();
        Thief& getThief();
        bool checkGameOver();
        bool nextPhase();
        void handleInteraction(int option);
        void handlePhase1(int optionOne);
        void handlePhase2(int optionTwo);
        void handlePhase3(int optionThree);
        std::string handlePhase4();
        void handlePhase5(int optionFour);
};

int GameController::getCurrentPhase(){
    return currentPhase;
}

bool GameController::getCamaraAlert(){
    return camaraAlert;
}

Thief& GameController::getThief(){
    return thief;
}

bool GameController::checkGameOver(){
    return !thief.isAlive() || (thief.getSuspicion() >= 100.0 
    && currentPhase < 4);
}

bool GameController::nextPhase(){
    return currentPhase < 5 ? (currentPhase++, true) : false;
}

void GameController::handleInteraction(int opcion){
    switch(currentPhase){
        case 1: handlePhase1(opcion); 
            break;
        case 2: handlePhase2(opcion); 
            break;
        case 3: handlePhase3(opcion); 
            break;
        case 4: handlePhase4();       
            break;
        case 5: handlePhase5(opcion); 
            break;
    }
}

void GameController::handlePhase1(int opcion){
    if(opcion == 1){
        Tool* t = thief.getInventory()[0];
        t->consumeUse(1);
        thief.addSuspicion(t->getSuspicionCost());
    } else if(opcion == 2){
        thief.takeDamage(20);
        thief.addSuspicion(40.0);
        thief.setGoldenKey(true);
    }
}

void GameController::handlePhase2(int opcion){
    if(opcion == 1){
    } else if(opcion == 2){
        thief.addSuspicion(15.0);
        camaraAlert = true;
    } else if(opcion == 3){
        Tool* t = thief.getInventory()[0];
        t->consumeUse(1);
    } else if(opcion == 4){
        thief.addSuspicion(35.0);
    }
}

void GameController::handlePhase3(int opcion){
    if(thief.getGoldenKey()){
        nextPhase();
        return;
    }
    if(opcion == 1){
        Tool* t = thief.getInventory()[0];
        t->consumeUse(1);
        thief.addSuspicion(10.0);
    } else if(opcion == 2){
        Tool* t = thief.getInventory()[0];
        t->consumeUse(1);
        thief.addSuspicion(20.0);
    } else if(opcion == 3){
        thief.addSuspicion(25.0);
    }
}

std::string GameController::handlePhase4(){
    std::ostringstream phase4;
    phase4 << thief.getName() << ": Y... finalmente estoy dentro." << std::endl;
    phase4 << "Rodrigo: ¡VAMOS! Toma todo... ¡Dubai nos espera!" << std::endl;
    phase4 << "* Un estruendo sordo resuena en las paredes *" << std::endl;
    phase4 << "* No es un error, es el sistema físico de seguridad *" << std::endl;
    phase4 << "Rodrigo: ¡MALDICIÓN! Activaron la alarma de presión hidrostática." << std::endl;
    phase4 << "¡Sal de ahí! Mi señal se está... estática... ¡##&&#@...!" << std::endl;
    phase4 << thief.getName() << ": ¿Rodrigo, me escuchas? No se te entiende nada." <<std::endl;
    phase4 << "..." << std::endl;
    phase4 << thief.getName() << ": Bueno, supongo que ahora estoy por mi cuenta." << std::endl;
    phase4 << "Y yo que queria hacer esto sin manchar mi ropa, ¡Ni modo!" <<std::endl;
    
    nextPhase();
    return phase4.str();
}

void GameController::handlePhase5(int opcion){
    if(opcion == 1){
        Tool* t = thief.getInventory()[0];
        t->consumeUse(1);
    } else if(opcion == 2){
        thief.takeDamage(30);
    } else if(opcion == 3){
        Tool* t = thief.getInventory()[0];
        t->consumeUse(1);
    } else if(opcion == 4){
        Tool* t = thief.getInventory()[0];
        t->consumeUse(2);
    } else if(opcion == 5){
        Tool* t = thief.getInventory()[0];
        t->consumeUse(1);
        thief.takeDamage(50);
    } else if(opcion == 6){
        Tool* t = thief.getInventory()[0];
        t->consumeUse(1);
        thief.takeDamage(20);
    } else if(opcion == 7){
        thief.takeDamage(50);
    }
}

#endif

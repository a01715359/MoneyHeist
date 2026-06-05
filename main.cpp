#include <iostream>
#include <string>
#include "GameController.h"
#include "Weapon.h"
#include "Gadget.h"

/*
Tool chooseTool(int opcion, Weapon dagger, Weapon gun, Gadget taser, Gadget polvo){
    if(opcion == 1) return dagger;
    if(opcion == 2) return gun;
    if(opcion == 3) return taser;
    return polvo;
}
*/

int main(){
    // --- INTRODUCCION ---
    std::string player;
    std::cout << "Mar: Oye, antes de empezar... ¿cómo te llamas?" << std::endl;
    std::cout << "> ";
    std::cin >> player;
    std::cout << "Mar: Perfecto, " << player << ". Ya estamos dentro del sistema." << std::endl;
    std::cout << "Mar: Elige 2 herramientas antes de entrar." << std::endl;
    
    Thief ladron(player, 100, 0.0, false);  

    // --- SELECCION DE TOOLS ---
    std::cout << "\n1. dagger (5 usos, 10% sospecha)" << std::endl;
    std::cout << "2. gun Silenciosa (3 usos, 2% sospecha)" << std::endl;
    std::cout << "3. Taser Electrico (2 usos, 5% sospecha)" << std::endl;
    std::cout << "4. Polvo Cegador (1 uso, 0% sospecha)" << std::endl;

    int tool1, tool2;
    std::cout << "\nElige tu primera herramienta: ";
    std::cin >> tool1;
    switch(tool1){
        case 1:
            ladron.addWeapon("dagger", 5, 10.0, false, true);
            break;
        case 2:
            ladron.addWeapon("silenced gun", 3, 2.0, true, false);
            break;
        case 3:
            ladron.addGadget("electric taser", 2, 5.0, true);
            break;
        case 4:
            ladron.addGadget("blinding powder", 1, 0.0, false);
            break;
        default: 
            std::cout << "Mar: How much time do you think we have left, huh?" << std::endl;
            std::cout << "Mar: Just choose your tools, and do it fast." << std::endl;
            std::cout << "Choose between 1 and 4" << std::endl;
    }

    std::cout << "Elige tu segunda herramienta: ";
    std::cin >> tool2;
    switch(tool2){
                case 1:
            ladron.addWeapon("dagger", 5, 10.0, false, true);
            break;
        case 2:
            ladron.addWeapon("silenced gun", 3, 2.0, true, false);
            break;
        case 3:
            ladron.addGadget("electric taser", 2, 5.0, true);
            break;
        case 4:
            ladron.addGadget("blinding powder", 1, 0.0, false);
            break;
        default: 
            std::cout << "Mar: How much time do you think we have left, huh?" << std::endl;
            std::cout << "Mar: Just choose your tools, and do it fast." << std::endl;
            std::cout << "Choose between 1 and 4" << std::endl;
    }


    GameController game(ladron, 1, false);

    std::cout << "\nMar: Listo " << player << ", llevas ";
    std::cout << game.getThief().getInventory()[0]->getName() << " y ";
    std::cout << game.getThief().getInventory()[1]->getName() << "." << std::endl;

    // --- FASE 1 ---
    std::cout << "\n=== FASE 1: EL LOBBY ===" << std::endl;
    std::cout << "Mar: Ya estas dentro, " << player << "." << std::endl;
    std::cout << "Mar: Hay un conserje y un guardia. ¿Que haces?" << std::endl;
    std::cout << "1. Usar herramienta" << std::endl;
    std::cout << "2. Noquear a puños (perderas 20 HP y +40% sospecha, pero obtienes la llave dorada)" << std::endl;

    int opcionFase1;
    std::cout << "> ";
    std::cin >> opcionFase1;
    game.handleInteraction(opcionFase1);

    std::cout << "\nHP: " << game.getThief().getHp() << "/100" << std::endl;
    std::cout << "Sospecha: " << game.getThief().getSuspicion() << "%" << std::endl;

    if(game.checkGameOver()){
        std::cout << "\nMar: ¡Te atraparon! Game Over." << std::endl;
        return 0;
    }

    // --- FASE 4 (narrativa) ---
    game.nextPhase();
    game.nextPhase();
    game.nextPhase();
    std::cout << "\n=== FASE 4: LA BOVEDA ===" << std::endl;
    std::cout << game.handlePhase4() << std::endl;

    std::cout << "\nHP final: " << game.getThief().getHp() << "/100" << std::endl;
    std::cout << "Sospecha final: " << game.getThief().getSuspicion() << "%" << std::endl;

    return 0;
}

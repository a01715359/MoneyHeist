#include <iostream>
#include <string>
#include "GameController.h"
#include "Weapon.h"
#include "Gadget.h"

Tool elegirTool(int opcion, Weapon daga, Weapon pistola, Gadget taser, Gadget polvo){
    if(opcion == 1) return daga;
    if(opcion == 2) return pistola;
    if(opcion == 3) return taser;
    return polvo;
}

int main(){
    // --- INTRODUCCION ---
    std::string nombreJugador;
    std::cout << "Rodrigo: Oye, antes de empezar... ¿como te llamas?" << std::endl;
    std::cout << "> ";
    std::cin >> nombreJugador;
    std::cout << "Rodrigo: Perfecto, " << nombreJugador << ". Ya estamos dentro del sistema." << std::endl;
    std::cout << "Rodrigo: Elige 2 herramientas antes de entrar." << std::endl;

    // --- SELECCION DE TOOLS ---
    Weapon daga("Daga", 5, 10.0, false, true);
    Weapon pistola("Pistola Silenciosa", 3, 2.0, true, false);
    Gadget taser("Taser Electrico", 2, 5.0, true);
    Gadget polvo("Polvo Cegador", 1, 0.0, false);

    std::cout << "\n1. Daga (5 usos, 10% sospecha)" << std::endl;
    std::cout << "2. Pistola Silenciosa (3 usos, 2% sospecha)" << std::endl;
    std::cout << "3. Taser Electrico (2 usos, 5% sospecha)" << std::endl;
    std::cout << "4. Polvo Cegador (1 uso, 0% sospecha)" << std::endl;

    int tool1, tool2;
    std::cout << "\nElige tu primera herramienta: ";
    std::cin >> tool1;
    std::cout << "Elige tu segunda herramienta: ";
    std::cin >> tool2;

    Thief ladron(nombreJugador, 100, 0.0, false);

    ladron.addToInventory(elegirTool(tool1, daga, pistola, taser, polvo));
    ladron.addToInventory(elegirTool(tool2, daga, pistola, taser, polvo));
    GameController game(ladron, 1, false);

    std::cout << "\nRodrigo: Listo " << nombreJugador << ", llevas ";
    std::cout << game.getThief().getInventory()[0].getName() << " y ";
    std::cout << game.getThief().getInventory()[1].getName() << "." << std::endl;

    // --- FASE 1 ---
    std::cout << "\n=== FASE 1: EL LOBBY ===" << std::endl;
    std::cout << "Rodrigo: Ya estas dentro, " << nombreJugador << "." << std::endl;
    std::cout << "Rodrigo: Hay un conserje y un guardia. ¿Que haces?" << std::endl;
    std::cout << "1. Usar herramienta" << std::endl;
    std::cout << "2. Noquear a puños (perderas 20 HP y +40% sospecha, pero obtienes la llave dorada)" << std::endl;

    int opcionFase1;
    std::cout << "> ";
    std::cin >> opcionFase1;
    game.handleInteraction(opcionFase1);

    std::cout << "\nHP: " << game.getThief().getHp() << "/100" << std::endl;
    std::cout << "Sospecha: " << game.getThief().getSuspicion() << "%" << std::endl;

    if(game.checkGameOver()){
        std::cout << "\nRodrigo: ¡Te atraparon! Game Over." << std::endl;
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

#include "Gadget.h"
#include "Thief.h"
#include "Weapon.h"
#include <iostream>
#include <string>
#include <limits>

bool checkGameOver(int currentPhase, Thief& thief) {
    return !thief.isAlive() ||
           (thief.getSuspicion() >= 100.0 && currentPhase < 4);
}

bool nextPhase(int& currentPhase) {
    return currentPhase < 5 ? (currentPhase++, true) : false;
}

Tool* findTool(const std::string& toolName, Thief& thief) {
    for (int i = 0; i < (int)thief.getInventory().size(); i++) {
        if (thief.getInventory()[i]->getName() == toolName) {
            return thief.getInventory()[i];
        }
    }
    return nullptr;
}

void handlePhase1(int optionPhase1, Thief& thief) {
    if (optionPhase1 == 1) {
        std::cout << "Choose the tool you want to use" << std::endl;
        std::cout << "1. " << thief.getInventory()[0]->getName() << std::endl;
        std::cout << "2. " << thief.getInventory()[1]->getName() << std::endl;

        int chooseTool = 0;
        std::cin >> chooseTool;
        while (chooseTool != 1 && chooseTool != 2) {
            std::cout << "Invalid option, choose 1 or 2" << std::endl;
            std::cin >> chooseTool;
        }

        Tool* t = thief.getInventory()[chooseTool - 1];
        t->consumeUse(1);
        thief.addSuspicion(t->getSuspicionCost());

    } else if (optionPhase1 == 2) {
        thief.setHp(20);
        thief.addSuspicion(40.0);
        thief.setGoldenKey(true);
        std::cout << thief.getName() << ": Hey, the guard had a key!" << std::endl;
        std::cout << "Mar: keep it, it might come in handy." << std::endl;
        std::cout << "=== YOU NOW HAVE THE GOLDEN KEY === " << std::endl;
    }
}

bool handlePhase2(int optionPhase2, std::string& toolAvailable, int optionRoute,
                  bool& camaraAlert, Thief& thief) {
    if (optionRoute == 73378) {
        if (optionPhase2 == 1) {
            Tool* t = findTool("blinding powder", thief);
            if (t != nullptr && t->hasUses()) {
                t->consumeUse(1);
                thief.addSuspicion(t->getSuspicionCost());
                return true;
            } else {
                toolAvailable =
                    "Mar: Dude, you are doing this on purpose, aren't you? "
                    "Cause you don't even have a blinding powder.\n"
                    "If you wanted one so much, why didn't you just choose it back then?\n"
                    "This is exactly why I told you I better hoped you knew what you were doing.\n"
                    "Now choose again, and try to do something you can actually do.";
                return false;
            }
        } else if (optionPhase2 == 2) {
            thief.addSuspicion(15.0);
            std::cout << thief.getName() << ": Shoot, I think the camara saw me" << std::endl;
            std::cout << "Mar: WHAT DO YOU MEAN U THINK IT SAW YOU?!" << std::endl;
            std::cout << thief.getName() << ": It's fine, I have everything under control." << std::endl;
            std::cout << "Even though now it's following my every move." << std::endl;
            std::cout << "Mar: You gotta be kidding me. You know what? Just keep moving slowly" << std::endl;
            std::cout << " * You are not being discreet. + 15 suspicion * " << std::endl;
            camaraAlert = true;
            return true;
        }
    } else if (optionRoute == 55002) {
        if (optionPhase2 == 1) {
            Tool* t = findTool("dagger", thief);
            if (t != nullptr && t->hasUses()) {
                t->consumeUse(1);
                thief.addSuspicion(t->getSuspicionCost());
                return true;
            } else {
                toolAvailable = "Mar: You don't have a dagger. Choose again.";
                return false;
            }
        } else if (optionPhase2 == 2) {
            Tool* t = findTool("electric taser", thief);
            if (t != nullptr && t->hasUses()) {
                t->consumeUse(1);
                thief.addSuspicion(t->getSuspicionCost());
                return true;
            } else {
                toolAvailable = "Mar: You don't have an electric taser. Choose again.";
                return false;
            }
        } else if (optionPhase2 == 3) {
            thief.addSuspicion(20.0);
            return true;
        }
    }
    toolAvailable = "Mar: That's not a valid option.";
    return false;
}

void handlePhase3(int optionPhase3, Thief& thief, int& currentPhase) {
    if (thief.getGoldenKey()) {
        std::cout << thief.getName() << ": Well, thank God I got that key!" << std::endl;
        std::cout << "* Opening safe... *" << std::endl;
        std::cout << thief.getName() << ": Ha! Easy peasy. Anyway, let's continue, ";
        std::cout << "because we still have that money waiting for us." << std::endl;
        nextPhase(currentPhase);
        return;
    }

    Tool* d = findTool("dagger", thief);
    Tool* p = findTool("silenced gun", thief);
    bool hasDagger = (d != nullptr && d->hasUses());
    bool hasPistol = (p != nullptr && p->hasUses());

    if (hasDagger || hasPistol) {
        std::cout << "Mar: The firewall is locking me out, ";
        std::cout << thief.getName() << "." << std::endl;
        std::cout << "If I try to open the safe from here, we might ";
        std::cout << "lose our connection. " << std::endl;
        std::cout << "Check your backpack... do you have anything that ";
        std::cout << "can force metal open?\n" << std::endl;
        std::cout << "=== Choose what to do ===" << std::endl;

        int currentOption = 1;
        int daggerOption = -1, pistolOption = -1, hackOption;

        if (hasDagger) {
            std::cout << currentOption << ". Use dagger" << std::endl;
            daggerOption = currentOption++;
        }
        if (hasPistol) {
            std::cout << currentOption << ". Use silenced gun" << std::endl;
            pistolOption = currentOption++;
        }
        std::cout << currentOption << ". Wait for Mar to give you instructions" << std::endl;
        hackOption = currentOption;

        std::cin >> optionPhase3;
        while (optionPhase3 < 1 || optionPhase3 > hackOption) {
            std::cout << "Invalid option, choose between 1 and " << hackOption << std::endl;
            std::cin >> optionPhase3;
        }

        if (optionPhase3 == daggerOption) {
            d->consumeUse(1);
            thief.addSuspicion(10.0);
            std::cout << "You use the blade to pry the bolts loose." << std::endl;
        } else if (optionPhase3 == pistolOption) {
            p->consumeUse(1);
            thief.addSuspicion(20.0);
            std::cout << thief.getName() << ": shoot! I wasn't expecting it to ";
            std::cout << "be that loud." << std::endl;
        } else {
            thief.addSuspicion(25.0);
            std::cout << "Mar: Ain't no way you actually expect me to help you. ";
            std::cout << "You know how much time we'll waste?" << std::endl;
            std::cout << thief.getName() << ": Stop complaining and just ";
            std::cout << "help me. Hurry up!" << std::endl;
            std::cout << "Mar: Well, that wouldn't be necessary if you just ";
            std::cout << "used a tool. Anyway, just do as I say..." << std::endl;
        }

    } else {
        std::cout << thief.getName() << ": Mar, I don't have anything to force ";
        std::cout << "this open. What do I do?" << std::endl;
        std::cout << "Mar: Change of plans, you're going to have to do this ";
        std::cout << "the slow way." << std::endl;
        std::cout << "Listen to me carefully and follow my instructions ";
        std::cout << "to the letter. This is going to take longer than ";
        std::cout << "I planned." << std::endl;
        thief.addSuspicion(30.0);
    }

    nextPhase(currentPhase);
}

void handlePhase4(Thief& thief, int& currentPhase) {
    std::cout << thief.getName() << ": And... I'm finally in." << std::endl;
    std::cout << "Mar: LET'S GO! Take everything... Dubai is waiting for us!" << std::endl;
    std::cout << "* A low rumble echoes through the walls *" << std::endl;
    std::cout << "* It's not a glitch, it's the physical security system *" << std::endl;
    std::cout << "Mar: DANG IT! They triggered the hydrostatic pressure alarm." << std::endl;
    std::cout << "Get out of there! My signal is getting... static... ##&&#@...!" << std::endl;
    std::cout << thief.getName() << ": Mar, can you hear me? I can't understand you at all." << std::endl;
    std::cout << "..." << std::endl;
    std::cout << thief.getName() << ": Well, I guess I'm on my own now." << std::endl;
    std::cout << "And I wanted to do this without getting my clothes dirty. Oh well!" << std::endl;
    nextPhase(currentPhase);
}

void handlePhase5Part1(int optionPhase5Part1, Thief& thief) {
    std::cout << "\n=== FINAL PHASE: PART 1 ===" << std::endl;
    if (optionPhase5Part1 == 1) {
        Tool* t = thief.getInventory()[0];
        t->consumeUse(1);
    } else if (optionPhase5Part1 == 2) {
        Tool* t = thief.getInventory()[1];
        t->consumeUse(1);
    } else if (optionPhase5Part1 == 3) {
        thief.setHp(thief.getHp() - 20);
    }
}

void handlePhase5Part2(Tool* toolUsed, Thief& thief) {
    std::cout << "\n=== FINAL PHASE: PART 2 ===" << std::endl;

    if (toolUsed == nullptr) {
        std::cout << thief.getName() << ": Shoot, I have nothing left to use!" << std::endl;
        std::cout << " * " << thief.getName() << " panics and runs * " << std::endl;
        std::cout << "guard 3: not so fast" << std::endl;
        std::cout << "\n* guard 3 shoots twice to kill. -50 hp * " << std::endl;
        thief.setHp(thief.getHp() - 50);
        return;
    }

    std::string toolName = toolUsed->getName();

    if (toolName == "blinding powder") {
        toolUsed->consumeUse(1);
        std::cout << "\n* The smoke cuts off the guard's line of sight. ";
        std::cout << "You slip away unseen. *" << std::endl;
    } else if (toolName == "silenced gun") {
        if (toolUsed->getUses() >= 2) {
            toolUsed->consumeUse(2);
            std::cout << "\n* One shot wounds him, the second takes him ";
            std::cout << "down before he can react. *" << std::endl;
        } else {
            toolUsed->consumeUse(1);
            std::cout << "\n* You wound him, but he has time to pull the ";
            std::cout << "trigger before falling. *" << std::endl;
            thief.setHp(thief.getHp() - 30);
        }
    }
}

void addTool(Thief& thief) {
    int tool = 0;
    bool toolAdded = false;

    std::cout << "\nChoose your tool: ";
    while (!toolAdded) {
        std::cin >> tool;
        switch (tool) {
        case 1:
            thief.addWeapon("dagger", 3, 10.5, true);
            toolAdded = true;
            break;
        case 2:
            thief.addWeapon("silenced gun", 2, 2.5, false);
            toolAdded = true;
            break;
        case 3:
            thief.addGadget("electric taser", 1, 5.5, true);
            toolAdded = true;
            break;
        case 4:
            thief.addGadget("blinding powder", 1, 0.0, false);
            toolAdded = true;
            break;
        default:
            std::cout << "Mar: How many times do I have to repeat myself, huh?" << std::endl;
            std::cout << "We don't have much time, so don't test my patience." << std::endl;
            std::cout << "Choose between 1 and 4" << std::endl;
        }
    }
}

// === MAIN ===
int main() {
    int currentPhase = 0;
    bool camaraAlert = false;
    int optionRoute = 0;
    int optionPhase1 = 0;
    int optionPhase2 = 0;
    int optionPhase3 = 0;
    int optionPhase5Part1 = 0;

    std::string player;
    std::cout << "Mar: Hey, before we leave, what's your name?" << std::endl;
    std::cout << "> ";
    std::cin >> player;

    Thief thief(player, 100, 0.0, false);

    std::cout << "Mar: Perfect, " << player << ". Let's go." << std::endl;
    std::cout << "Mar: Wait, before I forget, please choose two tools, and fast." << std::endl;

    // === TOOLS ===
    std::cout << "\n1. dagger (3 uses, 10.5% suspicion)" << std::endl;
    std::cout << "2. silenced gun (2 uses, 2.5% suspicion)" << std::endl;
    std::cout << "3. electric taser (1 use, 5.5% suspicion)" << std::endl;
    std::cout << "4. blinding powder (1 use, 0.0% suspicion)" << std::endl;

    std::cout << "\nFirst tool: " << std::endl;
    addTool(thief);
    std::cout << "\nSecond tool: " << std::endl;
    addTool(thief);

    std::cout << "\nMar: Alright! " << player << ", now you have ";
    std::cout << thief.getInventory()[0]->getName() << " and ";
    std::cout << thief.getInventory()[1]->getName() << "." << std::endl;
    std::cout << "Mar: Great choice... I guess. I just hope you know what you're doing." << std::endl;
    std::cout << player << ": What do you mean?" << std::endl;
    std::cout << "Mar: Nevermind, let's go." << std::endl;

    std::cout << "\n=== Phase 1: LOBBY ===" << std::endl;
    std::cout << "Mar: We're in, " << player << "." << std::endl;
    std::cout << "Mar: There's a janitor and a guard. ";
    std::cout << "What are you gonna do?" << std::endl;
    std::cout << "=== Choose what to do ===" << std::endl;
    std::cout << "1. Use tool" << std::endl;
    std::cout << "2. Knock them out" << std::endl;
    std::cout << "> ";
    std::cin >> optionPhase1;

    handlePhase1(optionPhase1, thief);

    std::cout << "\nHP: " << thief.getHp() << "/100" << std::endl;
    std::cout << "Suspicion: " << thief.getSuspicion() << "%" << std::endl;

    if (checkGameOver(currentPhase, thief)) {
        std::cout << "\nMar: They got you, I'm out." << std::endl;
        std::cout << "==== Game Over. WA WA WAAAAAA! ====" << std::endl;
        return 0;
    }

    nextPhase(currentPhase);

    std::cout << "\n=== PHASE 2: SERVERS' CORE ===" << std::endl;
    std::cout << "Mar: The firewall's got us in its sights." << std::endl;
    std::cout << "I've got two options. Write the code fast," << std::endl;
    std::cout << "or the system shuts down." << std::endl;
    std::cout << " === ROUTE A (73378) === " << std::endl;
    std::cout << " === ROUTE B (55002) === " << std::endl;

    std::string toolAvailable = "";

    std::cout << "> ";
    std::cin >> optionRoute;
    while (optionRoute != 73378 && optionRoute != 55002) {
        thief.addSuspicion(10.5);
        std::cout << "Mar: I literally just told you to ";
        std::cout << "do it fast." << std::endl;
        std::cout << "We're gonna get caught if you keep doing ";
        std::cout << "this nonsense." << std::endl;
        std::cin >> optionRoute;
    }
    std::cout << "Mar: Ok, I guess!" << std::endl;

    if (optionRoute == 73378) {
        std::cout << "Mar: Shoot! There's a Nexus-7 ";
        std::cout << "camera, so don't move." << std::endl;
        std::cout << "=== Choose what to do ===" << std::endl;
        std::cout << "1. Use blinding powder" << std::endl;
        std::cout << "2. Run" << std::endl;
    }

    if (optionRoute == 55002) {
        std::cout << player << ": Shoot! There are guarding dogs, what do I do?" << std::endl;
        std::cout << "Mar: Well, I don't know. Use your tools, maybe? "
                     "What kind of question is that?" << std::endl;
        std::cout << "=== Choose what to do ===" << std::endl;
        std::cout << "1. Use " << thief.getInventory()[0]->getName() << std::endl;
        std::cout << "2. Use " << thief.getInventory()[1]->getName() << std::endl;
        std::cout << "3. Distract the guarding dogs" << std::endl;
    }

    bool validOption = false;
    std::cout << "> ";
    while (!validOption) {
        std::cin >> optionPhase2;
        validOption = handlePhase2(optionPhase2, toolAvailable, optionRoute,
                                   camaraAlert, thief);
        if (!validOption) {
            std::cout << toolAvailable << std::endl;
            std::cout << "> ";
        }
    }

    std::cout << "\nHP: " << thief.getHp() << "/100" << std::endl;
    std::cout << "Suspicion: " << thief.getSuspicion() << "%" << std::endl;

    if (checkGameOver(currentPhase, thief)) {
        std::cout << "\nMar: They got you, I'm out." << std::endl;
        std::cout << "==== Game Over. WA WA WAAAAAA! ====" << std::endl;
        return 0;
    }

    nextPhase(currentPhase);

    std::cout << "\n=== PHASE 3: THE MANAGER'S OFFICE ===" << std::endl;
    std::cout << "Mar: Gotta be kidding me... the firewall is "
              << "regenerating." << std::endl;
    std::cout << " I have to lock down all my bandwidth to keep the "
              << "doors open. You're on your own with "
              << "that safe." << std::endl;

    handlePhase3(optionPhase3, thief, currentPhase);

    std::cout << "\n=== PHASE 4: THE VAULT ===" << std::endl;
    handlePhase4(thief, currentPhase);

    std::cout << "guard 1: Hey, stop right there. Don't make me do something";
    std::cout << " I don't want to" << std::endl;
    std::cout << thief.getName() << ": Then... don't?" << std::endl;
    std::cout << "guard 2: You think you are so funny, huh?" << std::endl;
    std::cout << thief.getName() << ": Yeah, actually. But it's only ";
    std::cout << "because I am." << std::endl;

    // --- MENU PART 1 ---
    std::cout << "=== Choose what to do ===" << std::endl;
    std::cout << "1. Use " << thief.getInventory()[0]->getName() << std::endl;
    std::cout << "2. Use " << thief.getInventory()[1]->getName() << std::endl;
    std::cout << "3. Run" << std::endl;

    std::cout << "> ";
    std::cin >> optionPhase5Part1;
    while (optionPhase5Part1 < 1 || optionPhase5Part1 > 3) {
        std::cout << "Invalid option, choose between 1 and 3\n> ";
        std::cin >> optionPhase5Part1;
    }

    handlePhase5Part1(optionPhase5Part1, thief);

    std::cout << thief.getName() << ": Anyway, it was a pleasure meeting ";
    std::cout << "you both, but I gotta go. See ya!" << std::endl;
    std::cout << "guard 1: Wait, no!" << std::endl;
    std::cout << "guard 2: we're getting fired, aren't we?" << std::endl;
    std::cout << "guard 1: Absolutely. Anyway, let's just go ";
    std::cout << "at this point." << std::endl;

    std::cout << "\n" << thief.getName() << ": Anyway, I finally get ";
    std::cout << "to go home!" << std::endl;
    std::cout << " * You see a red light being pointed right in your ";
    std::cout << "forehead * " << std::endl;
    std::cout << "guard 3: Don't move! Now hands behind your back!" << std::endl;
    std::cout << thief.getName() << ": Well, if you could just-" << std::endl;
    std::cout << "guard 3: I said 'HANDS BEHIND YOUR BACK'. Don't make me ";
    std::cout << "repeat myself." << std::endl;

    std::cout << "\n* BANG! *" << std::endl;
    std::cout << "* Guard 3 shoots the strap of your backpack! It falls to the ground, scattering your tools! *" << std::endl;
    std::cout << thief.getName() << ": Hey! Those are expensive!" << std::endl;
    std::cout << "* You desperately look at the floor. If you had a dagger or a taser, they are completely shattered! *" << std::endl;

    Tool* powder = findTool("blinding powder", thief);
    Tool* gun    = findTool("silenced gun", thief);

    std::cout << "\n=== Quick! Grab a tool! ===" << std::endl;

    int currentOpt = 1;
    int optPowder = -1, optGun = -1;

    if (powder != nullptr && powder->hasUses()) {
        std::cout << currentOpt << ". Grab blinding powder" << std::endl;
        optPowder = currentOpt++;
    }
    if (gun != nullptr && gun->hasUses()) {
        std::cout << currentOpt << ". Grab silenced gun" << std::endl;
        optGun = currentOpt++;
    }

    int optRun = currentOpt;
    std::cout << optRun << ". Run" << std::endl;

    if (currentOpt == 1) {
        std::cout << "Mar: You have nothing useful left! You have to run!" << std::endl;
    }

    std::cout << "> ";
    int choicePart2;
    std::cin >> choicePart2;
    while (choicePart2 < 1 || choicePart2 > optRun) {
        std::cout << "Invalid option.\n> ";
        std::cin >> choicePart2;
    }

    Tool* selectedTool = nullptr;
    if (choicePart2 == optPowder) selectedTool = powder;
    else if (choicePart2 == optGun)   selectedTool = gun;

    nextPhase(currentPhase);

    handlePhase5Part2(selectedTool, thief);

    std::cout << "\nHP: " << thief.getHp() << "/100" << std::endl;
    if (checkGameOver(currentPhase, thief)) {
        std::cout << "\nMar: They got you, I'm out." << std::endl;
        std::cout << "==== Game Over. WA WA WAAAAAA! ====" << std::endl;
        return 0;
    }

    // --- VICTORY ---
    std::cout << "\nMar: Hello? " << thief.getName() << "?" << std::endl;
    std::cout << thief.getName() << ": Mar? Oh, thank God. I finally escaped, ";
    std::cout << "I'm almost there." << std::endl;
    std::cout << "Mar: PERFECT, I always believed in you!" << std::endl;
    std::cout << thief.getName() << ": Yeah, right -_-" << std::endl;
    std::cout << "Mar: What? You don't believe me?" << std::endl;
    std::cout << thief.getName() << ": ..." << std::endl;
    std::cout << "Mar: Come on. Don't be like that. You know I..." << std::endl;
    std::cout << "\n.............................................." << std::endl;
    std::cout << "\n=== V I C T O R Y ===" << std::endl;
    std::cout << "The End" << std::endl;

    return 0;
}

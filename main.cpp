#include <iostream>
#include <string>
#include <cctype>
#include "Board.h"
#include "Player.h"
#include "Utility.h"
#include "Constants.h"

/**
 * @file main.cpp
 * @brief Entry point for the Fantasy Board Game console application.
 *
 * Responsibilities:
 *  - Set up the game board and player.
 *  - Handle user input commands (movement, inventory, combat).
 *  - Manage day/night cycles and game loop.
 */

/**
 * @brief Prints a welcome message and basic game commands.
 */
static void printWelcome()
{
    std::cout << "======================================\n";
    std::cout << "  Fantasy Board Game (Console)       \n";
    std::cout << "======================================\n";
    std::cout << "Commands: N,S,E,W (move), L=look, P=pick, D=drop, A=attack, I=inventory, X=exit\n";
}

/**
 * @brief Main function for the game.
 *
 * Initializes board and player, then enters the game loop handling commands:
 *  - Movement: N/S/E/W
 *  - Look: L
 *  - Pick up item: P
 *  - Drop item: D
 *  - Attack enemy: A
 *  - Show inventory: I
 *  - Exit: X
 *
 * Also updates day/night cycles after a set number of commands.
 *
 * @return 0 on normal termination.
 */
int main()
{
    printWelcome();

    int width = 0, height = 0;
    std::cout << "Enter board width (columns): ";
    std::cin >> width;
    std::cout << "Enter board height (rows): ";
    std::cin >> height;

    if (width <= 0 || height <= 0) {
        std::cout << "Invalid board size. Exiting.\n";
        return 0;
    }
    std::string raceStr;

    bool charecheck{false};
    do{
    // ask for player's race
    std::cout << "Enter your character name to choose your race (Human / Elf / Dwarf / Hobbit / Orc): ";
    std::cin >> raceStr;
    raceStr[0] = std::toupper(raceStr[0]);
    for (size_t i = 1; i < raceStr.size(); i++) raceStr[i] = std::tolower(raceStr[i]);
    if (raceStr == "Human" ||
        raceStr == "Elf" ||
        raceStr == "Dwarf" ||
        raceStr == "Hobbit" ||
        raceStr == "Orc")
    {
        charecheck = true;
    }
    else {
        std::cout << "Invalid race. Please try again.\n";
    }
    }while(charecheck == false);


    std::cout << "Choosen charecter is "<< raceStr<<std::endl;
    Player player(raceStr, 0, 0);

    Board board(width, height);
    board.initialize();

    board.lookAtPlayerSquare(player);

    int commandCount = 0;
    bool running = true;

    while (running && player.isAlive()) {
        std::cout << "\nEnter command: ";
        std::string cmd; std::cin >> cmd;
        if (cmd.empty()) continue;

        char c = static_cast<char>(std::toupper(cmd[0]));
        bool known = true;

        switch (c) {
        case 'N':
        case 'S':
        case 'E':
        case 'W':
            board.movePlayer(player, c);
            break;
        case 'L':
            board.lookAtPlayerSquare(player);
            break;
        case 'P':
            board.playerPickUp(player);
            break;
        case 'D': {
            auto item = player.selectItemToDrop();
            if (item) {
                // Keep a backup raw pointer in case drop fails
                Item* rawBackup = item.get();

                if (!board.playerDrop(player, std::move(item))) {
                    // Restore ownership using the backup pointer
                    player.returnDroppedItem(std::unique_ptr<Item>(rawBackup));
                    std::cout << "Drop failed. Item returned.\n";
                }
            }
        } break;
        case 'A':
            board.playerAttack(player);
            break;
        case 'I':
            player.showInventory();
            break;
        case 'X':
            running = false;
            break;
        default:
            std::cout << "Unknown command.\n";
            known = false;
        }

        if (known) {
                ++commandCount;            
            // Show player's current position
            std::cout << "You are at (" << player.getX() << ", " << player.getY() << ").\n";

            if (commandCount % Constants::COMMANDS_PER_TIME_SWITCH == 0) {
                Utility::toggleDayNight();
                bool night = Utility::isNight();
                std::cout << "Time changed. It is now " << (night ? "Night" : "Day") << ".\n";
                player.updateForTime(night);
            }
        }
    }


    std::cout << "\nGame over. You collected " << player.getGold() << " gold.\n";
    return 0;
}

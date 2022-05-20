#include <iostream>
#include <string>
#include "../include/GridManager.h"
#include "../include/GameOfLife.h"
#include <chrono>
#include <thread>

#include <conio.h>

int main(){
    GridManager mainGridManager;
    GameOfLife mainGame = GameOfLife(mainGridManager);

    mainGridManager.PopulateWorld(17);

    bool change = true;
    bool pressToContinue = false;
    while (change)
    {
        system("cls");
        change = mainGame.UpdateCells();
        //mainGridManager.DrawGrid();
        std::cout << "\n---------------------------------------------------\n";
        mainGridManager.DrawGridBetween(2, 2, mainGridManager.GRID_WIDTH-2, mainGridManager.GRID_HEIGHT-2);
        std::cout << "\n---------------------------------------------------\n";
        std::cout << "R = Reset --- P = Pause --- S = Start/Stop Step Through" << std::endl;

            if (_kbhit())
            {
                char charPressed = getch();
                switch (charPressed)
                {
                case 'R':
                case 'r':
                {
                    // Restart
                    mainGridManager.ReLoadGrid();
                    break;
                }
                case 'P':
                case 'p':
                {
                    // Pause
                    char charPressed = getch();
                    break;
                }
                case 'S':
                case 's':
                {
                    // Enable Keypress to Continue (Step, by, step)
                    pressToContinue = !pressToContinue;
                    break;
                }

                default:
                    break;
                }
            }

        if (pressToContinue)
        {
            std::cout << "Press any key to continue OR S to go back to auto step through." << std::endl;
            // Wait for keypress before we continue
            char charPressed = getch();
            if (charPressed == 's' || charPressed == 'S'){
                pressToContinue = false;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    std::cout << "No more updates!\n";
    return 0;
}

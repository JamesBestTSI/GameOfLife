#include "../include/GameOfLife.h"

GameOfLife::GameOfLife() : GM {GridManager()}{};
GameOfLife::GameOfLife(GridManager &gm) : GM{gm} {};
GameOfLife::~GameOfLife() {};

bool GameOfLife::UpdateCells(){
    bool ChangeHappened = false;
    for (int cell = 0; cell < GM.GRID_HEIGHT * GM.GRID_WIDTH; cell++)
    {
        if (GM.IsGridInUse(cell)){
            std::vector<std::shared_ptr<GridSpace>> connectedLivingCells = GM.GetUsedConnectingGridSpaces(cell);
            if (connectedLivingCells.size() < 2 || connectedLivingCells.size() > 3)
            {
                // Kill Cell
                GM.SetGridInUse(cell, false);
                ChangeHappened = true;
            }
        }
        else{
            std::vector<std::shared_ptr<GridSpace>> connectedLivingCells = GM.GetUsedConnectingGridSpaces(cell);
            if (connectedLivingCells.size() == 3)
            {
                // Birth Cell
                GM.SetGridInUse(cell, true);
                ChangeHappened = true;
            }
        }
    }
    GM.UpdateMainGrid();
    return ChangeHappened;
}
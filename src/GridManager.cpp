#include <iostream>
#include "../include/GridManager.h"

/**
 * @brief Construct a new Grid Manager object
 * This will build us a grid based on GRID_WIDTH and GRID_HEIGHT
 * With 0,0 being in the top left.
 */
GridManager::GridManager(){
    for (int space = 0; space < GRID_HEIGHT * GRID_WIDTH; space++){
        std::shared_ptr<GridSpace>newSpace(new GridSpace(space));
        grid.push_back(std::move(newSpace));
    }

    for (int space = 0; space < GRID_HEIGHT * GRID_WIDTH; space++)    {
        std::shared_ptr<GridSpace> newSpace(new GridSpace(space));
        gridStartState.push_back(std::move(newSpace));
    }

    for (int space = 0; space < GRID_HEIGHT * GRID_WIDTH; space++)    {
        std::shared_ptr<GridSpace> newSpace(new GridSpace(space));
        updatedGrid.push_back(std::move(newSpace));
    }
};

/**
 * @brief Destroy the Grid Manager object
 */
GridManager::~GridManager(){};

/**
 * @brief Draws the grid to the console screen using the GridSpace.icon
 */
void GridManager::DrawGrid(){
    std::string line = "";
    for (int gridSpot = 0; gridSpot < GRID_HEIGHT * GRID_WIDTH; gridSpot++){
        if (gridSpot%GRID_WIDTH == 0){
            std::cout << line << std::endl;
            line = "";
            //std::cout << std::endl;
        }
        line += grid[gridSpot]->GetIcon();
        //std::cout << grid[gridSpot]->GetIcon();
    }
    std::cout << line << std::endl;
};


void GridManager::DrawGridBetween(int minX, int minY, int maxX, int maxY){
    std::string line = "";
    for (int gridSpot = (minY*GRID_WIDTH) + minX; gridSpot < (maxY*(GRID_WIDTH-1))+maxX; gridSpot++)    {
        if (gridSpot % GRID_WIDTH == 0){
            std::cout << line << std::endl;
            line = "";
        }
        else{
            if (gridSpot % GRID_WIDTH >= minX && gridSpot % GRID_WIDTH <= maxX){
                if (gridSpot>=GRID_WIDTH*minY && gridSpot < GRID_WIDTH*maxY){
                    line += grid[gridSpot]->GetIcon();
                    //std::cout << grid[gridSpot]->GetIcon();
                }
            }
        }
    }
};

/**
 * @brief Called to find out if a GridSpace is currently in use
 * 
 * @param location the location of the GridSpace we want to look at
 * @return true if in use
 * @return false if not in use
 */
bool GridManager::IsGridInUse(int location){
    if (updatedGrid[location]->GetClearIn() > 0)
    {
        updatedGrid[location]->UpdateClearIn();
    }
    return grid[location]->IsInUse();
}

/**
 * @brief Based on the state passed in we will change the state of the GridSpace
 * 
 * @param location the GridSpace to update
 * @param state the state we want to set it to
 */
void GridManager::SetGridInUse(int location, bool state)
{
    //grid[location]->Populate(state);
    updatedGrid[location]->Populate(state);
};

/**
 * @brief Gets all the GridSpace objects that are connected to the current GridSpace at the location provided
 * 
 * @param location The int location of the current GridSpace
 * @return std::vector<std::shared_ptr<GridSpace>> A list of shared pointers to GridSPaces that are connected
 */
std::vector<std::shared_ptr<GridSpace>> GridManager::GetGridConnectingGridSpaces(int location){
    std::vector<std::shared_ptr<GridSpace>> ConnectedSpaces;

    // If we are not on the first row
    if(location>=GRID_WIDTH){
        ConnectedSpaces.push_back(grid[location - GRID_WIDTH]);             // Add the above GridSpace
        if (location % GRID_WIDTH != 0){
            ConnectedSpaces.push_back(grid[location - (GRID_WIDTH + 1)]);   // Add the above left GridSpace
        }if(location%GRID_WIDTH!=GRID_WIDTH-1){
            ConnectedSpaces.push_back(grid[location - (GRID_WIDTH - 1)]);   // Add the above right GridSpace
        }
    }
    // If we are not on the last row
    if(location<GRID_WIDTH*(GRID_HEIGHT-1)-1){
        ConnectedSpaces.push_back(grid[location + GRID_WIDTH]);             // Add the below GridSpace
        if (location % GRID_WIDTH != 0){
            ConnectedSpaces.push_back(grid[location + (GRID_WIDTH - 1)]);   // Add the below left GridSpace
        }if(location%GRID_WIDTH!=GRID_WIDTH-1){
            ConnectedSpaces.push_back(grid[location + (GRID_WIDTH + 1)]);   // Add the below right GridSpace
        }
    }

    // If we are not at the far left
    if(location%GRID_WIDTH!=0)
    {ConnectedSpaces.push_back(grid[location - 1]);} // Add the left GridSpace
    
    // If we are not at the far right
    if(location%GRID_WIDTH!=GRID_WIDTH-1)
    {ConnectedSpaces.push_back(grid[location + 1]);} // Add the right GridSpace

    return ConnectedSpaces;
}

/**
 * @brief Gets all the EMPTY GridSpace objects that are connected to the current GridSpace at the location provided
 *
 * @param location The int location of the current GridSpace
 * @return std::vector<std::shared_ptr<GridSpace>> A list of shared pointers to GridSPaces that are EMPTY and connected
 */
std::vector<std::shared_ptr<GridSpace>> GridManager::GetEmptyConnectingGridSpaces(int location)
{
    std::vector<std::shared_ptr<GridSpace>> ConnectedSpaces = GetGridConnectingGridSpaces(location);
    std::vector<std::shared_ptr<GridSpace>> EmptySpaces;
    for (int connectedSpace = 0; connectedSpace < ConnectedSpaces.size(); connectedSpace++){
        if (!ConnectedSpaces[connectedSpace]->IsInUse()){
            EmptySpaces.push_back(ConnectedSpaces[connectedSpace]);
        }
    }
    return EmptySpaces;
}

/**
 * @brief Gets all the USED GridSpace objects that are connected to the current GridSpace at the location provided
 *
 * @param location The int location of the current GridSpace
 * @return std::vector<std::shared_ptr<GridSpace>> A list of shared pointers to GridSPaces that are USED and connected
 */
std::vector<std::shared_ptr<GridSpace>> GridManager::GetUsedConnectingGridSpaces(int location)
{
    std::vector<std::shared_ptr<GridSpace>> ConnectedSpaces = GetGridConnectingGridSpaces(location);
    std::vector<std::shared_ptr<GridSpace>> FullSpaces;
    for (int connectedSpace = 0; connectedSpace < ConnectedSpaces.size(); connectedSpace++){
        if (ConnectedSpaces[connectedSpace]->IsInUse()){
            FullSpaces.push_back(ConnectedSpaces[connectedSpace]);
        }
    }
    return FullSpaces;
}


void GridManager::PopulateWorld(int PopulationChance){
    std::srand(std::time(nullptr));
    for (int gridSpot = 0; gridSpot < GRID_HEIGHT * GRID_WIDTH; gridSpot++)
    {
        // Get random value
        int randomValue = rand() % 100;
        if (randomValue<=PopulationChance){
            grid[gridSpot]->Populate(true);
            gridStartState[gridSpot]->Populate(true);
        }
    }
}

void GridManager::ReLoadGrid()
{
    for (int gridSpot = 0; gridSpot < GRID_HEIGHT * GRID_WIDTH; gridSpot++){
        grid[gridSpot]->Populate(gridStartState[gridSpot]->IsInUse());
    }
}


void GridManager::UpdateMainGrid()
{
    for (int gridSpot = 0; gridSpot < GRID_HEIGHT * GRID_WIDTH; gridSpot++)
    {
        grid[gridSpot]->Populate(updatedGrid[gridSpot]->IsInUse());
        if (grid[gridSpot]->GetClearIn() > 0)
        {
            grid[gridSpot]->UpdateClearIn();
        }
    }
}
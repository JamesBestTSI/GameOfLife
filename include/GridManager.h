#ifndef GRIDMANAGER_H
#define GRIDMANAGER_H
#include <string>
#include <list>
#include <memory>
#include <vector>
#include <ctime>
#include "GridSpace.h"

class GridManager
{
private:
    std::vector<std::shared_ptr<GridSpace>> grid;
    std::vector<std::shared_ptr<GridSpace>> updatedGrid;
    std::vector<std::shared_ptr<GridSpace>> gridStartState;

public:
    const static int GRID_WIDTH = 100; // 200;
    const static int GRID_HEIGHT = 60;
    GridManager();
    ~GridManager();
    void DrawGrid();
    void DrawGridBetween(int minX, int minY, int maxX, int maxY);
    bool IsGridInUse(int location);
    void SetGridInUse(int location, bool state);
    std::vector<std::shared_ptr<GridSpace>> GetGridConnectingGridSpaces(int location);
    std::vector<std::shared_ptr<GridSpace>> GetEmptyConnectingGridSpaces(int location);
    std::vector<std::shared_ptr<GridSpace>> GetUsedConnectingGridSpaces(int location);

    void PopulateWorld(int PopulationChance);
    void ReLoadGrid();
    void UpdateMainGrid();
};

#endif
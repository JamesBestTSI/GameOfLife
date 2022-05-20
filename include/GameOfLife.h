#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H
#include "GridManager.h"
#include <memory>
#include <vector>
#include "GridSpace.h"

class GameOfLife
{
private:
    GridManager GM;

public:
    GameOfLife();
    explicit GameOfLife(GridManager &gm);
    ~GameOfLife();

    bool UpdateCells();
};

#endif
#ifndef GRIDSPACE_H
#define GRIDSPACE_H
#include <string>
#include <list>
#include <memory>

class GridSpace
{
private:
    int indexValue;
    bool inUse = false;
    char icon = ' ';
    int clearIn = 1;

public:
    GridSpace();
    explicit GridSpace(int index);
    ~GridSpace();
    void ClearSpace();
    int GetIndex();
    bool IsInUse();
    char GetIcon();
    int GetClearIn();
    void UpdateClearIn();

    void Populate(bool state);
};

#endif
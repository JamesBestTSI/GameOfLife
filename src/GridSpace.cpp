#include "../include/GridSpace.h"

GridSpace::GridSpace()          { indexValue = 0;};
GridSpace::GridSpace(int index) { indexValue = index;};
GridSpace::~GridSpace()         {};
void GridSpace::ClearSpace()    {};
int GridSpace::GetIndex()       { return indexValue; };
bool GridSpace::IsInUse()       { return inUse; }
char GridSpace::GetIcon()       { return icon; }

void GridSpace::Populate(bool state) {
    if (!state && inUse)
    {
        clearIn = 3;
        icon = '-';
    }
    else if(state){
        icon = '#';
    }
    inUse = state;
}
int GridSpace::GetClearIn() { return clearIn; }
void GridSpace::UpdateClearIn() { clearIn--; if(clearIn<=0){
        icon = ' ';
    }
}
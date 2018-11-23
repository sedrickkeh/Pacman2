#include "wall.h"

Wall::Wall(int row, int col, Character* (*board)[31][28]) :
    Character(row,col,board)
{}

char Wall::getImage() const {
    return IMAGE_WALL;
}

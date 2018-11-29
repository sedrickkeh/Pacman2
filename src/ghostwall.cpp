#include "ghostwall.h"

ghostwall::ghostwall(int row, int col, Character* (*board)[31][28]) :
    Character(row,col,board)
{}

char ghostwall::getImage() const {
    return IMAGE_GHOSTWALL;
}

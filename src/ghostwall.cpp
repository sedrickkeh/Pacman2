#include "ghostwall.h"

Ghostwall::Ghostwall(int row, int col, Character* (*board)[31][28]) :
    Character(row,col,board)
{}

char Ghostwall::getImage() const {
    return IMAGE_GHOSTWALL;
}

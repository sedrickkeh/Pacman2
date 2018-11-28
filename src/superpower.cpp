#include "superpower.h"

Superpower::Superpower(int row, int col, Character* (*board)[31][28]) :
    Food(row, col, board) {
    points = 200;
}

char Superpower::getImage() const {
    return IMAGE_SUPERPOWER;
}

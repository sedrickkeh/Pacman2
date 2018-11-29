#include "eatghost.h"

EatGhost::EatGhost(int row, int col, Character* (*board)[31][28], int timebox, Character* previous) :
    Ghost(row, col, board, timebox, previous, RANDOM),
    points(200)
{}

char EatGhost::getImage() const {
    return IMAGE_EATGHOST;
}

void EatGhost::update_points() {
    points *= 2;
}

int EatGhost::get_points() {
    return points;
}



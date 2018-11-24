#include "Pacman.h"

Pacman::Pacman(int row, int col, Character* (*board)[31][28]) :
	Character(row, col, board),
	superpower(-1),
    direction(Dir::LEFT),
    has_eaten_piece(false),
    addpoints(-1),
    lives(3)
{}

int Pacman::get_superpower() {
	return superpower;
}

Dir Pacman::get_direction() {
	return direction;
}

char Pacman::getImage() const {
    return IMAGE_PACMAN;
}


void Pacman::update_superpower(bool sup) {
	superpower = sup;
}

void Pacman::update_direction(Dir dir) {
	direction = dir;
}

void Pacman::eats_piece(Food* f) {
    has_eaten_piece = true;
    addpoints = f->get_points();
}

void Pacman::not_eat_piece() {
    has_eaten_piece = false;
    addpoints = -1;
}

int Pacman::get_points_to_add() {
    return addpoints;
}

int Pacman::get_lives() {
    return lives;
}

void Pacman::encounter_ghost(Ghost* g) {
    ((*board)[this->row][this->col]) = nullptr;
    if ((*board)[7][13] == nullptr) {
        ((*board)[7][13]) = this;
        this->row = 7; this->col = 13;
    }
    else if ((*board)[7][12] == nullptr) {
        ((*board)[7][12]) = this;
        this->row = 7; this->col = 12;
    }
    else if ((*board)[7][11] == nullptr) {
        ((*board)[7][11]) = this;
        this->row = 7; this->col = 11;
    }
    else {
        ((*board)[7][10]) = this;
        this->row = 7; this->col = 10;
    }
    lives--;
}

void Pacman::move(int row, int col) {
    if (row < 0 || col < 0 || row >= 31 || col >= 28) return;
    if ((*board)[row][col] == nullptr) {
        ((*board)[this->row][this->col]) = nullptr;
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
        return;
    }
    else if ((*board)[row][col] -> getImage() == 'W') return;
    else if ((*board)[row][col] -> getImage() == 'F') {
        eats_piece(dynamic_cast<Food*>((*board)[row][col]));
        ((*board)[this->row][this->col]) = nullptr;
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }
    else if ((*board)[row][col] -> getImage() == 'G') {
        encounter_ghost(dynamic_cast<Ghost*>((*board)[row][col]));
    }
}


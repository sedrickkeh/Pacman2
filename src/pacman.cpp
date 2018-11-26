#include "Pacman.h"
#include "Wall.h"

Pacman::Pacman(int row, int col, Character* (*board)[31][28]) :
	Character(row, col, board),
	superpower(-1),
    direction(Dir::LEFT),
	has_eaten_piece(false)
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
    if (dir ==Dir::UP){
        if (row==30) return;
        if ((*board)[row+1][col]!=nullptr){
            if ((*board)[row+1][col]->getImage()== Wall::IMAGE_WALL){
                return;
            }
        }
    }
    else if (dir ==Dir::DOWN){
        if (row==0) return;
        if ((*board)[row-1][col]!=nullptr){
            if ((*board)[row-1][col]->getImage()== Wall::IMAGE_WALL){
                return;
            }
        }
    }
    else if (dir == Dir::LEFT){
        if (col==0) return;
        if ((*board)[row][col-1]!=nullptr){
            if ((*board)[row][col-1]->getImage()== Wall::IMAGE_WALL){
                return;
            }
        }
    }
    else if (dir == Dir::RIGHT){
        if (col==27) return;
        if ((*board)[row][col+1]!=nullptr){
            if ((*board)[row][col+1]->getImage()== Wall::IMAGE_WALL){
                return;
            }
        }
    }
    direction = dir;
}

void Pacman::eats_piece(bool eat) {
	has_eaten_piece = eat;
}

void Pacman::move(int row, int col) {
    if (row < 0 || col < 0 || row >= 31 || col >= 28) return;
    if ((*board)[row][col] -> getImage() == 'W') return;
    else {
        delete ((*board)[row][col]);
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }
}


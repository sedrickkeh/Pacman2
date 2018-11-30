#include "pacman.h"
#include "pacmangame.h"
#include "ghost.h"
#include "wall.h"
#include "ghostwall.h"

Pacman::Pacman(PacmanGame* pacmangame, int row, int col, Character* (*board)[31][28], Mode mode) :
    Character(row, col, board),
    pacmangame(pacmangame),
    direction(Dir::NONE),
    mode(mode),
    has_eaten_piece(false),
    has_eaten_ghost(false),
    has_encountered_ghost(false),
    gain(false),
    lose(false),
    addpoints(-1)
{
    if(mode == CLASSIC) {
        superpower = -1;
        lives = 5;
    }

    else if (mode == REVERSE) {
        superpower = 200;
        lives = 0;
    }
}

char Pacman::getImage() const {
    return IMAGE_PACMAN;
}

bool Pacman::just_eaten_superpower() const {
    return gain;
}

bool Pacman::just_lost_superpower() const {
    return lose;
}

void Pacman::set_gain() {
    gain = false;
}

void Pacman::set_lose() {
    lose = false;
}

Dir Pacman::get_direction() const {
	return direction;
}

int Pacman::get_superpower() const {
    return superpower;
}

void Pacman::update_superpower() {
    if (gain) superpower += 100;
    else if (superpower > 0) --superpower;
    else if (superpower == 0) {
        lose = true;
        superpower = -1;
    }
    else superpower = -1;
}

void Pacman::update_direction(Dir dir) {
    if (dir ==Dir::UP){
        if (row==30) return;
        if ((*board)[row+1][col]!=nullptr){
            if ((*board)[row+1][col]->getImage()== Wall::IMAGE_WALL || (*board)[row+1][col]->getImage()== Ghostwall::IMAGE_GHOSTWALL){
                return;
            }
        }
    }
    else if (dir ==Dir::DOWN){
        if (row==0) return;
        if ((*board)[row-1][col]!=nullptr){
            if ((*board)[row-1][col]->getImage()== Wall::IMAGE_WALL || (*board)[row-1][col]->getImage()== Ghostwall::IMAGE_GHOSTWALL){
                return;
            }
        }
    }
    else if (dir == Dir::LEFT){
        if (col==0) return;
        if ((*board)[row][col-1]!=nullptr){
            if ((*board)[row][col-1]->getImage()== Wall::IMAGE_WALL || (*board)[row][col-1]->getImage()== Ghostwall::IMAGE_GHOSTWALL){
                return;
            }
        }
    }
    else if (dir == Dir::RIGHT){
        if (col==27) return;
        if ((*board)[row][col+1]!=nullptr){
            if ((*board)[row][col+1]->getImage()== Wall::IMAGE_WALL || (*board)[row][col+1]->getImage()== Ghostwall::IMAGE_GHOSTWALL){
                return;
            }
        }
    }
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

void Pacman::encounter_ghost() {
    has_encountered_ghost = true;
    --lives;
    direction = NONE;

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
}

void Pacman::eats_ghost(Ghost* g, int row, int col) {
    has_eaten_piece = true;
    has_eaten_ghost = true;
    addpoints = g->get_points();

    if(mode == CLASSIC) {
        g -> set_eatmode(false);

        if ((*board)[15][12] == nullptr) g -> move(15, 12);
        else if ((*board)[16][12] == nullptr) g -> move(16, 12);
        else if ((*board)[15][15] == nullptr) g -> move(15, 15);
        else if ((*board)[16][15] == nullptr) g -> move(16, 15);
        else if ((*board)[15][14] == nullptr) g -> move(15, 14);
        else if ((*board)[16][14] == nullptr) g -> move(16, 14);
        else if ((*board)[15][13] == nullptr) g -> move(15, 13);
        else if ((*board)[16][13] == nullptr) g -> move(16, 13);

        g -> set_time_in_box(20);
    }

    else if(mode == REVERSE) {
        (*board)[g->getRow()][g->getCol()] = nullptr;
        pacmangame->remove_ghost(g->get_number());
        g = nullptr;
        addpoints += (superpower * 5);
    }

    ((*board)[this->row][this->col]) = nullptr;
    ((*board)[row][col]) = this;
    this->row = row; this->col = col;
}

void Pacman::not_eat_ghost() {
    has_eaten_ghost = false;
}

bool Pacman::get_has_encountered_ghost() {
    if (has_encountered_ghost == true) {
        has_encountered_ghost = false;
        return true;
    }
    return false;
}

bool Pacman::get_has_eaten_ghost() const {
    return has_eaten_ghost;
}

int Pacman::get_points_to_add() const {
    return addpoints;
}

int Pacman::get_lives() const {
    return lives;
}

void Pacman::move(int row, int col) {
    if (col == -1 && row == 16) {
        ((*board)[this->row][this->col]) = nullptr;
        ((*board)[16][27]) = this;
        this->row = 16; this->col = 27;
        return;
    }
    if (col == 28 && row == 16) {
        ((*board)[this->row][this->col]) = nullptr;
        ((*board)[16][0]) = this;
        this->row = 16; this->col = 0;
        return;
    }

    if (row < 0 || col < 0 || row >= 31 || col >= 28) return;

    if ((*board)[this->row][this->col - 1] != nullptr) {
        if ((*board)[this->row][this->col-1]->getImage() == 'C' || (*board)[this->row][this->col-1]->getImage() == 'A' || (*board)[this->row][this->col-1]->getImage() == 'R')
        {
            encounter_ghost();
            return;
        }
    }
    if ((*board)[this->row][this->col + 1] != nullptr) {
        if ((*board)[this->row][this->col+1]->getImage() == 'C' || (*board)[this->row][this->col+1]->getImage() == 'A' || (*board)[this->row][this->col+1]->getImage() == 'R')
        {
            encounter_ghost();
            return;
        }
    }
    if ((*board)[this->row - 1][this->col] != nullptr) {
        if ((*board)[this->row-1][this->col]->getImage() == 'C' || (*board)[this->row-1][this->col]->getImage() == 'A' || (*board)[this->row-1][this->col]->getImage() == 'R')
        {
            encounter_ghost();
            return;
        }
    }
    if ((*board)[this->row + 1][this->col] != nullptr) {
        if ((*board)[this->row+1][this->col]->getImage() == 'C' || (*board)[this->row+1][this->col]->getImage() == 'A' || (*board)[this->row+1][this->col]->getImage() == 'R')
        {
            encounter_ghost();
            return;
        }
    }

    if ((*board)[row][col] == nullptr) {
        ((*board)[this->row][this->col]) = nullptr;
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
        return;
    }
    else if ((*board)[row][col] -> getImage() == 'W' || (*board)[row][col] -> getImage() == 'V') return;
    else if ((*board)[row][col] -> getImage() == 'F') {
        eats_piece(dynamic_cast<Food*>((*board)[row][col]));
        ((*board)[this->row][this->col]) = nullptr;
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }
    else if ((*board)[row][col] -> getImage() == 'U') {
        eats_piece(dynamic_cast<Food*>((*board)[row][col]));
        gain = true;
        ((*board)[this->row][this->col]) = nullptr;
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }
    else if ((*board)[row][col] -> getImage() == 'C' || (*board)[row][col] -> getImage() == 'A' || (*board)[row][col] -> getImage() == 'R') {
        encounter_ghost();
    }
    else if ((*board)[row][col] -> getImage() == 'E') {
        eats_ghost(dynamic_cast<Ghost*>((*board)[row][col]), row, col);
    }
}

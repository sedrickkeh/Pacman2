#include "ghost.h"

Ghost::Ghost(int row, int col, Character* (*board)[31][28], int timebox, Character* previous) :
    Character(row, col, board),
    prev(previous),
    points(200),
    time_in_box(timebox),
    eatmode(false)
{}

Ghost::~Ghost() {
    delete prev;
}

int Ghost::get_time_in_box() {
	return time_in_box;
}

void Ghost::set_time_in_box(int t) {
    time_in_box = t;
}

void Ghost::reduce_time_in_box() {
    --time_in_box;
}

char Ghost::getImage() const {
    if (eatmode) return IMAGE_EAT;
    else return IMAGE_GHOST;
}

bool Ghost::moves_empty() {
    if (moves.empty()) return true;
    return false;
}

Dir Ghost::get_next_move() {
    Dir temp = moves[0];
    moves.erase(moves.begin());
    return temp;
}

void Ghost::push_move(Dir d) {
    moves.push_back(d);
}

void Ghost::update_points() {
    points *= 2;
}

void Ghost::reset_points() {
    points = 200;
}

int Ghost::get_points() {
    return points;
}

bool Ghost::get_eatmode() {
    return eatmode;
}

void Ghost::set_eatmode(bool x){
    eatmode = x;
}

void Ghost::move(int row, int col) {
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

    if ((*board)[row][col] == nullptr) {
        (*board)[this->row][this->col] = prev;
        prev = ((*board)[row][col]);
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }
    else if ((*board)[row][col] -> getImage() == 'W' || (*board)[row][col] -> getImage() == 'G') return;
    else if ((*board)[row][col] -> getImage() == 'F' || (*board)[row][col] -> getImage() == 'U') {
        (*board)[this->row][this->col] = prev;
        prev = ((*board)[row][col]);
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }
}

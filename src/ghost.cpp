#include "ghost.h"

Ghost::Ghost(int row, int col, Character* (*board)[31][28], int timebox, Character* previous) :
    Character(row, col, board),
    prev(previous),
    time_in_box(timebox)
{}

int Ghost::get_time_in_box() {
	return time_in_box;
}

void Ghost::reduce_time_in_box() {
    time_in_box--;
}

char Ghost::getImage() const {
    return IMAGE_GHOST;
}

bool Ghost::moves_empty() {
    if (moves.empty()) return true;
    else return false;
}

Dir Ghost::get_next_move() {
    Dir temp = moves[0];
    moves.erase(moves.begin());
    return temp;
}

void Ghost::push_move(Dir d) {
    moves.push_back(d);
}

void Ghost::move(int row, int col) {
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

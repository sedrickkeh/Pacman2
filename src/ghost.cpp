#include "ghost.h"

Ghost::Ghost(int row, int col, Character* (*board)[31][28], int timebox) :
    Character(row, col, board),
	points(200),
	time_in_box(timebox),
    is_eaten(false),
    tempfood(nullptr)
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

void Ghost::eaten(bool eat) {
	is_eaten = eat;
}

void Ghost::set_color(bool eaten) {

}

void Ghost::update_points() {

}

void Ghost::move(int row, int col) {
    if (row < 0 || col < 0 || row >= 31 || col >= 28) return;
    if ((*board)[row][col] == nullptr) {
        if (tempfood != nullptr) (*board)[this->row][this->col] = tempfood;
        tempfood = nullptr;
        delete ((*board)[row][col]);
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }
    else if ((*board)[row][col] -> getImage() == 'W' || (*board)[row][col] -> getImage() == 'G') return;
    else if ((*board)[row][col] -> getImage() == 'F') {
        if (tempfood != nullptr) (*board)[this->row][this->col] = tempfood;
        tempfood = dynamic_cast<Food*>((*board)[row][col]);
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }
}

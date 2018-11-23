#include "ghost.h"

Ghost::Ghost(int row, int col, Character* (*board)[31][28], int timebox) :
    Character(row, col, board),
	points(200),
	time_in_box(timebox),
	is_eaten(false)
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

}

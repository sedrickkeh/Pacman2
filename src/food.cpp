#include "food.h"

Food::Food(int row, int col, Character* (*board)[31][28]) : 
	Character(row, col, board),
    points(20)
{}

char Food::getImage() const {
    return IMAGE_FOOD;
}

int Food::get_points() {
	return points;
}

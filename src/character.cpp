#include "character.h"

Character::Character(int row, int col, Character* (*board)[31][28]) :
	row(row),
	col(col),
	board(board)
{}

Character::~Character() {}

int Character::getRow() const {return row;}
int Character::getCol() const {return col;}

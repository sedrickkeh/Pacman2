#include "ghost.h"
#include <algorithm>

Ghost::Ghost(int row, int col, Character* (*board)[31][28], int timebox, Character* previous, Movement pattern) :
    Character(row, col, board),
    prev(previous),
    time_in_box(timebox),
    direction(NONE),
    pattern(pattern)
{
}

int Ghost::get_time_in_box() {
	return time_in_box;
}

void Ghost::reduce_time_in_box() {
    --time_in_box;
}

char Ghost::getImage() const {
    if (pattern == CHASE) return 'C';
    if (pattern == AMBUSH) return 'A';
    if (pattern == RANDOM) return 'R';
    return IMAGE_GHOST;
}

void Ghost::calculateTarget(int &row, int &col) {
    if (pattern == CHASE) {
        row = pacman->getRow();
        col = pacman->getCol();
    }
    else if (pattern == AMBUSH) {
        int row = pacman->getRow(), col = pacman->getCol();

        if (pacman->get_direction() == UP) row += 4;
        else if (pacman->get_direction() == DOWN) row -= 4;
        else if (pacman->get_direction() == LEFT) col -= 4;
        else if (pacman->get_direction() == RIGHT) col += 4;

        while(!potentialMove(row, col)){
            if(row > pacman->getRow()) --row;
            else if(row < pacman->getRow()) ++row;
            else if(col > pacman->getCol()) --col;
            else if(col < pacman->getCol()) ++col;

            if(row == pacman->getRow() && col == pacman->getCol()) break;
        }
    }
}

Dir Ghost::get_next_move() {
    if(pattern == RANDOM) {
        int arr[4] = {0, 1, 2, 3};
        random_shuffle(arr, arr+4);
        for(int i = 0; i < 4; ++i){
            if(direction!= DOWN && arr[i] == 0 && potentialMove(row+1, col)) return UP;
            if(direction!= UP && arr[i] == 1 && potentialMove(row-1, col)) return DOWN;
            if(direction!= LEFT && arr[i] == 2 && potentialMove(row, col+1)) return RIGHT;
            if(direction!= RIGHT && arr[i] == 3 && potentialMove(row, col-1)) return LEFT;
        }

        if(direction == LEFT) return RIGHT;
        if(direction == RIGHT) return LEFT;
        if(direction == UP) return DOWN;
        if(direction == DOWN) return UP;
    }

    int target_row, target_col;
    calculateTarget(target_row, target_col);

    int up = 0, down = 0, left = 0, right = 0;
    int curr_row, curr_col;

    curr_row = row+1; curr_col = col;
    up = (curr_row - target_row) * (curr_row - target_row) + (curr_col - target_col) * (curr_col - target_col);
    curr_row = row-1; curr_col = col;
    down = (curr_row - target_row) * (curr_row - target_row) + (curr_col - target_col) * (curr_col - target_col);
    curr_row = row; curr_col = col-1;
    left = (curr_row - target_row) * (curr_row - target_row) + (curr_col - target_col) * (curr_col - target_col);
    curr_row = row; curr_col = col+1;
    right = (curr_row - target_row) * (curr_row - target_row) + (curr_col - target_col) * (curr_col - target_col);

    int current;

    if(!potentialMove(row+1, col)) up = -1;
    if(!potentialMove(row-1, col)) down = -1;
    if(!potentialMove(row, col-1)) left = -1;
    if(!potentialMove(row, col+1)) right = -1;

    if(direction == LEFT) right = -1;
    if(direction == RIGHT) left = -1;
    if(direction == UP) down = -1;
    if(direction == DOWN) up = -1;

    current = left;
    if(direction!= RIGHT && (current <= left || left == -1) && (current <= right || right == -1) && (current <= up || up == -1) && (current <= down || down == -1) && left != -1) return LEFT;
    current = right;
    if(direction!= LEFT && (current <= left || left == -1) && (current <= right || right == -1) && (current <= up || up == -1) && (current <= down || down == -1) && right != -1) return RIGHT;
    current = up;
    if(direction!= DOWN && (current <= left || left == -1) && (current <= right || right == -1) && (current <= up || up == -1) && (current <= down || down == -1) && up != -1) return UP;
    current = down;
    if(direction!= UP && (current <= left || left == -1) && (current <= right || right == -1) && (current <= up || up == -1) && (current <= down || down == -1) && down != -1) return DOWN;

    if(direction == LEFT) return RIGHT;
    if(direction == RIGHT) return LEFT;
    if(direction == UP) return DOWN;
    if(direction == DOWN) return UP;
}

void Ghost::set_direction(Dir direction){
    this->direction = direction;
}

bool Ghost::potentialMove(int row, int col) {
    if (col == -1 && row == 16) return true;
    if (col == 28 && row == 16) return true;
    if (row < 0 || col < 0 || row >= 31 || col >= 28) return false;
    if ((*board)[row][col] == nullptr) return true;
    if ((*board)[row][col] -> getImage() == 'W' || (*board)[row][col] -> getImage() == 'G') return false;
    if ((*board)[row][col] -> getImage() == 'F' || (*board)[row][col] -> getImage() == 'U') return true;
    return false;
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

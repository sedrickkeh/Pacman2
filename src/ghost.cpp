#include "ghost.h"

#include "pacman.h"
#include <algorithm>

Ghost::Ghost(int number, int row, int col, Character* (*board)[31][28], int timebox, Character* previous, Mode mode, Movement pattern) :
    Character(row, col, board),
    number(number),
    direction(Dir::NONE),
    prev(previous)
{
    //in classic, we start normally with each ghost worth 200
    if (mode == Mode::CLASSIC) {
        points = 200;
        eatmode = false;
        this->pattern = pattern;
        this->time_in_box = timebox;
    }

    //in reverse mode, we start with eatmode and ghosts are worth more with no movement pattern and shorter time in box
    else if (mode == Mode::REVERSE) {
        points = 1000;
        eatmode = true;
        this->pattern = Movement::RANDOM;
        this->time_in_box = 5;
    }
}

Ghost::~Ghost() {}

char Ghost::getImage() const
{
    if (eatmode) return IMAGE_EAT;
    if (pattern == Movement::CHASE) return 'C';
    if (pattern == Movement::AMBUSH) return 'A';
    if (pattern == Movement::RANDOM) return 'R';
    return IMAGE_GHOST;
}

int Ghost::get_number() const
{
    return number;
}

void Ghost::set_pacman(Pacman* pacman)
{
    this->pacman = pacman;
}

int Ghost::get_time_in_box() const
{
	return time_in_box;
}

void Ghost::set_time_in_box(int t)
{
    time_in_box = t;
}

void Ghost::reduce_time_in_box()
{
    --time_in_box;
}

Character* Ghost::get_prev() const
{
    return prev;
}

Dir Ghost::get_next_move() const
{
    if(pattern == Movement::RANDOM) {
        //choose a random direction and check whether the square is valid, not allowing ghosts to go back

        int arr[4] = {0, 1, 2, 3};
        std::random_shuffle(arr, arr+4);
        for(int i = 0; i < 4; ++i){
            if(direction!= Dir::DOWN && arr[i] == 0 && potentialMove(row+1, col)) return Dir::UP;
            if(direction!= Dir::UP && arr[i] == 1 && potentialMove(row-1, col)) return Dir::DOWN;
            if(direction!= Dir::LEFT && arr[i] == 2 && potentialMove(row, col+1)) return Dir::RIGHT;
            if(direction!= Dir::RIGHT && arr[i] == 3 && potentialMove(row, col-1)) return Dir::LEFT;
        }

        //in case only going back is the remaining move
        if(direction == Dir::LEFT) return Dir::RIGHT;
        if(direction == Dir::RIGHT) return Dir::LEFT;
        if(direction == Dir::UP) return Dir::DOWN;
        if(direction == Dir::DOWN) return Dir::UP;

        //in case no movements
        return Dir::NONE;
    }

    //calculate the target pixel of the ghost, depending on the movement pattern
    int target_row, target_col;
    calculateTarget(target_row, target_col);

    //store the distance to pacman of the 4 directions wrt to current position
    int up = 0, down = 0, left = 0, right = 0;
    int curr_row, curr_col;

    //calculate absolute distance of all 4 directions
    curr_row = row+1; curr_col = col;
    up = (curr_row - target_row) * (curr_row - target_row) + (curr_col - target_col) * (curr_col - target_col);
    curr_row = row-1; curr_col = col;
    down = (curr_row - target_row) * (curr_row - target_row) + (curr_col - target_col) * (curr_col - target_col);
    curr_row = row; curr_col = col-1;
    left = (curr_row - target_row) * (curr_row - target_row) + (curr_col - target_col) * (curr_col - target_col);
    curr_row = row; curr_col = col+1;
    right = (curr_row - target_row) * (curr_row - target_row) + (curr_col - target_col) * (curr_col - target_col);

    //set invalid move as -1 for checking
    if(!potentialMove(row+1, col)) up = -1;
    if(!potentialMove(row-1, col)) down = -1;
    if(!potentialMove(row, col-1)) left = -1;
    if(!potentialMove(row, col+1)) right = -1;

    if(direction == Dir::LEFT) right = -1;
    if(direction == Dir::RIGHT) left = -1;
    if(direction == Dir::UP) down = -1;
    if(direction == Dir::DOWN) up = -1;

    int current;

    //if shortest distance and valid, go there
    current = left;
    if(direction != Dir::RIGHT && (current <= left || left == -1) && (current <= right || right == -1) && (current <= up || up == -1) && (current <= down || down == -1) && left != -1) return Dir::LEFT;
    current = right;
    if(direction != Dir::LEFT && (current <= left || left == -1) && (current <= right || right == -1) && (current <= up || up == -1) && (current <= down || down == -1) && right != -1) return Dir::RIGHT;
    current = up;
    if(direction!= Dir::DOWN && (current <= left || left == -1) && (current <= right || right == -1) && (current <= up || up == -1) && (current <= down || down == -1) && up != -1) return Dir::UP;
    current = down;
    if(direction!= Dir::UP && (current <= left || left == -1) && (current <= right || right == -1) && (current <= up || up == -1) && (current <= down || down == -1) && down != -1) return Dir::DOWN;

    //in case none of the above were valid, then have to turn back
    if(direction == Dir::LEFT) return Dir::RIGHT;
    if(direction == Dir::RIGHT) return Dir::LEFT;
    if(direction == Dir::UP) return Dir::DOWN;
    if(direction == Dir::DOWN) return Dir::UP;

    //in case nothing is valid, just stay there
    return Dir::NONE;
}

void Ghost::set_direction(Dir direction)
{
    this->direction = direction;
}

void Ghost::move(int row, int col)
{
    //wrap around for the esge of map teleportation
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

    //check if out of the map
    if (row < 0 || col < 0 || row >= 31 || col >= 28)
        return;

    //move the ghost if empty space
    if ((*board)[row][col] == nullptr) {
        (*board)[this->row][this->col] = prev;
        prev = ((*board)[row][col]);
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }

    //do nothing if we hit a wall
    else if ((*board)[row][col] -> getImage() == 'W' || (*board)[row][col] -> getImage() == 'G')
        return;

    //save the previous thing if we pass by food or ghostwall so it will not be deleted
    else if ((*board)[row][col] -> getImage() == 'F' || (*board)[row][col] -> getImage() == 'U' || (*board)[row][col] -> getImage() == 'V') {
        (*board)[this->row][this->col] = prev;
        prev = ((*board)[row][col]);
        ((*board)[row][col]) = this;
        this->row = row; this->col = col;
    }
}

int Ghost::get_points() const
{
    return points;
}

void Ghost::update_points()
{
    points *= 2;
}

void Ghost::reset_points()
{
    points = 200;
}

bool Ghost::get_eatmode() const
{
    return eatmode;
}

void Ghost::set_eatmode(bool x)
{
    eatmode = x;
    reset_points();
}

bool Ghost::potentialMove(int row, int col) const
{
    //this is like move, but only returns a boolean to see if valid move
    if (col == -1 && row == 16)
        return true;
    if (col == 28 && row == 16)
        return true;
    if (row < 0 || col < 0 || row >= 31 || col >= 28)
        return false;
    if ((*board)[row][col] == nullptr)
        return true;
    if ((*board)[row][col] -> getImage() == 'W' || (*board)[row][col] -> getImage() == 'G')
        return false;
    if ((*board)[row][col] -> getImage() == 'F' || (*board)[row][col] -> getImage() == 'P' || (*board)[row][col] -> getImage() == 'U' || (*board)[row][col] -> getImage() == 'V')
        return true;

    //default value
    return false;
}

void Ghost::calculateTarget(int &row, int &col) const
{
    //chase just targets pacman
    if (pattern == Movement::CHASE) {
        row = pacman->getRow();
        col = pacman->getCol();
    }

    //ambush tries to go 4 spaces ahead of pacman or closer if it is an invalid place
    else if (pattern == Movement::AMBUSH) {
        row = pacman->getRow();
        col = pacman->getCol();

        //4 spaces ahead
        if (pacman->get_direction() == Dir::UP) row += 4;
        else if (pacman->get_direction() == Dir::DOWN) row -= 4;
        else if (pacman->get_direction() == Dir::LEFT) col -= 4;
        else if (pacman->get_direction() == Dir::RIGHT) col += 4;

        //if not a valid place, reduce spaces ahead
        while(!potentialMove(row, col)) {
            if(row > pacman->getRow()) --row;
            else if(row < pacman->getRow()) ++row;
            else if(col > pacman->getCol()) --col;
            else if(col < pacman->getCol()) ++col;

            //stop when we reach position of pacman
            if(row == pacman->getRow() && col == pacman->getCol()) break;
        }
    }
}

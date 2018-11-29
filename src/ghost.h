#ifndef GHOST_H
#define GHOST_H

#include "character.h"
#include "direction.h"
#include "pacman.h"
#include "movement.h"
#include "food.h"
#include <vector>
using namespace std;

class Pacman;

class Ghost : public Character
{
public:
    Ghost(int row, int col, Character* (*board)[31][28], int timebox, Character* previous, Movement pattern);
    const static char IMAGE_GHOST = 'G';
    virtual char getImage() const override;
    int get_time_in_box();
    void reduce_time_in_box();
    bool potentialMove(int row, int col);
    void move(int row, int col);
    Character* prev;
    Pacman* pacman;

    void calculateTarget(int &row, int &col);
    Dir get_next_move();
    void set_direction(Dir direction);

protected:
    int time_in_box = 10;
    Dir direction;
    Movement pattern;
};

#endif // PACMAN_H

#ifndef GHOST_H
#define GHOST_H

#include "character.h"
#include "direction.h"
#include "food.h"
#include <vector>
using namespace std;

class Ghost : public Character
{
public:
    Ghost(int row, int col, Character* (*board)[31][28], int timebox, Character* previous);
    const static char IMAGE_GHOST = 'G';
    virtual char getImage() const override;
    int get_time_in_box();
    void reduce_time_in_box();
    void move(int row, int col);
    Character* prev;

    bool moves_empty();
    Dir get_next_move();
    void push_move(Dir d);

protected:
    int time_in_box = 10;
    vector<Dir> moves;
};

#endif // PACMAN_H

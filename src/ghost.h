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
    ~Ghost() override;
    const static char IMAGE_GHOST = 'G';
    const static char IMAGE_EAT = 'E';
    virtual char getImage() const override;
    int get_time_in_box();
    void set_time_in_box(int t);
    void reduce_time_in_box();
    void move(int row, int col);
    Character* prev;

    bool moves_empty();
    Dir get_next_move();
    void push_move(Dir d);

    void update_points();
    void reset_points();
    int get_points();
    bool get_eatmode();
    void set_eatmode(bool x);

protected:
    int points = 100;
    int time_in_box = 10;
    vector<Dir> moves;
    bool eatmode = false;
};

#endif // PACMAN_H

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
    ~Ghost() override;
    const static char IMAGE_GHOST = 'G';
    const static char IMAGE_EAT = 'E';
    virtual char getImage() const override;
    int get_time_in_box();
    void set_time_in_box(int t);
    void reduce_time_in_box();
    bool potentialMove(int row, int col);
    void move(int row, int col);
    Character* prev;
    Pacman* pacman;

    void calculateTarget(int &row, int &col);
    Dir get_next_move();
    void set_direction(Dir direction);

    void update_points();
    void reset_points();
    int get_points();
    bool get_eatmode();
    void set_eatmode(bool x);

protected:
    int points = 100;
    int time_in_box = 10;
    Dir direction;
    Movement pattern;
    bool eatmode = false;
};

#endif // PACMAN_H

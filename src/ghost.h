#ifndef GHOST_H
#define GHOST_H

#include "character.h"
#include "direction.h"
#include "food.h"

class Ghost : public Character
{
public:
    Ghost(int row, int col, Character* (*board)[31][28], int timebox);
    const static char IMAGE_GHOST = 'G';
    virtual char getImage() const override;
    int get_time_in_box();
    void reduce_time_in_box();
    void eaten(bool eat);
    void set_color(bool eaten);
    void update_points();
    void move(int row, int col);
    Character* prev;

private:
    int points = 200;
    int time_in_box = 10;
    bool is_eaten = false;
};

#endif // PACMAN_H

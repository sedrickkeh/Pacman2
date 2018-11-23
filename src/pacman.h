#ifndef PACMAN_H
#define PACMAN_H

#include "character.h"
#include "direction.h"

class Pacman : public Character
{
public:
    Pacman(int row, int col, Character* (*board)[31][28]);
    const static char IMAGE_PACMAN = 'P';
    virtual char getImage() const override;
    int get_superpower();
    Dir get_direction();
    void update_superpower(bool sup);
    void update_direction(Dir dir);
    void eats_piece(bool eat);
    void move(int row, int col);

private:
    int superpower = -1;
    Dir direction = Dir::LEFT;
    bool has_eaten_piece = false;
};

#endif // PACMAN_H

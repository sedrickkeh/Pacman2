#ifndef PACMAN_H
#define PACMAN_H

#include "character.h"
#include "direction.h"
#include "food.h"
#include "ghost.h"

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
    void eats_piece(Food* f);
    void not_eat_piece();
    void encounter_ghost(Ghost* g);
    void move(int row, int col);
    int get_lives();
    int get_points_to_add();

private:
    int superpower = -1;
    Dir direction = Dir::LEFT;
    bool has_eaten_piece = false;
    int addpoints = -1;
    int lives = 3;
};

#endif // PACMAN_H

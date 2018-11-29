#ifndef PACMAN_H
#define PACMAN_H

#include "character.h"
#include "direction.h"
#include "food.h"
#include "superpower.h"

class Ghost;

class Pacman : public Character
{
public:
    Pacman(int row, int col, Character* (*board)[31][28]);
    const static char IMAGE_PACMAN = 'P';
    virtual char getImage() const override;
    bool just_eaten_superpower();
    bool just_lost_superpower();
    void set_gain();
    void set_lose();
    Dir get_direction();
    void update_superpower();
    void update_direction(Dir dir);
    void eats_piece(Food* f);
    void eats_ghost(Ghost* g, int row, int col);
    void not_eat_piece();
    void encounter_ghost();
    bool get_has_eaten_ghost();
    void not_eat_ghost();
    void move(int row, int col);
    int get_lives();
    int get_points_to_add();

private:
    int superpower = -1;
    Dir direction = Dir::LEFT;
    bool has_eaten_piece = false;
    bool has_eaten_ghost = false;
    bool gain = false;
    bool lose = false;
    int addpoints = -1;
    int lives = 3;
};

#endif // PACMAN_H

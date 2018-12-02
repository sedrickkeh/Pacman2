#ifndef PACMAN_H
#define PACMAN_H

#include "character.h"
#include "direction.h"
#include "food.h"
#include "superpower.h"
#include "gamemode.h"

class Ghost;
class PacmanGame;

class Pacman : public Character
{
public:
    Pacman(PacmanGame* pacmangame, int row, int col, Character* (*board)[31][28], Mode mode);
    const static char IMAGE_PACMAN = 'P';
    virtual char getImage() const override;

    bool just_eaten_superpower() const;
    bool just_lost_superpower() const;
    void set_gain();
    void set_lose();
    Dir get_direction() const;

    int get_superpower() const;
    void set_superpower(int num);
    void update_superpower();
    void update_direction(Dir dir);

    void eats_piece(Food* f);
    void not_eat_piece();
    void encounter_ghost();
    void eats_ghost(Ghost* g, int row, int col);
    void not_eat_ghost();

    bool get_has_encountered_ghost();
    bool get_has_eaten_ghost() const;
    int get_points_to_add() const;
    int get_lives() const;

    void move(int row, int col);

private:
    PacmanGame* pacmangame;
    int superpower = -1;
    Dir direction = Dir::NONE;
    Mode mode;
    bool has_eaten_piece = false;
    bool has_eaten_ghost = false;
    bool has_encountered_ghost = false;
    bool gain = false;
    bool lose = false;
    int addpoints = -1;
    int lives = 3;
};

#endif // PACMAN_H

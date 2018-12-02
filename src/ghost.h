#ifndef GHOST_H
#define GHOST_H

#include "character.h"
#include "gamemode.h"
#include "direction.h"
#include "movement.h"

class Pacman;

class Ghost : public Character
{
public:
    Ghost(int number, int row, int col, Character* (*board)[31][28], int timebox, Character* previous, Mode mode = CLASSIC, Movement pattern = RANDOM);
    ~Ghost() override;
    const static char IMAGE_GHOST = 'G';
    const static char IMAGE_EAT = 'E';

    virtual char getImage() const override;
    int get_number() const;
    void set_pacman(Pacman* pacman);

    int get_time_in_box() const;
    void set_time_in_box(int t);
    void reduce_time_in_box();

    Character* get_prev() const;
    Dir get_next_move() const;
    void set_direction(Dir direction);
    void move(int row, int col);

    int get_points() const;
    void update_points();
    void reset_points();

    bool get_eatmode() const;
    void set_eatmode(bool x);

private:
    int number;
    Movement pattern;

    int points = 100;
    int time_in_box = 10;
    bool eatmode = false;
    Dir direction;
    Character* prev;
    Pacman* pacman;

    bool potentialMove(int row, int col) const;

    //for the ghost algorithms
    void calculateTarget(int &row, int &col) const;
};

#endif // PACMAN_H

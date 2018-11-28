#ifndef EATGHOST_H
#define EATGHOST_H

#include "character.h"
#include "ghost.h"

class EatGhost : public Ghost
{
public:
    EatGhost(int row, int col, Character* (*board)[31][28], int timebox, Character* previous);
    const static char IMAGE_EATGHOST = 'E';
    virtual char getImage() const override;

    void update_points();
    int get_points();

private:
    int points;
};

#endif // EATGHOST_H

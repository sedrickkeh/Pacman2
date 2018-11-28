#ifndef SUPERPOWER_H
#define SUPERPOWER_H

#include "character.h"
#include "food.h"

class Superpower : public Food
{
public:
    Superpower(int row, int col, Character* (*board)[31][28]);
    const static char IMAGE_SUPERPOWER = 'U';
    virtual char getImage() const override;
};

#endif // SUPERPOWER_H

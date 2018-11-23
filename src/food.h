#ifndef FOOD_H
#define FOOD_H

#include "character.h"

class Food : public Character
{
public:
	Food(int row, int col, Character* (*board)[31][28]);
    const static char IMAGE_FOOD = 'F';
    virtual char getImage() const override;
    int get_points();
    bool is_superpower();

private:
    int points;
    bool superpower;
};

#endif // FOOD_H

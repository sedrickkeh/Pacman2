#ifndef GHOSTWALL_H
#define GHOSTWALL_H

#include "character.h"

class ghostwall : public Character
{
public:
    ghostwall(int row, int col, Character* (*board)[31][28]);
    const static char IMAGE_GHOSTWALL = 'V';
    virtual char getImage() const override;
};


#endif // GHOSTWALL_H

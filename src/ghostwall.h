#ifndef GHOSTWALL_H
#define GHOSTWALL_H

#include "character.h"

class Ghostwall : public Character
{
public:
    Ghostwall(int row, int col, Character* (*board)[31][28]);
    const static char IMAGE_GHOSTWALL = 'V';
    virtual char getImage() const override;
};

#endif // GHOSTWALL_H

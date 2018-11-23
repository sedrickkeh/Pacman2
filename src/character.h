#ifndef CHARACTER_H
#define CHARACTER_H

class PacmanGame;

class Character
{
public:
    Character(int row, int col, Character* (*board)[31][28]);
    virtual ~Character();

    int getRow() const;
    int getCol() const;
    virtual char getImage() const = 0;

protected:
    int row, col;
    Character* (*board)[31][28];
};

#endif // CHARACTER_H

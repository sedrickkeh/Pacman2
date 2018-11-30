#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <algorithm>
#include <QObject>

#include "character.h"
#include "wall.h"
#include "food.h"
#include "pacman.h"
#include "ghost.h"
#include "direction.h"
#include "superpower.h"
#include "ghostwall.h"
#include "movement.h"

#include "makerwindow.h"
#include "square.h"
#include <string>

class MapMaker : public QObject {
    Q_OBJECT
public:
    MapMaker();
    void startGraphicUI();
    Makerwindow* get_maker_window() const;
    void process_user_input(int row, int col);
    Character* getchar(int row, int col);

private:
    Makerwindow* makerwindow;
    Character* board[31][28];
    void init_block(int row, int col, char c);
    void load_map();
};

#endif // MAPMAKER_H

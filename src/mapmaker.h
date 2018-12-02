#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <QObject>
#include "QString"

#include "makerwindow.h"
#include "square.h"

#include "character.h"
#include "wall.h"
#include "food.h"
#include "pacman.h"
#include "ghost.h"
#include "superpower.h"
#include "ghostwall.h"

#include "gamemode.h"
#include "movement.h"
#include "direction.h"

class MapMaker : public QObject {
    Q_OBJECT
public:
    MapMaker();
    void startGraphicUI();
    Makerwindow* get_maker_window() const;
    void process_user_input(int row, int col);
    Character* getchar(int row, int col) const;

private:
    Makerwindow* makerwindow;
    Character* board[31][28];
    void init_block(int row, int col, char c);
    void load_map();

    static const QString map_dir;
    static const QString map_path;
};

#endif // MAPMAKER_H

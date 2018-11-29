#ifndef PACMANGAME_H
#define PACMANGAME_H

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
#include "eatghost.h"

#include "gamewindow.h"
#include "square.h"
#include <string>
#include <QTimer>

class PacmanGame : public QObject {
    Q_OBJECT
public:
    PacmanGame();
    ~PacmanGame();
    void startGraphicUI();
    GameWindow* get_game_window() const;
    Pacman* get_pacman();

private:
    GameWindow* game_window;
    Character* board[31][28];
    Pacman* pacman;
    Ghost* ghost1;
    Ghost* ghost2;
    Ghost* ghost3;
    Ghost* ghost4;
    int current_score;
    int high_score;
    int level;

    void load_map();
    void init_block(int row, int col, char c);
    void load_high_score();

    void complete_level();
    bool is_level_finished();

    bool exists_ghost_in_box();

    void move_pacman(int r, int c);
    void move_ghost(int r, int c, Ghost* g);
    void gain_power();
    void lose_power();
    void set_weak(Ghost* g);
    void set_unweak(Ghost* g);
    void update_ghost_scores();
    void reset_ghosts();
    void update_score();
    void update_map();
    void update_lives();
    void game_over();
    QTimer *timer;

private slots:
    void refresh_frame();
};

#endif // PACMANGAME_H

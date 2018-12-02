#ifndef PACMANGAME_H
#define PACMANGAME_H

#include <QObject>
#include <QTimer>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QString>

#include "gamewindow.h"
#include "square.h"
#include "gamemode.h"

#include "character.h"
#include "wall.h"
#include "food.h"
#include "pacman.h"
#include "ghost.h"
#include "direction.h"
#include "superpower.h"
#include "ghostwall.h"
#include "modedialog.h"

class PacmanGame : public QObject {
    Q_OBJECT
public:
    PacmanGame(Mode mode, int highscore);
    ~PacmanGame();
    void startGraphicUI();
    GameWindow* get_game_window() const;
    Pacman* get_pacman() const;
    Mode get_mode() const;
    bool is_mapmaker_mode() const;
    void remove_ghost(int number);
    int get_score() const;

private:
    GameWindow* game_window;
    QTimer *timer;
    Mode mode;
    Character* board[31][28];
    Pacman* pacman;
    Ghost* ghost1;
    Ghost* ghost2;
    Ghost* ghost3;
    Ghost* ghost4;
    int current_score;
    int high_score;
    int level;
    bool mapmaker_mode;

    static const QString map_dir;
    static const QString map_path;

    void set_mode();
    void load_map(int highscore);
    void update_map();
    void init_block(int row, int col, char c);

    void move_pacman(int r, int c);
    void move_ghost(int r, int c, Ghost* g);

    void gain_power();
    void lose_power();
    void update_ghost_scores();
    void reset_ghosts();
    void update_score();
    void update_lives();
    void update_timer();

    void complete_level();
    bool is_level_finished();
    void game_over();

private slots:
    void refresh_frame();
};

#endif // PACMANGAME_H

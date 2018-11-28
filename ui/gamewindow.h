#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QPixmap>

class Square;
class PacmanGame;

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, PacmanGame* _pacman_game = nullptr);
    ~GameWindow();
    static const int HIGH_SCORE = 0;
    static const int SCORE = 1;
//    static const int LEVEL_LCD = 2;
    PacmanGame* get_pacman_game() const;
    Square* get_square(int row, int col) const;
    void set_square(int row, int col, char i);
    void set_lives();
    void set_lcd(int type, int value);

private:
    void closeEvent(QCloseEvent *event);
    void make_grid();
    void keyPressEvent(QKeyEvent* event);
    Ui::GameWindow *ui;
    Square* square[31][28];
    PacmanGame* pacman_game;

signals:
    void closed();
};

#endif // GAMEWINDOW_H

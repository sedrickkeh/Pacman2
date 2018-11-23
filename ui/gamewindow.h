#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QCloseEvent>

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

    PacmanGame* get_pacman_game() const;
    Square* get_square(int row, int col) const;
    void set_square(int row, int col, char i);

private:
    void closeEvent(QCloseEvent *event);
    void make_grid();

    Ui::GameWindow *ui;
    Square* square[31][28];
    PacmanGame* pacman_game;

signals:
    void closed();
};

#endif // GAMEWINDOW_H

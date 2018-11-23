#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gamewindow.h"
#include <QImage>
#include <QImage>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class PacmanGame;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PacmanGame* pacman_game;

private slots:
    void startButton_clicked_handler();
    void game_window_closed_handler();
};

#endif // MAINWINDOW_H
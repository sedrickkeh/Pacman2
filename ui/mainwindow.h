#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>

#include "gamewindow.h"
#include "makerwindow.h"

namespace Ui {
class MainWindow;
}

class PacmanGame;
class RecordManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RecordManager *rm;
    PacmanGame* pacman_game;
    MapMaker* mapmaker;

private slots:
    void start_button_clicked_handler();
    void map_button_clicked_handler();
    void game_window_closed_handler();
    void maker_window_closed_handler();
};

#endif // MAINWINDOW_H

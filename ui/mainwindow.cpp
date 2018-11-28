#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pacmangame.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pacman_game(nullptr)
{
    ui->setupUi(this);
    //ui->label->setStyleSheet("*{background-image: url(:/titlescreen.jpg);}");
    QPixmap img(":/resources/img/titlepage.jpg");
    ui->label->setPixmap(img.scaled(1000, 500, Qt::KeepAspectRatio));
   connect(this->ui->startButton, &QPushButton::clicked, this, &MainWindow::startButton_clicked_handler);
}

MainWindow::~MainWindow()
{
    if (this->pacman_game != nullptr) delete this->pacman_game;
    delete this->ui;
}

void MainWindow::startButton_clicked_handler()
{
    if (this->pacman_game) delete this->pacman_game;
    this->pacman_game = new PacmanGame;
    this->pacman_game->startGraphicUI();
    connect(this->pacman_game->get_game_window(), &GameWindow::closed, this, &MainWindow::game_window_closed_handler);
    this->hide();
}

void MainWindow::game_window_closed_handler() {
    this->show();
}

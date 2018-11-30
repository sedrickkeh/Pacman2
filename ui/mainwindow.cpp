#include "mainwindow.h"

#include "qinputdialog.h"
#include "ui_mainwindow.h"
#include "pacmangame.h"
#include "recordmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rm(new RecordManager()),
    pacman_game(nullptr)
{
    ui->setupUi(this);
    QPixmap img(":/resources/img/titlepage.jpg");
    ui->label->setPixmap(img.scaled(1000, 500, Qt::KeepAspectRatio));
    connect(this->ui->startButton, &QPushButton::clicked, this, &MainWindow::start_button_clicked_handler);
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->rm;
}

void MainWindow::start_button_clicked_handler()
{
    //have an if statement for highest score
    this->pacman_game = new PacmanGame(REVERSE, rm->get_classic_highest_score());
    this->pacman_game->startGraphicUI();
    connect(this->pacman_game->get_game_window(), &GameWindow::closed, this, &MainWindow::game_window_closed_handler);
    this->hide();
}

void MainWindow::game_window_closed_handler() {
    //have an if statement for lowest score
    if(pacman_game->get_score() > rm->get_classic_lowest_score()){
        QString name = QInputDialog::getText(this, "New Highscore", "Enter Name");
        //have an if statement for update record
        rm->update_classic_record(name, pacman_game->get_score());
    }

    if (pacman_game != nullptr) delete pacman_game;
    pacman_game = nullptr;

    this->show();
}

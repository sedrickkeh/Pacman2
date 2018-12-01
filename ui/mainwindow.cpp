#include "mainwindow.h"

#include "qinputdialog.h"
#include "ui_mainwindow.h"
#include "pacmangame.h"
#include "mapmaker.h"
#include "recordmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rm(new RecordManager()),
    pacman_game(nullptr),
    mapmaker(nullptr),
    highscore(nullptr)
{
    ui->setupUi(this);
    QPixmap img(":/resources/img/titlepage.jpg");
    ui->label->setPixmap(img.scaled(1000, 500, Qt::KeepAspectRatio)); 
    connect(this->ui->classic_button, &QPushButton::clicked, this, &MainWindow::classic_button_clicked_handler);
    connect(this->ui->reverse_button, &QPushButton::clicked, this, &MainWindow::reverse_button_clicked_handler);
    connect(this->ui->highscore_button, &QPushButton::clicked, this, &MainWindow::highscore_button_clicked_handler);
    connect(this->ui->mapmaker_button, &QPushButton::clicked, this, &MainWindow::map_button_clicked_handler);
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->rm;
}

void MainWindow::classic_button_clicked_handler()
{
    //have an if statement for highest score
    this->pacman_game = new PacmanGame(CLASSIC, rm->get_classic_highest_score());
    this->pacman_game->startGraphicUI();
    connect(this->pacman_game->get_game_window(), &GameWindow::closed, this, &MainWindow::game_window_closed_handler);
    this->hide();
}

void MainWindow::map_button_clicked_handler() {
    this->mapmaker = new MapMaker();
    this->mapmaker->startGraphicUI();
    connect(this->mapmaker->get_maker_window(), &Makerwindow::closed, this, &MainWindow::maker_window_closed_handler);
    this->hide();
}

void MainWindow::reverse_button_clicked_handler() {
    //have an if statement for highest score
    this->pacman_game = new PacmanGame(REVERSE, rm->get_reverse_highest_score());
    this->pacman_game->startGraphicUI();
    connect(this->pacman_game->get_game_window(), &GameWindow::closed, this, &MainWindow::game_window_closed_handler);
    this->hide();
}

void MainWindow::highscore_button_clicked_handler() {
    //have an if statement for highest score
    highscore = new Highscorewindow(nullptr, rm);
    highscore->show();
    connect(this->highscore, &Highscorewindow::closed, this, &MainWindow::highscore_window_closed_handler);
    this->hide();
}

void MainWindow::game_window_closed_handler() {
    //have an if statement for lowest score
    if(pacman_game->get_mode()==Mode::CLASSIC){
        if(pacman_game->get_score() > rm->get_classic_lowest_score()){
            QString name = QInputDialog::getText(this, "New Highscore", "Enter Name");
            //have an if statement for update record
            rm->update_classic_record(name, pacman_game->get_score());
        }
    }
    else {
        if(pacman_game->get_score() > rm->get_reverse_lowest_score()){
            QString name = QInputDialog::getText(this, "New Highscore", "Enter Name");
            //have an if statement for update record
            rm->update_reverse_record(name, pacman_game->get_score());
        }

    }

    if (pacman_game != nullptr) delete pacman_game;
    pacman_game = nullptr;
    this->show();
}

void MainWindow::maker_window_closed_handler() {
    if (mapmaker != nullptr) delete mapmaker;
    mapmaker = nullptr;
    this->show();
}

void MainWindow::highscore_window_closed_handler(){
   if (highscore!=nullptr) delete highscore;
   highscore=nullptr;
   this->show();
}

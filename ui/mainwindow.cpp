#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "recordmanager.h"
#include "qinputdialog.h"

#include "pacmangame.h"
#include "mapmaker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rm(new RecordManager()),
    pacman_game(nullptr),
    mapmaker(nullptr),
    highscore(nullptr)
{
    ui->setupUi(this);

    //load and show title page image
    QPixmap titlepage(":/resources/img/titlepage.jpg");
    ui->label->setPixmap(titlepage.scaled(1000, 500, Qt::KeepAspectRatio));

    //connect the buttons with appropriate slots
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
    ModeDialog d(nullptr);
    char result = d.get_choice();
    if (result == ' ') return;

    //create new classic pacman game with corresponding parameters
    this->pacman_game = new PacmanGame(Mode::CLASSIC, rm->get_classic_highest_score(), result);
    this->pacman_game->startGraphicUI();

    //connect the close button with the slot
    connect(this->pacman_game->get_game_window(), &GameWindow::closed, this, &MainWindow::game_window_closed_handler);

    //hide main window
    this->hide();
}

void MainWindow::reverse_button_clicked_handler()
{
    ModeDialog d(nullptr);
    char result = d.get_choice();
    if (result == ' ') return;

    //create new reverse pacman game with corresponding parameters
    this->pacman_game = new PacmanGame(Mode::REVERSE, rm->get_reverse_highest_score(), result);
    this->pacman_game->startGraphicUI();

    //connect the close button with the slot
    connect(this->pacman_game->get_game_window(), &GameWindow::closed, this, &MainWindow::game_window_closed_handler);

    //hide main window
    this->hide();
}

void MainWindow::highscore_button_clicked_handler()
{
    //create window for high score with corresponding parameters
    highscore = new Highscorewindow(nullptr, rm);
    highscore->show();

    //connect the close button with the slot
    connect(this->highscore, &Highscorewindow::closed, this, &MainWindow::highscore_window_closed_handler);

    //hide main window
    this->hide();
}

void MainWindow::map_button_clicked_handler()
{
    //create new map maker window with corresponding parameters
    this->mapmaker = new MapMaker();
    this->mapmaker->startGraphicUI();

    //connect the close button with the slot
    connect(this->mapmaker->get_maker_window(), &Makerwindow::closed, this, &MainWindow::maker_window_closed_handler);

    //hide main window
    this->hide();
}

void MainWindow::game_window_closed_handler()
{
    if(pacman_game->get_mode() == Mode::CLASSIC) {
        //update high score for classic if needed and only when using default map
        if (pacman_game->is_mapmaker_mode());
        else if(pacman_game->get_score() > rm->get_classic_lowest_score()){
            //ask for name of new high score player and update record
            QString name = QInputDialog::getText(this, "New Highscore", "Enter Name");
            rm->update_classic_record(name, pacman_game->get_score());
        }
    }
    else if(pacman_game->get_mode() == Mode::REVERSE) {
        //update high score for reverse if needed and only when using default map
        if (pacman_game->is_mapmaker_mode());
        else if(pacman_game->get_score() > rm->get_reverse_lowest_score()){
            //ask for name of new high score player and update record
            QString name = QInputDialog::getText(this, "New Highscore", "Enter Name");
            rm->update_reverse_record(name, pacman_game->get_score());
        }
    }

    //delete the game and reshow main window
    if (pacman_game != nullptr) delete pacman_game;
    pacman_game = nullptr;
    this->show();
}

void MainWindow::highscore_window_closed_handler()
{
    //delete the high score window and reshow main window
    if (highscore != nullptr) delete highscore;
    highscore = nullptr;
    this->show();
}

void MainWindow::maker_window_closed_handler()
{
    //delete mapmaker window and reshow main window
    if (mapmaker != nullptr) delete mapmaker;
    mapmaker = nullptr;
    this->show();
}

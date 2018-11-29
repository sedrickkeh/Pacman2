#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "square.h"
#include "pacmangame.h"

GameWindow::GameWindow(QWidget *parent, PacmanGame* _pacman_game) :
   QWidget(parent),
   ui(new Ui::GameWindow),
   pacman_game(_pacman_game)
{
   ui->setupUi(this);
   this->make_grid();

   QPixmap img1(":/resources/img/pac_man_hed.jpg");
   QPixmap img2(":/resources/img/lives.jpg");
   QPixmap img3(":/resources/img/highscore.jpg");
   QPixmap img4(":/resources/img/score.jpg");

   ui->obj_1->setPixmap(img1.scaled(32, 32, Qt::KeepAspectRatio));
   ui->obj_2->setPixmap(img1.scaled(32,32,Qt::KeepAspectRatio));
   ui->obj_3->setPixmap(img1.scaled(32,32,Qt::KeepAspectRatio));
//   ui->obj_4->setPixmap(img1.scaled(32,32,Qt::KeepAspectRatio));
//   ui->obj_5->setPixmap(img1.scaled(32,32,Qt::KeepAspectRatio));
   ui->highscore->setPixmap(img3.scaled(200,32));
   ui->score->setPixmap(img4.scaled(60,32));
   ui->lives->setPixmap(img2.scaled(100,32,Qt::KeepAspectRatio));

   set_lcd(GameWindow::SCORE, 0);
   set_lcd(GameWindow::HIGH_SCORE, 0);
}

GameWindow::~GameWindow()
{
   delete ui;
   for (int i = 0; i < 31; i ++)
       for (int j = 0; j < 28; j ++)
           delete square[i][j];
}

void GameWindow::closeEvent(QCloseEvent *event) {
   emit closed();
}

void GameWindow::make_grid() {
   for (int i=0; i<31; i++) {
       for (int j=0; j<28; j++) {
           this->square[i][j] = new Square(this, i, j);
       }
   }
}

PacmanGame* GameWindow::get_pacman_game() const {
   return this->pacman_game;
}

Square* GameWindow::get_square(int row, int col) const {
   return this->square[row][col];
}

void GameWindow::set_square(int row, int col, char i) {
   this->square[row][col]->set_piece(i);
}

void GameWindow::keyPressEvent(QKeyEvent * event){
    if (event->key() == Qt::Key_W){
        pacman_game->get_pacman()->update_direction(Dir::UP);
        event->accept();
    } else if (event->key() == Qt::Key_S){
        pacman_game->get_pacman()->update_direction(Dir::DOWN);
        event->accept();
    } else if (event->key() == Qt::Key_A){
        pacman_game->get_pacman()->update_direction(Dir::LEFT);
        event->accept();
    } else if (event->key() == Qt::Key_D){
        pacman_game->get_pacman()->update_direction(Dir::RIGHT);
        event->accept();
    }
}

void GameWindow::set_lcd(int type, int value)
{
    QLCDNumber *lcds[2] = {ui -> highscore_display, ui -> score_display};
    lcds[type] -> display(value);
    lcds[type] -> show();
}

void GameWindow::set_lives()
{
    int lives = pacman_game->get_pacman()->get_lives();
    QPixmap img2(":/resources/img/pac_man_hed.jpg");
    QLabel* liveWidgets[5] = {ui->obj_1,ui->obj_2,ui->obj_3,ui->obj_4,ui->obj_5};
    int i =0;
    for (; i<lives; ++i){
        liveWidgets[i]->setPixmap(img2.scaled(32,32,Qt::KeepAspectRatio));
    }
    for (; i<5; ++i){
        liveWidgets[i]->clear();
    }
}

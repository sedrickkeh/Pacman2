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


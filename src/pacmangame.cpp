#include "pacmangame.h"
#include <QTimer>
#include <QMessageBox>
#include <QApplication>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

PacmanGame::PacmanGame() :
    pacman(nullptr),
    ghost1(nullptr),
    ghost2(nullptr),
    ghost3(nullptr),
    ghost4(nullptr),
    current_score(0),
    level(1)
{
    game_window = new GameWindow(nullptr, this);
    for (int k = 0; k < 31; k ++)
        for (int l = 0; l < 28; l ++)
            board[k][l] = nullptr;

    load_map();
    update_map();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh_frame()));
    timer -> start(20);
}

PacmanGame::~PacmanGame(){}

void PacmanGame::startGraphicUI() {
    game_window->show();
}

GameWindow* PacmanGame::get_game_window() const {
    return game_window;
}

Pacman* PacmanGame::get_pacman() const{
    return pacman;
}

int PacmanGame::get_score() const{
    return current_score;
}

void PacmanGame::load_map() {
    QFile file(":/resources/maps/pacman_map.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    int rownum = 30;
    while (!file.atEnd()) {
        QString line = file.readLine();
        for (int k = 0; k < line.size()-1; k ++) {
            if (line[k] == 'W') board[rownum][k] = new Wall(rownum, k, &board);
            else if (line[k] == 'V') board[rownum][k] = new Ghostwall(rownum, k, &board);
            else if (line[k] == 'P') {
                pacman = new Pacman(rownum, k, &board);
                board[rownum][k] = pacman;
            }
            else if (line[k] == 'G') {
                if (ghost1 == nullptr) {
                    ghost1 = new Ghost(rownum, k, &board, 20, nullptr, pacman, CHASE);
                    board[rownum][k] = ghost1;
                }
                else if (ghost2 == nullptr) {
                    ghost2 = new Ghost(rownum, k, &board, 40, nullptr, pacman, AMBUSH);
                    board[rownum][k] = ghost2;
                }
                else if (ghost3 == nullptr) {
                    ghost3 = new Ghost(rownum, k, &board, 60, nullptr, pacman, RANDOM);
                    board[rownum][k] = ghost3;
                }
                else if (ghost4 == nullptr) {
                    ghost4 = new Ghost(rownum, k, &board, 80, nullptr, pacman, RANDOM);
                    board[rownum][k] = ghost4;
                }
            }
            else if (line[k] == 'F') board[rownum][k] = new Food(rownum, k, &board);
            else if (line[k] == 'U') board[rownum][k] = new Superpower(rownum, k, &board);
        }
        --rownum;
    }
}

void PacmanGame::update_map() {
    for (int k = 0; k < 31; k ++) {
        for (int l = 0; l < 28; l ++) {
            if (board[k][l] != nullptr)
                init_block(k, l, board[k][l]->getImage());
            else
                init_block(k, l, 'S');
        }
    }
}

void PacmanGame::init_block(int row, int col, char c) {
    game_window->set_square(row, col, c);
}

void PacmanGame::move_pacman(int r, int c) {
    Dir dir = pacman->get_direction();

    if (dir == Dir::NONE) return;

    int row = r; int col = c;
    if (dir == Dir::DOWN) pacman->move(row-1, col);
    else if (dir == Dir::UP) pacman->move(row+1, col);
    else if (dir == Dir::LEFT) pacman->move(row, col-1);
    else if (dir == Dir::RIGHT) pacman->move(row, col+1);

    update_ghost_scores();
    pacman->update_superpower();
    if (pacman->just_eaten_superpower()) gain_power();
    else if (pacman->just_lost_superpower()) lose_power();
}

void PacmanGame::move_ghost(int r, int c, Ghost* g) {
    if (g->get_time_in_box() > 0) {
        g->reduce_time_in_box();
        return;
    }

    Dir direction = g->get_next_move();

    if (direction == DOWN) {
        g->move(r-1, c);
        g->set_direction(DOWN);
    }
    else if (direction == UP) {
        g->move(r+1,c);
        g->set_direction(UP);
    }
    else if (direction == RIGHT) {
        g->move(r, c+1);
        g->set_direction(RIGHT);
    }
    else if (direction == LEFT) {
        g->move(r,c-1);
        g->set_direction(LEFT);
    }
}

void PacmanGame::gain_power() {
    ghost1->set_eatmode(true);
    ghost2->set_eatmode(true);
    ghost3->set_eatmode(true);
    ghost4->set_eatmode(true);
    pacman->set_gain();
}

void PacmanGame::lose_power() {
    ghost1->set_eatmode(false);
    ghost1->reset_points();
    ghost2->set_eatmode(false);
    ghost2->reset_points();
    ghost3->set_eatmode(false);
    ghost3->reset_points();
    ghost4->set_eatmode(false);
    ghost4->reset_points();
    pacman->set_lose();
}

void PacmanGame::update_ghost_scores() {
    if (pacman->get_has_eaten_ghost()) {
        ghost1->update_points();
        ghost2->update_points();
        ghost3->update_points();
        ghost4->update_points();
        pacman->not_eat_ghost();
    }
}

void PacmanGame::reset_ghosts() {
    ghost1->move(17, 15);
    ghost1->move(15, 15);
    ghost1->move(17, 12);
    ghost1->move(15, 12);
    ghost1->set_eatmode(false);
    ghost1->set_time_in_box(20);

    ghost2->move(17, 15);
    ghost2->move(15, 15);
    ghost2->move(17, 12);
    ghost2->move(15, 12);
    ghost2->set_eatmode(false);
    ghost2->set_time_in_box(40);

    ghost3->move(17, 15);
    ghost3->move(15, 15);
    ghost3->move(17, 12);
    ghost3->move(15, 12);
    ghost3->set_eatmode(false);
    ghost3->set_time_in_box(60);

    ghost4->move(17, 15);
    ghost4->move(15, 15);
    ghost4->move(17, 12);
    ghost4->move(15, 12);
    ghost4->set_eatmode(false);
    ghost4->set_time_in_box(80);
}

void PacmanGame::update_score() {
    if (pacman->get_points_to_add() == -1) {
        pacman->not_eat_piece();
        return;
    }
    else {
        current_score += pacman->get_points_to_add();
        game_window->set_lcd(1, current_score);
        pacman->not_eat_piece();
    }
}

void PacmanGame::update_lives() {
    game_window->set_lives();
}

void PacmanGame::complete_level() {
    if (is_level_finished() == false) return;
    else {
        QMessageBox::information(nullptr, "Congratulations!", "Level complete");
        game_window->close();
        timer->stop();
    }
}

bool PacmanGame::is_level_finished() {
    for (int k = 0; k < 31; k ++) {
        for (int l = 0; l < 28; l ++) {
            if (board[k][l] != nullptr && (board[k][l] -> getImage() == 'F' || board[k][l] -> getImage() == 'S')) return false;
        }
    }

    if (ghost1->get_prev() != nullptr && (ghost1->get_prev()->getImage() == 'F' || ghost1->get_prev()->getImage() == 'S')) return false;
    if (ghost2->get_prev() != nullptr && (ghost2->get_prev()->getImage() == 'F' || ghost2->get_prev()->getImage() == 'S')) return false;
    if (ghost3->get_prev() != nullptr && (ghost3->get_prev()->getImage() == 'F' || ghost3->get_prev()->getImage() == 'S')) return false;
    if (ghost4->get_prev() != nullptr && (ghost4->get_prev()->getImage() == 'F' || ghost4->get_prev()->getImage() == 'S')) return false;

    return true;
}

void PacmanGame::game_over() {
    if (pacman->get_lives() == 0) {
        QMessageBox::information(nullptr, "Game over!", "Game over!");
        game_window->close();
        timer->stop();
    }
}

void PacmanGame::refresh_frame() {
    move_ghost(ghost1->getRow(), ghost1->getCol(), ghost1);
    move_ghost(ghost2->getRow(), ghost2->getCol(), ghost2);
    move_ghost(ghost3->getRow(), ghost3->getCol(), ghost3);
    move_ghost(ghost4->getRow(), ghost4->getCol(), ghost4);
    move_pacman(pacman->getRow(), pacman->getCol());

    update_score();
    update_lives();

    if (pacman->get_has_encountered_ghost()) reset_ghosts();

    update_map();
    complete_level();
    game_over();
}

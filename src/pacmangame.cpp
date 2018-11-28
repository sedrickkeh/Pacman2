#include "pacmangame.h"
#include <QTimer>
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
    for (int k = 0; k < 31; k ++) for (int l = 0; l < 28; l ++) board[k][l] = nullptr;
    load_map();
    update_map();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh_frame()));
    timer -> start(20);
}

PacmanGame::~PacmanGame(){}

void PacmanGame::load_map() {
    QFile file(":/resources/maps/pacman_map.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    int rownum = 30;
    while (!file.atEnd()) {
        QString line = file.readLine();
        for (int k = 0; k < line.size()-1; k ++) {
            if (line[k] == 'W') board[rownum][k] = new Wall(rownum, k, &board);
            else if (line[k] == 'P') {
                pacman = new Pacman(rownum, k, &board);
                board[rownum][k] = pacman;
            }
            else if (line[k] == 'G') {
                if (ghost1 == nullptr) {
                    ghost1 = new Ghost(rownum, k, &board, 20, nullptr);
                    board[rownum][k] = ghost1;
                }
                else if (ghost2 == nullptr) {
                    ghost2 = new Ghost(rownum, k, &board, 40, nullptr);
                    board[rownum][k] = ghost2;
                }
                else if (ghost3 == nullptr) {
                    ghost3 = new Ghost(rownum, k, &board, 60, nullptr);
                    board[rownum][k] = ghost3;
                }
                else if (ghost4 == nullptr) {
                    ghost4 = new Ghost(rownum, k, &board, 80, nullptr);
                    board[rownum][k] = ghost4;
                }
            }
            else if (line[k] == 'F') board[rownum][k] = new Food(rownum, k, &board);
            else if (line[k] == 'U') board[rownum][k] = new Superpower(rownum, k, &board);
        }
        rownum--;
    }
}

void PacmanGame::init_block(int row, int col, char c) {
    game_window->set_square(row, col, c);
}

void PacmanGame::startGraphicUI() {
    game_window->show();
}

void PacmanGame::refresh_frame() {
    move_ghost(ghost1->getRow(), ghost1->getCol(), ghost1);
    move_ghost(ghost2->getRow(), ghost2->getCol(), ghost2);
    move_ghost(ghost3->getRow(), ghost3->getCol(), ghost3);
    move_ghost(ghost4->getRow(), ghost4->getCol(), ghost4);
    move_pacman(pacman->getRow(), pacman->getCol());
    update_score();
    update_map();
    game_over();
    complete_level();
}

void PacmanGame::move_pacman(int r, int c) {
    Dir dir = pacman->get_direction();
    int row = r; int col = c;
    if (dir == Dir::DOWN) pacman->move(row-1, col);
    else if (dir == Dir::UP) pacman->move(row+1, col);
    else if (dir == Dir::LEFT) pacman->move(row, col-1);
    else if (dir == Dir::RIGHT) pacman->move(row, col+1);
    pacman->update_superpower();
    if (pacman->just_eaten_superpower()) gain_power();
    else if (pacman->just_lost_superpower()) lose_power();
}

void PacmanGame::move_ghost(int r, int c, Ghost* g) {
    if (g->get_time_in_box() > 0) {
        g->reduce_time_in_box();
        return;
    }
    int rv = std::rand();
    if (rv % 4 == 0) g->move(r-1, c);
    else if (rv % 4 == 1) g->move(r+1,c);
    else if (rv%4 == 2) g->move(r, c+1);
    else g->move(r,c-1);
}

void PacmanGame::gain_power() {
    set_weak(ghost1);
    set_weak(ghost2);
    set_weak(ghost3);
    set_weak(ghost4);
    pacman->set_gain();
}

void PacmanGame::lose_power() {
    set_unweak(ghost1);
    set_unweak(ghost2);
    set_unweak(ghost3);
    set_unweak(ghost4);
    pacman->set_lose();
}

void PacmanGame::set_weak(Ghost* g) {
    //if (g->get_time_in_box() > 0) return;
    EatGhost* temp = new EatGhost(g->getRow(), g->getCol(), &board, 0, g->prev);
    g = temp;
}

void PacmanGame::set_unweak(Ghost* g) {
    Ghost* temp = new Ghost(g->getRow(), g->getCol(), &board, 0, g->prev);
    g = temp;
}

void PacmanGame::update_map() {
    for (int k = 0; k < 31; k ++)
        for (int l = 0; l < 28; l ++) {
            if (board[k][l] != nullptr) init_block(k, l, board[k][l]->getImage());
            else init_block(k, l, 'S');
        }
}

void PacmanGame::update_score() {
    if (pacman->get_points_to_add() == -1) {
        pacman->not_eat_piece();
        return;
    }
    else {
        current_score += pacman->get_points_to_add();
        pacman->not_eat_piece();
    }
}

void PacmanGame::complete_level() {
    if (is_level_finished() == false) return;
    else std::cout << "level complete" << std::endl;
}

bool PacmanGame::is_level_finished() {
    for (int k = 0; k < 31; k ++)
        for (int l = 0; l < 28; l ++) {
            if (board[k][l] != nullptr && (board[k][l] -> getImage() == 'F' || board[k][l] -> getImage() == 'S')) return false;
        }
    if (ghost1 -> prev != nullptr && (ghost1->prev->getImage() == 'F' || ghost1->prev->getImage() == 'F')) return false;
    if (ghost2 -> prev != nullptr && (ghost2->prev->getImage() == 'F' || ghost2->prev->getImage() == 'F')) return false;
    if (ghost3 -> prev != nullptr && (ghost3->prev->getImage() == 'F' || ghost3->prev->getImage() == 'F')) return false;
    if (ghost4 -> prev != nullptr && (ghost4->prev->getImage() == 'F' || ghost4->prev->getImage() == 'F')) return false;
    return true;
}

void PacmanGame::game_over() {
    if (pacman->get_lives() == 0) std::cout << "game over" << std::endl;
}

GameWindow* PacmanGame::get_game_window() const {return game_window;}

Pacman* PacmanGame::get_pacman(){
    return pacman;
}

#include "mapmaker.h"
#include <iostream>
using namespace std;

MapMaker::MapMaker() {
    makerwindow = new Makerwindow(nullptr, this);
    for (int k = 0; k < 31; k ++) for (int l = 0; l < 28; l ++) board[k][l] = nullptr;
}

void MapMaker::startGraphicUI() {
    makerwindow->show();
    for (int k = 0; k < 31; k ++) for (int l = 0; l < 28; l ++)
            connect(makerwindow->get_square(k, l), &Square::clicked_with_pos, this, &MapMaker::process_user_input);
}

Makerwindow* MapMaker::get_maker_window() const {
    return makerwindow;
}

void MapMaker::init_block(int row, int col, char c) {
    makerwindow->set_square(row, col, c);
}

void MapMaker::process_user_input(int row, int col) {
    char c = makerwindow->get_square_choice();
    delete board[row][col];
    if (c == 'P') board[row][col] = new Pacman(row, col, &board);
    else if (c == 'G') board[row][col] = new Ghost(row, col, &board, 0, nullptr, Movement::AMBUSH);
    else if (c == 'W') board[row][col] = new Wall(row, col, &board);
    else if (c == 'F') board[row][col] = new Food(row, col, &board);
    else if (c == 'U') board[row][col] = new Superpower(row, col, &board);
    else board[row][col] = nullptr;
    init_block(row, col, c);
}

Character* MapMaker::getchar(int row, int col) {
    return board[row][col];
}

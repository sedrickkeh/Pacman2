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
    char c = 'P';
    init_block(row, col, c);
}

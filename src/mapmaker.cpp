#include "mapmaker.h"
#include "QMessageBox"
#include "QString"
#include "QStandardPaths"
#include <iostream>
using namespace std;

const QString MapMaker::map_dir =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/pacman";
const QString MapMaker::map_path =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/pacman/mapmaker.txt";

MapMaker::MapMaker() {
    makerwindow = new Makerwindow(nullptr, this);
    for (int k = 0; k < 31; k ++) for (int l = 0; l < 28; l ++) board[k][l] = nullptr;
    load_map();
    QMessageBox::information(nullptr, "Welcome!", "This is map maker mode. You can click on a block in the game board and replace it with a block of your choice. Click the SAVE button when you are done.");
}

void MapMaker::startGraphicUI() {
    makerwindow->show();
    for (int k = 0; k < 31; k ++) for (int l = 0; l < 28; l ++)
            connect(makerwindow->get_square(k, l), &Square::clicked_with_pos, this, &MapMaker::process_user_input);
}

void MapMaker::load_map() {

    QFile file(map_path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::information(nullptr, "ERROR", "Unable to read record file.");
    else {
        int rownum = 30;
        while (!file.atEnd()) {
            QString line = file.readLine();
            for (int k = 0; k < line.size()-1; k ++) {
                if (line[k] == 'W' || line[k] == 'V') {
                    board[rownum][k] = new Wall(rownum, k, &board);
                    init_block(rownum, k, 'W');
                }
                else if (line[k] == 'P') {
                    board[rownum][k] = new Pacman(nullptr, rownum, k, &board, Mode::CLASSIC);
                    init_block(rownum, k, 'P');
                }
                else if (line[k] == 'G') {
                    board[rownum][k] = new Ghost(1, rownum, k, &board, 20, nullptr,  Mode::CLASSIC, Movement::CHASE);
                    init_block(rownum, k, 'C');
                }
                else if (line[k] == 'F') {
                    board[rownum][k] = new Food(rownum, k, &board);
                    init_block(rownum, k, 'F');
                }
                else if (line[k] == 'U') {
                    board[rownum][k] = new Superpower(rownum, k, &board);
                    init_block(rownum, k, 'U');
                }
                else {
                    board[rownum][k] = nullptr;
                    init_block(rownum, k, 'S');
                }
            }
            --rownum;
        }
    }
    file.close();
}

Makerwindow* MapMaker::get_maker_window() const {
    return makerwindow;
}

void MapMaker::init_block(int row, int col, char c) {
    makerwindow->set_square(row, col, c);
}

void MapMaker::process_user_input(int row, int col) {
    char c = makerwindow->get_square_choice();
    if (c == 'N') return;
    delete board[row][col];
    if (c == 'P') board[row][col] = new Pacman(nullptr, row, col, &board, Mode::CLASSIC);
    else if (c == 'C') board[row][col] = new Ghost(1, row, col, &board, 0, nullptr, Mode::CLASSIC, Movement::CHASE);
    else if (c == 'W') board[row][col] = new Wall(row, col, &board);
    else if (c == 'F') board[row][col] = new Food(row, col, &board);
    else if (c == 'U') board[row][col] = new Superpower(row, col, &board);
    else board[row][col] = nullptr;
    init_block(row, col, c);
}

Character* MapMaker::getchar(int row, int col) {
    return board[row][col];
}

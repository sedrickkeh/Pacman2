#include "makerwindow.h"
#include "ui_makerwindow.h"
#include "square.h"
#include "mapmaker.h"
#include "choicedialog.h"

Makerwindow::Makerwindow(QWidget *parent, MapMaker* _mapmaker) :
    QWidget(parent),
    ui(new Ui::Makerwindow),
    mapmaker(_mapmaker)
{
    ui->setupUi(this);
    this->make_grid();
}

Makerwindow::~Makerwindow()
{
    delete ui;
}

MapMaker* Makerwindow::get_mapmaker() const {
    return mapmaker;
}

Square* Makerwindow::get_square(int row, int col) const {
    return this->square[row][col];
}

void Makerwindow::set_square(int row, int col, char i) {
   this->square[row][col]->set_piece(i);
}

char Makerwindow::get_square_choice() {
    ChoiceDialog d(this);
    char result;
    while((result = d.get_choice()) == ' ');
    return result;
}

void Makerwindow::make_grid() {
    for (int i=0; i<31; ++i) {
        for (int j=0; j<28; ++j) {
            this->square[i][j] = new Square(this, i, j);
        }
    }
}

void Makerwindow::save_button_clicked_handler() {
    char mapchars[31][28];
    for (int k = 0; k < 31; k ++) for (int l = 0; l < 28; l ++) {
        if (mapmaker->getchar(k, l) == nullptr) mapchars[k][l] = 'S';
        else if (mapmaker->getchar(k, l)->getImage() == 'P') mapchars[k][l] = 'P';
        else if (mapmaker->getchar(k, l)->getImage() == 'W') mapchars[k][l] = 'W';
        else if (mapmaker->getchar(k, l)->getImage() == 'U') mapchars[k][l] = 'U';
        else if (mapmaker->getchar(k, l)->getImage() == 'F') mapchars[k][l] = 'F';
        else if (mapmaker->getchar(k, l)->getImage() == 'G' ||
                 mapmaker->getchar(k, l)->getImage() == 'C' ||
                 mapmaker->getchar(k, l)->getImage() == 'A' ||
                 mapmaker->getchar(k, l)->getImage() == 'R') mapchars[k][l] = 'G';
        else mapchars[k][l] = 'S';
    }
}

void Makerwindow::closeEvent(QCloseEvent *event) {
   emit closed();
}

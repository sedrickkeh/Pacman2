#include "makerwindow.h"
#include "ui_makerwindow.h"
#include "square.h"
#include "mapmaker.h"

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

void Makerwindow::make_grid() {
    for (int i=0; i<31; ++i) {
        for (int j=0; j<28; ++j) {
            this->square[i][j] = new Square(this, i, j);
        }
    }
}

void Makerwindow::closeEvent(QCloseEvent *event) {
   emit closed();
}

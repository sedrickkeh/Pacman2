#include "makerwindow.h"
#include "ui_makerwindow.h"
#include "square.h"
#include "mapmaker.h"
#include "choicedialog.h"
#include "QMessageBox"

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
    int numpac = 0; int numghost = 0;
    for (int k = 0; k < 31; k ++) for (int l = 0; l < 28; l ++)
        if (mapmaker->getchar(k, l) != nullptr) {
            if (mapmaker ->getchar(k, l) -> getImage() == 'P') numpac++;
            if (mapmaker->getchar(k, l) ->getImage() == 'G' ||
                mapmaker->getchar(k, l) ->getImage() == 'C' ||
                mapmaker->getchar(k, l) ->getImage() == 'A' ||
                mapmaker->getchar(k, l) ->getImage() == 'R') numghost++;
        }
    if (numpac == 0 && numghost < 4) {
        while((result = d.get_choice()) == ' ');
        return result;
    }
    else if (numpac >= 1 && numghost <= 3) {
        while((result = d.get_choice()) == ' ');
        if (result != 'P') return result;
        else {
            QMessageBox::information(nullptr, "Error!", "You can only have one pacman. Plese select another");
            return get_square_choice();
        }
    }
    else if (numghost >= 4 && numpac == 0) {
        while((result = d.get_choice()) == ' ');
        if (result != 'C') return result;
        else {
            QMessageBox::information(nullptr, "Error!", "You can only have four ghosts. Plese select another");
            return get_square_choice();
        }
    }
    else {
        while((result = d.get_choice()) == ' ');
        if (result != 'P' && result != 'C') return result;
        else if (result == 'P') {
            QMessageBox::information(nullptr, "Error!", "You can only have one pacman. Plese select another");
            return get_square_choice();
        }
        else if (result == 'C') {
            QMessageBox::information(nullptr, "Error!", "You can only have four ghosts. Plese select another");
            return get_square_choice();
        }
    }
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
    int numpac = 0; int numghost = 0;
    for (int k = 0; k < 31; k ++) for (int l = 0; l < 28; l ++) {
        if (mapmaker->getchar(k, l) == nullptr) mapchars[k][l] = 'S';
        else if (mapmaker->getchar(k, l)->getImage() == 'P') {
            mapchars[k][l] = 'P'; numpac++;
        }
        else if (mapmaker->getchar(k, l)->getImage() == 'W') mapchars[k][l] = 'W';
        else if (mapmaker->getchar(k, l)->getImage() == 'U') mapchars[k][l] = 'U';
        else if (mapmaker->getchar(k, l)->getImage() == 'F') mapchars[k][l] = 'F';
        else if (mapmaker->getchar(k, l)->getImage() == 'G' ||
                 mapmaker->getchar(k, l)->getImage() == 'C' ||
                 mapmaker->getchar(k, l)->getImage() == 'A' ||
                 mapmaker->getchar(k, l)->getImage() == 'R') {
            mapchars[k][l] = 'G'; numghost++;
        }
        else mapchars[k][l] = 'S';
    }
    if (numpac != 1) {
        QMessageBox::information(nullptr, "Error!", "You need exactly one pacman.");
        return;
    }
    if (numghost != 4) {
        QMessageBox::information(nullptr, "Error!", "You need exactly four ghosts.");
        return;
    }
}

void Makerwindow::closeEvent(QCloseEvent *event) {
   emit closed();
}

#include <sstream>

#include "square.h"
#include <string>
#include <QPushButton>
#include <QString>

using std::string;
using std::ostringstream;

Square::Square(QWidget* parent, int _row, int _col) :
    QPushButton(parent),
    row(_row),
    col(_col),
    piece(' ')
{
    this->render();
    connect(this, &Square::clicked, this, &Square::clicked_handler);
}

string Square::get_path() {
    return ":/resources/img/pac_man_hed.jpg";
}

void Square::set_image(string path) {
    setStyleSheet(QString::fromStdString("border-image: url(\"" + path + "\");"));
}

void Square::render() {
    setGeometry(QRect(OFFSET_X + SQUARE_WIDTH * this->col, OFFSET_Y + SQUARE_HEIGHT * (31-this->row), SQUARE_WIDTH, SQUARE_HEIGHT));
    setVisible(true);
    setFlat(true);
    setAutoFillBackground(true);
    setText("");
    setStyle("border-color", "black");
    setStyle("border-width", "0px");
    setStyle("border-style", "solid");
    if ((this->row + this->col) % 2 == 0)
        setStyle("background-color", "gray");
    else
        setStyle("background-color", "white");
    applyStyle();
}

void Square::setStyle(string key, string value) {
    this->style[key] = value;
}

void Square::applyStyle() {
    ostringstream s;
    for (StyleMap::iterator i=this->style.begin(); i!=this->style.end(); i++) {
        s << i->first << ":" << i->second << ";";
    }
    string style_string = s.str();
    setStyleSheet(QString::fromStdString(style_string));
}

void Square::clicked_handler() {
    emit clicked_with_pos(this->row, this->col);
}

void Square::set_piece(char i) {
    this->piece = i;
    if (i == 'P') setStyle("background-color", "yellow");
    else if (i == 'C') setStyle("background-color", "red");
    else if (i == 'A') setStyle("background-color", "pink");
    else if (i == 'R') setStyle("background-color", "orange");
    else if (i == 'F') setStyle("background-color", "blue");
    else if (i == 'U') setStyle("background-color", "green");
    else if (i == 'E') setStyle("background-color", "purple");
    else if (i == 'W') setStyle("background-color", "black");
    else setStyle("background-color", "white");
    applyStyle();
}

char Square::get_piece() const {
    return this->piece;
}

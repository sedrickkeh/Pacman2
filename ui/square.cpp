#include "square.h"

#include <sstream>
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

void Square::set_piece(char i) {
    //set the correct graphics for each piece
    this->piece = i;
    if (i == 'P') setStyle("background-color", "yellow");
    else if (i == 'C') setStyle("background-color", "red");
    else if (i == 'A') setStyle("background-color", "pink");
    else if (i == 'R') setStyle("background-color", "orange");
    else if (i == 'F') setStyle("background-color", "blue");
    else if (i == 'U') setStyle("background-color", "rgb(50, 205, 50)");
    else if (i == 'E') setStyle("background-color", "purple");
    else if (i == 'W') setStyle("background-color", "black");
    else if (i == 'V') setStyle("background-color", "gray");
    else setStyle("background-color", "white");
    applyStyle();
}

char Square::get_piece() const {
    return this->piece;
}

void Square::clicked_handler() {
    if (this->row == 0 || this->row == 30 || this->col == 0 || this->col == 27) return;
    emit clicked_with_pos(this->row, this->col);
}

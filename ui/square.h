#ifndef SQUARE_H
#define SQUARE_H

#include <QPushButton>
#include <QString>
#include <QWidget>
#include <string>

using std::string;
typedef std::map<std::string, std::string> StyleMap;

class Square : public QPushButton
{
    Q_OBJECT
public:
    Square(QWidget *parent = nullptr, int _row = 0, int _col = 0);
    void setStyle(std::string key, std::string value);
    void applyStyle();
    void set_piece(char i);
    char get_piece() const;

    string get_path();
    void set_image(string path);

private:
    void render();

    int row, col;
    StyleMap style;
    char piece;
    static const int OFFSET_X = 0;
    static const int OFFSET_Y = 0;
    static const int SQUARE_WIDTH = 20;
    static const int SQUARE_HEIGHT = 20;

signals:
    void clicked_with_pos(int row, int col);

private slots:
    void clicked_handler();

};

#endif // SQUARE_H

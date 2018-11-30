#ifndef MAKERWINDOW_H
#define MAKERWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QPixmap>

class Square;
class MapMaker;

namespace Ui {
class Makerwindow;
}

class Makerwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Makerwindow(QWidget *parent = nullptr, MapMaker* _mapmaker = nullptr);
    ~Makerwindow();

    MapMaker* get_mapmaker() const;
    Square* get_square(int row, int col) const;
    void set_square(int row, int col, char i);
    char get_square_choice();

private:
    Ui::Makerwindow *ui;
    Square* square[31][28];
    MapMaker* mapmaker;

    void closeEvent(QCloseEvent *event);
    void make_grid();

private slots:
    void save_button_clicked_handler();

signals:
    void closed();
};

#endif // MAKERWINDOW_H

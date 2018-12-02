#ifndef HIGHSCOREWINDOW_H
#define HIGHSCOREWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QPixmap>
#include <QString>

class RecordManager;

namespace Ui {
class Highscorewindow;
}

class Highscorewindow: public QWidget
{
    Q_OBJECT

public:
    explicit Highscorewindow(QWidget *parent =nullptr, RecordManager* _records=nullptr);
    ~Highscorewindow();

private:
    RecordManager *rm;
    Ui::Highscorewindow *ui;
    void closeEvent(QCloseEvent *event);
    void set_lcd(int[], int[]);
    void set_names(QString[], QString[]);

signals:
    void closed();

};

#endif // HIGHSCOREWINDOW_H

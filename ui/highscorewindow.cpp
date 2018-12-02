#include "highscorewindow.h"
#include "ui_highscorewindow.h"

#include "recordmanager.h"

Highscorewindow::Highscorewindow(QWidget *parent, RecordManager *_rm) :
    QWidget(parent),
    rm(_rm),
    ui(new Ui::Highscorewindow)
{
    //load pictures for high score
    QPixmap high(":/resources/img/highscores.png");
    QPixmap classic(":/resources/img/classical.png");
    QPixmap reverse(":/resources/img/reverse.png");
    QPixmap high_head(":/resources/img/highscore_header.jpg");
    QPixmap rank(":/resources/img/ranking.jpg");

    //use the pictures for the high score
    ui->setupUi(this);
    ui->highscore->setPixmap(high.scaled(381,51));
    ui->classic->setPixmap(classic.scaled(211,41));
    ui->reverse->setPixmap(reverse.scaled(211,41));
    ui->header_1->setPixmap(high_head.scaled(441,31));
    ui->header_2->setPixmap(high_head.scaled(441,31));
    ui->ranking_1->setPixmap(rank.scaled(51,221));
    ui->ranking_2->setPixmap(rank.scaled(51,221));

    //show the scores and names
    set_lcd(rm->get_classic_scores(),rm->get_reverse_scores());
    set_names(rm->get_classic_names(), rm->get_reverse_names());
}

Highscorewindow::~Highscorewindow()
{
    delete ui;
}

void Highscorewindow::closeEvent(QCloseEvent *event)
{
    emit closed();
}

void Highscorewindow::set_lcd(int classic_scores[], int reverse_scores[])
{
    //show each score in the array for classic and reverse
    QLCDNumber *classic[5] = {ui->classic_1, ui->classic_2, ui->classic_3, ui->classic_4, ui->classic_5};
    for (int i=0; i<5; i++) {
        classic[i] -> display(classic_scores[i]);
        classic[i] ->show();
    }
    QLCDNumber *reverse[5] = {ui->reverse_1, ui->reverse_2, ui->reverse_3, ui->reverse_4, ui->reverse_5};
    for (int i=0; i<5; ++i) {
        reverse[i] -> display(reverse_scores[i]);
        reverse[i] ->show();
    }
}

void Highscorewindow::set_names(QString c_names[], QString r_names[])
{
    //show each name in the array for classic and reverse
    QLabel* classic_names[5] = {ui->classic_6, ui->classic_7, ui->classic_8, ui->classic_9, ui->classic_10};
    QLabel* reverse_names[5] = {ui->reverse_6, ui->reverse_7, ui->reverse_8, ui->reverse_9, ui->reverse_10};
    for (int i=0; i<5; ++i) {
        classic_names[i]->setText(c_names[i]);
        reverse_names[i]->setText(r_names[i]);
    }
}

#include "choicedialog.h"
#include "ui_choicedialog.h"

ChoiceDialog::ChoiceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoiceDialog),
    choice(' ')
{
    ui->setupUi(this);
}

ChoiceDialog::~ChoiceDialog()
{
    delete ui;
}

void ChoiceDialog::on_food_clicked() {
    this->choice = 'F';
    close();
}
void ChoiceDialog::on_empty_clicked() {
    this->choice = 'S';
    close();
}
void ChoiceDialog::on_ghost_clicked() {
    this->choice = 'C';
    close();
}
void ChoiceDialog::on_pacman_clicked() {
    this->choice = 'P';
    close();
}
void ChoiceDialog::on_superpower_clicked() {
    this->choice = 'U';
    close();
}
void ChoiceDialog::on_wall_clicked() {
    this->choice = 'W';
    close();
}

char ChoiceDialog::get_choice() {
    exec();
    return this->choice;
}

#include "modedialog.h"
#include "ui_modedialog.h"

ModeDialog::ModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeDialog),
    choice(' ')
{
    ui->setupUi(this);
}

ModeDialog::~ModeDialog()
{
    delete ui;
}

void ModeDialog::on_classic_clicked() {
    this->choice = 'C';
    close();
}

void ModeDialog::on_mapmaker_clicked() {
    this->choice = 'M';
    close();
}

char ModeDialog::get_choice() {
    exec();
    return this->choice;
}

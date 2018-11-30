#ifndef CHOICEDIALOG_H
#define CHOICEDIALOG_H

#include <QDialog>

namespace Ui {
class ChoiceDialog;
}

class ChoiceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoiceDialog(QWidget *parent = nullptr);
    ~ChoiceDialog();

    char get_choice();

private:
    Ui::ChoiceDialog *ui;
    char choice;

private slots:
    void on_pacman_clicked();
    void on_ghost_clicked();
    void on_wall_clicked();
    void on_food_clicked();
    void on_superpower_clicked();
    void on_empty_clicked();
};

#endif // CHOICEDIALOG_H

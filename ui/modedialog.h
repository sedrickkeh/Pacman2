#ifndef MODEDIALOG_H
#define MODEDIALOG_H

#include <QDialog>

namespace Ui {
class ModeDialog;
}

class ModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModeDialog(QWidget *parent = nullptr);
    ~ModeDialog();
    char get_choice();

private:
    Ui::ModeDialog *ui;
    char choice;

private slots:
    void on_classic_clicked();
    void on_mapmaker_clicked();
};

#endif // MODEDIALOG_H


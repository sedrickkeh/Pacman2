#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStandardPaths>
#include <QMessageBox>

#include "recordmanager.h"

const QString RecordManager::record_dir =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/pacman";
const QString RecordManager::record_path_classic =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/pacman/classic.txt";
const QString RecordManager::record_path_reverse =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/pacman/reverse.txt";

RecordManager::RecordManager()
{
    if (!QDir(record_dir).exists())
        QDir().mkdir(record_dir);
    if (!QFile(record_path_classic).exists()) {
        QFile file(record_path_classic);
        if (!file.open(QFile::WriteOnly | QFile::Text))
            QMessageBox::information(nullptr, "ERROR", "Unable to write newly made record file.");
        else {
            QTextStream out_stream(&file);
            for(int i=0; i<NUM_OF_SCORES; ++i){
                out_stream << "AAA" << "\n";
                out_stream << (NUM_OF_SCORES - i) * 500;
                if (i < NUM_OF_SCORES-1) out_stream << "\n";
            }
        }
        file.close();
    }
    if (!QFile(record_path_reverse).exists()) {
        QFile file(record_path_reverse);
        if (!file.open(QFile::WriteOnly | QFile::Text))
            QMessageBox::information(nullptr, "ERROR", "Unable to write newly made record file.");
        else {
            QTextStream out_stream(&file);
            for(int i=0; i<NUM_OF_SCORES; ++i){
                out_stream << "AAA" << "\n";
                out_stream << (NUM_OF_SCORES - i) * 500;
                if (i < NUM_OF_SCORES-1) out_stream << "\n";
            }
        }
        file.close();
    }

    QFile file1(record_path_classic);
    if (!file1.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::information(nullptr, "ERROR", "Unable to read record file.");
    else {
        for (int i=0; i<NUM_OF_SCORES && !file1.atEnd(); ++i) {
            QString line1 = file1.readLine();
            if(i != NUM_OF_SCORES - 1) line1.chop(1);
            classic_names[i] = line1;

            QString line2 = file1.readLine();
            classic_scores[i] = line2.toInt();
        }
    }
    file1.close();

    QFile file2(record_path_classic);
    if (!file2.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::information(nullptr, "ERROR", "Unable to read record file.");
    else {
        for (int i=0; i<NUM_OF_SCORES && !file2.atEnd(); ++i) {
            QString line1 = file2.readLine();
            if(i != NUM_OF_SCORES - 1) line1.chop(1);
            reverse_names[i] = line1;

            QString line2 = file2.readLine();
            reverse_scores[i] = line2.toInt();
        }
    }
    file2.close();
}

int RecordManager::get_classic_score_at(int rank)
{
    return classic_scores[rank-1];
}

int RecordManager::get_classic_lowest_score()
{
    return classic_scores[NUM_OF_SCORES-1];
}

int RecordManager::get_classic_highest_score()
{
    return classic_scores[0];
}

int RecordManager::get_reverse_score_at(int rank)
{
    return reverse_scores[rank-1];
}

int RecordManager::get_reverse_lowest_score()
{
    return reverse_scores[NUM_OF_SCORES-1];
}

int RecordManager::get_reverse_highest_score()
{
    return reverse_scores[0];
}

int RecordManager::get_num_of_scores()
{
    return NUM_OF_SCORES;
}

void RecordManager::update_classic_record(QString name, int score)
{
    int new_rank = NUM_OF_SCORES;
    while(new_rank > 0 && score > classic_scores[new_rank-1]) --new_rank;
    if (new_rank == NUM_OF_SCORES) return;

    for(int i = NUM_OF_SCORES-1; i < new_rank; --i){
        classic_names[i] = classic_names[i-1];
        classic_scores[i] = classic_scores[i-1];
    }
    classic_names[new_rank] = name;
    classic_scores[new_rank] = score;

    QFile file(record_path_classic);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        QMessageBox::information(nullptr, "ERROR", "Unable to write record file.");
    else {
        QTextStream out_stream(&file);
        for(int i=0; i<NUM_OF_SCORES; ++i){
            out_stream << classic_names[i] << "\n";
            out_stream << classic_scores[i];
            if (i < NUM_OF_SCORES-1) out_stream << "\n";
        }
    }
    file.close();
}

void RecordManager::update_reverse_record(QString name, int score)
{
    int new_rank = NUM_OF_SCORES;
    while(new_rank > 0 && score > reverse_scores[new_rank-1]) --new_rank;
    if (new_rank == NUM_OF_SCORES) return;

    for(int i = NUM_OF_SCORES-1; i < new_rank; --i){
        reverse_names[i] = reverse_names[i-1];
        reverse_scores[i] = reverse_scores[i-1];
    }
    reverse_names[new_rank] = name;
    reverse_scores[new_rank] = score;

    QFile file(record_path_reverse);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        QMessageBox::information(nullptr, "ERROR", "Unable to write record file.");
    else {
        QTextStream out_stream(&file);
        for(int i=0; i<NUM_OF_SCORES; ++i){
            out_stream << reverse_names[i] << "\n";
            out_stream << reverse_scores[i];
            if (i < NUM_OF_SCORES-1) out_stream << "\n";
        }
    }
    file.close();
}

int* RecordManager::get_classic_scores(){
    return classic_scores;
};
int* RecordManager::get_reverse_scores(){
    return reverse_scores;
};

QString* RecordManager::get_classic_names(){
    return classic_names;
};

QString* RecordManager::get_reverse_names(){
    return reverse_names;
};

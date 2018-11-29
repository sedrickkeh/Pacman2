#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStandardPaths>
#include <QMessageBox>

#include "recordmanager.h"

const QString RecordManager::record_dir =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/pacman";
const QString RecordManager::record_path =
    QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/pacman/record.txt";

RecordManager::RecordManager()
{
    if (!QDir(record_dir).exists())
        QDir().mkdir(record_dir);
    if (!QFile(record_path).exists()) {
        QFile file(record_path);
        if (!file.open(QFile::WriteOnly | QFile::Text))
            QMessageBox::information(nullptr, "ERROR", "Unable to write newly made record file.");
        else {
            QTextStream out_stream(&file);
            for(int i=0; i<NUM_OF_SCORES; ++i){
                out_stream << "AAA" << "\n";
                out_stream << i * 1000;
                if (i < NUM_OF_SCORES-1) out_stream << "\n";
            }
        }
        file.close();
    }

    QFile file(record_path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        QMessageBox::information(nullptr, "ERROR", "Unable to read record file.");
    else {
        for (int i=0; i<NUM_OF_SCORES && !file.atEnd(); ++i) {
            QString line1 = file.readLine();
            names[i] = line1;

            QString line2 = file.readLine();
            scores[i] = line2.toInt();
        }
    }
    file.close();
}

int RecordManager::get_score_at(int rank)
{
    return scores[rank-1];
}

int RecordManager::get_num_of_scores()
{
    return NUM_OF_SCORES;
}

void RecordManager::update_record(QString name, int score)
{
    int new_rank = NUM_OF_SCORES;
    while(new_rank > 0 && score < scores[new_rank-1]) --new_rank;
    if (new_rank == NUM_OF_SCORES) return;

    for(int i = NUM_OF_SCORES-1; i < new_rank; --i){
        scores[i] = scores[i-1];
        names[i] = names[i-1];
    }
    scores[new_rank] = score;
    names[new_rank] = name;

    QFile file(record_path);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        QMessageBox::information(nullptr, "ERROR", "Unable to write record file.");
    else {
        QTextStream out_stream(&file);
        for(int i=0; i<NUM_OF_SCORES; ++i){
            out_stream << names[i] << "\n";
            out_stream << scores[i];
            if (i < NUM_OF_SCORES-1) out_stream << "\n";
        }
    }
    file.close();
}

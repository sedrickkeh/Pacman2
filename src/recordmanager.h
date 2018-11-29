#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <QString>

class RecordManager
{
 public:
    RecordManager();
    int get_score_at(int rank);
    int get_num_of_scores();
    void update_record(QString name, int score);

 private:
    static const int NUM_OF_SCORES = 5;
    static const QString record_dir;
    static const QString record_path;
    int scores[NUM_OF_SCORES + 1];
    QString names[NUM_OF_SCORES + 1];
};

#endif // RECORDMANAGER_H

#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <QString>

class RecordManager
{
 public:
    RecordManager();
    int get_classic_lowest_score() const;
    int get_classic_highest_score() const;
    int get_reverse_lowest_score() const;
    int get_reverse_highest_score() const;
    int get_num_of_scores() const;
    void update_classic_record(QString name, int score);
    void update_reverse_record(QString name, int score);
    int* get_classic_scores();
    int* get_reverse_scores();
    QString* get_classic_names();
    QString* get_reverse_names();

 private:
    static const int NUM_OF_SCORES = 5;
    static const QString record_dir;
    static const QString record_path_classic;
    static const QString record_path_reverse;
    int classic_scores[NUM_OF_SCORES + 1];
    QString classic_names[NUM_OF_SCORES + 1];
    int reverse_scores[NUM_OF_SCORES + 1];
    QString reverse_names[NUM_OF_SCORES + 1];
};

#endif // RECORDMANAGER_H

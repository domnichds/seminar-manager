#ifndef STUDENTDATA_H
#define STUDENTDATA_H

#include <QString>
#include <QDate>
#include <map>

// Класс для представления данных студента
class StudentData
{
public:
    QString name;  // Имя студента
    std::map<QDate, short> marks;  // Оценки студента по датам

    // Конструктор класса
    StudentData(QString name, const std::vector<QDate>& dates);
};

#endif // STUDENTDATA_H

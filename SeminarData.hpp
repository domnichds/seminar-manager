#ifndef SEMINARDATA_H
#define SEMINARDATA_H

#include <QString>
#include <vector>
#include <QDate>
#include "StudentData.hpp"

// Класс для представления данных семинара
class SeminarData
{
public:
    QString name;  // Имя семинара
    std::vector<QDate> dates;  // Даты семинара
    std::vector<StudentData> students;  // Студенты, участвующие в семинаре

    // Конструктор класса
    SeminarData(QString name);
    SeminarData(QString name, std::vector<QDate> dates, std::vector<StudentData> students);
};

#endif // SEMINARDATA_H

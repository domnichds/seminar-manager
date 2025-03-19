#ifndef SEMINARMANAGER_H
#define SEMINARMANAGER_H

#include <QString>
#include <vector>
#include <QDate>
#include <stdexcept>
#include "SeminarData.hpp"

// Класс для управления данными семинара
class SeminarManager
{
private:
    SeminarData* seminarData;  // Указатель на данные семинара

public:
    // Конструктор класса
    SeminarManager(SeminarData* data);
    // Методы для управления данными семинара
    void changeName(QString new_name);
    void addDate(QDate new_date);
    void deleteDate(QDate old_date);
    void editDate(QDate old_date, QDate new_date);
    void addStudent(QString name);
    void deleteStudent(QString name);
};

#endif // SEMINARMANAGER_H

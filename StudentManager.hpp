#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <QString>
#include <vector>
#include <stdexcept>
#include "StudentData.hpp"

// Класс для управления данными студента
class StudentManager
{
private:
    StudentData* studentData;  // Указатель на данные студента

public:
    // Конструктор класса
    StudentManager(StudentData* data);
    // Метод для изменения имени студента
    void changeName(QString new_name, const std::vector<StudentData>& students);
};

#endif // STUDENTMANAGER_H

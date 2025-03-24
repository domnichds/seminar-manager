#include "SeminarData.hpp"

// Реализация конструктора класса SeminarData
SeminarData::SeminarData(QString name)
{
    this->name = name;  // Инициализация имени семинара
    this->dates = {};  // Инициализация пустого списка дат
    this->students = {};  // Инициализация пустого списка студентов
}

SeminarData::SeminarData(QString name, std::vector<QDate> dates, std::vector<StudentData> students)
{
    this->name = name;
    this->dates = dates;
    this->students = students;
}

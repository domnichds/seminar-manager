#include "SeminarData.hpp"

// Реализация конструктора класса SeminarData
SeminarData::SeminarData(QString name)
{
    this->name = name;  // Инициализация имени семинара
    this->dates = {};  // Инициализация пустого списка дат
    this->students = {};  // Инициализация пустого списка студентов
}

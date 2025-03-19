#include "StudentData.hpp"

// Реализация конструктора класса StudentData
StudentData::StudentData(QString name, const std::vector<QDate>& dates)
{
    this->name = name;  // Инициализация имени студента
    for (const auto& date : dates) {
        marks[date] = 0;  // Инициализация оценок по датам
    }
}

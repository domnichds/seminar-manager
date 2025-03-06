#include "seminar.hpp"
#include "QStandardItemModel"
#include <vector>

Seminar::Seminar(QString name)
{
    if (name.length() == 0) throw std::invalid_argument("Неверное имя");
    this->name = name;
    this->students = std::vector<Student>();
    this->dates = std::vector<QDate>();
}

void Seminar::changeSeminarName(QString name)
{
    if (name.length() == 0) throw std::invalid_argument("Неверное имя");
    this->name = name;
}


#include "seminar.hpp"
#include "QStandardItemModel"
#include <qdatetime.h>
#include <vector>
#include <algorithm>

Seminar::Seminar(QString name)
{
    if (name.isEmpty()) throw std::invalid_argument("Неверное имя");
    this->name = name;
    this->students = std::vector<Student*>();
    this->dates = std::vector<QDate>();
}

void Seminar::changeSeminarName(QString name)
{
    if (name.isEmpty()) throw std::invalid_argument("Неверное имя");
    this->name = name;
}

void Seminar::addDate(QDate date)
{
    for (int i = 0; i < this->dates.size(); i++)
    {
        if (date == this->dates[i]) throw std::invalid_argument("Дата уже присутствует");
    }
    this->dates.push_back(date);
    sort(this->dates.begin(), this->dates.end());
    for (int i = 0; i < this->students.size(); i++)
    {
        students[i]->marks[date] = 0;
    }
}

void Seminar::deleteDate(QDate date)
{
    this->dates.erase(
        std::remove(this->dates.begin(), this->dates.end(), date),
        this->dates.end());

    for (int i = 0; i < this->students.size(); i++)
    {
        this->students[i]->marks.erase(date);
    }
}

void Seminar::changeDate(QDate old_date, QDate new_date)
{
    for (int i = 0; i < this->dates.size(); i++)
    {
        if (new_date == this->dates[i]) throw std::invalid_argument("Дата уже присутствует");
    }
    for (int i = 0; i <this->students.size(); i++)
    {
        short temp_mark = this->students[i]->marks[old_date];
        this->students[i]->marks.erase(old_date);
        this->students[i]->marks[new_date] = temp_mark;
    }
}
Seminar::~Seminar()
{
    for (auto student : this->students)
    {
        delete student;
    }
}


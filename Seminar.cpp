#include "Seminar.h"
#include <QStandardItemModel>
#include <qdatetime.h>

void Seminar::changeName(QString new_name)
{
    name = new_name;
}

void Seminar::addDate(QDate new_date)
{
    for (auto date : dates)
    {
        if (date == new_date) throw std::invalid_argument("Дата уже присутствует");
    }
    dates.push_back(new_date);
    for (auto& student : students)
    {
        student.marks[new_date] = 0;
    }
}

void Seminar::deleteDate(QDate old_date)
{
    dates.erase((std::remove_if(dates.begin(), dates.end(),
        [old_date](const QDate& compare_date)
        {
        return compare_date == old_date;
        }
        )), dates.end());
    for (auto& student : students)
    {
        student.marks.erase(old_date);
    }
}

void Seminar::editDate(QDate old_date, QDate new_date)
{
    for (auto date : dates)
    {
        if (date == new_date) throw std::invalid_argument("Такая дата уже присутствует");
    }
    std::replace(dates.begin(), dates.end(), old_date, new_date);
    for (auto& student : students)
    {
        auto iterator_mark = student.marks.find(old_date);
        short mark_value = iterator_mark->second;
        student.marks.erase(iterator_mark);
        student.marks[new_date] = mark_value;
    }
}

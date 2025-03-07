#include "seminar.hpp"
#include "QStandardItemModel"
#include <qdatetime.h>
#include <vector>
#include <algorithm>

Seminar::Seminar(QString name)
{
    if (name.isEmpty()) throw std::invalid_argument("Неверное имя");
    this->name = name;
    this->students = std::vector<Student>();
    this->dates = std::vector<QDate>();
}

void Seminar::changeSeminarName(QString name)
{
    if (name.isEmpty()) throw std::invalid_argument("Неверное имя");
    this->name = name;
}

void Seminar::addDate(QDate new_date)
{
    for (const auto& date : dates)
    {
        if (new_date == date) throw std::invalid_argument("Дата уже присутствует");
    }
    dates.push_back(new_date);
    std::sort(dates.begin(), dates.end());
    for (auto& student : students)
    {
        student.marks[new_date] = 0;
    }
}

void Seminar::deleteDate(QDate date)
{
    dates.erase(
        std::remove(dates.begin(), dates.end(), date),
        dates.end());
    for (auto& student : students)
    {
        student.marks.erase(date);
    }
}
void Seminar::changeDate(QDate old_date, QDate new_date)
{
    for (const auto& date : dates)
    {
        if (date == new_date) throw std::invalid_argument("Дата уже присутствует");
    }
    for (auto& student : students)
    {
        short temp_mark = student.marks[old_date];
        student.marks.erase(old_date);
        student.marks[new_date] = temp_mark;
    }
}

void Seminar::addStudent(QString name)
{
    if (name.isEmpty()) throw std::invalid_argument("Имя студента не может быть пустым");
    for (const auto& student : students)
    {
        if (student.name == name) throw std::invalid_argument("Студент с таким именем уже существует");
    }
    students.emplace_back(Student{name, {}});
    for (const auto& date : dates)
    {
        students.back().marks[date] = 0;
    }
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.name < b.name;
    });
}



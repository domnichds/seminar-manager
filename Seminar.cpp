#include "Seminar.h"
#include <QStandardItemModel>
#include <qdatetime.h>

Seminar::Seminar(QString name)
{
    std::vector<Student> students = {};
    std::vector<QDate> dates = {};
    this->name = name;
    this->dates = dates;
    this->students = students;
}

Student::Student(QString name, const std::vector<QDate>& dates)
{
    this->name = name;
    for (const auto& date : dates) {
        marks[date] = 0;
    }
}

void Student::changeName(QString new_name, const std::vector<Student>& students)
{
    for (auto& student : students)
    {
        if (student.name == new_name) throw std::invalid_argument("Студент с таким именем уже существует");
    }
    this->name = new_name;
}

void Seminar::changeName(QString new_name)
{
    if (new_name.isEmpty()) throw std::invalid_argument("Имя не может быть пустым");
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
    dates.erase((std::remove_if(dates.begin(), dates.end(),[old_date](const QDate& compare_date){return compare_date == old_date;})), dates.end());
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

void Seminar::addStudent(QString name)
{
    for (auto& student : students)
    {
        if (student.name == name) throw std::invalid_argument("Такой студент уже существует");
    }
    Student new_student(name, dates);
    students.push_back(new_student);
}

void Seminar::deleteStudent(QString name)
{
    auto initialSize = students.size();

    students.erase(
        std::remove_if(students.begin(), students.end(),
                       [&name](const Student& student) { return student.name == name; }),
        students.end()
        );

    if (students.size() == initialSize)
    {
        throw std::invalid_argument("Студент не найден");
    }
}

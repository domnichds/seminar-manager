#ifndef SEMINAR_H
#define SEMINAR_H

#include <QStandardItemModel>
#include <map>
#include <vector>

struct Student
{
    QString name;
    std::map<QDate, short> marks;
    Student(QString, const std::vector<QDate>&);
    void changeName(QString, const std::vector<Student>&);
};

class Seminar
{
public:
    QString name;
    std::vector<Student> students;
    std::vector<QDate> dates;
    Seminar(QString); // Строит Seminar без дат и студентов
    void changeName(QString); // Изменяет имя семинара
    void addDate(QDate); // Добавляет дату
    void editDate(QDate, QDate); // Изменяет существующую дату
    void deleteDate(QDate); // Удаляет дату
    void addStudent(QString); // Добавляет нового студента
    void deleteStudent(QString); // Удаляет студента

};

#endif // SEMINAR_H

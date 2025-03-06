#ifndef SEMINAR_HPP
#define SEMINAR_HPP
#include <qstandarditemmodel.h>
#include <vector>
#include <map>
class Seminar
{
private:
    struct Student
    {
        QString name;
        std::map<QDate, short> marks;
    };
    QString name;
    std::vector<Student*> students;
    std::vector<QDate> dates;
public:
    Seminar(QString);
    void changeSeminarName(QString);
    void addDate(QDate);
    void changeDate(QDate, QDate);
    void deleteDate(QDate);
    void addStudent(QString);
    void changeStudentName(Student*, QString);
    void deleteStudent(Student*);
    ~Seminar();
};
#endif

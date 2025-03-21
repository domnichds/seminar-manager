#include "StudentManager.hpp"

// Реализация конструктора класса StudentManager
StudentManager::StudentManager(StudentData* data)
{
    this->studentData = data;  // Инициализация указателя на данные студента
}

// Метод для изменения имени студента
void StudentManager::changeName(QString new_name, const std::vector<StudentData>& students)
{
    // Проверка на дублирование студента
    for (const auto& student : students)
    {
        if (student.name == new_name) throw std::invalid_argument("Студент с таким именем уже существует");
    }
    studentData->name = new_name;
}

// Метод для выставлении отметки студенту
void StudentManager::setMark(QDate date, short mark)
{
    studentData->marks[date] = mark;
}

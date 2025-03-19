#include "SeminarManager.hpp"
#include <algorithm>

SeminarManager::SeminarManager(SeminarData* data) {
    // Проверка на валидность данных
    if (data == nullptr) {
        throw std::invalid_argument("Неверные данные семинара");
    }
    this->seminarData = data;
}

void SeminarManager::changeName(QString new_name) {
    // Проверка на пустое имя
    if (new_name.isEmpty()) throw std::invalid_argument("Имя не может быть пустым");
    seminarData->name = new_name;
}

void SeminarManager::addDate(QDate new_date) {
    // Проверка на дублирование даты
    for (const auto& date : seminarData->dates) {
        if (date == new_date) throw std::invalid_argument("Дата уже присутствует");
    }
    // Добавление даты в список всех дат семинара
    seminarData->dates.push_back(new_date);
    // Установка оценки "присутствовал" всем студентам
    for (auto& student : seminarData->students) {
        student.marks[new_date] = 0;
    }
}

void SeminarManager::deleteDate(QDate old_date) {
    auto& dates = seminarData->dates;
    // Удаление даты из вектора дат
    dates.erase(std::remove_if(dates.begin(), dates.end(),
                               [old_date](const QDate& date) { return date == old_date; }), dates.end());
    // Удаление оценок за дату у всех студентов
    for (auto& student : seminarData->students) {
        student.marks.erase(old_date);
    }
}

void SeminarManager::editDate(QDate old_date, QDate new_date) {
    auto& dates = seminarData->dates;
    // Проверка корректной передачи даты
    if (std::find(dates.begin(), dates.end(), old_date) == dates.end()) {
        throw std::invalid_argument("Старая дата не найдена");
    }
    // Проверка на дублирование даты
    for (const auto& date : dates) {
        if (date == new_date) throw std::invalid_argument("Новая дата уже существует");
    }
    // Перестановка новой и старой даты
    std::replace(dates.begin(), dates.end(), old_date, new_date);

    // Сохранение оценок и перенос их на измененную дату
    for (auto& student : seminarData->students) {
        if (student.marks.count(old_date)) {
            short mark = student.marks[old_date];
            student.marks.erase(old_date);
            student.marks[new_date] = mark;
        }
    }
}

void SeminarManager::addStudent(QString name) {
    // Проверка на  дублирование студента
    for (const auto& student : seminarData->students) {
        if (student.name == name) throw std::invalid_argument("Студент уже существует");
    }
    // Создание объекта через конструктор и добавление его в вектор
    seminarData->students.emplace_back(name, seminarData->dates);
}

void SeminarManager::deleteStudent(QString name) {
    auto& students = seminarData->students;
    // Сохранение начального размера вектора студентов
    const auto initial_size = students.size();
    // Удаление студента из вектора студентов
    students.erase(
        std::remove_if(students.begin(), students.end(),
                       [&name](const StudentData& student) { return student.name == name; }),
        students.end()
        );
    // Проверка на то, что студент действительно был удален
    if (students.size() == initial_size) {
        throw std::invalid_argument("Студент не найден");
    }
}

#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <vector>
#include <string>
#include "Seminar.h"

class CSVHandler
{
private:
    std::string path;
    std::vector<Seminar> seminars;
public:
    CSVHandler(std::string); // Создает CSVHandler, работающий с указанным путем
    void addSeminar(const Seminar&); // Добавляет в vector seminars
    void updateSeminar(const Seminar&); // Ищет нужный Seminar в seminars и изменяет его
    void readData(); // Читает из файлов и изменяет vector seminars
    void saveData(); // Записывает vector seminars по файлам
    std::vector<Seminar> getSeminars(); // Возвращает vector seminars
};
#endif // CSVHANDLER_H

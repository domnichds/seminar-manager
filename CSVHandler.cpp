#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDate>
#include <QString>
#include <QDir>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "CSVHandler.hpp"
#include <sstream>
#include <filesystem>
#include <cstdio>

CSVHandler::CSVHandler(std::string path)
{
    this->path = path;
    this->seminars = {};
}

std::vector<SeminarData> CSVHandler::getSeminars()
{
    return seminars;
}

void CSVHandler::readData()
{
    std::vector<SeminarData> seminars;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            std::ifstream file(entry.path());

            std::vector<QDate> dates;
            std::vector<StudentData> students;
            std::string line;
            int raw_counter = 0;
            std::string name;
            int first_symbol = 0;
            std::string filename = entry.path().filename().string();

            while (filename[first_symbol] != '.')
            {
                name += filename[first_symbol];
                first_symbol += 1;
                if (first_symbol >= 50)
                {
                    break;
                }
            }

            while (std::getline(file, line))
            {
                std::stringstream ss(line);
                std::string cell;
                int column_counter = 0;
                std::map<QDate, short> ReadDateMarks;
                std::vector<short> ReadMarks;
                QString ReadName;

                while (std::getline(ss, cell, ';'))
                {
                    QString cell_to_QString = QString::fromStdString(cell);

                    if (raw_counter == 0)
                    {
                        if (cell_to_QString.startsWith("И"))
                        {
                            continue;
                        }
                        else
                        {
                            QDate date = QDate::fromString(cell_to_QString, "dd.MM.yyyy");

                            if (!date.isValid())
                            {
                                throw std::invalid_argument("Неправильный формат Data " + cell + " в файле " + filename);
                            }
                            dates.push_back(date);
                        }
                    }
                    else
                    {
                        if (column_counter == 0)
                        {
                            ReadName = QString::fromStdString(cell);
                        }
                        else
                        {
                            if (cell_to_QString.startsWith("Н"))
                            {
                                ReadMarks.push_back(-1);
                            }
                            else if (cell_to_QString.startsWith("П"))
                            {
                                ReadMarks.push_back(0);
                            }
                            else if (cell_to_QString.startsWith("Р"))
                            {
                                ReadMarks.push_back(1);
                            }
                            else
                            {
                                throw std::invalid_argument("Неверный формат marks " + cell + " в файле " + filename);
                            }
                        }
                    }
                    column_counter += 1;
                }
                if (raw_counter != 0)
                {
                    for (int i = 0; i < dates.size(); i++)
                    {
                        ReadDateMarks[dates[i]] = ReadMarks[i];
                    }
                    StudentData newStudentData(ReadName, ReadDateMarks);
                    students.push_back(newStudentData);
                }
                raw_counter += 1;
            }

            SeminarData newSeminarData(QString::fromStdString(name));
            newSeminarData.dates = dates;
            newSeminarData.students = students;
            seminars.push_back(newSeminarData);
            file.close();
        }
    }
    this->seminars = seminars;
}

void CSVHandler::writeData(const std::vector<SeminarData>& AllSeminars)
{
    // Удаление всех файлов в папке
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            std::filesystem::remove(entry.path());
        }
    }

    if (AllSeminars.empty())
    {
        this->seminars = AllSeminars;
        return;
    }

    int Student_counter = 0;
    std::vector<QDate> WriteDates = AllSeminars[0].dates;
    std::sort(WriteDates.begin(), WriteDates.end());

    for (const auto& seminar : AllSeminars)
    {
        QString filePath = QString::fromStdString(path) + "/" + seminar.name + ".csv";
        QFile file(filePath);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            std::cerr << "Ошибка создания файла: " << filePath.toStdString() << std::endl;
            continue;
        }

        QTextStream out(&file);
        out << QChar(0xFEFF);

        out << "Имя студента;";
        for (const auto& date : WriteDates)
        {
            out << date.toString("dd.MM.yyyy") << ";";
        }
        out << "\n";

        std::vector<StudentData> SortStudentData = seminar.students;
        std::sort(SortStudentData.begin(), SortStudentData.end());

        for (const auto& student : SortStudentData)
        {
            out << student.name << ";";

            for (const auto& date : WriteDates)
            {
                if (student.marks.count(date))
                {
                    short mark = student.marks.at(date);
                    if (mark == -1) out << "Н;";
                    else if (mark == 0) out << "П;";
                    else if (mark == 1) out << "Р;";
                }
                else
                {
                    out << "П;";
                }
            }
            out << "\n";
        }

        file.close();
    }

    this->seminars = AllSeminars;
}

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
                            QDate date = QDate::fromString(cell_to_QString, "dd-MM-yyyy");

                            if (date.isValid())
                            {
                                dates.push_back(date);
                            }
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
    int Student_counter = 0;
    std::vector<QDate> WriteDates = AllSeminars[0].dates;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            std::ofstream file(entry.path(), std::ios::trunc);
            std::string oldName = path + "/" + seminars[Student_counter].name.toStdString() + ".csv";
            std::string newName = path + "/" + AllSeminars[Student_counter].name.toStdString() + ".csv";

            file << "Имя студента;";
            for (const auto& date : WriteDates)
            {
                file << date.toString("dd-MM-yyyy").toStdString() << ";";
            }
            file << std::endl;

            for (const auto& student : AllSeminars[Student_counter].students)
            {
                file << student.name.toStdString() << ";";

                for (const auto& date : WriteDates)
                {
                    if (student.marks.count(date))
                    {
                        short mark = student.marks.at(date);
                        if (mark == -1) file << "Н;";
                        else if (mark == 0) file << "П;";
                        else if (mark == 1) file << "Р;";
                    }
                    else
                    {
                        file << "П";
                    }
                }
                file << std::endl;
            }
            file.close();

            std::string oldFile = oldName;
            std::string newFile = newName;

            if (std::rename(oldFile.c_str(), newFile.c_str()) != 0)
            {
                perror("Error renaming file");
                std::cerr << "Failed to rename file: " << oldFile << " to " << newFile << std::endl;
            }
        }
        Student_counter += 1;
    }
    this->seminars = AllSeminars;
}

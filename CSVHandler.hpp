#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <vector>
#include <string>
#include "Seminar.h"

class CSVHandler
{
private:
    std::string path;
    std::vector<SeminarData> seminars;
public:
    CSVHandler(std::string);
    std::vector<SeminarData> getSeminars();
    void readData();
    void writeData(const std::vector<SeminarData>&);
};
#endif // CSVHANDLER_H


#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "Student.h"
#include "Timer.h"


class FileManager
{
public:
    static void generateRandomStudentList(int numStudents, const std::string &filename);
    static void readStudentDataFromFile(const std::string &filename, std::vector<Student> &students);
    static void writeStudentDataToFile(const std::vector<Student> &students, const std::string &filename);
    static void splitStudentsByGrade(const std::vector<Student> &students, const std::string &passedFile, const std::string &failedFile);
};

#endif

#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <deque>
#include <list>
#include "Student.h"

class Sorting
{
public:
    static void sortStudents(std::vector<Student> &students);
    static void sortStudents(std::list<Student> &students);
    static void sortStudents(std::deque<Student> &students);
};

#endif

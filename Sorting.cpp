#include "Sorting.h"
#include <algorithm>

void Sorting::sortStudents(std::vector<Student> &students)
{
    std::sort(students.begin(), students.end(), [](const Student &a, const Student &b)
              { return a.getFinalGrade() > b.getFinalGrade(); });
}

void Sorting::sortStudents(std::list<Student> &students)
{
    students.sort([](const Student &a, const Student &b)
                  { return a.getFinalGrade() > b.getFinalGrade(); });
}

void Sorting::sortStudents(std::deque<Student> &students)
{
    std::sort(students.begin(), students.end(), [](const Student &a, const Student &b)
              { return a.getFinalGrade() > b.getFinalGrade(); });
}


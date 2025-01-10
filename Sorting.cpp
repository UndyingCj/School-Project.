#include "Sorting.h"
#include <algorithm>

void Sorting::sortStudents(std::vector<Student> &students)
{
    std::sort(students.begin(), students.end(), [](const Student &a, const Student &b)
              { return a.getFinalGrade() > b.getFinalGrade(); });
}

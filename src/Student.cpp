#include "Student.h"

Student::Student(const std::string &firstName, const std::string &surname)
    : firstName(firstName), surname(surname), examResult(0.0), finalGrade(0.0) {}

void Student::setScores(const std::vector<double> &hwResults, double exam)
{
    homeworkResults = hwResults;
    examResult = exam;
}

void Student::calculateFinalGrade(bool useAverage)
{
    double hwScore = 0.0;

    if (useAverage)
    {
        hwScore = std::accumulate(homeworkResults.begin(), homeworkResults.end(), 0.0) / homeworkResults.size();
    }
    else
    {
        std::sort(homeworkResults.begin(), homeworkResults.end());
        if (homeworkResults.size() % 2 == 0)
        {
            hwScore = (homeworkResults[homeworkResults.size() / 2 - 1] +
                       homeworkResults[homeworkResults.size() / 2]) /
                      2.0;
        }
        else
        {
            hwScore = homeworkResults[homeworkResults.size() / 2];
        }
    }

    finalGrade = 0.4 * hwScore + 0.6 * examResult;
}

double Student::getFinalGrade() const
{
    return finalGrade;
}

std::string Student::getFullName() const
{
    return firstName + " " + surname;
}

std::ostream &operator<<(std::ostream &os, const Student &student)
{
    os << std::setw(10) << student.firstName
       << std::setw(15) << student.surname
       << std::setw(15) << std::fixed 
       << std::setprecision(2) << student.finalGrade;
    return os;
}

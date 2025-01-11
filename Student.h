#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <stdexcept>

class Student
{
private:
    std::string firstName;
    std::string surname;
    std::vector<double> homeworkResults;
    double examResult;
    double finalGrade;

public:
    Student(const std::string &firstName, const std::string &surname);
    void setScores(const std::vector<double> &hwResults, double exam);
    void calculateFinalGrade(bool useAverage);
    double getFinalGrade() const;
    std::string getFullName() const;

    friend std::ostream &operator<<(std::ostream &os, const Student &student);
};

#endif

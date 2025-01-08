#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

class Student
{
private:
    std::string firstName;
    std::string lastName;
    std::vector<double> assignmentScores;
    double examScore;
    double finalGrade;

public:
    // Constructor
    Student(const std::string &firstName, const std::string &lastName)
        : firstName(firstName), lastName(lastName), examScore(0.0), finalGrade(0.0) {}

    // Copy Constructor
    Student(const Student &other)
        : firstName(other.firstName), lastName(other.lastName),
          assignmentScores(other.assignmentScores), examScore(other.examScore),
          finalGrade(other.finalGrade) {}

    // Assignment Operator
    Student &operator=(const Student &other)
    {
        if (this == &other)
            return *this; // Self-assignment check
        firstName = other.firstName;
        lastName = other.lastName;
        assignmentScores = other.assignmentScores;
        examScore = other.examScore;
        finalGrade = other.finalGrade;
        return *this;
    }

    // Destructor
    ~Student() {}

    // Data Input Method
    friend std::istream &operator>>(std::istream &is, Student &student)
    {
        int numAssignments;
        std::cout << "Enter the number of assignments: ";
        is >> numAssignments;
        student.assignmentScores.resize(numAssignments);

        for (int i = 0; i < numAssignments; ++i)
        {
            std::cout << "Assignment " << (i + 1) << ": ";
            is >> student.assignmentScores[i];
        }

        std::cout << "Enter exam score: ";
        is >> student.examScore;
        return is;
    }

    // Data Output Method
    friend std::ostream &operator<<(std::ostream &os, const Student &student)
    {
        os << std::setw(10) << student.firstName
           << std::setw(15) << student.lastName
           << std::setw(15) << std::fixed << std::setprecision(2) << student.finalGrade;
        return os;
    }

    // Calculation Method for Final Grade
    void calculateFinalGrade(bool useAverage)
    {
        double assignmentScore = 0.0;
        if (useAverage)
        {
            assignmentScore = std::accumulate(assignmentScores.begin(), assignmentScores.end(), 0.0) / assignmentScores.size();
        }
        else
        {
            std::sort(assignmentScores.begin(), assignmentScores.end());
            if (assignmentScores.size() % 2 == 0)
            {
                assignmentScore = (assignmentScores[assignmentScores.size() / 2 - 1] +
                                   assignmentScores[assignmentScores.size() / 2]) /
                                  2.0;
            }
            else
            {
                assignmentScore = assignmentScores[assignmentScores.size() / 2];
            }
        }
        finalGrade = 0.4 * assignmentScore + 0.6 * examScore;
    }
};

int main()
{
    int studentCount;
    std::cout << "Enter the number of students: ";
    std::cin >> studentCount;

    std::vector<Student> students;
    for (int i = 0; i < studentCount; ++i)
    {
        std::string firstName, lastName;
        std::cout << "Enter first name and last name for student " << i + 1 << ": ";
        std::cin >> firstName >> lastName;

        Student student(firstName, lastName);
        std::cin >> student;

        students.push_back(student);
    }

    char choice;
    std::cout << "Calculate final grade using (A)verage or (M)edian of assignment scores? (A/M): ";
    std::cin >> choice;
    bool useAverage = (choice == 'A' || choice == 'a');

    // Calculate Final Grades for All Students
    for (auto &student : students)
    {
        student.calculateFinalGrade(useAverage);
    }

    // Display Final Grades
    std::cout << std::setw(10) << "First Name"
              << std::setw(15) << "Last Name"
              << std::setw(15) << "Final Grade"
              << "\n-------------------------------------------\n";

    for (const auto &student : students)
    {
        std::cout << student << std::endl;
    }

    return 0;
}
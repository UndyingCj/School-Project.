#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <ctime>

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

    // Data Input Method
    void inputScores()
    {
        double score;
        std::cout << "Enter homework scores for " << firstName << " " << lastName << " (type -1 to finish):\n";
        while (true)
        {
            std::cin >> score;
            if (score == -1)
                break;
            assignmentScores.push_back(score);
        }

        std::cout << "Enter exam score for " << firstName << " " << lastName << ": ";
        std::cin >> examScore;
    }

    // Random Score Generation
    void generateRandomScores(int numAssignments)
    {
        assignmentScores.clear();
        for (int i = 0; i < numAssignments; ++i)
        {
            assignmentScores.push_back((std::rand() % 101) / 1.0); // Random score between 0 and 100
        }
        examScore = (std::rand() % 101) / 1.0; // Random score between 0 and 100
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

    // Output Method
    friend std::ostream &operator<<(std::ostream &os, const Student &student)
    {
        os << std::setw(10) << student.firstName
           << std::setw(15) << student.lastName
           << std::setw(15) << std::fixed << std::setprecision(2) << student.finalGrade;
        return os;
    }
};

int main()
{
    std::srand(std::time(nullptr)); // Seed the random number generator

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

        char inputChoice;
        std::cout << "Do you want to (M)anually enter scores or (R)andomly generate scores? (M/R): ";
        std::cin >> inputChoice;

        if (inputChoice == 'M' || inputChoice == 'm')
        {
            student.inputScores();
        }
        else if (inputChoice == 'R' || inputChoice == 'r')
        {
            int numAssignments;
            std::cout << "Enter the number of assignments to randomly generate: ";
            std::cin >> numAssignments;
            student.generateRandomScores(numAssignments);
        }

        students.push_back(student);
    }

    char calculationChoice;
    std::cout << "Calculate final grade using (A)verage or (M)edian of assignment scores? (A/M): ";
    std::cin >> calculationChoice;
    bool useAverage = (calculationChoice == 'A' || calculationChoice == 'a');

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

    // Display the chosen calculation method
    std::cout << "\nFinal grades were calculated using the "
              << (useAverage ? "average" : "median")
              << " of assignment scores.\n";

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctime>

class Person {
private:
    std::string firstName;
    std::string surname;
    std::vector<double> homeworkResults;
    double examResult;
    double finalGradeAverage;
    double finalGradeMedian;

public:
    // Constructor
    Person(const std::string& firstName, const std::string& surname)
        : firstName(firstName), surname(surname), examResult(0.0), finalGradeAverage(0.0), finalGradeMedian(0.0) {}

    // Copy Constructor
    Person(const Person& other)
        : firstName(other.firstName), surname(other.surname),
          homeworkResults(other.homeworkResults), examResult(other.examResult),
          finalGradeAverage(other.finalGradeAverage), finalGradeMedian(other.finalGradeMedian) {}

    // Assignment Operator
    Person& operator=(const Person& other) {
        if (this == &other) return *this; // Self-assignment check
        firstName = other.firstName;
        surname = other.surname;
        homeworkResults = other.homeworkResults;
        examResult = other.examResult;
        finalGradeAverage = other.finalGradeAverage;
        finalGradeMedian = other.finalGradeMedian;
        return *this;
    }

    // Destructor
    ~Person() {}

    // Method to set homework results and exam score
    void setScores(const std::vector<double>& hwResults, double exam) {
        homeworkResults = hwResults;
        examResult = exam;
    }

    // Random Score Generation
    void generateRandomScores(int numAssignments) {
        homeworkResults.clear();
        for (int i = 0; i < numAssignments; ++i) {
            homeworkResults.push_back((std::rand() % 101) / 1.0); // Random score between 0 and 100
        }
        examResult = (std::rand() % 101) / 1.0; // Random score between 0 and 100
    }

    // Data Output Method
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << std::setw(10) << person.firstName
           << std::setw(15) << person.surname
           << std::setw(15) << std::fixed << std::setprecision(2) << person.finalGradeAverage
           << " | "
           << std::setw(15) << person.finalGradeMedian;
        return os;
    }

    // Calculation Method for Final Grades
    void calculateFinalGrades() {
        // Average Calculation
        double hwScoreAverage = std::accumulate(homeworkResults.begin(), homeworkResults.end(), 0.0) / homeworkResults.size();
        finalGradeAverage = 0.4 * hwScoreAverage + 0.6 * examResult;

        // Median Calculation
        double hwScoreMedian = 0.0;
        std::sort(homeworkResults.begin(), homeworkResults.end());
        if (homeworkResults.size() % 2 == 0) {
            hwScoreMedian = (homeworkResults[homeworkResults.size() / 2 - 1] +
                             homeworkResults[homeworkResults.size() / 2]) /
                            2.0;
        } else {
            hwScoreMedian = homeworkResults[homeworkResults.size() / 2];
        }
        finalGradeMedian = 0.4 * hwScoreMedian + 0.6 * examResult;
    }
};

int main() {
    std::srand(std::time(nullptr)); // Seed the random number generator

    std::vector<Person> persons;
    std::string inputChoice;

    std::cout << "Do you want to read data from a (F)ile or (M)anually enter/randomly generate data? (F/M): ";
    std::cin >> inputChoice;

    if (inputChoice == "F" || inputChoice == "f") {
        std::string filename = "StudentsList.txt";
       // std::cout << "Enter the filename: ";
       // std::cin >> filename;

        std::ifstream infile(filename);
        if (!infile) {
            std::cerr << "Unable to open file " << filename << std::endl;
            return 1; // Exit if the file could not be opened
        }

        std::string line;
        // Skip the header line
        std::getline(infile, line);

        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string firstName, surname;
            double score;
            std::vector<double> homeworkScores;

            // Read first name and surname
            iss >> firstName >> surname;

            // Read homework scores
            for (int i = 0; i < 5; ++i) { // Adjust the number of homework scores as needed
                iss >> score;
                homeworkScores.push_back(score);
            }

            // Read exam score
            double examScore;
            iss >> examScore;

            // Create a Person object and set scores
            Person person(firstName, surname);
            person.setScores(homeworkScores, examScore);
            persons.push_back(person);
        }

        infile.close(); // Close the file after reading
    } else if (inputChoice == "M" || inputChoice == "m") {
        int personCount;
        std::cout << "Enter the number of persons: ";
        std::cin >> personCount;

        for (int i = 0; i < personCount; ++i) {
            std::string firstName, surname;
            std::cout << "Enter first name and surname for person " << i + 1 << ": ";
            std::cin >> firstName >> surname;

            Person person(firstName, surname);

            char scoreChoice;
            std::cout << "Do you want to (M)anually enter scores or (R)andomly generate scores? (M/R): ";
            std::cin >> scoreChoice;

            if (scoreChoice == 'M' || scoreChoice == 'm') {
                double score;
                std::cout << "Enter homework scores (type -1 to finish): ";
                std::vector<double> homeworkScores;
                while (true) {
                    std::cin >> score;
                    if (score == -1)
                        break;
                    homeworkScores.push_back(score);
                }
                double examScore;
                std::cout << "Enter exam score: ";
                std::cin >> examScore;
                person.setScores(homeworkScores, examScore);
            } else if (scoreChoice == 'R' || scoreChoice == 'r') {
                int numAssignments;
                std::cout << "Enter the number of assignments to randomly generate: ";
                std::cin >> numAssignments;
                person.generateRandomScores(numAssignments);
            }

            persons.push_back(person);
        }
    }

    // Calculate Final Grades for All Students
    for (auto& person : persons) {
        person.calculateFinalGrades();
    }

    // Display Final Grades
    std::cout << std::setw(10) << "Name"
              << std::setw(15) << "Surname"
              << std::setw(15) << "Final (Avg. )"
              << " | "
              << std::setw(15) << "Final (Med. )"
              << "\n---------------------------------------------------------------\n";

    for (const auto& person : persons) {
        std::cout << person << std::endl;
    }

    return 0;
}
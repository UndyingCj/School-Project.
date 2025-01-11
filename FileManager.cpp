#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <random>
#include <iostream>

void FileManager::generateRandomStudentList(int numStudents, const std::string &filename)
{
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Setup for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 10.0);

    // Set column widths
    int nameWidth = 10;
    int scoreWidth = 8;

    // Write the header
    outFile << std::left << std::setw(nameWidth) << "Name"
        << std::setw(nameWidth) << "Surname";
    for (int i = 1; i <= 7; ++i) {
        outFile << std::setw(scoreWidth) << ("HW" + std::to_string(i));
    }
    outFile << std::setw(scoreWidth) << "Exam" << "\n";

    // Generate data for each student
    for (int i = 0; i < numStudents; ++i) {
        outFile << std::left << std::setw(nameWidth) << ("Name" + std::to_string(i + 1))
            << std::setw(nameWidth) << ("Surname" + std::to_string(i % 2 + 1));
        for (int j = 0; j < 7; ++j) {
            outFile << std::setw(scoreWidth) << std::fixed << std::setprecision(2) << dis(gen); // Random homework scores
        }
        outFile << std::setw(scoreWidth) << std::fixed << std::setprecision(2) << dis(gen) << "\n"; // Random exam score
    }
}

void FileManager::readStudentDataFromFile(const std::string &filename, std::vector<Student> &students)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string firstName, surname;
        double score;
        std::vector<double> homeworkScores;

        iss >> firstName >> surname;
        for (int i = 0; i < 7; ++i)
        {
            iss >> score;
            homeworkScores.push_back(score);
        }
        iss >> score; // Exam score

        Student student(firstName, surname);
        student.setScores(homeworkScores, score);
        students.push_back(student);
    }
}

void FileManager::readStudentDataFromFile(const std::string &filename, std::list<Student> &students)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string firstName, surname;
        double score;
        std::vector<double> homeworkScores;

        iss >> firstName >> surname;
        for (int i = 0; i < 7; ++i)
        {
            iss >> score;
            homeworkScores.push_back(score);
        }
        iss >> score; // Exam score

        Student student(firstName, surname);
        student.setScores(homeworkScores, score);
        students.push_back(student);
    }
}

void FileManager::readStudentDataFromFile(const std::string &filename, std::deque<Student> &students)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string firstName, surname;
        double score;
        std::vector<double> homeworkScores;

        iss >> firstName >> surname;
        for (int i = 0; i < 7; ++i)
        {
            iss >> score;
            homeworkScores.push_back(score);
        }
        iss >> score; // Exam score

        Student student(firstName, surname);
        student.setScores(homeworkScores, score);
        students.push_back(student);
    }
}

void FileManager::writeStudentDataToFile(const std::vector<Student> &students, const std::string &filename)
{
    std::ofstream outFile(filename);
    outFile << std::setw(10) << std::left << "Name" 
        << std::setw(10) << std::left << "Surname"
         << std::left  << std::setprecision(2) << "FinalGrade\n";

    for (const auto &student : students)
    {
        outFile << student << "\n"; // Ensure the output stream is correctly formatted
    }
}

void FileManager::writeStudentDataToFile(const std::list<Student> &students, const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    outFile << std::setw(10) << std::left << "Name" 
        << std::setw(10) << std::left << "Surname"
         << std::left  << std::setprecision(2) << "FinalGrade\n";

    for (const auto &student : students)
    {
        outFile << student << "\n";
    }
}

void FileManager::writeStudentDataToFile(const std::deque<Student> &students, const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    
    outFile << std::setw(10) << std::left << "Name" 
        << std::setw(10) << std::left << "Surname"
         << std::left  << std::setprecision(2) << "FinalGrade\n";
         
    for (const auto &student : students)
    {
        outFile << student << "\n";
    }
}

void FileManager::splitStudentsByGrade(const std::vector<Student> &students, const std::string &passedFile, const std::string &failedFile)
{
    std::vector<Student> passed, failed;
    Timer timer;

    timer.startTimer(); 

    for (const auto &student : students)
    {
       double roundedGrade = std::round(student.getFinalGrade() * 100.0) / 100.0;

        if (roundedGrade < 5.0)      
            failed.push_back(student);
        else
            passed.push_back(student);
    }

    double splitTime = timer.stopTimer();
    std::cout << "Splitting students took " << splitTime << " seconds.\n\n";

    
    timer.startTimer();
    writeStudentDataToFile(passed, passedFile);
    writeStudentDataToFile(failed, failedFile);
    double writeTime = timer.stopTimer();
    std::cout << "Writing students to two new files took " << writeTime << " seconds.\n\n";
}


void FileManager::splitStudentsByGrade(const std::list<Student> &students, const std::string &passedFile, const std::string &failedFile)
{
    std::list<Student> passed, failed;

     Timer timer;

    timer.startTimer(); 

    for (const auto &student : students)
    {
       double roundedGrade = std::round(student.getFinalGrade() * 100.0) / 100.0;

        if (roundedGrade < 5.0)      
            failed.push_back(student);
        else
            passed.push_back(student);
    }

    double splitTime = timer.stopTimer();
    std::cout << "Splitting students took " << splitTime << " seconds.\n\n";

    
    timer.startTimer();
    writeStudentDataToFile(passed, passedFile);
    writeStudentDataToFile(failed, failedFile);
    double writeTime = timer.stopTimer();
    std::cout << "Writing students to two new files took " << writeTime << " seconds.\n\n";
}

void FileManager::splitStudentsByGrade(const std::deque<Student> &students, const std::string &passedFile, const std::string &failedFile)
{
    std::deque<Student> passed, failed;

    Timer timer;

    timer.startTimer(); 

    for (const auto &student : students)
    {
       double roundedGrade = std::round(student.getFinalGrade() * 100.0) / 100.0;

        if (roundedGrade < 5.0)      
            failed.push_back(student);
        else
            passed.push_back(student);
    }

    double splitTime = timer.stopTimer();
    std::cout << "Splitting students took " << splitTime << " seconds.\n\n";

    
    timer.startTimer();
    writeStudentDataToFile(passed, passedFile);
    writeStudentDataToFile(failed, failedFile);
    double writeTime = timer.stopTimer();
    std::cout << "Writing students to two new files took " << writeTime << " seconds.\n\n";
}

void FileManager::splitStudentsByGrade1(std::vector<Student> &students, const std::string &passedFile, const std::string &failedFile)
{
     Timer timer;

    timer.startTimer();

    // Find the first student who passed (grade >= 5.0)
   auto FailStart = std::find_if(students.begin(), students.end(), [](const Student &student) {
        double roundedGrade = std::round(student.getFinalGrade() * 100.0) / 100.0;
        return roundedGrade < 5.0;
    });

     // Create a new container for failed students (before passStart)
    std::vector<Student> failed(FailStart, students.end());

     // Modify the original container to only contain passed students
    students.erase(FailStart, students.end());

    double findTime = timer.stopTimer();
    std::cout << "Splitting vector with one new container took " << findTime << " seconds.\n\n";

    timer.startTimer();
   
    // Write results to files
    writeStudentDataToFile(students, passedFile); // Passed students
    writeStudentDataToFile(failed, failedFile);   // Failed students

    double writeTime = timer.stopTimer();
    std::cout << "Writing students to files took " << writeTime << " seconds.\n\n";
}

void FileManager::splitStudentsByGrade1(std::list<Student> &students, const std::string &passedFile, const std::string &failedFile)
{
     Timer timer;

    timer.startTimer();

    // Find the first student who passed (grade >= 5.0)
    auto FailStart = std::find_if(students.begin(), students.end(), [](const Student &student) {
        double roundedGrade = std::round(student.getFinalGrade() * 100.0) / 100.0;
        return roundedGrade < 5.0;
    });

    std::list<Student> failed(FailStart, students.end());
    students.erase(FailStart, students.end());


    double findTime = timer.stopTimer();
    std::cout << "Splitting list with one new container took " << findTime << " seconds.\n\n";

    timer.startTimer();

    // Write results to files
    writeStudentDataToFile(students, passedFile); // Passed students
    writeStudentDataToFile(failed, failedFile);   // Failed students

    double writeTime = timer.stopTimer();
    std::cout << "Writing students to files took " << writeTime << " seconds.\n\n";
}

void FileManager::splitStudentsByGrade1(std::deque<Student> &students, const std::string &passedFile, const std::string &failedFile)
{
     Timer timer;

    timer.startTimer();

    // Find the first student who passed (grade >= 5.0)
    auto FailStart = std::find_if(students.begin(), students.end(), [](const Student &student) {
        double roundedGrade = std::round(student.getFinalGrade() * 100.0) / 100.0;
        return roundedGrade < 5.0;
    });

    std::deque<Student> failed(FailStart, students.end());
    students.erase(FailStart, students.end());

    double findTime = timer.stopTimer();
    std::cout << "Splitting deque with one new container took " << findTime << " seconds.\n\n";

    timer.startTimer();

   
    // Write results to files
    writeStudentDataToFile(students, passedFile); // Passed students
    writeStudentDataToFile(failed, failedFile);   // Failed students

    double writeTime = timer.stopTimer();
    std::cout << "Writing students to files took " << writeTime << " seconds.\n\n";
}


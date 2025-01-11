#include <iostream>
#include <vector>
#include <string>
#include "Student.h"
#include "FileManager.h"
#include "Sorting.h"
#include "Timer.h"

int main()
{
    int choice;
    bool exitProgram = false;

    while (!exitProgram)
    {
        std::cout << "\nWhat would you like to do?\n";
        std::cout << "1. Generate random students\n";
        std::cout << "2. Read data from file\n";
        std::cout << "3. Sort students And Split to two files \n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

           if(std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                    std::cout << "Invalid input. Please enter a valid integer.\n";
                }

        try
        {
            switch (choice)
            {
            case 1:
            {
                int numStudents;
                std::string filename;
                std::cout << "How many students to generate? ";
                std::cin >> numStudents;
                std::cout << "Enter the filename to save: ";
                std::cin >> filename;
                FileManager::generateRandomStudentList(numStudents, filename);
                break;
            }
            case 2:
            {
                std::string filename;
                std::cout << "Enter the filename to read from: ";
                std::cin >> filename;
                std::vector<Student> students;
                FileManager::readStudentDataFromFile(filename, students);

                char choice;
                std::cout << "Calculate final grade using (A)verage or (M)edian? ";
                std::cin >> choice;
                bool useAverage = (choice == 'A' || choice == 'a');

                

                // Loop through students and calculate final grade
                for (auto& student : students)
                {
                    student.calculateFinalGrade(useAverage);
                }

                if (choice == 'A' || choice == 'a') {
                    std::cout << std::setw(10) << "Name"
                        << std::setw(15) << "Surname"
                        << std::setw(15) << "Final (Avg. )"
                        << "\n---------------------------------------------------------------\n";
                }
                else
                {
                    std::cout << std::setw(10) << "Name"
                        << std::setw(15) << "Surname"
                        << std::setw(15) << "Final (Med. )"
                        << "\n---------------------------------------------------------------\n";
                }


                for (const auto& person : students) {
                    std::cout << person << std::endl;
                } break;
            }

            case 3:
            {
                std::string filename;
                std::cout << "Enter the filename to read from: ";
                std::cin >> filename;

                 
                std::cout << "Select container:\n1. Vector\n2. List\n3. Deque\nEnter your choice: ";
                int Choice;
                std::cin >> Choice;

                if(std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                    std::cout << "Invalid input. Please enter a valid integer.\n";
                }

                if(Choice == 1)
                {
                    std::vector<Student> students;

                    Timer timer; // Start the timer for the entire operation
                    timer.startTimer();

                    // Measure time for reading data
                    FileManager::readStudentDataFromFile(filename, students);
                    double readTime = timer.stopTimer(); // Stop and get elapsed time
                    std::cout << "\nReading data took " << readTime << " seconds.\n";

                    // Calculate final grade for each student
                    char choice;
                    std::cout << "Calculate final grade using (A)verage or (M)edian? ";
                    std::cin >> choice;
                    bool useAverage = (choice == 'A' || choice == 'a');

                    for (auto& student : students)
                    {
                        student.calculateFinalGrade(useAverage);
                    }

                    timer.startTimer(); // Restart timer for sorting phase
                    Sorting::sortStudents(students);
                    double sortTime = timer.stopTimer(); // Stop and get elapsed time
                    std::cout << "\nSorting took " << sortTime << " seconds.\n\n";

                    FileManager::splitStudentsByGrade(students, "passed_studentsVector.txt", "failed_studentsVector.txt");
                }
                else if (Choice == 2)
                {
                    std::list<Student> students;

                    Timer timer; // Start the timer for the entire operation
                    timer.startTimer();

                    // Measure time for reading data
                    FileManager::readStudentDataFromFile(filename, students);
                    double readTime = timer.stopTimer(); // Stop and get elapsed time
                    std::cout << "\nReading data took " << readTime << " seconds.\n";

                    // Calculate final grade for each student
                    char choice;
                    std::cout << "Calculate final grade using (A)verage or (M)edian? ";
                    std::cin >> choice;
                    bool useAverage = (choice == 'A' || choice == 'a');

                    for (auto& student : students)
                    {
                        student.calculateFinalGrade(useAverage);
                    }

                    timer.startTimer(); // Restart timer for sorting phase
                    Sorting::sortStudents(students);
                    double sortTime = timer.stopTimer(); // Stop and get elapsed time
                    std::cout << "\nSorting took " << sortTime << " seconds.\n\n";

                    FileManager::splitStudentsByGrade(students, "passed_studentsList.txt", "failed_studentsList.txt");
                }
                else if (Choice == 3)
                {
                    std::deque<Student> students;

                    Timer timer; // Start the timer for the entire operation
                    timer.startTimer();

                    // Measure time for reading data
                    FileManager::readStudentDataFromFile(filename, students);
                    double readTime = timer.stopTimer(); // Stop and get elapsed time
                    std::cout << "\nReading data took " << readTime << " seconds.\n";

                    // Calculate final grade for each student
                    char choice;
                    std::cout << "Calculate final grade using (A)verage or (M)edian? ";
                    std::cin >> choice;
                    bool useAverage = (choice == 'A' || choice == 'a');

                    for (auto& student : students)
                    {
                        student.calculateFinalGrade(useAverage);
                    }

                    timer.startTimer(); // Restart timer for sorting phase
                    Sorting::sortStudents(students);
                    double sortTime = timer.stopTimer(); // Stop and get elapsed time
                    std::cout << "\nSorting took " << sortTime << " seconds.\n\n";

                    FileManager::splitStudentsByGrade(students, "passed_studentsDeque.txt", "failed_studentsDeque.txt");
                }
                else std::cout << " Wrong Choice!";






















                
                
                break;
            }

            case 4:
                exitProgram = true;
                std::cout << "Exiting the program...\n";
                break;
            default:
                std::cout << "Invalid choice! Please select a valid option.\n";
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}

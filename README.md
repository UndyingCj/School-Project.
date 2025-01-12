SP-Projects
Systemic Programmic work - VVK 2024/2025

Introduction to the Proposed Application
Student Points Calculation Formula:
Final Points = 0.4 * (Average of Homework | Median of Homework) + 0.6 * Exam





                                                                                 Releases
Release v0.1
This version outlines the basic structure of the grade calculator, with the implementation of a Person class that includes essential attributes and methods, such as the Rule of Three.

Key Features:

The Person class stores details for an individual student, including:
Name and surname
Homework and exam results
Final grade
Users can populate the class via input and calculate the final grade using either the average or median of homework scores. Results are displayed on the console.
Homework Input:

Allows users to input homework scores without specifying the total number of assignments and to end input anytime.
Supports random generation of homework and exam scores.
File Input:

Reads student data from files formatted as:
Copy code
Name    Surname  HW1 HW2 HW3 HW4 HW5 Exam  
Name1   Surname1   8   9   10   6   10   9  
Name2   Surname2   7   10   8   5    4   6  
Computes and displays final grades (average and median) for all students.
Performance Note:
A vector container is utilized for efficient handling, though frequent pushbacks may be costly if reallocation occurs.

Release v0.2
Enhancements:

Code refactored into .cpp and .h files for better readability and maintenance.
Error handling introduced via exception handlers for smoother operation.
New Features:

Random Data Generation:
Users specify the number of students; output is saved to a file.
File Operations:
Reads student data into a vector.
Sorts data in descending order using std::sort.
Splits data into two containers (passed and failed grades) and outputs results to two files.
Performance Tracking:
Tracks execution speed for file reading, sorting, splitting, and file writing.
Release v0.25
Container Comparison:

Adds list and deque containers alongside vector.
Performance Observations:

Sorting: Lists are faster due to pointer-based sorting, avoiding element copying.
Splitting: Deques perform efficiently with insertions and deletions.
Refinements:

Functions for reading, sorting, splitting, and file writing tested across containers with speed analysis displayed on the console.
Final Release 1.0
Splitting Strategies:

Two-Container: Separates passed and failed students into distinct containers.
One-Container: Moves failed students to a new container, leaving passed students in the original.
One-container strategy is faster and memory-efficient.
Vector Optimization:
Utilizes algorithms like std::find_if and range-based construction for efficient operations.

Repository Cleanup:

Removes unnecessary files, retaining only source and include files.
Adds CMakeLists.txt and runMe.bat for streamlined compilation and execution.




                                                   Application User Guide
Setup and Installation:

Requires CMake compiler version 3.25 or higher.
Provided CMakeLists.txt outlines compilation requirements.
Running the Application:

Use runMe.bat for automatic compilation, installation, and execution. Alternatively, commands can be entered manually.
Runtime Options:

File Input:
Specify the file name (e.g., FileName.txt) and container type (vector, list, or deque).
Choose a splitting strategy (one-container or two-container).
Random Data Generation:
Input the desired file name and number of students; output is saved to a file.
Manual Data Entry:
Enter the number of students and their details, including names, exam scores, and homework data (manually or randomly).







                                                   Observations and Container Comparison
Reading Data:

Vector: Efficient with predictable data size but slower with frequent reallocations.
List: Handles large files well due to non-contiguous memory but uses more memory.
Deque: Similar to vector but handles reallocations more effectively.
Sorting Data:

Vector: Fastest for sorting with contiguous memory.
List: Optimized for linked structures but slower overall for large datasets.
Deque: Slightly slower than vector due to non-contiguous memory.
Splitting Data:

Vector: Memory-intensive but benefits from fast iteration.
List: Excels due to pointer-based element movement.
Deque: Efficient at ends but slower for middle operations.
File Writing:

Vector: Fast due to contiguous memory.
List: Slower due to traversal needs.
Deque: Comparable to vector but slower with non-contiguous data.
General Observations:

Efficiency: Vector excels in random access tasks; list is best for frequent insertions/deletions; deque balances both.
Memory Usage: Vector uses the least memory, list the most, and deque is moderate.
# Student Management System

A console-based student management system written in C. This system allows the management of student records, including adding, modifying, displaying, and removing students. It also includes functionality for managing attendance and securing access with password protection.

![Student Management System](https://via.placeholder.com/800x400.png?text=Student+Management+System)

## Features

- Add, modify, and remove student records
- Display all students or individual student records
- Secure system with password protection
- Search students by name
- Sort students by CGPA
- Manage and display attendance records
- Change system password

## Getting Started

### Prerequisites

- Windows operating system
- A C compiler (such as GCC)
- `conio.h` and `windows.h` libraries

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/anasraza524/student-management-system.git
    ```

2. Compile the code:

    ```bash
    gcc -o student_management_system main.c -lconio -lwindows
    ```

3. Run the executable:

    ```bash
    ./student_management_system
    ```

### Usage

1. When you run the program, you will be prompted to enter a password. The default password is stored in the `Password.txt` file.

2. Once logged in, you can choose from the following menu options:

    - `1. Add Student`: Add a new student record.
    - `2. Modify Student`: Modify an existing student record.
    - `3. Show All Students`: Display all student records.
    - `4. Individual View`: View a specific student record by roll number.
    - `5. Remove Student`: Remove a student record.
    - `6. Change Password`: Change the system password.
    - `7. Search Student by Name`: Search for a student by name.
    - `8. Sort Students by CGPA`: Sort and display students by CGPA.
    - `9. Add Attendance`: Add attendance records for students.
    - `10. Display Attendance`: Display all attendance records.
    - `11. Logout`: Exit the system.

## Code Overview

### Main Function

The `main` function initializes the system, prompts for the password, and displays the main menu.

### Functions

- `title()`: Displays the title of the system.
- `displayMenu()`: Displays the main menu.
- `isValidRoll(int roll)`: Validates the roll number.
- `isUniqueRoll(int roll, FILE *fp)`: Checks if the roll number is unique.
- `isValidSGPA(float sgpa)`: Validates the SGPA value.
- `encryptDecrypt(char *data)`: Encrypts or decrypts data using a simple XOR operation.
- `openFile(char *fileName, char *mode)`: Opens a file and handles errors.
- `safeFileWrite(const char *filename, const void *data, size_t size)`: Safely writes data to a file.
- `printChar(char ch, int n)`: Prints a character `n` times.
- `addStudent(FILE *fp)`: Adds a new student record.
- `modifyStudent(FILE *fp)`: Modifies an existing student record.
- `displayStudents(FILE *fp)`: Displays all student records.
- `individualView(FILE *fp)`: Displays a specific student record.
- `removeStudent(FILE *fp)`: Removes a student record.
- `changePassword()`: Changes the system password.
- `searchByName(FILE *fp)`: Searches for a student by name.
- `sortByCGPA(FILE *fp)`: Sorts students by CGPA.
- `addAttendance(FILE *fp)`: Adds attendance records.
- `displayAttendance()`: Displays all attendance records.


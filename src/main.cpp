#include "database.h"
#include "student.h"
#include <iostream>

void displayMenu() {
    std::cout << "\n===== Student Management System =====\n";
    std::cout << "1. Add New Student\n";
    std::cout << "2. View All Students\n";
    std::cout << "3. Search Student\n";
    std::cout << "4. Update Student Record\n";
    std::cout << "5. Delete Student\n";
    std::cout << "6. View Results\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter choice: ";
}

int main() {
    Database db("student_system.db");
    db.initializeSchema();
    StudentManager manager(db);

    int choice = 0;
    while (choice != 7) {
        displayMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid option! Please enter a numerical menu option.\n";
            continue;
        }

        switch (choice) {
            case 1: manager.addStudent(); break;
            case 2: manager.viewAllStudents(); break;
            case 3: manager.searchStudent(); break;
            case 4: manager.updateStudent(); break;
            case 5: manager.deleteStudent(); break;
            case 6: manager.viewResults(); break;
            case 7: std::cout << "Exiting program. Goodbye!\n"; break;
            default: std::cout << "Invalid choice! Please select 1-7.\n";
        }
    }
    return 0;
}

# Student Records Management System

A console-based Student Management System built in C++ with SQLite for data storage and a Python script for bulk CSV imports.

## About

This project manages student records and academic results through a simple command-line interface. It supports adding, viewing, searching, updating, and deleting student records, along with viewing individual academic report cards.

## Features

- Add new student records with input validation (email format, CGPA range, year range)
- View all students in a formatted table
- Search students by ID, name, or course
- Update existing student records (course/CGPA)
- Delete student records
- View academic results (subject-wise marks and grades) per student
- Bulk import students from a CSV file using a Python script

## Tech Stack

| Layer | Technology |
|---|---|
| Core Logic | C++ |
| Database | SQLite3 |
| Bulk Import | Python |
| Validation | Regex (C++ std::regex) |

## Project Structure

student-records-management-system/
- src/main.cpp
- src/student.h
- src/student.cpp
- src/database.h
- src/database.cpp
- src/validation.h
- src/validation.cpp
- scripts/data_import.py
- schema.sql
- README.md

## Database Schema

students — student_id, name, course, year, email (unique), cgpa, created_at

results — result_id, student_id (foreign key), subject, marks, grade

## Setup & Run

### Prerequisites
- g++ compiler
- SQLite3 development library installed
- Python 3 (only for bulk import)

### Compile and Run

g++ src/main.cpp src/student.cpp src/database.cpp src/validation.cpp -o sms -lsqlite3
./sms


## What I Learned

- Working with SQLite in C++ using prepared statements
- Writing input validation using regex
- Structuring a C++ project into separate header/source files
- Connecting Python scripts to the same SQLite database for batch operations

## Author

Atul Pandey
B.Tech Computer Science

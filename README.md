Library Management System (C++ | Linked Lists | Console-Based)

A console-based Library Management System implemented in C++ using linked lists and object-oriented programming. This project demonstrates dynamic data handling, searching, sorting, and transaction logging with timestamps.

Features
Book Management

Add new books

View all books

Search by title, author, or ISBN

Sort books by title or author

Track availability (Available / Issued)

User Management

Add new users

View all users

Search by name or ID

Transactions

Borrow a book

Return a book

Automatic transaction logging with timestamp, user ID, ISBN, and action

Data Structures

All modules (Books, Users, Transactions) implemented using singly linked lists

Supports insertion, traversal, searching, and node value swapping for sorting

Technologies Used

C++

Linked Lists

Object-Oriented Programming

ctime for timestamps

iomanip for formatted console output

Standard console-based interface

Project Structure
.
├── Book Class
├── User Class
├── Transaction Class
└── Library Class
      ├── Book Operations
      ├── User Operations
      ├── Transaction Logging
      ├── Search and Sort
      └── Menu and Program Control (main function)

How to Run

Clone the repository:

git clone https://github.com/your-username/library-management-system.git


Navigate into the project:

cd library-management-system


Compile:

g++ main.cpp -o library


Run:

./library

Menu Overview
1. Add Book
2. Add User
3. View All Books
4. View All Users
5. Borrow Book
6. Return Book
7. View Transactions
8. Search Book
9. Search User
10. Sort Books by Title
11. Sort Books by Author
0. Exit

Output Formatting

Formatted using iomanip:

setw() for alignment and column widths

left for text alignment

setfill() for separators

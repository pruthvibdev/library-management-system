# Library Management System

A simple console-based Library Management System developed in C++ using Object-Oriented Programming and file handling.

## What the Project Does

This program helps a small library manage its books and members. It can add books and members, issue and return books, and search for books using their title or author.

The records are saved in files so they are not lost when the program is closed.

## Features

- Add a new book
- Add a new member
- Issue a book to a member
- Return a book
- Search books by title or author
- View all books
- View all members
- Check whether a book is available or issued
- Prevent duplicate book IDs
- Prevent duplicate member IDs
- Save records automatically
- Load old records when the program starts
- Simple menu-driven interface

## C++ Concepts Used

- Classes and objects
- Encapsulation
- Constructors
- `vector`
- `string`
- File handling
- `ifstream` and `ofstream`
- Pointers
- Searching
- Input validation
- Functions
- Loops and `switch`

## Classes Used

### Book

The `Book` class stores the details of a book:

- Book ID
- Title
- Author
- Issue status
- Member who borrowed it

It also handles issuing, returning, displaying, saving, and loading book records.

### Member

The `Member` class stores:

- Member ID
- Member name

It handles saving and loading member information.

### Library

The `Library` class controls the complete application. It manages the book and member lists and provides all the menu operations.

## Data Files

The program automatically uses:

```text
books.txt
members.txt
```

These files are created in the same folder as the program and keep the records between different runs.

## Program Menu

```text
========================================
        LIBRARY MANAGEMENT SYSTEM
========================================
1. Add Book
2. Add Member
3. Issue Book
4. Return Book
5. Search Book
6. Show All Books
7. Show All Members
8. Exit
========================================
```

## How to Run

### Windows with MinGW

```bash
g++ library_management.cpp -o library_management.exe
library_management.exe
```

### Linux / macOS

```bash
g++ library_management.cpp -o library_management
./library_management
```

## Example

```text
Enter Book ID: 101
Enter Book Title: C++ Programming
Enter Author Name: Bjarne Stroustrup
Book added successfully.

Enter Member ID: 1001
Enter Member Name: Rahul
Member added successfully.

Enter Book ID: 101
Enter Member ID: 1001
Book issued successfully to Rahul.
```

## Assignment Requirements Covered

| Requirement | Implemented |
|---|---|
| Book details | Yes |
| Member details | Yes |
| Add books | Yes |
| Issue books | Yes |
| Return books | Yes |
| Search by title | Yes |
| Search by author | Yes |
| Structured/OOP programming | Yes |
| File handling | Yes |
| Menu-driven operations | Yes |

## Project Outcome

The application provides the basic operations required to manage books, members, and borrowing records in a small library through a simple console interface.

## Author

**Pruthvi Raj B**

Library Management System – C++

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;

class Book {
    int id, issuedTo;
    string title, author;
    bool issued;
public:
    Book() : id(0), issuedTo(0), issued(false) {}
    Book(int i, string t, string a) : id(i), issuedTo(0), title(t), author(a), issued(false) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isIssued() const { return issued; }

    void issue(int memberId) { issued = true; issuedTo = memberId; }
    void returnBook() { issued = false; issuedTo = 0; }

    void save(ofstream& f) const {
        f << id << '\n' << title << '\n' << author << '\n'
          << issued << '\n' << issuedTo << '\n';
    }

    bool load(ifstream& f) {
        if (!(f >> id)) return false;
        f.ignore(numeric_limits<streamsize>::max(), '\n');
        if (!getline(f, title) || !getline(f, author)) return false;
        if (!(f >> issued >> issuedTo)) return false;
        f.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    void display() const {
        cout << left << setw(8) << id << setw(30) << title
             << setw(25) << author << (issued ? "Issued" : "Available") << '\n';
    }
};

class Member {
    int id;
    string name;
public:
    Member() : id(0) {}
    Member(int i, string n) : id(i), name(n) {}

    int getId() const { return id; }
    string getName() const { return name; }

    void save(ofstream& f) const { f << id << '\n' << name << '\n'; }

    bool load(ifstream& f) {
        if (!(f >> id)) return false;
        f.ignore(numeric_limits<streamsize>::max(), '\n');
        return static_cast<bool>(getline(f, name));
    }
};

class LibrarySystem {
    vector<Book> books;
    vector<Member> members;
    const string bookFile = "books.txt";
    const string memberFile = "members.txt";

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int readInt(const string& prompt) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                clearInput();
                return value;
            }
            cout << "Invalid input. Enter a number.\n";
            clearInput();
        }
    }

    string readText(const string& prompt) {
        string text;
        cout << prompt;
        getline(cin, text);
        while (text.empty()) {
            cout << "This field cannot be empty. Try again: ";
            getline(cin, text);
        }
        return text;
    }

    Book* findBook(int id) {
        for (auto& b : books)
            if (b.getId() == id) return &b;
        return nullptr;
    }

    Member* findMember(int id) {
        for (auto& m : members)
            if (m.getId() == id) return &m;
        return nullptr;
    }

    string lower(string text) const {
        transform(text.begin(), text.end(), text.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });
        return text;
    }

    void loadData() {
        ifstream bf(bookFile);
        Book b;
        while (bf && b.load(bf)) books.push_back(b);

        ifstream mf(memberFile);
        Member m;
        while (mf && m.load(mf)) members.push_back(m);
    }

    void saveData() const {
        ofstream bf(bookFile);
        for (const auto& b : books) b.save(bf);

        ofstream mf(memberFile);
        for (const auto& m : members) m.save(mf);
    }

public:
    LibrarySystem() { loadData(); }
    ~LibrarySystem() { saveData(); }

    void addBook() {
        cout << "\n--- Add Book ---\n";
        int id = readInt("Enter Book ID: ");
        if (findBook(id)) {
            cout << "Book ID already exists.\n";
            return;
        }
        string title = readText("Enter Book Title: ");
        string author = readText("Enter Author Name: ");
        books.emplace_back(id, title, author);
        saveData();
        cout << "Book added successfully.\n";
    }

    void addMember() {
        cout << "\n--- Add Member ---\n";
        int id = readInt("Enter Member ID: ");
        if (findMember(id)) {
            cout << "Member ID already exists.\n";
            return;
        }
        string name = readText("Enter Member Name: ");
        members.emplace_back(id, name);
        saveData();
        cout << "Member added successfully.\n";
    }

    void issueBook() {
        int bookId = readInt("\nEnter Book ID: ");
        Book* book = findBook(bookId);
        if (!book) { cout << "Book not found.\n"; return; }
        if (book->isIssued()) { cout << "Book is already issued.\n"; return; }

        int memberId = readInt("Enter Member ID: ");
        Member* member = findMember(memberId);
        if (!member) { cout << "Member not found.\n"; return; }

        book->issue(memberId);
        saveData();
        cout << "Book issued successfully to " << member->getName() << ".\n";
    }

    void returnBook() {
        int id = readInt("\nEnter Book ID: ");
        Book* book = findBook(id);
        if (!book) { cout << "Book not found.\n"; return; }
        if (!book->isIssued()) { cout << "Book is not currently issued.\n"; return; }

        book->returnBook();
        saveData();
        cout << "Book returned successfully.\n";
    }

    void searchBook() const {
        string key = readText("\nEnter title or author to search: ");
        transform(key.begin(), key.end(), key.begin(),
                  [](unsigned char c) { return static_cast<char>(tolower(c)); });

        bool found = false;
        cout << "\n" << left << setw(8) << "ID" << setw(30) << "Title"
             << setw(25) << "Author" << "Status\n";
        cout << string(75, '-') << '\n';

        for (const auto& b : books) {
            string title = lower(b.getTitle());
            string author = lower(b.getAuthor());
            if (title.find(key) != string::npos || author.find(key) != string::npos) {
                b.display();
                found = true;
            }
        }
        if (!found) cout << "No matching books found.\n";
    }

    void listBooks() const {
        if (books.empty()) { cout << "\nNo books available.\n"; return; }

        cout << "\n" << left << setw(8) << "ID" << setw(30) << "Title"
             << setw(25) << "Author" << "Status\n";
        cout << string(75, '-') << '\n';
        for (const auto& b : books) b.display();
    }

    void listMembers() const {
        if (members.empty()) { cout << "\nNo members registered.\n"; return; }

        cout << "\n" << left << setw(12) << "Member ID" << "Name\n";
        cout << string(40, '-') << '\n';
        for (const auto& m : members)
            cout << left << setw(12) << m.getId() << m.getName() << '\n';
    }

    void run() {
        int choice;
        do {
            cout << "\n========================================\n"
                 << "        LIBRARY MANAGEMENT SYSTEM\n"
                 << "========================================\n"
                 << "1. Add Book\n2. Add Member\n3. Issue Book\n"
                 << "4. Return Book\n5. Search Book\n6. List All Books\n"
                 << "7. List All Members\n8. Exit\n"
                 << "========================================\n";

            choice = readInt("Enter your choice (1-8): ");

            switch (choice) {
                case 1: addBook(); break;
                case 2: addMember(); break;
                case 3: issueBook(); break;
                case 4: returnBook(); break;
                case 5: searchBook(); break;
                case 6: listBooks(); break;
                case 7: listMembers(); break;
                case 8: cout << "Thank you. Goodbye!\n"; break;
                default: cout << "Please select 1-8.\n";
            }
        } while (choice != 8);
    }
};

int main() {
    LibrarySystem library;
    library.run();
    return 0;
}

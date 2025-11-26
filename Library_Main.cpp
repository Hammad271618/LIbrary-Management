#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class Book {
public:
    string title, author, isbn;
    bool available;
    Book* next;

    Book(string t = "", string a = "", string i = "", bool av = true) {
        title = t;
        author = a;
        isbn = i;
        available = av;
        next = nullptr;
    }
};

class User {
public:
    int id;
    string name, contact;
    User* next;

    User(int i = 0, string n = "", string c = "") {
        id = i;
        name = n;
        contact = c;
        next = nullptr;
    }
};

class Transaction {
public:
    int userID;
    string isbn, action, timestamp;
    Transaction* next;

    Transaction(int u = 0, string i = "", string a = "") {
        userID = u;
        isbn = i;
        action = a;
        time_t now = time(0);
        timestamp = ctime(&now);
        next = nullptr;
    }
};

class Library {
    Book* bookHead;
    User* userHead;
    Transaction* transHead;

public:
    Library() {
        bookHead = nullptr;
        userHead = nullptr;
        transHead = nullptr;
    }

    void addBook() { 
        string title, author, isbn;
        cout << "\nEnter Book Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter ISBN: ";
        getline(cin, isbn);

        Book* newBook = new Book(title, author, isbn, true);

        if (!bookHead)
            bookHead = newBook;
        else {
            Book* temp = bookHead;
            while (temp->next)
                temp = temp->next;
            temp->next = newBook;
        }

        cout << "\n Book added successfully!\n";
    }

    void addUser() {
        int id;
        string name, contact;
        cout << "\nEnter User ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter User Name: ";
        getline(cin, name);
        cout << "Enter Contact: ";
        getline(cin, contact);

        User* newUser = new User(id, name, contact);

        if (!userHead)
            userHead = newUser;
        else {
            User* temp = userHead;
            while (temp->next)
                temp = temp->next;
            temp->next = newUser;
        }

        cout << "\n User added successfully!\n";
    }

    void viewAllBooks() {
        cout << "\n All Books:\n";
        cout << left << setw(25) << "Title" << setw(20) << "Author"
             << setw(15) << "ISBN" << setw(10) << "Status" << endl;
        cout << string(70, '-') << endl;

        Book* temp = bookHead;
        while (temp) {
            cout << left << setw(25) << temp->title
                 << setw(20) << temp->author
                 << setw(15) << temp->isbn
                 << setw(10) << (temp->available ? "Available" : "Issued") << endl;
            temp = temp->next;
        }

        cout << string(70, '-') << endl;
    }

    void viewAllUsers() {
        cout << "\n All Users:\n";
        cout << left << setw(10) << "ID" << setw(25) << "Name" << setw(20) << "Contact" << endl;
        cout << string(55, '-') << endl;

        User* temp = userHead;
        while (temp) {
            cout << left << setw(10) << temp->id
                 << setw(25) << temp->name
                 << setw(20) << temp->contact << endl;
            temp = temp->next;
        }

        cout << string(55, '-') << endl;
    }

    Book* findBook(string isbn) {
        Book* temp = bookHead;
        while (temp) {
            if (temp->isbn == isbn)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    User* findUser(int id) {
        User* temp = userHead;
        while (temp) {
            if (temp->id == id)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void borrowBook() {
        int id;
        string isbn;
        cout << "\nEnter User ID: ";
        cin >> id;
        cout << "Enter Book ISBN: ";
        cin >> isbn;

        User* user = findUser(id);
        Book* book = findBook(isbn);

        if (!user || !book) {
            cout << "\n Invalid User ID or ISBN.\n";
            return;
        }
        if (!book->available) {
            cout << "\n Book already issued.\n";
            return;
        }

        book->available = false;
        recordTransaction(id, isbn, "Borrowed");
        cout << "\n Book borrowed successfully!\n";
    }

    void returnBook() {
        int id;
        string isbn;
        cout << "\nEnter User ID: ";
        cin >> id;
        cout << "Enter Book ISBN: ";
        cin >> isbn;

        Book* book = findBook(isbn);
        if (!book) {
            cout << "\n Book not found.\n";
            return;
        }

        book->available = true;
        recordTransaction(id, isbn, "Returned");

        cout << "\n Book returned successfully!\n";
    }

    void recordTransaction(int userID, string isbn, string action) {
        Transaction* newTrans = new Transaction(userID, isbn, action);

        if (!transHead)
            transHead = newTrans;
        else {
            Transaction* temp = transHead;
            while (temp->next)
                temp = temp->next;
            temp->next = newTrans;
        }
    }

    void viewTransactions() {
        cout << "\n Transaction History:\n";
        cout << left << setw(10) << "UserID" << setw(15) << "ISBN"
             << setw(12) << "Action" << "Timestamp" << endl;
        cout << string(60, '-') << endl;

        Transaction* temp = transHead;
        while (temp) {
            cout << left << setw(10) << temp->userID << setw(15) << temp->isbn << setw(12) << temp->action << temp->timestamp;
            temp = temp->next;
        }

        cout << string(60, '-') << endl;
    }

    void searchBook() {
        string key;
        cout << "\nEnter Title/Author/ISBN to search: ";
        cin.ignore();
        getline(cin, key);

        Book* temp = bookHead;
        bool found = false;

        while (temp) {
            if (temp->title == key || temp->author == key || temp->isbn == key) {
                cout << "\nFound Book: " << temp->title << " | "<< temp->author << " | " << temp->isbn << " | "<< (temp->available ? "Available" : "Issued") << endl;
                found = true;
            }
            temp = temp->next;
        }

        if (!found)
            cout << "\n No matching book found.\n";
    }

    void searchUser() {
        cout << "\nEnter User Name or ID: ";
        string key;
        cin.ignore();
        getline(cin, key);

        bool found = false;
        User* temp = userHead;

        while (temp) {
            if (temp->name == key || to_string(temp->id) == key) {
                cout << "\nFound User: " << temp->id << " | "
                     << temp->name << " | " << temp->contact << endl;
                found = true;
            }
            temp = temp->next;
        }

        if (!found)
            cout << "\n No matching user found.\n";
    }

    void sortBooksByTitle()
    {
        if (!bookHead)
            return;

        for (Book *temp = bookHead; temp && temp->next; temp = temp->next){
            for (Book *temp2 = temp->next; temp2; temp2 = temp2->next){
                 if (temp->title > temp2->title)
                    swap(temp->title, temp2->title),
                    swap(temp->author, temp2->author),
                    swap(temp->isbn, temp2->isbn),
                    swap(temp->available, temp2->available);
            }
        }

        cout << "\n Books sorted by Title!\n";
    }

    void sortBooksByAuthor() {
        if (!bookHead)
            return;

        for (Book* temp = bookHead; temp && temp->next; temp = temp->next)
            for (Book* temp2 = temp->next; temp2; temp2 = temp2->next)
                if (temp->author > temp2->author)
                    swap(temp->title, temp2->title),
                    swap(temp->author, temp2->author),
                    swap(temp->isbn, temp2->isbn),
                    swap(temp->available, temp2->available);

        cout << "\n Books sorted by Author!\n";
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n==========  LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Book\n2. Add User\n3. View All Books\n4. View All Users\n";
        cout << "5. Borrow Book\n6. Return Book\n7. View Transactions\n";
        cout << "8. Search Book\n9. Search User\n10. Sort Books by Title\n11. Sort Books by Author\n";
        cout << "0. Exit\n";
        cout << "==============================================\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.addUser(); break;
            case 3: lib.viewAllBooks(); break;
            case 4: lib.viewAllUsers(); break;
            case 5: lib.borrowBook(); break;
            case 6: lib.returnBook(); break;
            case 7: lib.viewTransactions(); break;
            case 8: lib.searchBook(); break;
            case 9: lib.searchUser(); break;
            case 10: lib.sortBooksByTitle(); break;
            case 11: lib.sortBooksByAuthor(); break;
            case 0: cout << "\nExiting...\n"; break;
            default: cout << "\n Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
    
}

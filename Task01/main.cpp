
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Book {
private:
    string title;
    string author;
    int copies;

public:
    // Default constructor
    Book() : Book("Unknown", "Unknown", 0) {}

    // Overloaded constructor for title only
    explicit Book(string t) : Book(t, "Unknown", 1) {}

    // Parameterized constructor
    Book(string t, string a, int c)
        : title(t), author(a), copies(c) {

        if (c < 0) {
            throw invalid_argument(
                "Copies cannot be negative"
            );
        }
    }

    // Display book details
    void display() const {
        cout << "Title: " << title
             << ", Author: " << author
             << ", Copies: " << copies << '\n';
    }
};

int main() {
    cout << "LIBRARY BOOK RECORDS\n";

    // Default constructor
    Book b1;

    // Single parameter constructor
    Book b2("C++ Programming");

    // Parameterized constructor
    Book b3("Data Structures", "Mark Allen", 5);

    b1.display();
    b2.display();
    b3.display();

    // Test negative copies
    try {
        Book b4("Invalid Book", "Unknown", -2);
        b4.display();
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << '\n';
    }

    return 0;
}

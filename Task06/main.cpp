
#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
using namespace std;

class Text {
private:
    char* data;
    int length;

public:
    static int copyCount;

    // Constructor
    Text(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    // Copy constructor
    Text(const Text& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        copyCount++;
    }

    // Copy assignment operator
    Text& operator=(const Text& other) {
        if (this != &other) {
            char* newData = new char[other.length + 1];
            strcpy(newData, other.data);

            delete[] data;
            data = newData;
            length = other.length;
        }
        return *this;
    }

    // Destructor
    ~Text() {
        delete[] data;
    }

    // Concatenation operator
    Text operator+(const Text& other) const {
        string combined = string(data) + other.data;
        return Text(combined.c_str());
    }

    // Equality operator
    bool operator==(const Text& other) const {
        return strcmp(data, other.data) == 0;
    }

    // Not equal operator
    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    // Output operator
    friend ostream& operator<<(ostream& out, const Text& t) {
        out << t.data;
        return out;
    }
};

int Text::copyCount = 0;

int main() {
    cout << "===== TEXT CLASS TEST =====\n";

    Text a("Hello");
    Text b("World");

    cout << "Text A: " << a << endl;
    cout << "Text B: " << b << endl;

    cout << "\n===== CONCATENATION =====\n";

    Text c = a + b;
    cout << "A + B: " << c << endl;

    cout << "\n===== COMPARISON =====\n";

    Text x("Hello");
    Text y("Hello");
    Text z("Welcome");

    cout << "x == y: " << (x == y) << endl;
    cout << "x != z: " << (x != z) << endl;

    cout << "\n===== COPY CONSTRUCTOR =====\n";

    Text copied = a;
    cout << "Copied text: " << copied << endl;
    cout << "Copy constructor calls: " << Text::copyCount << endl;

    cout << "\n===== ASSIGNMENT =====\n";

    Text assigned;
    assigned = b;
    cout << "Assigned text: " << assigned << endl;

    // Self-assignment test
    assigned = assigned;
    cout << "After self-assignment: " << assigned << endl;

    cout << "\n===== EMPTY TEXT TEST =====\n";

    Text empty("");
    cout << "Empty text: [" << empty << "]" << endl;

    cout << "\n===== LONG TEXT TEST =====\n";

    Text longText("This is a long message used to test dynamic memory allocation in the Text class.");
    cout << longText << endl;

    cout << "\n===== a + b + c COPY TEST =====\n";

    Text::copyCount = 0;
    Text result = a + b + x;

    cout << "Result: " << result << endl;
    cout << "Copy constructor calls: " << Text::copyCount << endl;

    cout << "\n===== CONCATENATION PERFORMANCE =====\n";

    const int N = 100000;

    Text textResult("");
    Text piece("a");

    auto start1 = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        textResult = textResult + piece;
    }

    auto end1 = chrono::high_resolution_clock::now();

    cout << "Custom Text length: " << N << endl;
    cout << "Custom Text time: "
         << chrono::duration<double, milli>(end1 - start1).count()
         << " ms" << endl;

    string standardResult = "";

    auto start2 = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        standardResult = standardResult + "a";
    }

    auto end2 = chrono::high_resolution_clock::now();

    cout << "std::string length: " << standardResult.length() << endl;
    cout << "std::string time: "
         << chrono::duration<double, milli>(end2 - start2).count()
         << " ms" << endl;

    cout << "\n===== PROGRAM COMPLETED =====\n";

    return 0;
}

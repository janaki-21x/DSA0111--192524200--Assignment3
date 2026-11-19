
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0)
        : paise(rupees * 100 + p) {}

    // Addition operator
    Money operator+(const Money& m) const {
        Money result;
        result.paise = paise + m.paise;
        return result;
    }

    // Subtraction operator
    Money operator-(const Money& m) const {
        Money result;
        result.paise = paise - m.paise;
        return result;
    }

    // Addition assignment operator
    Money& operator+=(const Money& m) {
        paise += m.paise;
        return *this;
    }

    // Equality operator
    bool operator==(const Money& m) const {
        return paise == m.paise;
    }

    // Less than operator
    bool operator<(const Money& m) const {
        return paise < m.paise;
    }

    // Output stream operator
    friend ostream& operator<<(ostream& out, const Money& m) {
        long long amount = llabs(m.paise);

        if (m.paise < 0)
            out << "-";

        out << "Rs " << amount / 100 << "."
            << setw(2) << setfill('0') << amount % 100
            << setfill(' ');

        return out;
    }

    // Input stream operator
    friend istream& operator>>(istream& in, Money& m) {
        long long rupees;
        int p;
        in >> rupees >> p;
        m.paise = rupees * 100 + p;
        return in;
    }
};

int main() {
    Money a(120, 75), b(79, 25);

    cout << "===== MONEY CALCULATOR =====\n";

    Money c = a + b;
    cout << "Addition: " << c << endl;

    Money d = a - b;
    cout << "Subtraction: " << d << endl;

    a += b;
    cout << "Addition assignment: " << a << endl;

    cout << boolalpha;
    cout << "Equality: " << (a == Money(200)) << endl;
    cout << "Less than: " << (Money(50) < Money(100)) << endl;

    cout << "\n===== PAISE CARRY TEST =====\n";
    Money x(0, 75), y(0, 50);
    cout << "0.75 + 0.50 = " << x + y << endl;

    cout << "\n===== NEGATIVE SUBTRACTION TEST =====\n";
    Money p(50), q(100);
    cout << "50 - 100 = " << p - q << endl;

    cout << "\nProgram completed successfully.\n";

    return 0;
}

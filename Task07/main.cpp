
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    // Default constructor
    Complex() {
        real = 0;
        imag = 0;
    }

    // Constructor with real part only
    Complex(double r) {
        real = r;
        imag = 0;
    }

    // Constructor with real and imaginary parts
    Complex(double r, double i) {
        real = r;
        imag = i;
    }

    // Addition operator
    Complex operator+(const Complex& c) const {
        return Complex(real + c.real, imag + c.imag);
    }

    // Subtraction operator
    Complex operator-(const Complex& c) const {
        return Complex(real - c.real, imag - c.imag);
    }

    // Multiplication operator
    Complex operator*(const Complex& c) const {
        return Complex(
            real * c.real - imag * c.imag,
            real * c.imag + imag * c.real
        );
    }

    // Division operator
    Complex operator/(const Complex& c) const {
        double denominator = c.real * c.real + c.imag * c.imag;

        if (denominator == 0) {
            throw runtime_error("Division by zero impedance!");
        }

        return Complex(
            (real * c.real + imag * c.imag) / denominator,
            (imag * c.real - real * c.imag) / denominator
        );
    }

    // Equality operator
    bool operator==(const Complex& c) const {
        return real == c.real && imag == c.imag;
    }

    // Calculate magnitude
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }

    // Display operator
    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << fixed << setprecision(2)
            << c.real;

        if (c.imag >= 0)
            out << " + j" << c.imag;
        else
            out << " - j" << -c.imag;

        return out;
    }
};

// Calculate parallel impedance of two components
Complex parallel(const Complex& z1, const Complex& z2) {
    return (z1 * z2) / (z1 + z2);
}

int main() {
    cout << "===== COMPLEX NUMBER CLASS =====\n";

    Complex a;
    Complex b(10);
    Complex c(5, 3);

    cout << "Default constructor: " << a << endl;
    cout << "Real constructor: " << b << endl;
    cout << "Real and imaginary constructor: " << c << endl;

    cout << "\n===== OPERATOR TESTING =====\n";

    Complex x(8, 4);
    Complex y(2, 2);

    cout << "X = " << x << endl;
    cout << "Y = " << y << endl;

    cout << "Addition: " << x + y << endl;
    cout << "Subtraction: " << x - y << endl;
    cout << "Multiplication: " << x * y << endl;
    cout << "Division: " << x / y << endl;
    cout << "Equality: " << (x == y) << endl;

    cout << "\n===== MAGNITUDE =====\n";

    cout << "Magnitude of X: " << x.magnitude() << endl;

    cout << "\n===== AC CIRCUIT IMPEDANCE =====\n";

    double R = 10.0;
    double L = 0.1;
    double C = 100e-6;
    double frequency = 50.0;

    const double PI = 3.141592653589793;
    double omega = 2 * PI * frequency;

    // Individual RLC impedances
    Complex Zr(R, 0);
    Complex Zl(0, omega * L);
    Complex Zc(0, -1.0 / (omega * C));

    cout << "Resistance impedance: " << Zr << endl;
    cout << "Inductor impedance: " << Zl << endl;
    cout << "Capacitor impedance: " << Zc << endl;

    // Series RLC impedance
    Complex Zseries = Zr + Zl + Zc;

    cout << "\nSeries RLC impedance: " << Zseries << endl;
    cout << "Series magnitude: " << Zseries.magnitude() << endl;

    // Parallel RLC impedance
    Complex Zparallel = parallel(parallel(Zr, Zl), Zc);

    cout << "\nParallel RLC impedance: " << Zparallel << endl;
    cout << "Parallel magnitude: " << Zparallel.magnitude() << endl;

    cout << "\n===== DIVISION BY ZERO TEST =====\n";

    try {
        Complex zero(0, 0);
        Complex result = x / zero;
        cout << result << endl;
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\n===== PROGRAM COMPLETED =====\n";

    return 0;
}


#include <iostream>
#include <iomanip>
using namespace std;

class AuditoriumEvent {
private:
    int rows, seatsPerRow;
    bool **seatMap;
    int bookedSeats;

public:
    // Dynamic constructor
    AuditoriumEvent(int r, int s) {
        rows = r;
        seatsPerRow = s;
        bookedSeats = 0;

        seatMap = new bool*[rows];

        for (int i = 0; i < rows; i++) {
            seatMap[i] = new bool[seatsPerRow]();
        }

        cout << "Constructor: Event created ("
             << rows << " x " << seatsPerRow << ")" << endl;
    }

    // Book a seat
    void bookSeat(int r, int s) {
        if (r < 0 || r >= rows ||
            s < 0 || s >= seatsPerRow) {
            cout << "Invalid seat position!" << endl;
            return;
        }

        if (!seatMap[r][s]) {
            seatMap[r][s] = true;
            bookedSeats++;
            cout << "Seat (" << r + 1 << ","
                 << s + 1 << ") booked." << endl;
        } else {
            cout << "Seat already booked!" << endl;
        }
    }

    // Cancel a seat
    void cancelSeat(int r, int s) {
        if (r < 0 || r >= rows ||
            s < 0 || s >= seatsPerRow) {
            cout << "Invalid seat position!" << endl;
            return;
        }

        if (seatMap[r][s]) {
            seatMap[r][s] = false;
            bookedSeats--;
            cout << "Seat (" << r + 1 << ","
                 << s + 1 << ") cancelled." << endl;
        } else {
            cout << "Seat is not booked!" << endl;
        }
    }

    // Display seat map
    void display() {
        cout << "\nSeat Map (1 = Booked, 0 = Available)\n";

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < seatsPerRow; j++) {
                cout << seatMap[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Total booked seats: "
             << bookedSeats << endl;
    }

    // Calculate allocated memory
    void memoryUsage() {
        size_t bytes =
            rows * sizeof(bool*) +
            rows * seatsPerRow * sizeof(bool);

        cout << "Memory allocated: "
             << bytes << " bytes" << endl;
    }

    // Destructor
    ~AuditoriumEvent() {
        cout << "Destructor: Closing event. "
             << "Booked seats: " << bookedSeats << endl;

        for (int i = 0; i < rows; i++) {
            delete[] seatMap[i];
        }

        delete[] seatMap;

        cout << "Memory released successfully." << endl;
    }
};

int main() {

    cout << "===== STACK OBJECT =====\n";

    AuditoriumEvent event1(3, 4);
    event1.bookSeat(0, 0);
    event1.bookSeat(1, 2);
    event1.cancelSeat(0, 0);
    event1.display();
    event1.memoryUsage();

    cout << "\n===== BLOCK SCOPE OBJECT =====\n";

    {
        AuditoriumEvent event2(2, 3);
        event2.bookSeat(0, 1);
        event2.display();
    }

    cout << "\n===== HEAP OBJECT =====\n";

    AuditoriumEvent *event3 =
        new AuditoriumEvent(4, 5);

    event3->bookSeat(2, 3);
    event3->bookSeat(1, 1);
    event3->display();
    event3->memoryUsage();

    delete event3;

    cout << "\n===== MEMORY MEASUREMENT =====\n";

    AuditoriumEvent small(10, 20);
    small.memoryUsage();

    AuditoriumEvent medium(100, 200);
    medium.memoryUsage();

    AuditoriumEvent large(1000, 2000);
    large.memoryUsage();

    cout << "\nProgram completed successfully.\n";

    return 0;
}

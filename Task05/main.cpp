
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>
using namespace std;

class Time {
private:
    int hours, minutes, seconds;

    void normalize() {
        minutes += seconds / 60;
        seconds %= 60;

        hours += minutes / 60;
        minutes %= 60;
    }

public:
    Time(int h = 0, int m = 0, int s = 0)
        : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    // Prefix increment
    Time& operator++() {
        ++seconds;
        normalize();
        return *this;
    }

    // Postfix increment
    Time operator++(int) {
        Time old = *this;
        ++(*this);
        return old;
    }

    // Equality comparison
    bool operator==(const Time& other) const {
        return hours == other.hours &&
               minutes == other.minutes &&
               seconds == other.seconds;
    }

    // Less-than comparison
    bool operator<(const Time& other) const {
        if (hours != other.hours)
            return hours < other.hours;

        if (minutes != other.minutes)
            return minutes < other.minutes;

        return seconds < other.seconds;
    }

    friend ostream& operator<<(ostream& out, const Time& t) {
        out << t.hours << ":"
            << (t.minutes < 10 ? "0" : "") << t.minutes << ":"
            << (t.seconds < 10 ? "0" : "") << t.seconds;
        return out;
    }
};

class Playlist {
private:
    vector<string> tracks;

public:
    Playlist(vector<string> songs) : tracks(songs) {}

    // Non-const subscript operator
    string& operator[](int index) {
        if (index < 0 || index >= (int)tracks.size())
            throw out_of_range("Playlist index out of range");

        return tracks[index];
    }

    // Const subscript operator
    const string& operator[](int index) const {
        if (index < 0 || index >= (int)tracks.size())
            throw out_of_range("Playlist index out of range");

        return tracks[index];
    }

    int size() const {
        return tracks.size();
    }
};

int main() {
    cout << "===== TIME OPERATOR TEST =====\n";

    Time t(0, 0, 5);

    Time a = t++;
    Time b = ++t;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "Current time = " << t << endl;

    cout << "\n===== TIME COMPARISON =====\n";

    Time t1(1, 20, 30);
    Time t2(1, 20, 40);

    cout << "t1 = " << t1 << endl;
    cout << "t2 = " << t2 << endl;

    cout << "t1 == t2: " << (t1 == t2) << endl;
    cout << "t1 < t2: " << (t1 < t2) << endl;

    cout << "\n===== PLAYLIST TEST =====\n";

    Playlist playlist({
        "Shape of You",
        "Perfect",
        "Believer"
    });

    for (int i = 0; i < playlist.size(); i++) {
        cout << "Track " << i << ": " << playlist[i] << endl;
    }

    // Modify a track using non-const operator[]
    playlist[1] = "Night Changes";
    cout << "\nUpdated track 1: " << playlist[1] << endl;

    // Test const Playlist access
    const Playlist& constPlaylist = playlist;
    cout << "Const playlist track 0: "
         << constPlaylist[0] << endl;

    // Test invalid indexes
    cout << "\n===== RANGE CHECK TEST =====\n";

    try {
        cout << playlist[-1] << endl;
    } catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << playlist[playlist.size()] << endl;
    } catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Test minute and hour rollover
    cout << "\n===== TIME ROLLOVER TEST =====\n";

    Time rollover(0, 59, 59);
    cout << "Before increment: " << rollover << endl;
    ++rollover;
    cout << "After increment: " << rollover << endl;

    return 0;
}

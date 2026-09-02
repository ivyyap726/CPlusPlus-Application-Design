#include <iostream>
#include <limits>
using namespace std;

void addRecord() {
      cout << "Add Record selected." << endl;
}

void viewRecord() {
      cout << "View Record selected." << endl;
}

void searchRecord() {
      cout << "Search Record selected." << endl;
}

void viewSummary() {
      cout << "View Summary selected." << endl;
}

int main() {
      int choice = 0;
    bool running = true;

    cout << "Welcome to My Personal Budget Tracker!" << endl;

    while (running) {
        cout << endl;
        cout << "===== Main Menu =====" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. View Record" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. View Summary" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";

        cin >> choice;

        // If the user types something that is not a number, cin will fail.
        // This clears the error and skips the bad input so the program does not crash.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            continue;
        }

        switch (choice) {
case 1:
                addRecord();
                break;
case 2:
                viewRecord();
                break;
case 3:
                searchRecord();
                break;
case 4:
                viewSummary();
                break;
case 5:
                cout << "Exiting program. Goodbye!" << endl;
                running = false;
                break;
default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                break;
        }
    }

    system("pause>0");
    return 0;
}

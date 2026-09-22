#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include "BudgetTools.h"
using namespace std;

const int MAX_RECORDS = 10;
string transactionDate[MAX_RECORDS];
string category[MAX_RECORDS];
double amount[MAX_RECORDS];
int recordCount = 0;

void loadRecords() {
      ifstream inFile("personal_finance_data.csv");
    if (!inFile) {
        cout << "Could not open personal_finance_data.csv" << endl;
        return;
    }

    string line;
    getline(inFile, line); // skip header row

    while (getline(inFile, line) && recordCount < MAX_RECORDS) {
        stringstream ss(line);
        string dateStr, categoryStr, amountStr;

        getline(ss, dateStr, ',');
        getline(ss, categoryStr, ',');
        getline(ss, amountStr, ',');

        transactionDate[recordCount] = dateStr;
        category[recordCount] = categoryStr;
        amount[recordCount] = stod(amountStr);
        recordCount++;
    }

    inFile.close();
}

void addRecord() {
      if (recordCount >= MAX_RECORDS) {
        cout << "Record list is full. Cannot add more records." << endl;
        return;
      }

    string newDate, newCategory;
    double newAmount;

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> newDate;
    cout << "Enter category: ";
    cin >> newCategory;
    cout << "Enter amount: ";
    cin >> newAmount;

    transactionDate[recordCount] = newDate;
    category[recordCount] = newCategory;
    amount[recordCount] = newAmount;
    recordCount++;

    cout << "Record added!" << endl;
}

void viewRecord() {
      if (recordCount == 0) {
        cout << "No records to display." << endl;
        return;
      }

    double *amountPtr = &amount[0];

    for (int i = 0; i < recordCount; i++) {
        cout << transactionDate[i] << " | " << category[i] << " | $" << amount[i] << endl;
    }

    cout << "First transaction amount through pointer: $" << *amountPtr << endl;
}

void searchRecord() {
      cout << "Search Record selected." << endl;
}

void viewSummary() {
      double total = calculateTotal(amount, recordCount);
    cout << "Total of all transactions: $" << total << endl;
}

int main() {
      loadRecords();

    // Variables for the welcome screen
    string userName = "Jordan Lee";
    int userAge = 20;
    string userCollege = "Laney College";
    string appName = "Personal Budget Tracker";
    string appVersion = "1.0";

    int choice = 0;
    bool running = true;

    cout << "========================================" << endl;
    cout << "        Welcome to My Application" << endl;
    cout << "   " << appName << " (v" << appVersion << ")" << endl;
    cout << "========================================" << endl;
    cout << "User: " << userName << endl;
    cout << "Age: " << userAge << endl;
    cout << "College: " << userCollege << endl;
    cout << "========================================" << endl;

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

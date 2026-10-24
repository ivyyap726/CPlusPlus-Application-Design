#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include "BudgetTools.h"
using namespace std;

// Represents one budget entry (a date, a category, and an amount).
class Transaction {
private:
    int id;
    string date;
    string category;
    double amount;

public:
    Transaction(int transId, string transDate, string transCategory, double transAmount) {
        id = transId;
        date = transDate;
        category = transCategory;
        amount = transAmount;
    }

    void displayTransaction() {
        cout << "ID " << id << " | " << date << " | " << category << " | $" << amount << endl;
    }

    double getAmount() {
        return amount;
    }

    void setAmount(double newAmount) {
        amount = newAmount;
    }
};

// Base class for anyone using the program.
class User {
protected:
    string username;

public:
    User(string name) {
        username = name;
    }

    string getUsername() {
        return username;
    }
};

// Admins can add and delete records.
class Admin : public User {
public:
    Admin(string name) : User(name) {}
};

// Regular users can only view, search, and see the summary.
class RegularUser : public User {
public:
    RegularUser(string name) : User(name) {}
};

const int MAX_RECORDS = 10;
int transactionID[MAX_RECORDS];
string transactionDate[MAX_RECORDS];
string category[MAX_RECORDS];
double amount[MAX_RECORDS];
int recordCount = 0;
int nextID = 1;

// Prints the size (in bytes) of each data type used in this program.
void printDataSizes() {
    cout << "----- Data Type Sizes -----" << endl;
    cout << "int: " << sizeof(int) << " bytes" << endl;
    cout << "double: " << sizeof(double) << " bytes" << endl;
    cout << "char: " << sizeof(char) << " bytes" << endl;
    cout << "bool: " << sizeof(bool) << " bytes" << endl;
    cout << "string (object): " << sizeof(string) << " bytes" << endl;
    cout << "----------------------------" << endl;
}

// Reads all records from the data file into the arrays above.
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

        transactionID[recordCount] = nextID;
        transactionDate[recordCount] = dateStr;
        category[recordCount] = categoryStr;
        amount[recordCount] = stod(amountStr);
        nextID++;
        recordCount++;
    }

    inFile.close();
}

// Writes all current records back to the data file so changes are not lost.
void saveRecords() {
    ofstream outFile("personal_finance_data.csv");
    outFile << "Date,Category,Amount" << endl;

    for (int i = 0; i < recordCount; i++) {
        outFile << transactionDate[i] << "," << category[i] << "," << amount[i] << endl;
    }

    outFile.close();
}

// Checks that a date string is exactly in YYYY-MM-DD format.
bool isValidDate(string date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }

    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}

// Keeps asking until the user enters a valid positive amount.
double getValidAmount() {
    double value;

    while (true) {
        cout << "Enter amount: ";

        if (cin >> value && value > 0) {
            return value;
        }

        cout << "Invalid amount. Please enter a positive number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Adds a new record after validating the date, category, and amount.
void addRecord() {
    if (recordCount >= MAX_RECORDS) {
        cout << "Record list is full. Cannot add more records." << endl;
        return;
    }

    string newDate;
    bool validDate = false;
    while (!validDate) {
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> newDate;

        if (isValidDate(newDate)) {
            validDate = true;
        } else {
            cout << "Invalid date format. Please use YYYY-MM-DD." << endl;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline before getline

    string newCategory;
    bool validCategory = false;
    while (!validCategory) {
        cout << "Enter category: ";
        getline(cin, newCategory);

        if (!newCategory.empty()) {
            validCategory = true;
        } else {
            cout << "Category cannot be empty. Please try again." << endl;
        }
    }

    double newAmount = getValidAmount();

    transactionID[recordCount] = nextID;
    transactionDate[recordCount] = newDate;
    category[recordCount] = newCategory;
    amount[recordCount] = newAmount;
    nextID++;
    recordCount++;

    saveRecords();

    cout << "Record added with ID " << (nextID - 1) << "!" << endl;
}

// Displays every record using a Transaction object for each one.
void viewRecord() {
    if (recordCount == 0) {
        cout << "No records to display." << endl;
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        Transaction t(transactionID[i], transactionDate[i], category[i], amount[i]);
        t.displayTransaction();
    }

    // Pointer demonstration: access the first amount through a pointer.
    double *amountPtr = &amount[0];
    cout << "First transaction amount through pointer: $" << *amountPtr << endl;
}

// Binary search on the ID array. IDs are assigned in increasing order and
// never reordered, so the array stays sorted and this works directly.
int binarySearchByID(int data[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (data[mid] == target) return mid;
        if (data[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Looks up a single record by ID using binary search.
void searchRecord() {
    if (recordCount == 0) {
        cout << "No records to search." << endl;
        return;
    }

    int searchID;
    cout << "Enter the record ID to search for: ";
    cin >> searchID;

    int index = binarySearchByID(transactionID, recordCount, searchID);

    if (index == -1) {
        cout << "No record found with ID " << searchID << "." << endl;
    } else {
        Transaction t(transactionID[index], transactionDate[index], category[index], amount[index]);
        cout << "Record found:" << endl;
        t.displayTransaction();
    }
}

// Removes a record by ID (Admin only) and shifts the remaining records up.
void deleteRecord() {
    if (recordCount == 0) {
        cout << "No records to delete." << endl;
        return;
    }

    int deleteID;
    cout << "Enter the record ID to delete: ";
    cin >> deleteID;

    int index = binarySearchByID(transactionID, recordCount, deleteID);

    if (index == -1) {
        cout << "No record found with ID " << deleteID << "." << endl;
        return;
    }

    for (int i = index; i < recordCount - 1; i++) {
        transactionID[i] = transactionID[i + 1];
        transactionDate[i] = transactionDate[i + 1];
        category[i] = category[i + 1];
        amount[i] = amount[i + 1];
    }

    recordCount--;
    saveRecords();

    cout << "Record " << deleteID << " deleted." << endl;
}

// Adds up every amount using the helper in BudgetTools.
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

    cout << "========================================" << endl;
    cout << "        Welcome to My Application" << endl;
    cout << "   " << appName << " (v" << appVersion << ")" << endl;
    cout << "========================================" << endl;
    cout << "User: " << userName << endl;
    cout << "Age: " << userAge << endl;
    cout << "College: " << userCollege << endl;
    cout << "========================================" << endl;
    cout << endl;

    printDataSizes();

    // Ask who is using the program and create the matching role object.
    char roleChoice;
    bool isAdmin = false;

    cout << endl;
    cout << "Are you an Admin or a Regular User? (A/R): ";
    cin >> roleChoice;

    User* currentUser;
    if (roleChoice == 'A' || roleChoice == 'a') {
        currentUser = new Admin(userName);
        isAdmin = true;
        cout << "Logged in as Admin: " << currentUser->getUsername() << endl;
    } else {
        currentUser = new RegularUser(userName);
        isAdmin = false;
        cout << "Logged in as Regular User: " << currentUser->getUsername() << endl;
    }

    int choice = 0;
    bool running = true;

    while (running) {
        cout << endl;
        cout << "===== Main Menu =====" << endl;
        cout << "1. Add Record" << (isAdmin ? "" : " (Admin only)") << endl;
        cout << "2. View Record" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. View Summary" << endl;
        cout << "5. Delete Record" << (isAdmin ? "" : " (Admin only)") << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";

        cin >> choice;

        // If the user types something that is not a number, cin will fail.
        // This clears the error and skips the bad input so the program does not crash.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                if (isAdmin) {
                    addRecord();
                } else {
                    cout << "Access denied. Only an Admin can add records." << endl;
                }
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
                if (isAdmin) {
                    deleteRecord();
                } else {
                    cout << "Access denied. Only an Admin can delete records." << endl;
                }
                break;
            case 6:
                cout << "Exiting program. Goodbye!" << endl;
                running = false;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
                break;
        }
    }

    delete currentUser;
    return 0;
}

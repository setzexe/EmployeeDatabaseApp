#include "employee.hpp"
#include <fstream>
#include <iostream> 
#include <string>
#include <vector>
#include <cstdlib> 
using namespace std;

void fileFunctions::checkFile() { // Checks if the file exists. Creates it if otherwise.

    ofstream file("employees.txt", ios::app); // ofstream creates/writes to files. It will try to open
    // (or create, if it doesn't exist). app means it doesnt delete everything upon opening (by default, it does)

    if (file.is_open()) { // Checks if the file opened. !file.is_open() would check if closed
        cout << "Employee File loaded!\n" << endl; 
    } else {
        cerr << "File failed to open. Exiting program." << endl;
        exit(1); // Exits program with error code 1, which is general error
    }
    // ofstream goes out of scope, this function purely makes sure the file exists
    // if you wanted to write to it, you would need to add ofstream to each respective function
}

void EmployeeFunctions::loadEmployees(vector<Employee> &empList) { // Loads employees from file into the vector
    ifstream file("employees.txt"); // ifstream reads from files

    if (!file.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return; // exits function assuming file does not open
    }

    Employee emp;
    string line;
    while (getline(file, line)) { // Reads each line of the file
        size_t namePos = line.find("Name: "); // Searches for where "Name: " starts. Which is 0
        size_t pinPos = line.find("Pin: "); // This would purely be based on how long the name inputted is
        size_t positionPos = line.find("Position: ");
        size_t wagePos = line.find("Wage: ");

        if (namePos != string::npos && pinPos != string::npos && positionPos != string::npos && wagePos != string::npos) {
            // npos is a error constant used with find and similar functions that returns if nothing is found
            emp.name = line.substr(namePos + 6, pinPos - (namePos + 6) - 2);
            // the +(number) starts after the beginning text, and goes up until The end of name, aka The start of pin minus the . and space behind it 
            emp.pin = std::stoi(line.substr(pinPos + 5, positionPos - (pinPos + 5) - 2)); // Stoi turns the string output to an int
            emp.position = line.substr(positionPos + 10, wagePos - (positionPos + 10) - 2);
            emp.wage = std::stod(line.substr(wagePos + 6)); // Stod is stoi but double
            empList.push_back(emp); // Adds employee to the local memory list4

        }
    }

    file.close(); // Closes file
}

void EmployeeFunctions::registerEmployee(vector<Employee> &empList) { // Takes in a reference to the employee list vector) {
    ofstream file("employees.txt", ios::app); // Opens file in append mode

    if (!file.is_open()) {
        cerr << "Error opening file for writing." << endl; // cerr is standard output for errors
        return; // exits function assuming file does not open
    }

    Employee emp; // Emp goes away after its pushed into file and vector. There would be no purpose of iterating
    // It also automatically gets iterated (emmployees[0] = emp)
    cout << "Enter employee name: ";
    cin >> emp.name;
    cout << "Enter employee position (Programmer, Data Manager, Intern, Management): ";
    cin.ignore(); // ignores any whitespace that might mess up our input
    getline(cin, emp.position); // Incase you choose a position with spaces. cin just does one word;
    // wage will now be set by position
    if (emp.position == "Programmer") {
        emp.wage = 28.00;
    } else if (emp.position == "Data Manager") {
        emp.wage = 26.00;
    } else if (emp.position == "Intern") {
        emp.wage = 12.00;
    } else if (emp.position == "Management") {
        emp.wage = 36.00;
    } else { // default wage if position not recognized
        emp.wage = 15.00;
    }
    cout << "Enter employee PIN (numeric): ";
    cin >> emp.pin; 

    empList.push_back(emp); // Pushes emp into the vector

    file << "Name: " << emp.name << ". Pin: " << emp.pin << ". Position: " << emp.position << ". Wage: " << emp.wage << endl; // Writes to file
    file.close(); // Closes file, prevents leaks or errors
}

void EmployeeFunctions::employeeOptions(int pin, vector<Employee> &empList) {
    bool found = false;
    for (auto& emp : empList) { // Loop that does not modify EmpList. just reads it. Auto& means it takes the vector with its type (detectd automatically), no copy
        if (emp.pin == pin) { // If looped through and a pin matches
            found = true;
            cout << "Welcome, " << emp.name << "!" << endl;

            if (emp.position == "Management") {
                // placeholder for management options
            } else {
                bool condition = true;
                while (condition) {
                    cout << "\nWhat would you like to do today?" << endl; // Not many options now for phase 1
                    cout << "1. Change Pin" << endl;
                    cout << "2. View your information" << endl;

                    int choice;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            int newPin;
                            cout << "Enter your new PIN: ";
                            cin >> newPin;
                            if (newPin == emp.pin) { 
                                cout << "New PIN cannot be the same as the old PIN." << endl;
                            } else {
                                emp.pin = newPin; 
                                
                                ofstream file("employees.txt"); // rewriting the entire file with updated PIN. Note theres no append. No append = file overwrite
                                if (!file.is_open()) {
                                    cerr << "Error opening file for writing. Please check inside code." << endl;
                                    return;
                                }
                                for (const auto& e : empList) {
                                    file << "Name: " << e.name << ". Pin: " << e.pin << ". Position: " << e.position << ". Wage: " << e.wage << endl;
                                }
                                file.close();
                                pin = newPin; // Update current session pin
                                cout << "PIN changed successfully!" << endl;
                            }
                            cout << "PIN changed successfully!" << endl;
                            condition = false;
                            break;
                        }
                        case 2:
                            cout << "Employee's Name: " << emp.name << endl;
                            cout << "Employee's Position: " << emp.position << endl;
                            cout << "Employee's Wage: $" << emp.wage << " per hour" << endl;
                            condition = false;
                            break; 
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                }
            }

        }
    }
}
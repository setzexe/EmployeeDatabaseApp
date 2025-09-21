#include "employee.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::string;
using std::vector;  
using std::endl;

int main() {
    EmployeeFunctions empFuncs; // Because EmployeeFunctions is a class, we need to make an object of its type that allows us to access its functions
    fileFunctions fileFuncs; // Same logic as above but with files
    vector <Employee> employees; // employee list. This is for pulling information via local memory
    fileFuncs.checkFile(); // Automatically run first thing to ensure the file exists
    empFuncs.loadEmployees(employees); // Loads employees from file into a vector we can easily access

    int choice;
    cout << "Welcome to CyberSeverance. May the future hold bright." << endl;
        do {
            cout << "Please select your choice.\n" << endl;
            cout << "Choice 1: Register Employee" << endl;
            cout << "Choice 2: Employee Options" << endl;
            cout << "Choice 3: Employee Lists" << endl;
            cout << "Choice 4: Exit" << endl;
            cin >> choice;

        switch (choice) { 
            case 1:
                empFuncs.registerEmployee(employees);
                break;
            case 2:
                int pin;
                cout << "Enter your PIN: ";
                cin >> pin;
                empFuncs.employeeOptions(pin, employees);
                break;
            case 3:
                cout << "Lists feature coming soon" << endl;
                break;
            case 4:
                cout << "Farewell..." << endl;
                break;
            default:
                cout << "Invalid input. Try again." << endl;
        } 
    } while (choice != 4);

    return 0;
}

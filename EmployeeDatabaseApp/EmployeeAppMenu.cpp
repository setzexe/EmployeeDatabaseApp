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
    EmployeeFunctions empFuncs; 
    fileFunctions fileFuncs; 
    vector <Employee> employees; 
    fileFuncs.checkFile(); 
    empFuncs.loadEmployees(employees);

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
                empFuncs.listEmployees(employees);
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

#include "employee.hpp"
#include <fstream>
#include <iostream> 
#include <string>
#include <vector>
#include <cstdlib> 
using namespace std;
using std::cout;

void fileFunctions::checkFile() {

    ofstream file("employees.txt", ios::app); 

    if (file.is_open()) { 
        cout << "Employee File loaded!\n" << endl; 
    } else {
        cerr << "File failed to open. Exiting program." << endl;
        exit(1); 
    }
}

void EmployeeFunctions::loadEmployees(vector<Employee> &empList) { 
    ifstream file("employees.txt");

    if (!file.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return; 
    }

    Employee emp;
    string line;
    while (getline(file, line)) {
        size_t namePos = line.find("Name: ");
        size_t pinPos = line.find("Pin: ");
        size_t positionPos = line.find("Position: ");
        size_t wagePos = line.find("Wage: ");

        if (namePos != string::npos && pinPos != string::npos && positionPos != string::npos && wagePos != string::npos) {
            emp.name = line.substr(namePos + 6, pinPos - (namePos + 6) - 2);
            emp.pin = std::stoi(line.substr(pinPos + 5, positionPos - (pinPos + 5) - 2)); 
            emp.position = line.substr(positionPos + 10, wagePos - (positionPos + 10) - 2);
            emp.wage = std::stod(line.substr(wagePos + 6));
            empList.push_back(emp);

        }
    }

    file.close(); 
}

void EmployeeFunctions::registerEmployee(vector<Employee> &empList) {
    ofstream file("employees.txt", ios::app);

    if (!file.is_open()) {
        cerr << "Error opening file for writing." << endl; 
        return; 
    }

    Employee emp; 
    cout << "Enter employee name: ";
    cin >> emp.name;
    cout << "Enter employee position (Programmer, Data Manager, Intern, Management): ";
    cin.ignore(); 
    getline(cin, emp.position); 

    if (emp.position == "Programmer") {
        emp.wage = 28.00;
    } else if (emp.position == "Data Manager") {
        emp.wage = 26.00;
    } else if (emp.position == "Intern") {
        emp.wage = 12.00;
    } else if (emp.position == "Management") {
        emp.wage = 36.00;
    } else { 
        emp.wage = 15.00;
    }
    cout << "Enter employee PIN (numeric): ";
    cin >> emp.pin; 

    empList.push_back(emp);

    file << "Name: " << emp.name << ". Pin: " << emp.pin << ". Position: " << emp.position << ". Wage: " << emp.wage << endl; // Writes to file
    file.close(); // 
}

void EmployeeFunctions::employeeOptions(int pin, vector<Employee> &empList) {
    bool found = false;
    for (auto& emp : empList) { 
        if (emp.pin == pin) {
            found = true;
            cout << "Welcome, " << emp.name << "!" << endl;

            if (emp.position == "Management") {
                bool condition = true;
                while (condition) {
                    cout << "Welcome to the Manager Portal. What would you like to do today?" << endl;
                    cout << "1. Change Pin" << endl;
                    cout << "2. View your information" << endl;
                    cout << "3. Change employee position" << endl;
                    cout << "4. Delete employee" << endl;
                    cout << "5. Exit Manager Portal" << endl;
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
                                
                                ofstream file("employees.txt");
                                if (!file.is_open()) {
                                    cerr << "Error opening file for writing. Please check inside code." << endl;
                                    return;
                                }
                                for (const auto& e : empList) {
                                    file << "Name: " << e.name << ". Pin: " << e.pin << ". Position: " << e.position << ". Wage: " << e.wage << endl;
                                }
                                file.close();
                                pin = newPin;
                                cout << "PIN changed successfully!" << endl;
                            }
                            cout << "PIN changed successfully!" << endl;
                            condition = false;
                            break;
                        }
                        case 2: 
                            cout << "Manager's Name: " << emp.name << endl;
                            cout << "Manager's Wage: $" << emp.wage << " per hour" << endl;
                            cout << "Manager's Pin: " << emp.pin << endl;
                            condition = false;
                            break;
                        case 3: {
                            cout << "Enter the name of the employee whose position you want to change: ";
                            string inpEmpName;
                            cin.ignore();
                            cin >> inpEmpName;

                            for (auto& emp : empList) {
                                if (emp.name == inpEmpName) {
                                    cout << "Current position of " << emp.name << " is " << emp.position << endl;
                                    cout << "Enter new employee position (Programmer, Data Manager, Intern, Management): ";
                                    cin.ignore();
                                    string newPosition;
                                    getline(cin, newPosition);
                                    emp.position = newPosition;
                                    
                                    if (emp.position == "Programmer") {
                                        emp.wage = 28.00;
                                    } else if (emp.position == "Data Manager") {
                                        emp.wage = 26.00;
                                    } else if (emp.position == "Intern") {
                                        emp.wage = 12.00;
                                    } else if (emp.position == "Management") {
                                        emp.wage = 36.00;
                                    } else { 
                                        emp.wage = 15.00;
                                    }
                                    cout << "Entering information into file..." << endl;
                                }
                                
                            

                                ofstream file("employees.txt"); 
                                if (!file.is_open()) {
                                    cerr << "Error opening file for writing. Please check inside code." << endl;
                                    return;
                                }
                                for (const auto& e : empList) {
                                    file << "Name: " << e.name << ". Pin: " << e.pin << ". Position: " << e.position << ". Wage: " << e.wage << endl;
                                }
                                file.close();
                            }
                            cout << "Employee position changed!" << endl;
                            condition = false;
                            break;
                        }
                        case 4: {
                            string delEmpname;
                            cout << "Enter the name of the employee you want to delete: ";
                            cin.ignore();
                            cin >> delEmpname;

                            for (auto it = empList.begin(); it != empList.end(); ++it) {
                                if (it->name == delEmpname) {
                                    empList.erase(it);
                                    cout << "Employee " << delEmpname << " deleted." << endl;
                                    break;
                                }
                            }

                            ofstream file("employees.txt");
                            if (!file.is_open()) {
                                cerr << "Error opening file for writing. Please check inside code." << endl;
                                return;
                            }   
                            for (const auto& e : empList) {
                                file << "Name: " << e.name << ". Pin: " << e.pin << ". Position: " << e.position << ". Wage: " << e.wage << endl;
                            }
                            condition = false;
                            break;
                        }
                        case 5:
                            cout << "Exiting Manager Portal..." << endl;
                            condition = false;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                }
                break;
            } else {
                bool condition = true;
                while (condition) {
                    cout << "\nWhat would you like to do today?" << endl; 
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
                                
                                ofstream file("employees.txt"); 
                                if (!file.is_open()) {
                                    cerr << "Error opening file for writing. Please check inside code." << endl;
                                    return;
                                }
                                for (const auto& e : empList) {
                                    file << "Name: " << e.name << ". Pin: " << e.pin << ". Position: " << e.position << ". Wage: " << e.wage << endl;
                                }
                                file.close();
                                pin = newPin; 
                                cout << "PIN changed successfully!" << endl;
                            }
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

void EmployeeFunctions::listEmployees(const vector<Employee> &empList) {
    cout << "Employee List\n" << endl;

    cout << "Managers: " << endl;
    for (auto& emp : empList) {
        if (emp.position == "Management") {
            cout << "Manager name: " << emp.name << ", Wage: $" << emp.wage << " per hour" << endl;
        }
    }
    cout << "\nProgrammers: " << endl;
    for (auto& emp : empList) {
        if (emp.position == "Programmer") {
            cout << "Programmer name: " << emp.name << ", Wage: $" << emp.wage << " per hour" << endl;
        }
    }
    cout << "\nData Managers: " << endl;
    for (auto& emp : empList) {
        if (emp.position == "Data Manager") {
            cout << "Data Manager's name: " << emp.name << ", Wage: $" << emp.wage << " per hour" << endl;
        }
    }
    cout << "\nInterns: " << endl;
    for (auto& emp : empList) {
        if (emp.position == "Intern") {
            cout << "Intern name: " << emp.name << ", Wage: $" << emp.wage << " per hour" << endl;
        }
    }
    cout << "\nOther positions: " << endl;
    for (auto& emp : empList) {
        if ((emp.position != "Management") && (emp.position != "Intern") && (emp.position != "Data Manager") && (emp.position != "Programmer")) {
            cout << "Employee name: " << emp.name << ", Wage: $" << emp.wage << " per hour" << endl;
        }
    }
}

#ifndef EMP
#define EMP
#include <string>
#include <vector>
using std::string;
using std::vector;

struct Employee { // Similar to class objects. Stores multiple members under one name/variable
    string name; // Members can be different types
    int pin;
    string position;
    double wage;
}; // c++ is weird and needs a semicolon here. ONLY PUT STRUCT IN HEADER IF MODULAR

 
class EmployeeFunctions {
    private: 
        vector<Employee> empList;
    public:;
        void registerEmployee(vector<Employee> &empList);
        void employeeOptions(int pin, vector<Employee> &empList);
        void listEmployees(vector<Employee> &empList);
        void loadEmployees(vector<Employee> &empList);
};

class fileFunctions {
    public: 
        void checkFile();
        
};

#endif
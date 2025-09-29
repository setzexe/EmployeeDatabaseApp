#ifndef EMP
#define EMP
#include <string>
#include <vector>
using std::string;
using std::vector;

struct Employee { 
    string name;
    int pin;
    string position;
    double wage;
}; 

 
class EmployeeFunctions {
    private: 
        vector<Employee> empList;
    public:;
        void registerEmployee(vector<Employee> &empList);
        void employeeOptions(int pin, vector<Employee> &empList);
        void listEmployees(const vector<Employee> &empList);
        void loadEmployees(vector<Employee> &empList);
};

class fileFunctions {
    public: 
        void checkFile();
        
};

#endif
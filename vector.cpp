#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include <stdlib.h>

using namespace std;

class employee
{
   /* Employee class to contain employee data
   */
   
   private:
      string surname;
      double hourlyRate;
     int empNumber;
     
   public:
      employee() 
	  {
         hourlyRate = -1;
         empNumber = -1;
         surname = "";
      }
      
      employee(const employee &other) :
         surname(other.surname),
         hourlyRate(other.hourlyRate),
         empNumber(other.empNumber)
      {
         // copy constructor
      }
      
      void setEmployee(const string &name, double rate, int num) 
	  { 
         surname = name;
         hourlyRate = rate;
         empNumber = num;
      }
      
      const string& getSurname() const 
	  {
         return surname;
      }
      
      void printEmployee() const 
	  {
         cout << fixed << setprecision(2);
         cout << setw(20) << left << surname << setw(4) << empNumber << "  " << hourlyRate << "\n";
      }
      
      void loadEmployee(ifstream &fin) 
	  {
         fin >> surname;
         fin >> hourlyRate;
         fin >> empNumber;
      }
      
};
      
void swap(vector<employee> &employees, int a, int b);
void sortEmployees(vector<employee> &employees);
void printEmployees(const vector<employee> &employees);
void loadEmployees(vector<employee> &employees, const char *file);

int main(int argc, char *argv[])
{
   vector<employee> employees;

   if (argc != 2) 
   {
      cout << "Syntax : employee employeefile\n";
      return 0;
   }

   loadEmployees(employees, argv[1]);
   printEmployees(employees);
   sortEmployees(employees);
   printEmployees(employees);

   return 0;
}

void loadEmployees(vector<employee> &employees, const char *file)
{
   ifstream fin;
   employee emp;
   
   fin.open(file);
   if (!fin) 
   {
      cout << "Unable to read from " << file << "\n";
      exit(0);
   }
   
   while (!fin.eof()) 
   {
      emp.loadEmployee(fin);
      employees.push_back(emp);
   }
   fin.close();   
}

void printEmployees(const vector<employee> &employees)
{
   unsigned int i;

   for (i=0; i<employees.size(); i++) 
   {
      employees[i].printEmployee();
   }
   printf("\n");
}

void swap(vector<employee> &employees, int a, int b)
{
   employee temp(employees[a]);

   employees[a] = employees[b];
   employees[b] = temp;
}

void sortEmployees(vector<employee> &employees)
{
   /* use selection sort to order employees, 
      in employee name order
   */

   int number = employees.size();
   int inner, outer, max;

   for (outer=number-1; outer>0; outer--)
   {
      // run though array number of times
      max = 0;
      for (inner=1; inner<=outer; inner++)
      {
         // find alphabeticaly largest surname
         if (employees[inner].getSurname() > employees[max].getSurname())
            max = inner;
      }
      if (max != outer)
      {
         // swap largest with last element in array
         swap(employees, max, outer);
      }
   }
}

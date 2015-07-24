#include <iostream>
#include <iomanip>
#include <string>

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
      
      void printEmployee() const {
         cout << fixed << setprecision(2);
         cout << setw(20) << left << surname << setw(4) << empNumber << "  " << hourlyRate << "\n";
      }
};

void swap(employee employees[], int a, int b);
void sortEmployees(employee employees[], int number);
void printEmployees(employee employees[], int number);

int main()
{
   employee employees[5];

   employees[0].setEmployee("Stone", 35.75, 053);
   employees[1].setEmployee("Rubble", 12, 163);
   employees[2].setEmployee("Flintstone", 15.75, 97);
   employees[3].setEmployee("Pebble", 10.25, 104);
   employees[4].setEmployee("Rockwall", 22.75, 15);

   printEmployees(employees, 5);
   sortEmployees(employees, 5);
   printEmployees(employees, 5);

   return 0;
}

void printEmployees(employee employees[], int number)
{
   for (int i=0; i<number; i++) 
   {
      employees[i].printEmployee();
   }
   cout << "\n";
}

void swap(employee employees[], int a, int b)
{
   employee temp(employees[a]);

   employees[a] = employees[b];
   employees[b] = temp;
}

void sortEmployees(employee employees[], int number)
{
   /* use selection sort to order employees, 
      in employee name order
   */

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

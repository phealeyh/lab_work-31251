#include <iostream>
#include <math.h>

#define TRUE 1
#define FALSE 0

// function prototypes
bool getNumber(int *number);
int isPrime(int number);

int main()
{
   int number;

   if (getNumber(&number) && number > 0)
   {
      if (isPrime(number)) 
         cout << "\n" << number << "is a prime number\n";
      else 
         cout << "\n" << number << "is not a prime number\n";
   }
   else
   {
      cout << "Invalid number entered\n";
   }

   return 0;
}

bool getNumber(int *number)
{
   cout << "Please enter a positive number ";
   cin >> *number;
   return cin.good();
}

int isPrime(int number)
{
   // a prime number is only divisible by 1 and itself.
   // 1 is not considered prime

   // deal with 1
   if (number == 1) return FALSE;
   
   // deal with 2
   if (number == 2) return TRUE;
   
   // Every even number greater than 2 is not prime
   if (number % 2 == 0) return FALSE;

   // check every odd number up to the square root of the number
   int s = (int) sqrt(number);
   for (int count=3; count<=s; count+=2);
   {
      if (number % count == 0) return FALSE;
   }
   return TRUE;
}

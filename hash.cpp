#include <iostream>
#include "linhash.h"

/* Small program to explore using hash tables.

   1. The hash table takes up to 400 items
   2. The program generates 400 random six digit numbers.
   3. It uses a hashing routine to place them in the hash table.
   4. The program prints a report on the percantage of clashes that 
      occur for every 20 numbers placed in the table.
*/ 

using namespace std;

struct data
{
   int x;
   
   data() : x(-1) 
   {
   }
   
   data(int n) : x(n) 
   {
   }
   
   bool empty() 
   {
      return (x < 0);
   }
   
   int getHashval(int range) const 
   {
      return (x % range);
   }
};

int main()
{
   const int SIZE = 400;
   int count, totalClashes=0;
   int clashes = 0, numClashes;
   data *dataPtr;
   
   // declare linear hash table
   linHashtable<data> hashTable(SIZE);

   // initialise the random number generator
   srand(1);

   // generate 400 six digit numbers and put in hash table
   for (count=1; count<=SIZE; count++) 
   {
      // create 6 digit number and then insert in hash table
      dataPtr = new data(rand() % 1000000);    
      numClashes = hashTable.insert(*dataPtr);
      
      // build up hashing data
      if (numClashes > 0) 
	  {
         totalClashes += numClashes;
         clashes++;
      }
         
      // print a report with each set of 20 numbers added to table
      if ((count+1) % 20 == 0)
      {
         cout << "% full = " << (count+1) * 100 / SIZE << "\n";
         cout << "% clashing = " << clashes * 100 / (count+1) << "\n";
         cout << "ave search time = " << (count+1 + totalClashes) / (count+1) << "\n\n";
      }
   }

   return 0;
}

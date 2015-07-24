
/********************************************************\
   Test program for demonstrating sorting algorithms
\********************************************************/
#include <stdlib.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>

#include "dataobject.h"

using namespace std;

int randNum();

template <class iterator> 
   void sortContainer(iterator start, iterator finish, int gap);
   
template <class iterator> 
   double sortPercent(iterator start, iterator finish);


int randNum()
{
   // rand() produces pseudo-random number in range 0 to RAND_MAX
   // for most compilers RAND_MAX is 2^15-1
   // randNum() produces pseudo-random number in range 0 to 2^31-1
  
   return ((rand() << 16) + rand());
} 

template <class iterator> 
   double sortPercent(iterator start, iterator finish)
{
   /*************************************************************************\
      sortPercentage
      Checks every consecutive pair of items in the container, 
      eg, 1st and 2nd, 2nd and 3rd, 3rd and 4th ... to ... 2nd last and last
      and finds the percentage that are in order vs the total number of pairs.
      This percentage value is returned.
   \*************************************************************************/

   int order=0, size=0;
   iterator next = start;
   next++;
   
   while (next != finish) 
   {
      if (*start < *next) order++;
      size++;
      next++;
      start++;
   }
   if (size == 0) return 100.0;
   return (order * 100.0 / size);
}
  
template <class iterator> 
   void sortContainer(iterator start, iterator finish, int gap)
{
   /****************************************************************\
       Sort the container using shell sort
       gap will be called with the original size of the container
       The underlying sort for the container is bubble sort which
       will be run twice for each gap decrement
   \****************************************************************/

   if (gap == 1) return;
   
   iterator left, right;
   int i, numswap, totswap=0, numpass;
   
   gap = gap * 3 / 4;
   do 
   {
      numswap = 0;
      
      // Reduce gap. Gap will start out at half the size of the container
      // Eventually will stabilize at 1 in size
      gap = (gap * 2 + 1) / 3; 
      
      // make two passes through container with bubble sort
      for (numpass=0; numpass<2; numpass++) 
	  {
         right = left = start;
         // Make the distance between left and right gap in size
         for (i=0; i<gap; i++) right++;
         
         // Make a pass through container using Bubble sort
         while (right != finish) 
		 {
            if (*left > *right) 
			{
               swap(*left, *right);
               numswap++;
            }
            left++;
            right++;
         }
      
         // update some statistics and print them
         totswap += numswap;
         cout << "gap = " << gap << " num swaps = " << numswap;
         cout << " sort percentage = " << sortPercent(start, finish) << "\n";
         
         if (numswap == 0) break;
      }
   } while (numswap > 0 || gap > 1);
   
   cout << "Total swaps = " << totswap << "\n";
}

int main(int argc, char *argv[])
{
   const int MAXDATA = 10000;
   vector<dataObject> array;
   dataObject *doPtr;
   int i, rand;
   
   try 
   {
      /**************************************************************\
         Initialise things to demonstrate the sort
      \**************************************************************/
      
      // fill vector with unique values
      for (i=0; i<MAXDATA; i++) 
	  {
         doPtr = new dataObject(i);
         array.push_back(*doPtr);
         delete doPtr;
      }
      
      // set up random number generator
      if (argc != 2) 
	  {
         cout << "Syntax : program seed\n";
         cout << "seed is any integer value\n";
         return 0;
      }
      int seed = atoi(argv[1]);
      srand(seed);
      
      // scramble vector
      for (i=0; i<MAXDATA; i++) 
	  {
         rand = randNum() % MAXDATA;
         swap(array[i], array[rand]);
      }
      cout << MAXDATA << " Items in vector\n";
      
      /*************************************************************\
         sort the vector using iterators 
      \*************************************************************/
      
      cout << "Sorting vector using shell sort\n";
      sortContainer(array.begin(), array.end(), array.size());
      
   } 
   catch(...) 
   {
      cout << "\nERROR - undefined Exception thrown\n";
      exit(1);
   }
   
   return 0;
}

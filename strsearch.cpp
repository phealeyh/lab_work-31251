
/********************************************************\
   Test program for demonstrating sorting algorithms
\********************************************************/
#include <stdlib.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>

using namespace std;

int randNum();

template <class iterator> 
   bool containerSame(iterator s1Begin, iterator s1End,
                      iterator s2Begin, iterator s2End);

template <class iterator> 
   int stringSearch(iterator baseBegin, iterator baseEnd,
                    iterator searchBegin, iterator seachEnd);

int randNum()
{
   // rand() produces pseudo-random number in range 0 to RAND_MAX
   // for most compilers RAND_MAX is 2^15-1
   // randNum() produces pseudo-random number in range 0 to 2^31-1
  
   return ((rand() << 16) + rand());
} 

template <class iterator> 
   bool containerSame(iterator s1Begin, iterator s1End,
                      iterator s2Begin, iterator s2End)
{
   // is the container from s1Begin to s1End the same as the
   // container s2Begin to s2End?
   
   for (; s1Begin != s1End && s2Begin != s2End; s1Begin++, s2Begin++) 
   {
      if (*s1Begin != *s2Begin) return false;
   }
   return (s1Begin == s1End && s2Begin == s2End);
}

template <class iterator> 
   int stringSearch(iterator baseBegin, iterator baseEnd,
                    iterator searchBegin, iterator searchEnd)
{
   /****************************************************************\
       Search the container using Rabin-Karp algorithm
       Return location in base container as an integer
       Return -1 if not found
   \****************************************************************/

   const int Q = 33554393;
   const int D = 32;
   
   unsigned int i, hashs=0, hashb=0, ds=1;
   iterator bitr, sitr;
   
   // create hash of search string and 
   // equivalent number of chars in base string
   bitr = baseBegin;
   sitr = searchBegin;
   for (; sitr != searchEnd && bitr != baseEnd; bitr++, sitr++) 
   {
      hashb = (hashb*D + *bitr) % Q; 
      hashs = (hashs*D + *sitr) % Q; 
   }
   
   if (bitr == baseEnd) 
   {
      // base string must be <= search string in size
      if (sitr != searchEnd) 
	  {
         // base string smaller that search string
         return -1;
      }
      else 
	  {
         // base string and search string same size
         if (hashb == hashs) 
		 {
            // hashes are same but are the strings the same?
            if (containerSame(baseBegin, baseEnd, searchBegin, searchEnd))
               // search string found starting location 0 in base
               return 0;
            else
               return -1;
         }
         else 
		 {
            return -1;
         }
      }
   }
   
   // calculate Q - ((D ^ (slen-1)) mod Q)
   // set bitr to the element after search in base string
   sitr = searchBegin;
   sitr++;
   for (; sitr != searchEnd; sitr++) ds = (ds*D) % Q;
   ds = Q-ds;
   
   // set bitr pointing to element in base about to be added 
   // set sitr pointing to element in base about to be removed
   for (sitr = searchBegin, bitr = baseBegin; sitr != searchEnd; sitr++, bitr++);
   sitr = baseBegin;
   
   // run the rabin-karp search
   for (i=0; bitr != baseEnd; sitr++, bitr++, i++)
   {  
      if (hashs == hashb) 
	  {
         // confirm search string has been found
         if (containerSame(sitr, bitr, searchBegin, searchEnd)) return i;
      }
      
      // remove left most char
      hashb = (hashb + (*sitr)*ds) % Q;
      // add new right char
      hashb = (hashb*D + *bitr) % Q;
   }
   
   if (hashs == hashb) 
   {
      // confirm search string has been found
      if (containerSame(sitr, bitr, searchBegin, searchEnd)) return i;
   }
   return -1;
}

int main(int argc, char *argv[])
{
   const int MAXDATA = 10000;
   vector<char> baseArray;
   vector<char> searchArray;
   int i;
   
   try 
   {
      /**************************************************************\
         Initialise things to demonstrate the string search
      \**************************************************************/
      
      // set up random number generator
      if (argc != 2) 
	  {
         cout << "Syntax : program seed\n";
         cout << "seed is any integer value\n";
         return 0;
      }
      int seed = atoi(argv[1]);
      srand(seed);
      
      // fill the base vector with a's
      for (i=0; i<MAXDATA; i++) baseArray.push_back('a');
      
      // insert into the base vector with some b's 
      // decrease frequency of b's towards end of vector
      for (i=0; i<MAXDATA; i++) 
	  {
         if ((randNum() % (i/200+2)) == 0) baseArray[i] = 'b';
      }
      
      // setup search vector with all a's except last is b
      for (i=0; i<MAXDATA/100; i++) searchArray.push_back('a');
      searchArray.push_back('b');
      
      /*************************************************************\
         search the vector using iterators 
      \*************************************************************/
      
      cout << MAXDATA << " Items in vector\n";
      cout << "Searching vector using Rabin-Karp algorithm\n";
      i  = stringSearch(baseArray.begin(), baseArray.end(),
                        searchArray.begin(), searchArray.end());
      cout << "Search string found at location " << i << " in base\n";
      
   } 
   catch(...) 
   {
      cout << "\nERROR - undefined Exception thrown\n";
      exit(1);
   }
   
   return 0;
}

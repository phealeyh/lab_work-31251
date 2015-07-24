#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>

#include "dlist.h"
#include "person.h"

#include <stdlib.h>

using namespace std;

void sortFamily(dlist<person> &family);
void printFamily(const dlist<person> &family);
void loadFamily(dlist<person> &family, const char *file);

int main(int argc, char *argv[])
{
   dlist<person> family;

   if (argc != 2) 
   {
      cout << "Syntax : family familyFile\n";
      return 0;
   }

   loadFamily(family, argv[1]);
   printFamily(family);
   sortFamily(family);
   printFamily(family);

   return 0;
}

void loadFamily(dlist<person> &family, const char *file)
{
   ifstream fin;
   person member;
   
   fin.open(file);
   if (!fin) 
   {
      cout << "Unable to read from " << file << "\n";
      exit(0);
   }
   
   while (!fin.eof()) 
   {
      if (member.loadPerson(fin)) 
	  {
         family.push_back(member);
      }
   }
   fin.close();   
}

void printFamily(const dlist<person> &family)
{
   dlistConstIter<person> itr = family.begin();

   for (; itr != family.end(); itr++) 
   {
      itr->printPerson();
   }
   cout << "\n";
}

void sortFamily(dlist<person> &family)
{
   /* use insertion sort to order family, 
      in person name order
   */

   dlistIterator<person> outer = family.begin(), first, second;
   outer++;
   
   while (outer != family.end()) 
   {
      second = first = outer;
      second--;
      while (second != family.begin()) 
	  {
         if (first->getSurname() < second->getSurname()) 
		 {
            first->swap(*second);
            first--;
            second--;
         }
         else 
		 {
            break;
         }
      }
      // sort 1st and 2nd item in list
      if (first->getSurname() < second->getSurname()) 
	  {
         first->swap(*second);
      }
      outer++;
   }
}

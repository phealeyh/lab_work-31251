#include <iostream>
#include <vector>

using namespace std;

void binarySearch(const vector<int> &numbers, int value);
void linearSearch(const vector<int> &numbers, int value);

int main()
{
   vector<int> numbers;
  
   for (int i=0; i<16; i++) numbers.push_back(i);

   cout << "Searching for -1 in numbers using linear search\n";
   linearSearch(numbers, -1);
   cout << "Searching for -1 in numbers using binary search\n";
   binarySearch(numbers, -1);

   cout << "\nSearching for 0 in numbers using linear search\n";
   linearSearch(numbers, 0);
   cout << "Searching for 0 in numbers using binary search\n";
   binarySearch(numbers, 0);

   cout << "\nSearching for 7 in numbers using linear search\n";
   linearSearch(numbers, 7);
   cout << "Searching for 7 in numbers using binary search\n";
   binarySearch(numbers, 7);

   cout << "\nSearching for 11 in numbers using linear search\n";
   linearSearch(numbers, 11);
   cout << "Searching for 11 in numbers using binary search\n";
   binarySearch(numbers, 11);

   cout << "\nSearching for 15 in numbers using linear search\n";
   linearSearch(numbers, 15);
   cout << "Searching for 15 in numbers using binary search\n";
   binarySearch(numbers, 15);

   cout << "\nSearching for 22 in numbers using linear search\n";
   linearSearch(numbers, 22);
   cout << "Searching for 22 in numbers using binary search\n";
   binarySearch(numbers, 22);

   return 0;
}

void binarySearch(const vector<int> &numbers, int value)
{
   int step = 1, left = 0, right = numbers.size()-1, mid;

   while (left <= right)
   {
      mid = (left + right) / 2;
      if (numbers[mid] == value)
      {
         cout << "Number found after " << step << " steps\n";
         return;
      }
      else if (numbers[mid] < value)
         left = mid+1;
      else
         right = mid-1;
      step++;
   }
   cout << "Number not found after " << step << " steps\n";
}

void linearSearch(const vector<int> &numbers, int value)
{
   unsigned int index;

   for (index = 0; index<numbers.size(); index++)
   {
      if (numbers[index] == value)
      {
         cout << "Number found after " << index+1 << " steps\n";
         return;
      }
   }
   cout << "Number not found after " << index << " steps\n";
}



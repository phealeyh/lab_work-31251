#include <iostream>

#include "bintree.h"

using namespace std;

/* Small program to explore using binary trees.
   The program fills a tree with number in the order 1 to 16;
   It then prints some statistics about the tree
   It then rebalances the tree calling the rebalance function
   of bintree and then reprints the stats.
   
   Can you figure out what this tree looks like when first constructed?
   Can you figure out what balance value it could have if properly
   balanced?
*/ 

void fillTree(bintree<int> &treeRoot);
void printTreeStats(const bintree<int> &treeRoot);

int main()
{
   bintree<int> treeRoot;

   fillTree(treeRoot);
   printTreeStats(treeRoot);
   treeRoot.rebalance();
   printTreeStats(treeRoot);

   return 0;
}

void fillTree(bintree<int> &treeRoot)
{
   int *ptr;
   
   for (int i=1; i<16; i++) 
   {
      ptr = new int(i);
      treeRoot.insert(*ptr);
   }
}

void printTreeStats(const bintree<int> &treeRoot)
{
   cout << "Num nodes      = " << treeRoot.size() << "\n";
   cout << "Max tree depth = " << treeRoot.maxTreeDepth() << "\n";
   cout << "Num leaf nodes = " << treeRoot.numLeafNodes() << "\n";
   cout << "Tree balance   = " << treeRoot.balance() << "\n";
   
   printf("\n");
}

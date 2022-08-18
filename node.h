//file node.h
#ifndef NODE_H
#define NODE_H

struct node_t // Declares a struct data type and its members.
{
   char key[10][25]; // 2D array to hold value of nodes. Each row is a new word length. Each column a new word.
   struct node_t *left;
   struct node_t *right;
   int wordCount;
   int wordLength;
};

#endif /* NODE_H_ */

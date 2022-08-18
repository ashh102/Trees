//file tree.h
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printPreorder(struct node_t*, FILE*, int level);
void printInorder(struct node_t*, FILE*, int level);
void printPostorder(struct node_t*, FILE*, int level);

struct node_t* buildTree(FILE* filePointer, struct node_t *root);
struct node_t* insertNode(struct node_t*, char data[]);
struct node_t* newNode(char[], int);

#endif /* TREE_H */

#include "node.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Function that takes a file pointer and root node to build a search tree from the data in the file being pointed to. */
struct node_t* buildTree(FILE* filePointer , struct node_t *root)
{
  const int ARRAYSIZE = 15;
  char data[ARRAYSIZE];
  struct node_t *node;

  while (fscanf(filePointer,"%s",data) != EOF) //Continue to read from file until EOF token is found.
  {
   if(root == NULL) //If root has no child nodes then create the nodes and insert the current word being read.
   {
    root = insertNode ( root , data );
    node = root;
   }
   else  //If root has child nodes then insert current word being read into appropriate node.
	node = insertNode(node,data);
  }
  return root;
}

/*Function that takes the BST's root node and prints the inorder traversal with levels to the filename passed. */
void printInorder(struct node_t *root, FILE* filename, int level)
{
  int i;

  if(root == NULL)
   return;

  printInorder(root->left, filename, level + 1); //Recursive call to traverse the left nodes and print to filename with levels.

  fprintf(filename,"%*c%d: ",level*2,' ',root->wordLength); //Prints indentation of each line by 2X node depth to filename.

  for (i = 0; i < root->wordCount; i++) // loop to print each word in the current node.
  {
   fprintf (filename,"%s ",root->key[i]);
  }

  fprintf(filename, "\n");
  printInorder(root->right,filename,level + 1);
}

/*Function that takes the BST's root node and prints the preorder traversal with levels to the filename passed. */
void printPreorder(struct node_t *root, FILE* filename, int level)
{
  int i;

  if (root == NULL)
   return;

  fprintf(filename,"%*c%d: ",level*2,' ',root->wordLength); //Prints indentation of each line by 2X node depth.

  for (i = 0; i < root->wordCount; i++) // loop to print each word in the current node.
  {
   fprintf ( filename, "%s ", root->key [ i ] );
  }

  fprintf (filename,"\n");

  //Traverses the tree to the left then to the right and prints data to filename with levels.
  printPreorder(root->left,filename,level + 1);
  printPreorder(root->right,filename,level + 1);
}

/*Function that takes the BST's root node and prints the Postorder traversal with levels to the filename passed. */
void printPostorder(struct node_t *root, FILE* filename, int level)
{
  int i;

  if (root == NULL)
   return;

  //Traverses the tree to the left then to the right and prints data to filename with levels.
  printPostorder(root->left,filename,level + 1);
  printPostorder(root->right,filename,level + 1);

  fprintf(filename,"%*c%d: ",level*2,' ',root->wordLength); //Prints indentation of each line by 2X node depth.

  for (i = 0; i < root->wordCount; i++) // loop to print each word in the current node.
  {
   fprintf(filename,"%s ",root->key[i]);
  }
  fprintf(filename,"\n");
}

/*When a new word length is found, this function creates a new node, creates its child nodes,
*sets the nodes current word count, length, and inserts the word.*/
struct node_t *newNode(char word[],int length)
{
  struct node_t *temp = (struct node_t *)malloc(sizeof(struct node_t)); // Allocates memory for variable "temp".

  strcpy(temp->key[0],word);
  temp->left = temp->right = NULL; //setting right and left child nodes to null.
  temp->wordCount = 1;
  temp->wordLength = length;

  return temp;
}

//This function takes the current word or data from the command line and inserts it into the node being passed.
struct node_t* insertNode ( struct node_t* node , char data[] )
{
  int length;
  length = strlen(data);
  int i;
  int flag = 0;

  if(node == NULL) //If tree is empty create new node else find correct node to insert data.
  {
   return ( newNode(data, length));
  }

  else //Compare data to current node data. Insert in left node if word length is less, right if greater.
  {
   if(length < node->wordLength)
   {
	node->left = insertNode(node->left,data);
   }
   else if(length > node->wordLength)
    node->right = insertNode ( node->right , data );

   else if(node->wordLength == length) //If words are same length check for duplicates.
   {
    for (i = 0; i < node->wordCount; i++) //Loop to iterate through every word currently in node and compare with data.
	{
	 if(strcmp(node->key[i], data)== 0)
	 flag = 1;
	}

    if(flag == 0) //If no duplicates were found insert data else skip current word.
	{
	 strcpy(node->key[node->wordCount],data);
	 node->wordCount = node->wordCount + 1;
	}
   }
  }
  return node;
}


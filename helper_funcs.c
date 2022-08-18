#include "node.h"
#include "helper_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function that takes a string and checks for the correct file extension .sp19*/
int isCorrectExtension(char *string)
{
  char *extension = malloc(sizeof(char) * strlen(string)); //Allocates memory size of char * string length for variable extension.
  int i, k = 0;

  for (i = strlen(string) - 5; i < strlen(string) + 1; i++) //Loop that copies last 5 chars of string passed in.
  {
   extension[k] = string[i];
   k++;
  }

  if (strcmp(extension, ".sp19") == 0) //If last 5 chars of string = .sp19 return true else return false.
  {
   return 0;
  }
  else
   return 1;
}

/* Function to take filename on command line and append the correct extension to it.*/
char *concat( const char *s1, const char *s2 )
  {
   char* filename = malloc ( sizeof ( char ) * 25 );
   sprintf ( filename, "%s%s", s1, s2 ); // creates new file name by adding s2 to the end of s1 in filename.
   return filename;
  }

/* Function that takes 2 strings, gets the name of the first string and appends the 2 string to it.
  Assuming first string is a filename and 2 string is a file extension.*/
char *get_fileName(char* fileName, char* extension)
{

  char *newFileName = (char* )malloc (sizeof(char) * 25); //Allocates memory size of char * 25 for variable "newFilename".
  int i;

  memset ( newFileName, '\0', 25 * sizeof ( char ) );

  for( i = 0; i < strlen (fileName)-5; i++) // Loop to copy name of first string up to its length - 5 into "newFileName".
  {

   newFileName[i] = fileName[i];

  }

  char *s = concat ( newFileName, extension ); // calls function to append file extension to new file name and returns it.

  return s;

}

/*Function that creates traversal output files with correct file name.*/
void createOutputFile(char* oldFileName, char* fileExtension, struct node_t* root, void(*traversal_Func)( ) )
{

  int level = 0;

  char* newFileName = get_fileName (oldFileName, fileExtension);

  FILE *traversal = fopen(newFileName , "w"); //Create news file with the new file name from line before.

  traversal_Func (root , traversal, level); //Passes new file to traversal function so it can print to the file.

  fclose (traversal);
}

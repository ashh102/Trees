#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "node.h"
#include "tree.h"
#include "helper_funcs.h"

/*
	Macros
*/
#define TRUE 0
#define FALSE 1


int main(int argc, char *argv[])
{
  int i;
  int c;
  FILE *fp;
  char filename[15] = "out.sp19"; //Holds the name of the file used to copy everything read from stdin.
  struct node_t *root = NULL;

  printf("\n");

  if(argc == 1) // Executes if command line has file redirect or executable is launched without arguments.
  {
   printf("Reading data from Keyboard. \n");
   printf("\n");
   printf("If you did not redirect a file this program will read from keyboard until EOF is read.\n");
   printf("\n");

   c = getc(stdin);

   if(c == EOF) // // If stdin is empty then error; else put back character and read stream.
   {
    printf("ERROR: File redirect is empty.\n");
    return -1;
   }

   else
    ungetc(c, stdin);

   fp = fopen("out.sp19", "w"); //create file out.sp19 to copy read in data.

   while((c = getc(stdin)) != EOF) // While next character in not end of file print the char to file out.sp19.
   {
    fprintf(fp, "%c", c);
   }

   fclose(fp);

   fp = fopen (filename , "r" );

   if(fp != NULL) //If file is not empty build tree.
   {
    root = buildTree(fp , root );
   /*Next 3 lines creates final output files with appropriate name and prints the corresponding tree traversal to it.*/
    createOutputFile(filename, ".preorder", root, &printPreorder);
    createOutputFile(filename, ".inorder", root, &printInorder);
    createOutputFile(filename, ".postorder", root, &printPostorder);

    printf("EOF token found. Check directory for .Out files.\n");
  }

   else
    printf("Failed to open the file\n");

   fclose(fp);
  }

  if(argc == 2) //Execute if only 1 word or file passed on command line.
  {
   int x;
   int c;
   int ch = 0;
   int test = 3;

   printf("Checking for file in command line argument. \n");

   for(x = 0; x < strlen(argv[1]); x++) //For loop to search argument for dot operator.
   {
    ch = argv[1][x];

    if (ch == '.') // If dot operator is found argument is a file. Set flag to true.
    {
     test = 1;
    }
   }

   if(test == 1) // If argument is a file test for valid file extension.
   {
    printf("File given - Checking for correct extension.\n");

     if(isCorrectExtension(argv[1]) == FALSE) // If file extension is not .sp19 set test to false.
     {
      test = 2;
     }
    }

   switch(test)
   {
    case 1: //Argument is a file with extension .sp19
    {
     strcpy (filename , argv [1] ); // copy the file name from argv into variable.

     fp = fopen (filename , "r" );

      if(fp != NULL) // validation for opening the file. File opens execute, if not send error.
      {
	   c = fgetc(fp);

	   if(c == EOF) //If EOF character is found file is empty send error else print traversals to file.
	   {
        printf("FAIL - File is empty. Nothing to read.\n");
		break;
	   }

	   else
       {
		ungetc(c, fp);

		root = buildTree (fp , root );

		createOutputFile ( filename, ".preorder", root, &printPreorder);
		createOutputFile ( filename, ".inorder", root, &printInorder);
		createOutputFile ( filename, ".postorder", root, &printPostorder);

		printf("Success. - Check directory for traversal files.\n");
       }
	  }

      else
	   printf("Failed to open the file\n");
       break;
    }

    case 2: // Argument is a file with wrong extension. Send error.

	 printf("FAIL - INVALID file extension.\n");

	 break;

	case 3: //User only entered 1 word on command line and it's not a file. Send Error

	 printf("Argument is not a file.\n");
	 printf("Please enter more than 1 word on the command line if not a file.\n");
   }
  }

  if(argc > 2) // Execute for more than 2 arguments on command line.
  {
   printf("Reading data from keyboard.\n");

   fp = fopen("out.sp19", "w"); //create file out.sp19 to copy data from stdin.

   for(i = 1; i < argc; i++) //Loop to read and pint each argument from stdin to out.sp19.
   {
    fprintf(fp, "%s ", argv[i]);
   }

   fclose(fp);

   fp = fopen (filename , "r" );

   if(fp != NULL) //If file opens and is not empty build tree and print traversals to file else error.
   {
	root = buildTree (fp , root );
	createOutputFile ( filename, ".preorder", root, &printPreorder);
	createOutputFile ( filename, ".inorder", root, &printInorder);
	createOutputFile ( filename, ".postorder", root, &printPostorder);

	printf("Success. Check directory for Out files.\n");
   }

   else
	printf("Failed to open the file\n");

   fclose(fp);

  }
  printf("\n");
  return 0;
}

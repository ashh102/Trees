// file helper_func.h
#ifndef HELPER_FUNCS
#define HELPER_FUNCS

int isCorrectExtension(char *string);
char *concat(const char *s1, const char *s2);
char* get_fileName(char* string, char* extension);
void createOutputFile(char* string, char* extension, struct node_t* root, void(*traversalFunc)( ));

#endif /* HELPER_FUNCS_H_ */

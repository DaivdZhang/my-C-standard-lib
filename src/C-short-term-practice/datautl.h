#ifndef _DATAUTL_H
#define _DATAUTL_H

/* C99 Standard */

#include <stdio.h>
#include "llist.h"

unsigned int freadlines(FILE*, char**);
Song** data_assemble(Song**, char**, unsigned int);
int data_pickle(FILE*, LList);
LList file_to_list(char*);
char** strsplit(char**, char*, char);

#endif // _DATAUTL_H

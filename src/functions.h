#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include "structs.h"


int hash_function(char *, int);

int countWords(char *);

hash_table *hash_init(int, int);

void insert(hash_table *, info_caller *, char *);

void delete(hash_table *, char *, char *);

void find(hash_table *, char *, char *, char *, char *, char *);	

void lookup(hash_table *, char *, char *, char *, char *, char *);

void print(hash_table *);

void topdest(hash_table *, char *);

void bye(hash_table *);

int relation(hash_table *, char *, char *);

void indist(hash_table *, hash_table *, char *, char *);

int date(int, int, int, int, int, int, int, int, int);

int time(int, int, int, int, int, int);

#endif
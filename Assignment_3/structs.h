#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct termList{
	char * term;
	struct fileCountList * filesAndCounts;
	struct termList * next;
} termList;

typedef struct fileCountList{
	char * file;
	int count;
	struct fileCountList * next;
} fileCountList;

#endif
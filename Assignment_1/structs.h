#ifndef STRUCTS_H
#define STRUCTS_H

//This is a "logline," it contains three char arrays, level, timestamp, and message. This is used for storing the lines of the loglists.
typedef struct logline{
	char level[20];
	char timestamp[20];
	char message[100];
} logline_t;

//This is a "loglist," it is a linked list that uses a logline as a datapoint.
typedef struct loglist {
	logline_t line;
	struct loglist *next;
} loglist_t;

/*
	Because of the typedefs, refer to these structure types as (for example) struct loglist or just loglist_t.
	I.E. struct loglist == loglist_t 
*/

#endif

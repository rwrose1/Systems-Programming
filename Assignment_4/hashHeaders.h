/*
4. A header file containing:
	• Structure definition(s) for a hash table to store your symbol table.
	• Function prototypes for functions related to the hash table, i.e., inserting a node into
	the hash table, retrieving the LC value for a given symbol, and printing the contents of
	the hash table to stdout.
*/

typedef struct hashNode {
	char symbol[11];
	int address;
	struct hashNode * next;
} hashNode;

int  hashFunction(char *s,  int T);
void insertHash(hashNode ** head, hashNode * newNode);
void printHashTable(int size, hashNode * hashTable[]);
hashNode * newHashNode(char symbol[11], int address);
void deleteHashTable(int size, hashNode * hashTable[]);

/*
2. A header file containing:
	• Structure definition(s) for a BST to store your machine opcode table.
	• Function prototypes for functions related to the machine opcode table, i.e., inserting
	a node into the table, retrieving an opcode given the instruction name, retrieving the
	instruction format given the instruction name, and printing the contents of the tree to
	stdout.
*/

//This is the structure of a node contained in the BST
typedef struct instructionSet{
	char instruction [6]; //The five character long instruction
	unsigned char opcode; //The unsigned char to hold the opcode integer 
	unsigned char format; //The unsigned char to hold the format integer
	struct instructionSet * left; //A pointer to its left child
	struct instructionSet * right; //A pointer to its right child
}instructionSet;

//Prototypes
instructionSet * newInstructionSet(char * instruction, unsigned char opcode, unsigned char format);
unsigned char searchFormatBST(instructionSet * currentNode, char instruction[6]);
unsigned char searchOpcodeBST(instructionSet * currentNode, char instruction[6]);
int maxHeight(instructionSet * currentNode);
void insertBST(instructionSet ** head, instructionSet * newNode);
void printInOrder(instructionSet * currentNode);
void deleteBST(instructionSet * headNode);

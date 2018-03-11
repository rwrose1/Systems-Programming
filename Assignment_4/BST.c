//Project: 	Prog4
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/15/2017
//Course:  	ICSI 402
/*Desc:    this file contains implemented functions that correspond to the prototypes in BSTheaders.h.
it contains the following functions newInstructionSet, insertBST, printInOrder, searchOpcodeBST,searchFormatBST, and maxHeight
*/
/*Output: the output for the functions associated with the binary search tree include the inorder traversal of the binary search tree,
along with the height of the binary search tree
*/


//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//including external header files containing prototypes
#include "other.h"
#include "BSTheaders.h"

/*
    This function takes the attributes of a instructionSet struct as parameters. Allocating memory for and 
    assigning for a newInstructionSet struct. Finally it returns a pointer to the new struct.
*/
instructionSet * newInstructionSet(char * instruction, unsigned char opcode, unsigned char format)
{
    //Allocate memory for the new struct and checks if null, if NULL, prints errors and terminates
    instructionSet * newInstructionSet = (instructionSet *)malloc(sizeof(instructionSet));
    if(newInstructionSet == NULL){
        fprintf(stderr, "Could not allocate memory for newInstructionSet.\n");
        exit(1);
	}

    //Copy the supplied string 
	strcpy(newInstructionSet->instruction, instruction);

    //Assign the supplied numbers
	newInstructionSet->opcode = opcode;
	newInstructionSet->format = format;
    
    //Initialize the left and right pointers to NULL
    newInstructionSet->left = NULL;
    newInstructionSet->right = NULL;

    //Return the new struct
    return newInstructionSet;
}

/* 
the function insertBST inserts each individual instruction into the binary search tree, it takes a double pointer named head to the struct named instructionSet,
and a pointer named newNode to the same struct
*/
void insertBST(instructionSet ** head, instructionSet * newNode) {
	
	//if head == null, set head = to newNode and then return;
	if ((*head) == NULL) {
		*head = newNode;
		return;
	}
	/*
	compares the opcode, contained in the head node and newNode, if the head's instruction is less than that of newNode's instruction, then
	newNode is inserted into the left head's node, else insert it into the 
	right of head's node.
	*/
	if (strcmp((*head)->instruction, newNode->instruction) >= 0) {
		insertBST(&(*head)->left, newNode);
		return;
	} 
	else {
		insertBST(&(*head)->right, newNode);
		return;
	}
	
}


// the printInOrder function, prints the BST(binary search tree) in inorder traversal, takes a parameter named currentNode of the struct instructionSet
void printInOrder(instructionSet * currentNode) {
	
	//checks if currentNode is NULL
	if (currentNode == NULL) {
		return;
	}
	
	//checks the left child node
	printInOrder(currentNode->left);
	
	//prints the instruction that is contained in currentNode
	printf("%s, ", currentNode->instruction);
	
	 //check the right child node
	printInOrder(currentNode->right);
	
}

/* the searchOpcodeBST function searches the BST for the opcode of a specified instruction, it takes parameters of a char named instruction with a max size of 6, 
and a pointer named currentNode of the struct instructionSet.
*/
unsigned char searchOpcodeBST(instructionSet * currentNode, char instruction[6]) {
	
	//if current node is NULL
	if (currentNode == NULL) {
		return NULL;
	}
	//compares the instruction contained in the currentNode with the specified instruction, if they are equal return the opcode of currentNode
	if (strcmp(currentNode->instruction, instruction) == 0) {
		return currentNode->opcode;
	}
	
	/*
	compares the instruction contained in the currentNode with the specified instruction, if they are not equal, check the instruction with that of the right node
	and return that, otherwise checks the left and returns that.
	*/

	if (strcmp(currentNode->instruction, instruction) < 0) {
		return searchOpcodeBST(currentNode->right, instruction);
	} 
	else {
		return searchOpcodeBST(currentNode->left, instruction);
	}
	
}

/*
the searchFormatBST function searches the BST for the opcode of a specified instruction, it takes parameters of a char named instruction with a max size of 6,
and a pointer named currentNode of the struct instructionSet.
*/
unsigned char searchFormatBST(instructionSet * currentNode, char instruction[6]) {
	
	//checks current node is NULL
	if (currentNode == NULL) {
		return NULL;
	}
	
	//compares the instruction contained in the currentNode with the specified instruction, if they are equal return the format of currentNode
	if (strcmp(currentNode->instruction, instruction) == 0) {
		return currentNode->format;
	}
	
	/*
	compares the instruction contained in the currentNode with the specified instruction, if they are not equal, check the instruction with that of the right node
	and return that, otherwise checks the left and returns that.
	*/
	if (strcmp(currentNode->instruction, instruction) < 0) {
		return searchFormatBST(currentNode->right, instruction);
	} 
	else {
		return searchFormatBST(currentNode->left, instruction);
	}
	
}

/*
the function maxHeight takes a pointer named currentNode of the struct named instructionSet, the purpose of this function is that
it calculates the height of the tree, by finding the longest path starting from the root, and that is the height of the tree
*/
int maxHeight(instructionSet * currentNode) {
	
	//checks the current node is equal to NULL, if it is return 0. 
	if (currentNode == NULL) {
		return 0;
	}
	
	//computes the height of the left and right subtrees
	int leftHeight = maxHeight(currentNode->left);
	int rightHeight = maxHeight(currentNode->right);
	
	/*
	compares the height of the left subtree, with the right, if the left is greater than the right return the height of the left increased by one, 
	otherwise the height of the right increased by 1.
	*/
	if (leftHeight > rightHeight) {
		return (leftHeight + 1);
	} 
	else {
		return (rightHeight + 1);
	}
}

/*
	The deleteBST function returns nothing. It takes a pointer to the head node of a binary search tree as its only
	parameter. It recursively traverses the tree, freeing the allocated memory.
*/
void deleteBST(instructionSet * headNode){
	//Check if the supplied node is NULL
	if(headNode != NULL){
		//Recursively call deleteBST on the supplied node's left and right subtree
		deleteBST(headNode->left);
		deleteBST(headNode->right);
		//printf("\nDeleted: %s from BST.\n", headNode->instruction);
		free(headNode); //call free on the current node
	}
} //end deleteBST

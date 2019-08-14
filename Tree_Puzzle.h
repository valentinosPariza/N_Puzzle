/**
*
* @file Tree_Puzzle.h
* @brief This file contains the methods that are associated with the tree
*
* This file is responsible for creating and manipulating the tree which 
* inside holds the different states of the puzzle.It contains all the methods
* for this purpose an also a test-driver main for testing its correctness.
*
* @bug No known bugs. 
* @author Valentinos Pariza 
*/

#ifndef TREE_PUZZLE_H
#define TREE_PUZZLE_H
#define PUZZLE_MOVES 4
#include "puzzleArray.h"



typedef struct tree_node {

int** puzzle;     // two-dimensional array of integers
int g;                           // number of moves/distance from the root
int h;                           // search distance value
struct tree_node *parent;        // pointer to father
struct tree_node *children[4];   // pointers to children
                                 
}TREE_NODE;

/**
* @brief Checks if node's puzzle already exists at any ancestors of the node
*
* This method checks whether the node's puzzle  exists as a state of
* move at an ancestor in the tree.
*
*
* @param firstAncestor The node from where it starts the checking for equality
*        puzzles
* @param node The node which it checkes whether its puzzle exists or not
* @param sizePuzzle The size of the puzzle array 
*
* @return
* @author Valentinos Pariza 
*/
bool existsAtAncestors(TREE_NODE* firstAncestor,TREE_NODE* node,int sizePuzzle);


/**
* @brief Deletes the tree which has as a root the node-parameter which is given
*
* This method deletes all the nodes and their contents of the tree starting from
* node root(parameter).The parameter which is passed is a pointer to a pointer
* to a TREE_NODE struct.This is beacuse after the delete of the subtree or 
* tree, the variable which used to hold the pointer to NODE is set to NULL. 
* 
*
* @param root a pointer to a variable which has a pointer to a node of the tree
* @param sizePuzzle The size of the puzzle array 
*
* @return
* @author Valentinos Pariza 
*/
void deleteTree(TREE_NODE** root,int sizePuzzle);

/**
* @brief Creates the children of a node in the tree.
*
* This method creates the children of a a node in the tree.It creates all the
* valid moves-children and not all the children.This method uses many methods
* of the @file puzzleArray.c  
*
* @param parent The parent node on which the method creates the children
* @param sizePuzzle The size of the puzzle array 
* @param blankTileR The row where the blank tile is located in the puzzle
* @param blankTileC The column where the blank tile is located in the puzzle
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
int createChildren(TREE_NODE* parent,int sizePuzzle,bool 
includeDistanceFromRoot,int blankTileR,int blankTileC);

/**
* @brief Creates a node with the puzzle-Array whcih is given as parameter
*
*This method creates a TREE_NODE structure that contains the puzzle which is
*given as a parameter and returns it.
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
* @param sizePuzzle The size of the puzzle array 
*
* @return the structure of type TREE_NODE which contains the puzzle 
* @author Valentinos Pariza 
*/
TREE_NODE* createRootOfTree(int** puzzle,int sizePuzzle);

/**
* @brief Prints the tree which has a root the node given as a parameter
*
* This method prints the tree which has root the node which is given 
* as a parameter.
*
* @param treeNode The node which is the root of the tree
* @param sizePuzzle The size of the puzzle array 
*
* @return void
* @author Valentinos Pariza 
*/
void printTree(TREE_NODE* treeNode,int sizePuzzle);


/**
* @brief Prints the node which isgiven as a parameter
*
* This method prints the node which is given as a parameter.It prints
* the address of the node, the addresses of its children, the grade of the
* node ,the puzzle stored in the node and if it is activated,its height from
* the root.
*
* @param treeNode The node which is going to be printed
* @param sizePuzzle The size of the puzzle array 
*
* @return void
* @author Valentinos Pariza 
*/
void printNode(TREE_NODE* treeNode,int sizePuzzle);

#endif


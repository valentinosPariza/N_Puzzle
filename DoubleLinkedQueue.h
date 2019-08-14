/**
*
* @file DoubleLinkedQueue.h
* @brief Contains inforamtion about the use of queues in the program
*
* This file contains all the method prototypes and type definitions
* about the queue that is used in order to store the different states of the 
* puzzle examined.The queue that this file represents is a special type of
* a queue which is douvle linked ,so there is the cabability to traverse its elements
* from right to left and from left to right.
*
*
* @bug No known bugs. 
* @author Valentinos Pariza 
*/
#ifndef DOUBLE_LINKED_QUEUE_H
#define DOUBLE_LINKED_QUEUE_H
#include "Tree_Puzzle.h"
#include "puzzleArray.h"

// Type struct for the nodes of the queue
typedef struct frontier_node
{
   TREE_NODE* leaf;

   struct frontier_node* next;

   struct frontier_node* previous;

} FRONTIER_NODE;

// Type struct for the queue 
typedef struct queue
{ 
   FRONTIER_NODE* frontier_head;
   FRONTIER_NODE* frontier_tail;
   int size;

} QUEUE;

/**
* @brief Prints a structure(struct) type of QUEUE
*
*This method prints a struct of type QUEUE, starting from the head(frontier_head) 
* of the queue until its tail(frontier_tail).
*
* @param queue a struct of type QUEUE that holds the states of moves of a puzzle
* @param sizePuzzle The size of the puzzle array 
*
* @return void
* @author Valentinos Pariza 
*/
void printQueue(QUEUE* queue,int sizePuzzle);

/**
* @brief Inserts an element at the end(At the tail) of the queue passed as a parameter
*
*This method inserts a new element at the end of the queue,which means the new 
*element is inserted at the tail(frontier_tail) in the queue.
*
* @param queue a struct of type QUEUE that holds the states of moves of a puzzle
* @param treeNode The node(element of type TREE_NODE*) to be inserted at queue
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
int enqueue(QUEUE* queue,TREE_NODE* treeNode);

/**
* @brief Inserts an element at the queue passed as a parameter in a specific
*          way in order to be sorted in ascending order 
*
* This method inserts a new element in the queue.The element which is of type
* TREE_NODE* is inserted in the appropriate position in the queue based on its 
* priority.The priority is based on two attributes of the struct node that is
* placed inside the queue.Tha attribute h and the attribute g of every struct of 
* type TREE_NODE.The criteria of priority is the sum of these two attributes.The
* struct with the smallest sum is plaed first and then the others.
*
* @param queue a struct of type QUEUE that holds the states of moves of a puzzle
* @param treeNode The node(element of type TREE_NODE) to be inserted at queue
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
int priorityEnqueue(QUEUE* queue,TREE_NODE* treeNode);



/**
* @brief Removes the first element in the queue and put it in the parameter given
*
* This method takes a queue and removes the first element in the queue(The element
* at the head of the queue or the older element in the queue) and places it in
* a variable which its address is given as a parameter
*
* @param queue a struct of type QUEUE that holds the states of moves of a puzzle
* @param returnTreeNode a pointer to a variable which holds a struct type of
*        TREE_NODE
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process 
* @author Valentinos Pariza 
*/
int dequeue(QUEUE* queue,TREE_NODE** returnTreeNode);



/**
* @brief Checks whether a queue is empty or not
*
* This method checks if a queue(passed as an argument in the parameter queue)
* is empty or not.
*
*
* @param queue A struct of typee QUEUE* to check if it's empty
*
* @return true if the queue is empty or false if it's not
* @author Valentinos Pariza 
*/
bool isEmpty(QUEUE* queue);


/**
* @brief Creates a new struct of type QUEUE and returns it
*
* This method creates a new struct of type QUEUE and returns it.If during the
* allocation of memory or creation of the struct appeared a problem ,it returns
* NULL.
*
* @return the new struct of type QUEUE that was created or NULL if the new struct
*         couldn't be created
* @author Valentinos Pariza 
*/
QUEUE* createQueue();


/**
* @brief Deletes-frees the nodes of a queue and the queue itself from the memory 
*
* This method deletes-frees the nodes of the queue and the queue itself from 
* the memory,but it doesn't free the structs of type TREE_NODE of the nodes  
* (type of FRONTIER_NODE) in the queue.That job is made by the tree which these
* elements belong to.
*
* @param queue A struct of type QUEUE to delete-free its existance from memory  
* @return void
* @author Valentinos Pariza 
*/
void deleteQueue(QUEUE* queue);

#endif

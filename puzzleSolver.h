
/**
*
* @file puzzleSolver.h
* @brief File that contains the methods are reffering to the solution of the puzzle.
*
* This file contains all the methods that manipulate the solution of the 
* puzzle through these three possible algorythms
*-> Breadth first search
*-> Best first search
*-> A* search
* Alos this file contains all the necessary methods for creating and displaying 
* the solution.
*
* @bug No known bugs. 
* @author Valentinos Pariza 
*/
#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H
#include "DoubleLinkedQueue.h"
#include <math.h>
#define DEFAULT_NUMBER_OF_STEPS 10
#define BREADTH_FIRST_SEARCH_OPTION 0
#define BEST_FIRST_SEARCH_OPTION 1
#define A_START_SEARCH_ALGORYTHM 2
#include <math.h>

/**
* @brief This method applies the solution of the puzzle with the breadth first 
* algorythm
*
* This method tries to solve the (sizePuzzle)-puzzle game with the algorythm
* of the breadth First Search.
*
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*      the two dimensional array which is used for building the puzzle structure
*
*@param solution a pointer to a variable which points to a sequence of pointers
*       to characters.In this structure the first position is used for the 
*       number of steps that needed to solve the puzzle and the rest are the steps  
*
* @param sizePuzzle The size of the puzzle array 
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
int breadthFirstSearchSolver(int** puzzle,int sizePuzzle,char*** solution);



/**
* @brief This method applies the solution of the puzzle with the best first 
* algorythm
*
* This method tries to solve the (sizePuzzle)-puzzle game with the algorythm
* of the best First Search.
*
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*      the two dimensional array which is used for building the puzzle structure
*
*@param solution a pointer to a variable which points to a sequence of pointers
*       to characters.In this structure the first position is used for the 
*       number of steps that needed to solve the puzzle and the rest are the steps  
*
* @param sizePuzzle The size of the puzzle array 
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
int bestFirstSearchSolver(int** puzzle,int sizePuzzle,char*** solution);


/**
* @brief This method applies the solution of the puzzle with the a-star first 
* algorythm
*
* This method tries to solve the (sizePuzzle)-puzzle game with the algorythm
* of the a-star First Search.
*
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*      the two dimensional array which is used for building the puzzle structure
*
*@param solution a pointer to a variable which points to a sequence of pointers
*       to characters.In this structure the first position is used for the 
*       number of steps that needed to solve the puzzle and the rest are the steps  
*
* @param sizePuzzle The size of the puzzle array 
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
int aStarSearchSolver(int** puzzle,int sizePuzzle,char*** solution);



/**
* @brief This method writes the solution of a puzzle to a file
*
* This method writes the solution of the puzzle as given by the parameter
* solution to a file (the file is indicated by the fileName);
*
*@param fileName the name of the file where the solution will be written 
*@param solution a pointer to a variable which points to a sequence of pointers
*       to characters.In this structure the first position is used for the 
*       number of steps that needed to solve the puzzle and the rest are the steps.  
*
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
int writeTheSolutionToFile(char** solution,char* fileName);

#endif


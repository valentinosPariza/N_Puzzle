
/**
*
* @file puzzleArray.h
* @brief File that contains the methods about manipulating the puzzle arrays.
*
* This file is responsible for manipulating the puzzle arrays of the program.
* In this file here are all the function prototypes of all the methods that 
* are used on the puzzle arrays (like printPuzzle...).Also some constants are
* defined in order to replace all the names if the constants with specific values 
* at the preprocessor state and give a more efficient way of replacing these 
* constants with its values.The constants are associated with some functions
* that manipulate the puzzle arrays.
*
* @bug No known bugs. 
* @author Valentinos Pariza 
*/
#ifndef PUZZLE_ARRAY_H
#define PUZZLE_ARRAY_H
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define DEFAULT_SIZE 5
#define CHARS_PER_LINE 100
#define DELIMETERS " \n\r\f\t\v"
#define END_OF_FILE -1
#define absolute(x) (((x)<0)?(-(x)):(x))

/**
* @brief This method prints the content of the puzzle
*
* This method prints on the screen the contents of a puzzle given as an argument.
*
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
* @param size The size of the puzzle array 
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
void printPuzzle(int** puzzle,int size);


/**
* @brief Deletes the puzzle and frees the memory that is used from it
*
* This method deletes a puzzle that is passed as an argument in the method 
* and frees the memory that is allocated for it.
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
* @param size The size of the puzzle array 
* @return void
* @author Valentinos Pariza 
*/
void deletePuzzle(int*** puzzle,int size);

/**
* @brief Reads from a file the format of a structure and builds the puzzle
* 
* This method takes as an argument the name of the file to read from it .It 
* reads from the text file the format of the puzzle and builds the puzzle.
*
* @param puzzle A pointer to a variable which its value is an address which 
* points to a sequence of pointers which represent the two dimensional array 
* which is used for building the puzzle structure
*
* @return
* @author Valentinos Pariza 
*/
int createPuzzleFromFile(int*** puzzle,int* size,char* fileName);


/**
* @brief Creates a copy of the puzzle and returns it
*
* this method takes a puzzle two dimensional array and returns a copy of it.If
* the copy couldn't be created.It returns 
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
* @param size The size of the puzzle array 
*
* @return a copy of the puzzle that is passed as an argument (int**)
* @author Valentinos Pariza 
*/
int** createCopyOfPuzzle(int** puzzle,int size);


/**
* @brief Checks if the two puzzles passed as arguments are equal
*
* This method takes two pointers on two puzzles and returns if the two puzzles 
* are equals or not.
*
* @param puzzle1 a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
*        The first puzzle to check for equality with the second
* @param puzzle2 a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
*        The second puzzle to check for equality with the first
* @param size The size of the puzzle array 
*
* @return true if they are equal otherwise false
* @author Valentinos Pariza 
*/
bool puzzlesAreEqual(int** puzzle1,int** puzzle2,int size);


/**
* @brief Calculates the Manhattan distance of all the elements in the puzzle
*
* This method takes a two-dimensional array which represents a puzzle and 
* returns the Manhattan distance of all the elements in the puzzle from their
* final destination.
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
* @param size The size of the puzzle array 
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
*
* @author Valentinos Pariza 
*/
int calculateGradeOfPuzzle(int** puzzle,int size);

/**
* @brief Moves the blank tile to a position that is indicated by the parameter option.
* 
* 
*
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
*
* @param size The size of the puzzle array 
*
* @param  srcRow the row in the puzzle where the blank tile is located
* @param  srcColumn the column in the puzzle where the blank tile is located
* @param  option the option that indicates the move of the blank tile in the puzzle
*         to a predefined direction.
*         options :
*         0 -> right
*         1 -> down
*         2 -> left
*         3 -> up 
* @param  grade a pointer to a variable of integer which inside there is stored
*         the new value of Manhattan grade of the puzzle after the move of the 
*         blank tile          
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
int movePuzzleBlankTile(int** puzzle,int size,int srcRow,int srcColumn,int option,int* grade);

/**
* @brief Examines whether a blank tile can move to a specific direction 
*
* This method examines whether a tile can move to a specific direction
* which direction is given as an argument to the parameter option.
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
* @param size The size of the puzzle array 
* @param option the option that indicates the move of the blank tile in the puzzle
*         to a predefined direction.
*         options :
*         0 -> right
*         1 -> down
*         2 -> left
*         3 -> up 
* @param blankTileR the row in the puzzle where the blank tile is located
* @param blankTileC the column in the puzzle where the blank tile is located
*
* @return
* @author Valentinos Pariza 
*/
bool canMove(int** puzzle,int size,int blankTileR,int blankTileC,int option);


/**
* @brief Finds the position of the blank tile in the puzzle
*
*
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
* @param size The size of the puzzle array 
* @param r a pointer to an integer which is the row where the blank tile is located
* @param c a pointer to an integer which is the column where the blank tile is located
*
* @return void
* @author Valentinos Pariza 
*/
void findBlankTile(int** puzzle,int size,int* r,int* c);


/**
* @brief Checks whether the format of a puzzle is correct and returns the result
*
* This method checks if the format of a puzzle is correct or not.Which means
* if in the puzzle are included all the correct numbers and the numbers occur
* only once.
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure 
* @param size The size of the puzzle array 
*
* @return
* @author Valentinos Pariza 
*/
bool isCorrectPuzzleFormat(int** puzzle,int size);

/**
* @brief This method creates a random puzzle of a specific size.
*
* This method creates a puzzle with randomized shuffled its elements from the
* desired final result-state and places it at the address of the variable that
* is passed(puzzle).
*
* @param a pointer to a variable which its value points to a sequence of pointers to 
* integers which represent the two dimensional array which is used for building 
* the puzzle structure 
* @param size The size of the puzzle array to create
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
int createRandomPuzzle(int*** puzzle,int size);

/**
* @brief This method checks whether a puzzle is completed or not
*
* This method takes a puzzle of size as indicated by the argument passed in the
* variable size and checks if that puzzle is at the final-state .
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure 
* @param size The size of the puzzle array to create
*
* @return true if the puzzle is complete or false if it isn't
* @author Valentinos Pariza 
*/
bool puzzleIsCompleted(int** puzzle,int size);

#endif

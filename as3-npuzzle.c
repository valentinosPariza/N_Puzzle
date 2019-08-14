
#include "puzzleSolver.h"
#define toLowerCase(c) ((((c)>=('A')) && ((c)<=('Z')))?((c)+('a'-'A')) :((c)))

/**
* @brief Compares two character squences if and returns the compare result
*
* This method compares two character sequences and returns the result of the 
* comparison.It returns a negative number if the first character sequence is
* less than the second character sequence ,returns a positive if the first
* character sequence is greater than the second character sequence or 0 if 
* they are equal.
* 
* @param a A pointer to a sequence of characters
* @param b A pointer to a sequence of characters
*
* @return
* @author Valentinos Pariza 
*/
static int strcmpIgnoreCase(char* a,char* b);

static int strcmpIgnoreCase(char* a,char* b)
{
   if(a==NULL && b==NULL)
      return 0;

   if(b==NULL)
      return 1;

   if(a==NULL)
      return -1;

   char* pointerA=a;
   char* pointerB=b;

   while(*pointerA!='\0' && *pointerB!='\0')
   {
      if(toLowerCase(*pointerA)!=toLowerCase(*pointerB))
            return (*pointerA)-(*pointerB);
         
      pointerA++;
      pointerB++;
   }

   if(*pointerA=='\0' && *pointerB=='\0')
      return 0;

   if(*pointerA=='\0')
      return -(int)(*pointerB);

   else return (int)(*pointerA);


}

int main(int argc,char* argv[])
{

   

   if(argc!=4)
   {
      printf("Undefined command for the solver.\n");
      return 0;
   }
   

   int** puzzle=NULL;   // The puzzle array

   int sizePuzzle=0;    // The dimensions-size of the array

   char* fileName=argv[2]; // The fileName from where the initial state of the 
                        // puzzle will be read

   char* solutionFile=argv[3]; // the file where the solution will be written

   char* optionSolver=argv[1];

   char **solution=NULL; // A sequence of pointers to characters that represent
                         // the solution of the puzzle.The first entry is the
                         // the number of the steps to arrive at the final solution
                         // state and the rest of them the steps    

   int status=createPuzzleFromFile(&puzzle,&sizePuzzle,fileName);

   if(status==EXIT_FAILURE)
   {
      printf("Problem creating the puzzle\n");
      
      return 0;

    }

   if(!isCorrectPuzzleFormat(puzzle,sizePuzzle))
   {
      printf("Not a correct format of puzzle\n");
      return 0;
   }

   
   if(strcmpIgnoreCase(optionSolver,"breadth")==0)
   {
      if(breadthFirstSearchSolver( puzzle,sizePuzzle,&solution)==EXIT_SUCCESS)
         printf("The breadth-first search solver has found a solution for the puzzle.\n");
      else
       {
         printf("The breadth-first search solver hasn't found a solution for the puzzle.\n");
         return 0;
       }   
   }
   else if(strcmpIgnoreCase(optionSolver,"best")==0)
   {
      if(bestFirstSearchSolver( puzzle,sizePuzzle,&solution)==EXIT_SUCCESS)
         printf("The best-first search solver has found a solution for the puzzle.\n");
      else
        {
          printf("The best-first search solver hasn't found a solution for the puzzle.\n");
          return 0; 
        }

   }
   else if(strcmpIgnoreCase(optionSolver,"a-star")==0)
   {
      if(aStarSearchSolver(puzzle,sizePuzzle,&solution)==EXIT_SUCCESS)
         printf("The a-star search solver has found a solution for the puzzle.\n");
      else
        {
          printf("The a-star search solver hasn't found a solution for the puzzle.\n");
          return 0; 
        }

   }
   else
   {
      printf("Invalid option for solver.\n");
      return 0;
   }
   
 

  if(writeTheSolutionToFile(solution, solutionFile)==EXIT_SUCCESS)
   {
         printf("The solution was written to the file %s.\n",solutionFile);
   }
   else
      printf("The solution couldn't be written to the file.\n");

   

   free(solution[0]);
   free(solution);

   return 0;
}

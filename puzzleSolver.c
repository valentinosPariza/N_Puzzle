
#include "puzzleSolver.h"


/**
* @brief This method solves a n-puzzle based on an algorythm-option and returns the solution
*
* This method takes a puzzle of dimensions indicated by the sizePuzzle parameter
* and solves it using an algorythm that is chosed base on the option parameter 
*
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
*
*@param sizePuzzle The size of the puzzle array 
*
*@param solution a pointer to a variable which points to a sequence of pointers
*       to characters.In this structure the first position is used for the 
*       number of steps that needed to solve the puzzle and the rest are the steps  
*
* @param option is the option of what algorythm to use 
*-> BREADTH_FIRST_SEARCH_OPTION 0
*-> BEST_FIRST_SEARCH_OPTION 1
*-> A_START_SEARCH_ALGORYTHM 2
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
static int puzzleSolver(int** puzzle,int sizePuzzle,char*** solution,int option);



/**
* @brief This method records the solution of the puzzle to a dynamic array
*
* @param node The struct node of TREE_NODE type from which the method starts
*        to traversing the tree until the root and cite down the steps for
*        the solution
*@param solutionSteps a pointer to a variable which points to a sequence of pointers
*       to characters.In this structure the first position is used for the 
*       number of steps that needed to solve the puzzle and the rest are the steps  
*
*
* @return EXIT_SUCCESS if the process was excecuted succesfully or
*         EXIT_FAILURE if there were any problems that ended the process
* @author Valentinos Pariza 
*/
static int recordSolutionSteps(TREE_NODE* node,char*** solutionSteps);

/**
* @brief This method takes the move-step in the puzzle as an integer and returns
*        the string literal that corresponds to this move-step
*
*
* @param option The option of a move-step in the puzzle as an integer
*
* @return a pointer to characters that these characters represent the integer 
*        option of move-step in the puzzle
*         
* @author Valentinos Pariza 
*/
static char* getMoveFromRepresentation(int option);


/**
* @brief Reverses a sequence of char* pointers
*
* This method takes a sequence of pointers and reverses its entries.More
* specific it takes every element until (begin+end)/2 and swaps it with 
* the corresponting element at the second half of the sequence.
*
*
* @param sequence A pointer to a sequence of pointers to characters
* @param begin The beginning index of reversing in the sequence
* @param end The last index of reversing in the sequence
*
* @return void
* @author Valentinos Pariza 
*/

static void reverseEntries(char** sequence,int begin,int end);



static int recordSolutionSteps(TREE_NODE* node,char*** solutionSteps)
{

   
   if(node==NULL || solutionSteps==NULL)
      return EXIT_FAILURE;  


  
   int size=DEFAULT_NUMBER_OF_STEPS;

   *solutionSteps=(char**)malloc(sizeof(char*)*DEFAULT_NUMBER_OF_STEPS);
  
   if(*solutionSteps==NULL)
      return EXIT_FAILURE;

   int counter=0;
   char** temp=NULL;

  
     

   while(node!=NULL && node->parent!=NULL)
   {

      // plus 1 beacause we want the first position for the number of moves
      if(counter+1>=size)
      {
         temp=(char**)realloc(*solutionSteps,(size*=2)*sizeof(char*));

         if(temp==NULL)
         return EXIT_FAILURE;
      
         *solutionSteps=temp;

      }


      int i=0;

      for( i=0;i<PUZZLE_MOVES;i++)
      {
         if( node->parent->children[i]==node)
               break;
      }

      
      (*solutionSteps)[counter+1]=getMoveFromRepresentation(i);
      counter++;
      
      node=node->parent;
     
   }


   
     (*solutionSteps)[0]=(char*)malloc(sizeof(char)*((int)(log10((counter==0)? 1 :counter )+2)));
        
     if((*solutionSteps)[0]==NULL)
         return EXIT_FAILURE;   
     
      sprintf((*solutionSteps)[0],"%d",counter);             
    

   reverseEntries(*solutionSteps,1,counter);

   return EXIT_SUCCESS;

}

static void reverseEntries(char** sequence,int begin,int end)
{
   if(sequence==NULL)
         return ;

   char* temp;

   while(begin<end)
   {
        temp=sequence[begin];
        sequence[begin]=sequence[end];
        sequence[end]=temp; 
        begin++;
        end--;

   }


} 

static char* getMoveFromRepresentation(int option)
{
   switch (option)
   {
      case (0) : return "right";

      case (1) : return "down";
   
      case (2) : return "left";

      case (3) :  return "up";

     default : return NULL;


   }
}


static int puzzleSolver(int** puzzle,int sizePuzzle,char*** solution,int option)
{
   if(puzzle==NULL || sizePuzzle<=0 || solution==NULL)
      return EXIT_FAILURE;


   *solution=NULL;

   //create the tree with root the base puzzle
   TREE_NODE* root=createRootOfTree(puzzle,sizePuzzle);

   // problems in allocation of memory for the tree
   if(root==NULL)
      return EXIT_FAILURE;

   int status=0;
   
   if(root->h==0)
    {
      status=recordSolutionSteps(root,solution);
      deleteTree(&root,sizePuzzle);
      return status;
    }


   //create the queue
   QUEUE* queue=createQueue();
  
   // problems in allocation of memory for the queue
   if(queue==NULL)
    {
      deleteTree(&root,sizePuzzle);     // free the memory used by the tree
      return EXIT_FAILURE;
    }     
   
   
     // Inserting the root to the queue based on the algorythm that is going to
     // be used
    if(option==BREADTH_FIRST_SEARCH_OPTION)
     {
       status=enqueue(queue,root);             
     }
    else
     {             
       status=priorityEnqueue(queue,root);         
     }  
    

   if(status==EXIT_FAILURE)
   {
      deleteQueue(queue);
      deleteTree(&root,sizePuzzle);     // free the memory used by the data 
      return EXIT_FAILURE;             // structures created so far
   
   }


   int blankRow=0,blankColumn=0;

   TREE_NODE* node=NULL;


   // when the queue becomes empty it means that the solution couldn't be found
   while(!isEmpty(queue))
   {

      if((status=dequeue(queue,&node))==EXIT_FAILURE)
         break;

   

      // find the row and the column of the blank tile
      findBlankTile(node->puzzle,sizePuzzle,&blankRow,&blankColumn);    

      
      if((status=createChildren(node, sizePuzzle,A_START_SEARCH_ALGORYTHM==option,blankRow,blankColumn))==EXIT_FAILURE)
         break;

      for(int i=0;i<PUZZLE_MOVES;i++)
      {

         
         if(node->children[i]!=NULL)
         {
         
             if(node->children[i]->h==0)
              {
                  
                  status=recordSolutionSteps(node->children[i],solution);

                 deleteQueue(queue);
                 deleteTree(&root,sizePuzzle); 
   
                 return status;
              }
              
            // if the option is for breadth first search then use the enqueue
            // method,else use the priorityEnqueue
            if(option==BREADTH_FIRST_SEARCH_OPTION)
            {
               if((status=enqueue(queue,node->children[i]))==EXIT_FAILURE)
                   break;  
   
            }
            else
            {
            
               if((status=priorityEnqueue(queue,node->children[i]))==EXIT_FAILURE)
                  break;
            }               
                        
         }

      }

      if(status==EXIT_FAILURE)
         break;
      
   }

  deleteQueue(queue);
  deleteTree(&root,sizePuzzle);  // free the structures that are used
  

   return EXIT_FAILURE;


}


int breadthFirstSearchSolver(int** puzzle,int sizePuzzle,char*** solution)
{
      return puzzleSolver(puzzle,sizePuzzle, solution,BREADTH_FIRST_SEARCH_OPTION);
}



int bestFirstSearchSolver(int** puzzle,int sizePuzzle,char*** solution)
{
   return puzzleSolver(puzzle,sizePuzzle, solution,BEST_FIRST_SEARCH_OPTION);
}


int aStarSearchSolver(int** puzzle,int sizePuzzle,char*** solution)
{
   return puzzleSolver(puzzle,sizePuzzle, solution,A_START_SEARCH_ALGORYTHM);
}


int writeTheSolutionToFile(char** solution,char* fileName)
{  
   if(solution==NULL || fileName==NULL || strlen(solution[0])==0)
        return EXIT_FAILURE;
 
   FILE* filePointer=fopen(fileName,"w");
   
   if(filePointer==NULL)
      return EXIT_FAILURE;

   int counter=0;
   int numberOfMoves=atoi(solution[0]);   // the first positon is the number of
                                          // steps

   while(counter<=numberOfMoves)   
   {
      fprintf(filePointer,"%s\n",solution[counter]);
      counter++;
   }


   fclose(filePointer);

   return EXIT_SUCCESS;
}


#ifdef DEBUG_PUZZLE_SOLVER

int main(int argc,char* argv[])
{


   return 0;
}


#endif

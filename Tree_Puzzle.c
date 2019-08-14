
#include "Tree_Puzzle.h"

/**
* @brief Deletes all the methods that are ancestors of the node which is given
*
* This method deletes all the nodes that are ancestors of the node which is 
* given as a parameter and also deletes the node.
*
*
* @param node a node which deletes all its ancestor and the node too.
* @param sizePuzzle The size of the puzzle array 
*
* @return
* @author Valentinos Pariza 
*/
static void deleteNodes(TREE_NODE* node,int sizePuzzle);

TREE_NODE* createRootOfTree(int** puzzle,int sizePuzzle)
{


   if(puzzle==NULL || sizePuzzle<=0 )
         return NULL;

   TREE_NODE* node=(TREE_NODE*)malloc(sizeof(TREE_NODE));

   if(node==NULL)
      return NULL;

   node->puzzle=puzzle;

   node->h=calculateGradeOfPuzzle(puzzle,sizePuzzle); // calculates the Manhattan
                                                      // grade of the tree   
   node->g=0;

   for(int i=0;i<PUZZLE_MOVES;i++)
      node->children[i]=NULL;

   
   return node;
   
}



int createChildren(TREE_NODE* parentNode,int sizePuzzle,bool 
  includeDistanceFromRoot,int blankTileR,int blankTileC)
{
      

      if(parentNode==NULL || sizePuzzle<=0 || blankTileR<0 || blankTileC<0 || 
         (parentNode->puzzle)[blankTileR][blankTileC]!=0)
         return EXIT_FAILURE;

        

      for(int i=0;i<PUZZLE_MOVES;i++)
      {


         // if the blank tile cannot be moved in a direction with number i then 
         // skip that child
         if(!canMove(parentNode->puzzle,sizePuzzle,blankTileR,blankTileC,i))
            continue;

         

         // create the tree node
         parentNode->children[i]=(TREE_NODE*)malloc(sizeof(TREE_NODE));    
         

         if(parentNode->children[i]==NULL)    // problem in allocation of memory
            return EXIT_FAILURE;

         // set to NULL all the children of the new tree node created
        for(int j=0;j<PUZZLE_MOVES;j++)
         (parentNode->children[i])->children[j]=NULL;
          

        (parentNode->children[i])->puzzle=createCopyOfPuzzle(parentNode->puzzle,sizePuzzle);
         // create a copy of the puzzle array of the father

        if((parentNode->children[i])->puzzle==NULL)
            return EXIT_FAILURE;   

          parentNode->children[i]->h=parentNode->h;   

         // on the copy array the program applies the appropriate changes of  
         // move of the blank tile at one position and updates the search 
         // distance value of the puzzle
        if(movePuzzleBlankTile((parentNode->children[i])->puzzle,sizePuzzle,
         blankTileR,blankTileC,i,&(parentNode->children[i]->h))==EXIT_FAILURE)
          {     
             deleteNodes((parentNode->children[i]), sizePuzzle);
             parentNode->children[i]=NULL;
              continue ;
          }

          

         parentNode->children[i]->parent=parentNode;
         
      
         // if the node exists at one of the ancestors then delete it and
         // move to the next one

        
      
         if(existsAtAncestors(parentNode, parentNode->children[i],sizePuzzle))
           {
               deleteNodes(parentNode->children[i],sizePuzzle);
               parentNode->children[i]=NULL;
               
               continue;
           }

         
         // if there is an inclusion of the number of moves/distance from the 
         // root ,include its value.Else set it to zero
         if(includeDistanceFromRoot)
            (parentNode->children[i])->g=(parentNode->g)+1;
         else 
            (parentNode->children[i])->g=0;
               
      }

   return EXIT_SUCCESS;

}


void deleteTree(TREE_NODE** root,int sizePuzzle)
{
   if(sizePuzzle<=0 || root==NULL)
         return ;

   deleteNodes(*root, sizePuzzle);

   *root=NULL;
}


static void deleteNodes(TREE_NODE* node,int sizePuzzle)
{
      if(node==NULL)
         return ;

      for(int i=0;i<PUZZLE_MOVES;i++)
      {
         if(node->children[i]!=NULL)
            deleteNodes(node->children[i],sizePuzzle);
      }   

      deletePuzzle(&(node->puzzle),sizePuzzle);

      free(node);
}





bool existsAtAncestors(TREE_NODE* firstAncestor,TREE_NODE* node,int sizePuzzle)
{
   if( firstAncestor==NULL || node==NULL || sizePuzzle<=0)
         return false;


   // For all the rest ancestors check the ancestors and not the brothers
   // of the node.Checking only at ancestors of the node for equal puzzles.
   while(firstAncestor!=NULL)
   {
      if(puzzlesAreEqual(firstAncestor->puzzle,node->puzzle,sizePuzzle))
       return true;

      firstAncestor=firstAncestor->parent;
      
   }

   return false;

}


void printNode(TREE_NODE* treeNode,int sizePuzzle)
{
   if(treeNode==NULL)
      return ;

   printf("\nIts address %p\n",(void*)treeNode);
   printf("h= %d\n",treeNode->h);
   printf("g= %d\n",treeNode->g);
   printf("\n");
   printPuzzle(treeNode->puzzle,sizePuzzle);
   
   printf("\nAddress of the children :\n");

   for(int i=0;i<PUZZLE_MOVES;i++)
      if(treeNode->children[i]!=NULL)
         printf("%p | ",(void*)treeNode->children[i]);
      else 
         printf("NULL | ");

      printf("\n");
}

void printTree(TREE_NODE* treeNode,int sizePuzzle)
{
      if(treeNode==NULL || sizePuzzle<=0)
         return ;

   printNode(treeNode,sizePuzzle);

   for(int i=0;i<PUZZLE_MOVES;i++)
      printTree(treeNode->children[i],sizePuzzle);
      
      

}

// The debug mode of the file
#ifdef DEBUG_TREE_PUZZLE

static bool isIntegerNumber(char* charsequence);

static void cutStringAtFirstNewLineCharacter(char* charsequence);


static void printMenu()
{
   printf("1) Create Children.\n");
   printf("2) print Tree.\n");
   printf("3) Exit DEBUG_TREE_PUZZLE.\n");

}

// Checks if the char sequence is an integer number
static bool isIntegerNumber(char* charsequence)
{
      
   if(charsequence==NULL || *charsequence=='\0')   // NULL or empty String
      return false;
   
   char* pointerToCharacter=charsequence;

   while(*pointerToCharacter!='\0')
   {
      
      if(*pointerToCharacter<'0' || *pointerToCharacter>'9')
         return false;      
      
      pointerToCharacter++;
   }   

   return true;
}


// Cuts the sequence of characters to the first appearance of the new line 
// escape character
static void cutStringAtFirstNewLineCharacter(char* charsequence)
{
    if(charsequence==NULL )   
      return ;

   char* pointerToCharacter=charsequence;

   while(*pointerToCharacter!='\0')
   {
      if(*pointerToCharacter=='\n')      
      {
         *pointerToCharacter='\0';
          break;
      }
      
      pointerToCharacter++;
   }

}




int main(int argc,char* argv[])
{
   int**puzzle=NULL;
   int size=3;
   createRandomPuzzle(&puzzle,size);

   printf("The puzzle is :\n");
   printPuzzle(puzzle,size);
   printf("\n");
   int decision=0;
   TREE_NODE* node=NULL;
   TREE_NODE* tree=createRootOfTree(puzzle,size);

   if(tree==NULL)
     {     
        printf("Problem creating the tree : \n");
        return 0;
     }

   int option=0;
   int c=0,r=0;         // variables for the row and the column for the blank tile
   size_t nbytes=100;
   bool correctOption=false;
   char* line=NULL;

   printf("\n************************************** DEBUG MODE ");
      printf("**************************************\n");   

   do{

      printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n");

      option=0;
      printMenu();

      correctOption=false;
      

      do{
         getline(&line,&nbytes,stdin);
         cutStringAtFirstNewLineCharacter(line);
         correctOption=isIntegerNumber(line);

      }while(!correctOption);
      // take an integer number from the keyboard
      option=atoi(line);    
   
      switch (option)
      {
         case 1 :     // Create children option
                  decision=0;
                  node=tree;
                  

                 do{

                      printNode(node,size);
                      printf("\n");
                     // The options which let the user to create a tree as he/she
                     // wants
                     printf("i) Move to children i where i=[0,%d]\n",(PUZZLE_MOVES-1));
                     printf("%d) Create children on this node.\n",PUZZLE_MOVES);
                     printf("%d) Move to father.\n",(PUZZLE_MOVES+1));
                     printf("%d) End creation of children.\n",(PUZZLE_MOVES+2));


                     correctOption=false;
      
                     printf("Give your option :\n");

                     do{
                        getline(&line,&nbytes,stdin);
                        cutStringAtFirstNewLineCharacter(line);
                        correctOption=isIntegerNumber(line);

                    }while(!correctOption);
                     

                    decision=atoi(line);

                     switch (decision)
                     {
                        
                          case (0) ... (PUZZLE_MOVES-1) :
   
                                    if(node->children[decision]==NULL)
                                        printf("Cannot move to the child.\n");
                                    else
                                         node= node->children[decision];                                       
                                    

                                    break;

                        case PUZZLE_MOVES :

      
                             findBlankTile(node->puzzle,size,&r,&c);

                           bool hasAlreadyCreatedChildren=false;
   
                           for(int i=0;i<PUZZLE_MOVES;i++)
                                 if(node->children[i]!=NULL)
                                   {
                                    hasAlreadyCreatedChildren=true;
                                    break;
                                   }

                           if(!hasAlreadyCreatedChildren && createChildren(node,size,true,r,c)==EXIT_SUCCESS)
                           {
                              printf("Children were created\n");
      
                           }
                           else  printf("Children haven't been created\n");

                                    break;
      
                        case PUZZLE_MOVES+1 :

                                    if(node->parent==NULL)
                                       printf("Cannot move to the parent.\n");
                                    else
                                        node=node->parent;

                                    break;

                        case PUZZLE_MOVES+2 :  
                                     printf("Exiting mode.\n");
                                    break;

         
                        default : printf("Undefined option.\n");
                                    break;

                     }



                  }while(decision!=PUZZLE_MOVES+2 );

                 
                  break;

         case 2 : // Print the tree
                  printf("\n------------------------------------------------\n");
                  printTree(tree,size);
                  printf("\n------------------------------------------------\n");
                     
                  break;
         

         case 3 : printf("Exiting the DEBUG_TREE_PUZZLE.\n\n");
                  break;

         default : printf("Undefined option.\n");
      }
      printf("\n");

   printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n");

   }while(option!=3);

   printf("\n************************************** DEBUG MODE ");
   printf("**************************************\n"); 

   deleteTree(&tree,size);
   free(line);

   return 0;
}

#endif






#include "puzzleArray.h"



/**
* @brief Reads from a file its first line and calculates the size-dimension of the puzzle
*
* This method opens a file,reads the first line of the program and calculates
* the size of the puzzle.The size of the puzzle is stored to a variable which
* variable's address it's passed as an argument to parameter size.
*
*
* @param fileName The name of the file which contains the puzzle as a text format
* @param size A pointer to an integer which represents the size of the puzzle.
*        After the end of the method the address of the variable that is passed
*        as an argument is updated with the size of the puzzle
*
* @return
* @author Valentinos Pariza 
*/
static int calculateSizeOfPuzzleThroughFile(char* fileName,int* size);

/**
* @brief Shuffles a puzzle array so the its state to be different from the initial state
*
* This method takes a two-dimensional array of the puzzle and shuffles it so,
* after the shuffle he final state to be different from the first one.
*
*
* @param puzzle a pointer to a sequence of pointers to integers which represent
*        the two dimensional array which is used for building the puzzle structure
* @param sizePuzzle The size of the puzzle array 
*
* @return void
* @author Valentinos Pariza 
*/
static void shufflePuzzle(int** puzzle,int size);


int createPuzzleFromFile(int*** puzzle,int* size,char* fileName)
{
   if(puzzle==NULL || size==NULL || fileName==NULL)
      return EXIT_FAILURE;

   int status=calculateSizeOfPuzzleThroughFile(fileName,size);
   
   if(status==EXIT_FAILURE || *size<=0)
         return EXIT_FAILURE;

   FILE* filePointer=fopen(fileName,"r");

   if(filePointer==NULL)
      return EXIT_FAILURE;      

  *puzzle=(int**)malloc(sizeof(int*)*(*size));

   if(*puzzle==NULL)
       return EXIT_FAILURE;

   
   for(int i=0;i<*size;i++)
   {
      (*puzzle)[i]=(int*)malloc(sizeof(int)*(*size));
   
      if((*puzzle)[i]==NULL)
         return EXIT_FAILURE;
   }


   

   char* line=NULL;
   size_t nbytes=100;

   int lines=0,elementsPerLine=0;

   while(getline(&line,&nbytes,filePointer)>0)  
   {
      if(lines>*size || elementsPerLine>*size)
      {
         if(line!=NULL )
            free(line);
         

         return EXIT_FAILURE;
      }

      char* token=strtok(line,DELIMETERS);   // tokenize the line to the tokens
   
      elementsPerLine=0;

      while(token!=NULL)      // while there are more tokens to read.Take them
      {
         if(elementsPerLine>*size)
            break;

         (*puzzle)[lines][elementsPerLine]=atoi(token);  // Turn into the tokens
         elementsPerLine++;                              // to numbers and place 
                                                         // to appropriate position   
         token=strtok(NULL,DELIMETERS);                  // in the array
      }


      lines++;

   }

   if(line!=NULL )
      free(line);

   fclose(filePointer);

   return EXIT_SUCCESS;
}


static int calculateSizeOfPuzzleThroughFile(char* fileName,int* size)
{
   if(fileName==NULL || size==NULL)
      return EXIT_FAILURE;

   char* line=NULL;
   size_t nbytes=0;

   FILE* fp=fopen(fileName,"r");
   

   if(fp==NULL)
      return EXIT_FAILURE;

   *size=0;
  
   if(getline(&line,&nbytes,fp)>0)
   {
      fclose(fp);
      char* token=strtok(line,DELIMETERS);
      
      while(token!=NULL)
      {
         token=strtok(NULL,DELIMETERS);
         (*size)++;

      }

      free(line);
   }
   else
   {
      fclose(fp);
      return EXIT_FAILURE;
   }
 
   return EXIT_SUCCESS;
}


void deletePuzzle(int*** puzzle,int size)
{
   if(puzzle==NULL || size<=0)
        return ;

   for(int i=0;i<size;i++)    // delete every sequence of integers pointed
      {                                // by (*puzzle)[i] pointer
         if((*puzzle)[i]!=NULL)
         free((*puzzle)[i]);
      }
   
   free(*puzzle);             // delete the sequence of pointers type of int*

   *puzzle=NULL;           // ensure that the variable that inside was
                           // the pointer of the sequence of pointers
                           // now is pointing on NULL and not in a place 
                           // in memory that doesn't belong to it
}



void printPuzzle(int** puzzle,int size)
{
      if(puzzle==NULL || size<=0)
         return ;

      for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
             {
               printf("%-8d ",puzzle[i][j]);  

             }

            printf("\n");
        }

}


bool puzzlesAreEqual(int** puzzle1,int** puzzle2,int size)
{
      if(puzzle1==NULL || puzzle2==NULL)
         return puzzle2==NULL && puzzle1==NULL;

      
      for(int i=0;i<size;i++)
      {
         for(int j=0;j<size;j++)
          {
            if(puzzle1[i][j]!=puzzle2[i][j])    
                  return  false;
         
          }

      }

      return true;

}


int** createCopyOfPuzzle(int** puzzle,int size)
{
      if(size<=0 || puzzle==NULL)
            return NULL;

      int** cpyPuzzle=(int**)malloc(sizeof(size*sizeof(int*)));
      // create the base sequence-array of pointers int* 

      if(cpyPuzzle==NULL)
         return NULL;

      for(int i=0;i<size;i++)
       {
         cpyPuzzle[i]=(int*)malloc(size*sizeof(int));    // create the sequence 
                                                         // of integers in 
         if(cpyPuzzle[i]==NULL)                          // memory
           {
               deletePuzzle(&puzzle,i-1); // if there is a problem in allocation
               return NULL;               // of memory -> delete all the memory       
           }                              // that was allocated by now( delete)
                                          // the sequenc of int* pointers and
                                          // the first i sequences-arrays 
                                          // of integers
 
            for(int j=0;j<size;j++)          // copy the integers from the 
               cpyPuzzle[i][j]=puzzle[i][j]; // puzzle array which was given
                                             // as a parameter to the one that
       }                                     // was recently created

   
      return cpyPuzzle;

}


int calculateGradeOfPuzzle(int** puzzle,int size)
{
   if(puzzle==NULL || size<=0)
         return -1;           // indicate that this puzzle hasn't got a correct
   int sum=0,a=0,b=0;               //  grade for

   for(int i=0;i<size;i++)
   {
      for(int j=0;j<size;j++)
       {
         if(puzzle[i][j]!=0)
          {
             a=(puzzle[i][j]-1)/size;      // the variable a has the row that 
             b=(puzzle[i][j]-1)%size;      // the number at position puzzle[i][j] 
                                       // should be placed at the end, and 
                                       // variable b has the column
             sum+=abs(i-a)+abs(j-b); // the distance of a number between its
                                     // current position([i,j]) and its 
                                     // destination position([a,b])   
          }
       
       }
   }

   return sum;
}


int movePuzzleBlankTile(int** puzzle,int size,int srcRow,int srcColumn,int option,int* grade)
{
   // option parameter takes an argument that represents the direction of move
   // of the blank tile The options are : 0--> right, 1--> down , 2--> left
   // and 3--> up

   if(puzzle==NULL || size<=0 || srcRow<0 || srcColumn<0 ||
    puzzle[srcRow][srcColumn]!=0 || grade==NULL)
         return EXIT_FAILURE;

       int destR=0;
       int destC=0 ; 

     if(option==0 && srcColumn<size-1) // the case to move right
      {
         destR=(puzzle[srcRow][srcColumn+1]-1)/size;            
         destC=(puzzle[srcRow][srcColumn+1]-1)%size;
      

         *grade+=(abs(destR-srcRow)+abs(destC-srcColumn))-(abs(destR-srcRow)+abs(destC-(srcColumn+1)));
         
         puzzle[srcRow][srcColumn]=puzzle[srcRow][srcColumn+1];
         puzzle[srcRow][srcColumn+1]=0;

      }
      else if(option==1 && srcRow<size-1) // the case to move down 
      {
         destR=(puzzle[srcRow+1][srcColumn]-1)/size;            
         destC=(puzzle[srcRow+1][srcColumn]-1)%size;

         *grade+=(abs(destR-srcRow)+abs(destC-srcColumn))-(abs(destR-(srcRow+1))+abs(destC-srcColumn));
                

         puzzle[srcRow][srcColumn]=puzzle[srcRow+1][srcColumn];
         puzzle[srcRow+1][srcColumn]=0;

      }
      else if(option==2 && 0<srcColumn)  // the case to move left
      {
         destR=(puzzle[srcRow][srcColumn-1]-1)/size;            
         destC=(puzzle[srcRow][srcColumn-1]-1)%size;


         *grade+=(abs(destR-srcRow)+abs(destC-srcColumn))-(abs(destR-srcRow)+abs(destC-(srcColumn-1)));
         
         puzzle[srcRow][srcColumn]=puzzle[srcRow][srcColumn-1];
         puzzle[srcRow][srcColumn-1]=0;

      }
      else if(option==3 && 0<srcRow) // the case to move up
      {
         destR=(puzzle[srcRow-1][srcColumn]-1)/size;            
         destC=(puzzle[srcRow-1][srcColumn]-1)%size;

         *grade+=(abs(destR-srcRow)+abs(destC-srcColumn))-(abs(destR-(srcRow-1))+abs(destC-srcColumn));
         
         puzzle[srcRow][srcColumn]=puzzle[srcRow-1][srcColumn];
         puzzle[srcRow-1][srcColumn]=0;

      }
      else return EXIT_FAILURE;
      

      

   return EXIT_SUCCESS;
}


bool puzzleIsCompleted(int** puzzle,int size)
{
   if(puzzle==NULL || size<0)
        return false;

   for(int i=0;i<size;i++)
   {
     for(int j=0;j<size;j++)
      {
         if(puzzle[i][j]!=(i*size+j) && !(i==size-1 && j==size-1 && puzzle[i][j]==0))
               return false; 

      }
          
   }

   return true;

}


 void findBlankTile(int** puzzle,int size,int* r,int* c)
{
   if(puzzle==NULL || size<=0 || r==NULL || c==NULL)
      return ;

   for(int i=0;i<size;i++)
      for(int j=0;j<size;j++)
         if(puzzle[i][j]==0)
           {
               *r=i;
               *c=j;
               return ;
   
           }

}


 bool canMove(int** puzzle,int size,int blankTileR,int blankTileC,int option)
{
   if(puzzle==NULL || size<0 || blankTileR<0 || blankTileC<0 || puzzle[blankTileR][blankTileC]!=0)
         return false;

      return (option==0 && blankTileC<size-1) || (option==1 && blankTileR<size-1)
         || (option==2 && 0<blankTileC) || (option==3 && 0<blankTileR);
     
}


bool isCorrectPuzzleFormat(int** puzzle,int size)
{
   if(size<=0 || puzzle==NULL)
      return false;

   int temp[size][size];   // create a corresponding two-dimensional array of 
                           // integers that indiate if a number is used in
                           // the puzzle
   int i=0,j=0;

   // initialise all numbers as not found
   for(int i=0;i<size;i++)
   {
      for(int j=0;j<size;j++)
      {
         temp[i][j]=0;
      }

   }

   // note all the numbers that appear on the puzzle
    for( i=0;i<size;i++)
    {
      for( j=0;j<size;j++)
      {
      
        if(puzzle[i][j]<0 || puzzle[i][j]>=size*size)
         {
            return false;
         }
        else if(puzzle[i][j]==0)
         temp[size-1][size-1]+=1;
        else
          temp[(puzzle[i][j]-1)/size][(puzzle[i][j]-1)%size]+=1;
      }

    }

   // check which numbers appear in the puzzle
    for( i=0;i<size;i++)
    {
      for(j=0;j<size;j++)
       {
           if(!temp[i][j]) 
               return false;
       }
    }

   return true;

}



int createRandomPuzzle(int*** puzzle,int size)
{

   if(puzzle==NULL)
      return EXIT_FAILURE;

      *puzzle=(int**)malloc(size*sizeof(int*));

      if(*puzzle==NULL)
         return EXIT_FAILURE;

      for(int i=0;i<size;i++)
      {
         (*puzzle)[i]=(int*)malloc(sizeof(int)*size);
      
         if((*puzzle)[i]==NULL)
            return EXIT_FAILURE;
      }

   
      for(int i=0;i<size;i++)
         for(int j=0;j<size;j++)
            (*puzzle)[i][j]=i*size+j;

         shufflePuzzle(*puzzle, size);
     

      return EXIT_SUCCESS;

}


static void shufflePuzzle(int** puzzle,int size)
{
   srand(time(NULL));


   int count=1,r=0,c=0,temp=0;
      
   while(count<=100)
   {
      for(int i=0;i<size;i++)
      {
         for(int j=0;j<size;j++)
         {
            r=rand()%size;
            c=rand()%size;

            temp=(puzzle)[i][j];
            (puzzle)[i][j]=(puzzle)[r][c];
            (puzzle)[r][c]=temp;
   
         }

      }
      
   count++;

   }

}




#ifdef DEBUG_PUZZLE_ARRAY

static void printMenu()
{
   printf("1 ) Create a puzzle from reading from a file . \n");
   printf("2 ) Create a copy of the puzzle.\n");
   printf("3 ) Print the puzzles.\n");
   printf("4 ) Check if the puzzles are equal.\n");
   printf("5 )Calculate grades of puzzles.\n");
   printf("6 ) Move the blank Tile of the first puzzle.\n");
   printf("7 ) Exit the DEBUG_PUZZLE_ARRAY.\n");

   printf("Give your option :\n");

}

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
   
   int** puzzle=NULL;
   int size=0;

   int** previousPuzzle=NULL; 
   int size2=0;
   
      
   int option=0; 
   int status=0;
   char* line=NULL;
   size_t nbytes=100;
   int sizeName=CHARS_PER_LINE;
   bool correctOption=false;



     

   do{

      printMenu();      

      option=0;
      correctOption=false;
      

      do{
         getline(&line,&nbytes,stdin);
         cutStringAtFirstNewLineCharacter(line);
         correctOption=isIntegerNumber(line);

      }while(!correctOption);

      option=atoi(line);      
     

      switch (option)
       {
             case (1) :  
      
                  // moves the puzzle to the previousPuzzle variable
                  // and the and the previous value of previousPuzzle is deleted
                  if(previousPuzzle!=NULL)
                     deletePuzzle(&previousPuzzle,size2);
   
                  previousPuzzle=createCopyOfPuzzle(puzzle,size);
                  size2=size;

                   if(puzzle!=NULL)
                 deletePuzzle(&puzzle,size);
         

               
                  printf("Give the name of the file :\n");

                  do{
                    getline(&line,&nbytes,stdin) ; 
   
                  }while(strlen(line)<=0);

                  cutStringAtFirstNewLineCharacter(line);                                 
                  // reads an integer number from the keyboard
                 
         
                 if(createPuzzleFromFile(&puzzle,&size,line)==EXIT_FAILURE)
                  {
                   printf("The puzzle couldn't be created from the file!\n\n");
                   
                   break;
                  }
                  else printf("The puzzle was created succesfully.\n\n");
   
               
               // if the format of the puzzle isn't correct ERROR
                  if(!isCorrectPuzzleFormat( puzzle, size))
                  {
                     printf("The puzzle from the file doesn't have a correct"
                     " format\n\n");

                      deletePuzzle(&puzzle,size);
                      size=0;

                  }
                  else 
                      printf("The puzzle from the file has a correct"
                     " format\n\n");


                  printf("\n\n");

                break;

   
            case (2) : 

                   if(previousPuzzle!=NULL)
                     deletePuzzle(&previousPuzzle,size2);     


                  int**cpyPuzzle=createCopyOfPuzzle(puzzle,size);   
   

                  if(cpyPuzzle==NULL)
                  {
                      printf("Problem in creating a copy of the array.\n");
                        break;
                  }

                    
                  previousPuzzle=puzzle;
                  size2=size;
      
                  puzzle=cpyPuzzle;

                        
                  break;


         case (3) : 
               if(puzzle!=NULL)  // prints the first puzzle if isn't NULL
               {
                  printf("------------------ Puzzle 1 ------------------ \n");
                  printf("Size = %d\n\n",size);
                  printPuzzle( puzzle,size);
                  printf("----------------------------------------------\n\n");
               }
               else printf("Puzzle 1 doesn't exist.\n\n");
               

               if(puzzle!=NULL)  // prints the second puzzle if isn't NULL
               {
                  printf("------------------ Puzzle 2 ------------------ \n");
                  printf("Size = %d\n\n",size2);
                  printPuzzle(previousPuzzle,size2);
                  printf("----------------------------------------------\n\n");
               }
               else printf("Puzzle 2 doesn't exist.\n\n") ;           

               

              break;
   
        case (4) :

                     if( size!=size2 || !puzzlesAreEqual(puzzle,previousPuzzle,size))
                     {
                        printf("The puzzles aren't equal.\n\n");
                     }
                     else printf("The puzzles are equal.\n\n");

                     
                  break ;

           case (5) :   // The grades-Manhattan distances of the puzzles
         

               printf("Puzzle 1 has grade-search distance -> %d\n\n",calculateGradeOfPuzzle(puzzle, size));
   
               printf("Puzzle 2 has grade-search distance -> %d\n\n",calculateGradeOfPuzzle(previousPuzzle, size2));

               

               break ;


           case (6) :
                           
                     if(puzzle==NULL)
                      {
                          printf("The puzzle 1 is NULL\n\n");
                          break;
                      }
   
                     printf("------------------ Puzzle 1 ------------------ \n");
                     printf("Size = %d\n\n",size);
                     printPuzzle( puzzle,size);
                     printf("----------------------------------------------\n\n");

                     printf("Where do you want to move the blank Tile?\n");
                     printf("0 : right.\n");
                     printf("1 : down.\n");
                     printf("2 : left.\n");
                     printf("3 : up.\n");
                        
                     int moveOption=0;
                     int gradeChange=0;
            
                     scanf("%d",&moveOption);
   
                     int srcRow=0,srcColumn=0;     
   
                     findBlankTile(puzzle,size,&srcRow,&srcColumn);

                     if(movePuzzleBlankTile(puzzle,size,srcRow,srcColumn, moveOption,&gradeChange)==EXIT_SUCCESS)
                      {
                          printf("The blank Tile was moved succesfully\n\n");
   
                          printf("------------------ Puzzle 1 ------------------ \n");
                          printf("Size = %d / Grade change = %d\n\n",size,gradeChange);
                          printPuzzle( puzzle,size);
                          printf("----------------------------------------------\n\n");   


                     } 
                     else printf("Cannot move the blank Tile to that direction.\n\n"); 

                                 

                    break;   

           case (7) : printf("Exiting the DEBUG_PUZZLE_ARRAY\n\n"); 
                       
                     break;              

           default : break;

      }  


      


   }while(option!=7 && status!=EXIT_FAILURE);

   if(puzzle!=NULL)
      deletePuzzle(&puzzle,size);

   if(previousPuzzle!=NULL)
         deletePuzzle(&previousPuzzle,size2);
   
   free(line);

   return 0;
}

#endif






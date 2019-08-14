
#include "DoubleLinkedQueue.h"

// we suppose that from tail we insert elements normally in queues
// and at head we remove elements

QUEUE* createQueue()
{
   QUEUE* aQueue=(QUEUE*)malloc(sizeof(QUEUE));
   
   if(aQueue==NULL)
      return NULL;

   aQueue->frontier_head=NULL;
   
   aQueue->frontier_tail=NULL;

   aQueue->size=0;
   
   return aQueue;
}


int enqueue(QUEUE* queue,TREE_NODE* treeNode)
{
      if(queue==NULL || treeNode==NULL)
            return EXIT_FAILURE;

      FRONTIER_NODE*  node=(FRONTIER_NODE*)malloc(sizeof(FRONTIER_NODE));  
   
      if(node==NULL)
         return EXIT_FAILURE;

      node->leaf=treeNode;

      node->next=NULL;

      node->previous=NULL;      

      if(node==NULL)
         return EXIT_FAILURE;

   
      // the case where the queue was empty
     if(queue->frontier_tail==NULL)
      {
            queue->frontier_tail=queue->frontier_head=node;    
            (queue->size)=1;
      }
      else
      {
         node->previous=queue->frontier_tail;
         queue->frontier_tail->next=node;
         queue->frontier_tail=node;
         (queue->size)++;
      }

   

   return EXIT_SUCCESS;
}


int dequeue(QUEUE* queue,TREE_NODE** returnTreeNode)
{
      if(queue==NULL || queue->frontier_head==NULL || returnTreeNode==NULL)
         return EXIT_FAILURE;

      FRONTIER_NODE*  node=queue->frontier_head;

      *returnTreeNode=node->leaf;

      queue->frontier_head=queue->frontier_head->next;

      if(queue->frontier_head==NULL)
      {
         queue->frontier_tail=NULL;
         queue->size=0;
      }      
      else
      { 
         queue->frontier_head->previous=NULL; 
         (queue->size)--;     
      }

      free(node);

      return EXIT_SUCCESS;

}


int priorityEnqueue(QUEUE* queue,TREE_NODE* treeNode)
{
   
  
      if(queue==NULL || treeNode==NULL)
         return EXIT_FAILURE;


       FRONTIER_NODE*  node=(FRONTIER_NODE*)malloc(sizeof(FRONTIER_NODE));  
   
      if(node==NULL)
         return EXIT_FAILURE;

      node->leaf=treeNode;

      node->next=NULL;

      node->previous=NULL;

 
      // the case where the queue was empty
     if(queue->frontier_tail==NULL)
      {
            queue->frontier_tail=queue->frontier_head=node;    
            (queue->size)=1;
      }
      else if(((queue->frontier_head->leaf->g)+(queue->frontier_head->leaf->h)) > ((node->leaf->g)+(node->leaf->h))){

             queue->frontier_head->previous=node;
             node->next=queue->frontier_head;
             queue->frontier_head=node;
             (queue->size)++;
      }
     else{      
             FRONTIER_NODE* pointer=queue->frontier_head;

           

            while(pointer!=NULL)
            {
               if(((pointer->leaf->g)+(pointer->leaf->h)) > ((node->leaf->g)+(node->leaf->h)))
                 {
                  
                     node->next=pointer;
                     node->previous=pointer->previous;
                     pointer->previous=node;

                     if(node->previous!=NULL)
                        node->previous->next=node;  
      
                     (queue->size)++; 
                     return EXIT_SUCCESS;
                 }
               pointer=pointer->next;
            }

      
             queue->frontier_tail->next=node;
            node->previous=queue->frontier_tail;
            queue->frontier_tail=node;
            (queue->size)++;

      }   


      return EXIT_SUCCESS;
}


void deleteQueue(QUEUE* queue)
{
   if(queue==NULL)
      return ;

   FRONTIER_NODE* node=NULL;
   
   while(queue->frontier_head!=NULL)
   {
      node=queue->frontier_head;
      queue->frontier_head=queue->frontier_head->next;
      free(node);
   }

   free(queue);

}



bool isEmpty(QUEUE* queue)
{
      if(queue==NULL)
         return true;

      return queue->frontier_tail==NULL;

}




void printQueue(QUEUE* queue,int sizePuzzle)
{
   if(queue==NULL)
         return ;

   FRONTIER_NODE* node=queue->frontier_head;

   printf("Size = %d\n",queue->size);

   while(node!=NULL)
   {
      printNode( node->leaf, sizePuzzle);

      printf("\n");

      node=node->next;
   }

}
#ifdef DEBUG_DOUBLE_LINKED_QUEUE

// checks if a sequence of characters is an integer number
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

static void printMenu()
{
   printf("1 ) Enqueue random treeNode.\n");
   printf("2 ) Dequeue .\n");
   printf("3 ) Print the queue.\n");
   printf("4 ) Exit DOUBLE_LINKED_QUEUE.\n");

}


int main(int argc,char* argv[])
{
    QUEUE* queue=createQueue();

    int option=0;
    TREE_NODE* node=NULL;

    bool correctOption=false;
    bool usePriorityEnqueue=true;
    char* line=NULL;
    size_t nbytes=100;
    int** puzzle;
    int sizePuzzle=3;
   
   do{

       printMenu();
      printf("\nGive your option.\n");

      do{
         getline(&line,&nbytes,stdin);
         cutStringAtFirstNewLineCharacter(line);
         correctOption=isIntegerNumber(line);

      }while(!correctOption);
      // take an integer number from the keyboard       

      option=atoi(line); 

      switch (option)
      {
         case 1 :    createRandomPuzzle(&puzzle,sizePuzzle);
                     

                     node=createRootOfTree(puzzle, sizePuzzle);

                     printf("Node to add is :\n");
                     printNode(node,sizePuzzle);
   
                     if(usePriorityEnqueue && priorityEnqueue(queue,node)==EXIT_SUCCESS)
                     {
                        
                        printf("The element was enqueued succesfully.\n");
                     }   
                     else if(!usePriorityEnqueue && enqueue(queue,node)==EXIT_SUCCESS)
                     {
                        printf("The element was enqueued succesfully.\n");
                     }
                     else printf("The element couldn't be queued.\n");

                     
                     break;

         case 2 :    if(dequeue(queue,&node)==EXIT_SUCCESS)
                     {
                        printf("Node Dequeued is :\n");
                        printNode(node,sizePuzzle);
                        printf("\n");

                     }
                     else printf("Couldn't dequeue.\n");
                     break;

         case 3 :    printf("\n<<<<<<<<<<<<<< QUEUE >>>>>>>>>>>>>>\n");
                     printQueue(queue,sizePuzzle);
                     printf("\n<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>\n");
                     break;

         case 4 :    printf("Exiting the DOUBLE_LINKED_QUEUE.\n");
                     break;

         default :   printf("Undefined option.\n");
                     break;
               
         
      }

      printf("\n");
   
   }while(option!=4);


   deleteQueue(queue);

   return 0;
}

#endif




/*Tokenizer project using Linked List Structure to hold data*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Token 
{
	char *data;
	char *tokenType;	
	struct Token *next;
}*head;

typedef struct Token Token;
		

Token *CreateToken( char * ts ) 
{

		/* Creates an empty token node */
	Token *newToken;
       	newToken  = (struct Token*)malloc(sizeof(Token));   
  	return newToken;
}


void DestroyToken( Token * tk ) 
{
   
   Token *iterator=head;
   /*In case the linked list is empty*/
   if (iterator==NULL)
   {
	   return;
   }
   
   /*in case there is only one thing in the linked list*/
   else if (iterator->next==NULL)
   {
	   free(tk);
	   iterator->next=NULL;
   }
   
   /*for all other cases*/
   else
   {
	   while (iterator->next!=NULL)
	   {
		   if (strcmp(iterator->next->data,tk->data)==0)
		   {
			   iterator->next=tk->next;
			   free(tk);
		   }
		   iterator=iterator->next;
	   }
   }

}


char *GetNextToken( Token * tk ) {

  return NULL;
}

int main(int argc, char **argv) {
	
	int i = strlen(argv[1]);
	char arrayofstrings[i];
	strcpy(arrayofstrings, argv[1]); // copies the string into the array
	// keep this part, it should be fine, just stores the string into the array using its string length. 
	// the part below is not right but it splits up the array based off of tabs and whitespaces. 
	// I kind of understand the If Statements now, we can just check each character then
	// I'll add the if statements below
	
	int g;
	
	for (g = 0; g < i; g ++){ // this will go through each index of the array checking each character
	// the if statements will be in the loop

		if(isspace(arrayofstrings[g])){
      			printf("This is a white space: %s\n", argv[g] );
      			printf("This is the index id: %d\n", g);
      		}
      	}
	
  return 0;
}

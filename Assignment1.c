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

void populateTokenList(char* input)
{
	/* indicates how many times to iterate */
	int i = sizeof(input);

	/*Z keeps track of the beggining index*/
	int z = 0;
	
	/* Y keeps track of the ending */
	int y = 0;  
	
	while (z < i)
	{ // go through the entire array until it hits NULL character
		if (input[z]=='0')
		{ // big if statement for all 0 if statements
		
			if(input[z+1]=='X')
			{ // if the second character begins with BIG X, its a hexadecimal 
				y = z+2; // checks for everything after realizing its a hexadecimal
				while (isalnum(input[y]))
				{
						y++; // keeps count of how many indexes are part of the token.
	
						if (input[y] == '\0'){ // if it hits the end of the string, this adds on the null character index.
							y++;
							break;
						}
 						
				}
					
				int d = z; // goes to the beginning of the token
				int lengthoftoken = y-z; // determine how long the token actually is
				char newtokenstring[lengthoftoken]; // form a new array for the token
				int b = 0;	// variable used to loop through entire new array and add onto each character
				
				for (d=z; d<y; d++){ // loops through the input array and token array and adds on each character
						newtokenstring[b] = input[d];
						b++;
				}	
					
				int test; // used this to test for the size to make sure it includes the Null character.
				test = sizeof(newtokenstring);
				printf("This is the size of the token: %d\n", test);
				printf("%s\n", newtokenstring);			
					
			}
		}
	z++;
	}
}
int main(int argc, char **argv) {
	
	int i = sizeof(argv[1]); // size of function includes the Null character 
	char arrayofstrings[i];
	strcpy(arrayofstrings, argv[1]); // also includes the null character in the copying
	populateTokenList(arrayofstrings);
	

	
  return 0;
}

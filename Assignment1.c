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

void populateTokenList(char* input, int i)
{
	
/*
A word token is an alphabetic character followed by any number of alphanumeric characters.
A decimal integer constant token is a digit (0-9) followed by any number of digits.
An octal integer constant token is a 0 followed by any number of octal digits (i.e. 0-7).
A hexadecimal integer constant token is 0x (or 0X) followed by any number of hexadecimal digits
(i.e. 0-9, a-f, A-F).
A floating-point constant token is follows the rules for floating-point constants in Java or C.
C operator tokens are any of the C operators shown in your C language reference card.
*/
	
	
	int z=0;
	int y=0;
	
	
	while (z<i)
	{
		if (input[z]=='0'){ // big if statement for all 0 if statements
				
			if(input[z+1]=='X'){
				y = z+2;
				while (isalnum(input[y])){
					y++;
 					printf ("These values are all hexadecimal\n");
 					break;
				}
				
			}
				
			if(input[z+1]=='x'){
				y = z+2;
				while (isalnum(input[y])){
					y++;
 					printf ("These values are all hexadecimal\n");
 					break;
					}	
				}
			}
		
		if (isdigit(input[z]) && input[z]!= '0'){
				
			if (isdigit(input[z+1])){
				y = z+2;
				while (isdigit(input[y])){
					y++;
 					printf ("These are all integars\n");
 					break;
				}
			}
				
		}
		break;	
	}

int main(int argc, char **argv) {
	
	int i = strlen(argv[1]);
	char arrayofstrings[i];
	strcpy(arrayofstrings, argv[1]);
	populateTokenList(arrayofstrings, i);
	

	
  return 0;
}

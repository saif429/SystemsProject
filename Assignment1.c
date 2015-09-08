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
		

Token *CreateToken(char * ts) 
{
	/*if the token linked list is empty*/
	
	if (head==NULL)
	{
		Token *newToken=(struct Token*)malloc(sizeof(Token));
       	newToken->data=ts;
		head=newToken;
		newToken->next=NULL;
       	return newToken;
	}
	
	/* If the token list has at least 1 or more things in it */
	else
	{
		/*Iterator*/
		Token *iter=head;
		
		while (iter->next!=NULL)
		{
			iter=iter->next;
		
		}
		
		
		Token *newToken=(struct Token*)malloc(sizeof(Token));       	
       	newToken->data=ts;
       	iter->next=newToken;
		newToken->next=NULL;
       	return newToken;
	}
	
}

/*Destroys the linked list entirely, probably not the right way to do this */
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

void printAllTokens()
{
	Token *iterator=head;
	
	while (iterator!=NULL)
	{
		printf("%s\n", iterator->tokenType);
		iterator=iterator->next;
	}
}

char *GetNextToken( Token * tk ) {

  return NULL;
}

void createNewString (char* input, char* type, int y, int z)
{
	/* Gets the start of the token */	
	int TokenStart = z;
	/*Gets the length of the token */
	int TokenLength = y-z;
				
	/*Creates a string for just the token */
	char NewToken[TokenLength];
				
	/* Temporary variable simply used to add the token to the NewToken string */
	int b = 0;
				
	/*Loops through the input string, and adds the token to the NewToken string*/
	for (TokenStart=z; TokenStart<y; TokenStart++)
	{
		NewToken[b] = input[TokenStart];
		b++;
	}
printf("%s\n",NewToken);	
	Token *temporary=CreateToken(NewToken);
	temporary->tokenType=type;
	
}

void populateTokenList(char* input)
{
	/* indicates how many times to iterate */
	int i = strlen(input);

	/*Z keeps track of the beggining index*/
	int z = 0;
	
	/* Y keeps track of the ending */
	int y = 0;  
	
	while (z < i)
	{ // go through the entire array until it hits NULL character
	
		
	/*This if statement handles tokens that start with 0 */
	/*Hexadecimal eg. 0x */
	/*Octal eg. 0532 */
		if (input[z]=='0')
		{ 
		
			/*for finding hexadecimal characters*/
			if(input[z+1]=='x')
			{  
				/* Y is the stuff after the hexadecimal identifier */
				y = z+2; 
				while (isalnum(input[y]))
				{
						y++; // keeps count of how many indexes are part of the token.
	
						if (input[y] == '\0')
						{ // if it hits the end of the string, this adds on the null character index.
							y++;
							break;
						}
				}
					
				createNewString(input,"Hexadecimal",y,z);

					
			}
			else
			{
				y=z+1;
				while (isdigit(input[y]))
				{
						/*keeps count of how many indexes have been iterated through*/
						y++; 
	
						/* if the end of string is hit, add 1 to y in order to account for the null character index */
						if (input[y] == '\0')
						{ 
							y++;
							break;
						}
				}
				createNewString(input,"Octal",y,z);
			}
			
		}
	z++;
	}
}

/* The main function */
int main(int argc, char **argv) 
{
	
	populateTokenList(argv[1]);	
	printAllTokens();
	
  return 0;
}

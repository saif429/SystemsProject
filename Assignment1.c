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
		

Token *CreateToken(char * ts, char * type) 
{
	/*if the token linked list is empty*/
	
	
	
	if (head==NULL)
	{
		Token *newToken=(struct Token*)malloc(sizeof(Token));
       	newToken->data=ts;
		newToken->tokenType=type;	
		newToken->next=NULL;
		head=newToken;
       	return head;
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
		newToken->tokenType=type;
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
	Token *i=head;
	while (i!=NULL)
	{	
		printf("%s",i->tokenType);
		printf(" %s\n",i->data);
		
		i=i->next;
	}
}

char *GetNextToken( Token * tk ) 
{
  return NULL;
}

void createNewString (char* input, char* type, int y, int z)
{
	/* Gets the start of the token */	
	int TokenStart = z;
	/*Gets the length of the token */
	int TokenLength = y-z;
				
	/*Creates a string for just the token */
	/*Fixes a null termination bug */
	char *NewToken=malloc((TokenLength+1)*sizeof(char*));
	NewToken[TokenLength+1]='\0';
	
				
	/* Temporary variable simply used to add the token to the NewToken string */
	int b = 0;
				
	/*Loops through the input string, and adds the token to the NewToken string*/
	for (TokenStart=z; TokenStart<y; TokenStart++)
	{
		NewToken[b] = input[TokenStart];
		b++;
	}	
	if (strcmp(type,"Malformed Token")==0)
	{
		CreateToken(" ",type);
		return;
	}
	
	CreateToken(NewToken,type);
	
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
			if(input[z+1]=='x' || input[z+1] == 'X')
			{  
				/* Y is the stuff after the hexadecimal identifier */
				y = z+2; 
				while (isalnum(input[y]) && input[y]<'g')
				{
						y++; // keeps count of how many indexes are part of the token.
	
						if (input[y] == '\0')
						{ // if it hits the end of the string, this adds on the null character index.
							y++;
							break;
						}
				}
					
				createNewString(input,"Hexadecimal",y,z);
				z=y;
					
			}
			/*checks octal */
			else if (isdigit(input[z+1]) && (input[z+1]-'0')<=7)
			{
				y=z+1;
				while (isdigit(input[y]) && (input[z+1]-'0')<=7)
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
				z=y;
			}
			else if(input[z+1]=='.')
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
				
				createNewString(input,"Floating Point",y,z);
				z=y;
			}
			else
			{
				createNewString(input,"Malformed Token",0,0);
				z=y;
				z+=2;
				
			}
		}
		else if (isalpha(input[z]))
		{
			y = z+1;
			while (isalpha(input[y]))
			{
				y++;
				if (input[y] == '\0')
				{ // if it hits the end of the string, this adds on the null character index.
					y++;
					break;
				}
			}
			createNewString(input,"word",y,z);
			z=y;
			
		}
		else if (isdigit(input[z]))
		{
			y = z+1;
			while (isdigit(input[y]))
			{
				y++;
				if (input[y] == '\0')
				{ // if it hits the end of the string, this adds on the null character index.
					y++;
					break;
				}
			}
			createNewString(input,"Decimal",y,z);
			z=y;
			
		}
		if (input[z]==' ')
		{
			z++;
		}
		
		
	}
}

/* The main function */
int main(int argc, char **argv) 
{
	
	populateTokenList(argv[1]);	
	printAllTokens();
	
  return 0;
}

/*Tokenizer project using Linked List Structure to hold data*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Token Structure is based off a linked list
This was done so that we could store the tokens easily and then
be able to easily find a token or remove a token if needed
*/

struct Token 
{
	char *data;
	char *tokenType;	
	struct Token *next;
}
*head;

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

/*Prints the contens of the token linked list */

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

/* Creates a new token in the linked list, given a substring location, an input and the token type */
void createNewString (char* input, char* type, int y, int z)
{
	/* Gets the start of the token */	
	int TokenStart = z;
	/*Gets the length of the token */
	int TokenLength = y-z;
				
	/*Creates a string for just the token */
	/*Fixes a null termination bug */
	char *NewToken=malloc((TokenLength+1)*sizeof(char*));
	/*removing +1 fixes a null termiantion thing*/
	NewToken[TokenLength]='\0';
	
				
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

/* Populates the token list during the initial run */
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
				continue;
					
			}
			/*checks octal */
			else if (isdigit(input[z+1]) && (input[z+1]-'0')<=7)
			{
			int r = 0;
				y=z+1;
				while (isdigit(input[y]) && input[y]-'0'<=7)
				{
						/*keeps count of how many indexes have been iterated through*/
						y++; 
						
						if (input[y] == '.'){
						r++;
						}
	
						/* if the end of string is hit, add 1 to y in order to account for the null character index */
						if (input[y] == '\0')
						{ 
							y++;
							break;
						}
				}
				
				if (r == 0){
				createNewString(input,"Octal",y,z);
				z=y;
				}
				else if (r!=0)
				{			
					y = y+1;
					while (isdigit(input[y]) || input[y]=='e' || input[y]=='E' || (input[y]=='-' && isdigit(input[y])))
					{
						/*keeps count of how many indexes have been iterated through*/
						y++; 
	
						/* if the end of string is hit, add 1 to y in order to account for the null character index */
						if (input[y] == '\0')
						{ 
							y++;
							break;
						}
						
						if (input[y] == '0'){
							if (input[y+1] == 'X' || input[y+1] == 'x'){
								break;
							}
						}
				}
				
				createNewString(input,"Floating Point",y,z);
				z=y;
				continue;
			}	
			
			}
			/*  added E for floating point stuff" */
			
			else if(input[z+1]=='.' || input[z+1]=='e' || input[z+1]=='E')
			{
				y=z+2;
				
				while (isdigit(input[y]) || input[y]=='e' || input[y]=='E' || (input[y]=='-' && isdigit(input[y+1])))
				{
						/*keeps count of how many indexes have been iterated through*/
						y++; 
	
						/* if the end of string is hit, add 1 to y in order to account for the null character index */
						
						if (input[y] == '\0')
						{ 
							y++;
							break;
						}
						
						if (input[y] == '0')
						{
							if (input[y+1] == 'X' || input[y+1] == 'x'){
								break;
							}
						}
				}
				
				createNewString(input,"Floating Point",y,z);
				z=y;
				continue;
			}
			else
			{
				createNewString(input,"Malformed Token",0,0);
				z=y;
				z+=2;
				
			}
		}
		/*for words */
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
		/*Does regular digits*/
		else if (isdigit(input[z]) && input[z+1]!='.')
		{
			y = z+1;
			int h = 0;
			while (isdigit(input[y])) // in this statement we need to have something for floating point
			{
				
				if (input[y]=='0')
				{
					if (input[y+1]=='x' || input[y+1] == 'X')
					{
						break;
					}
				}
				y++;
				
				/*For floating point and floating point with E*/
				if (input[y] == '.' || input[y] == 'E' || input[y] == 'e' )
				{
					h++;
				}
				
				if (input[y] == '\0')
				{ // if it hits the end of the string, this adds on the null character index.
					y++;
					break;
				}

			}
			if (h == 0)
			{
			createNewString(input,"Decimal",y,z);
			z=y;
			}
			else if (h!=0)
			{			
			y = y+1;
				while (isdigit(input[y]) || input[y]=='e' || input[y]=='E' || (input[y]=='-' && isdigit(input[y+1])))
				{
						/*keeps count of how many indexes have been iterated through*/
						y++; 
	
						/* if the end of string is hit, add 1 to y in order to account for the null character index */
						if (input[y] == '\0')
						{ 
							y++;
							break;
						}
						
						if (input[y] == '0'){
							if (input[y+1] == 'X' || input[y+1] == 'x'){
								break;
							}
						}
				}
				
				createNewString(input,"Floating Point",y,z);
				z=y;
				continue;
			}	
		}
		/*added e for floating point*/
		else if (isdigit(input[z]) && (input[z+1]=='.' || input[z+1]=='E' || input[z+1]=='e'))
		{
			y=z+2;
				while (isdigit(input[y]) || input[y]=='e' || input[y]=='E' || (input[y]=='-' && isdigit(input[y+1])))
				{
						/*keeps count of how many indexes have been iterated through*/
						y++; 
	
						/* if the end of string is hit, add 1 to y in order to account for the null character index */
						if (input[y] == '\0')
						{ 
							y++;
							break;
						}
						
						if (input[y] == '0'){
							if (input[y+1] == 'X' || input[y+1] == 'x'){
								break;
							}
						}
				}
				
				createNewString(input,"Floating Point",y,z);
				z=y;
				continue;
		}
		
		
		switch (input[z])
		{
			case '+' :
				y=z+1;
				createNewString(input,"Addition",y,z);
				z=y;
				break;
			case '-' :
				y=z+1;
				createNewString(input,"Subtraction",y,z);
				z=y;
				break;
			case '*' :
				y=z+1;
				createNewString(input,"Multiplication",y,z);
				z=y;
				break;
			case '%' :
				y=z+1;
				createNewString(input,"Modulus",y,z);
				z=y;
				break;
			case '=' :
				y=z+1;
				createNewString(input,"Assignment",y,z);
				z=y;
				break;
			case '>' :
				y=z+1;
				createNewString(input,"Greater Than",y,z);
				z=y;
				break;
			case '<' :
				y=z+1;
				createNewString(input,"Less Than",y,z);
				z=y;
				break;
			case '|' :
				y=z+1;
				createNewString(input,"Bitwise Inclusive Or / Line",y,z);
				z=y;
				break;
			case '&' :
				y=z+1;
				createNewString(input,"Bitwise And / Ampersand",y,z);
				z=y;
				break;
			case '^' :
				y=z+1;
				createNewString(input,"Exclusive Or / Carret",y,z);
				z=y;
				break;
			case '?' :
				y=z+1;
				createNewString(input,"Question Mark",y,z);
				z=y;
				break;
			case ':' :
				y=z+1;
				createNewString(input,"Conditional Expression / Colon",y,z);
				z=y;
				break;
			case ',' :
				y=z+1;
				createNewString(input,"Comma",y,z);
				z=y;	
				break;
			case ';' :
				y=z+1;
				createNewString(input,"End of Expression / Semi Colon",y,z);
				z=y;
				break;
			case '/' :
				y=z+1;
				createNewString(input,"Slash",y,z);
				z=y;
				break;
			case '\\' :
				y=z+1;
				createNewString(input,"Backslash",y,z);
				z=y;
				break;
			case '[' :
				y=z+1;
				createNewString(input,"Left Brace",y,z);
				z=y;
				break;
			case ']' :
				y=z+1;
				createNewString(input,"Right Brace",y,z);
				z=y;
				break;
			case '{' :
				y=z+1;
				createNewString(input,"Left Bracket",y,z);
				z=y;
				break;
			case '}' :
				y=z+1;
				createNewString(input,"Right Bracket",y,z);
				z=y;
				break;
			case '_' :
				y=z+1;
				createNewString(input,"Underscore",y,z);
				z=y;
				break;
			case '#' :
				y=z+1;
				createNewString(input,"Hash",y,z);
				z=y;
				break;
			case '!' :
				y=z+1;
				createNewString(input,"Not / Exclamation",y,z);
				z=y;
				break;
			case '`' :
				y=z+1;
				createNewString(input,"Tilde",y,z);
				z=y;
				break;
			case '(' :
				y=z+1;
				createNewString(input,"Left Parenthesis",y,z);
				z=y;
				break;
			case ')' :
				y=z+1;
				createNewString(input,"Right Parenthesis",y,z);
				z=y;
				break;
			default :
				z++;
				break;
				
				
			
		}
		/*if (input[z]==' ')
		{
			z++;
		}
		*/
		
		
	}
}

/* The main function */
int main(int argc, char **argv) 
{
	if (argv[1]==NULL)
	{
		printf("%s\n", "No Argument");
		return 0;
	}
	
	populateTokenList(argv[1]);	
	
	printAllTokens();
	
  return 0;
}

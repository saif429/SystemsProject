#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Stores the token and the token type */

struct Token 
{
	char *data;
	char *tokenType;	
};

typedef struct Token Token;

/*Creates the token structure */
/* A glorified substring finder*/

Token *Create(char * input, char * type, int y, int z) 
{

	int TokenStart = z;
	int TokenLength = y-z;
	char *NewToken=malloc((TokenLength+1)*sizeof(char*));
	NewToken[TokenLength]='\0';
	
	/*Copies the substring to a string */		
	int b = 0;
	for (TokenStart=z; TokenStart<y; TokenStart++)
	{
		NewToken[b] = input[TokenStart];
		b++;
	}	
	
	/* stores stuff in the structure */
	Token *newToken=(struct Token*)malloc(sizeof(Token));
       	newToken->data=NewToken;
	newToken->tokenType=type;
	return newToken;

}

/* Basically frees the specified token */
void DestroyToken( Token * tk )
{
	free(tk);
}

/* Depreciated. Does not work, we have another function that extracts all the tokens at once instead
of looping the getnexttoken function */
char *GetNextToken( Token * tk ) 
{
  return NULL;
}

/*  USed to populate the linked list, now it checks the string
array and prints out tokens based on the input */
void populateTokenList(char* input)
{
	/* indicates how many times to iterate */
	int i = strlen(input);

	/*Z keeps track of the beggining index*/
	int z = 0;
	
	/* Y keeps track of the ending */
	int y = 0;  
	
	while (z < i)
	{	
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
					y++;
	
					if (input[y] == '\0')
					{ 
						y++;
						break;
					}
				}
					
				Token *hextoken = Create(input,"Hexadecimal",y,z);
				printf("%s ", hextoken->tokenType);
				printf("%s\n", hextoken->data);
				DestroyToken(hextoken);
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
						
						if (input[y] == '.')
						{
						r++;
						}
	
						/* if the end of string is hit, add 1 to y in order to account for the null character index */
						else if (input[y] == '\0')
						{ 
							y++;
							break;
						}
				}
				
				if (r == 0)
				{
					Token *octaltoken = Create(input,"Octal",y,z);
					printf("%s ", octaltoken->tokenType);
					printf("%s\n", octaltoken->data);
					DestroyToken(octaltoken);
					z=y;
				}
				
				/* A floating point decimal check */
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
						
						if (input[y] == '0' && (input[y+1] == 'X' || input[y+1] == 'x'))
						{
							break;
						}
				}
				
				Token *floatingpointtoken = Create(input,"Floating Point",y,z);
				printf("%s ", floatingpointtoken->tokenType);
				printf("%s\n", floatingpointtoken->data);
				DestroyToken(floatingpointtoken);
				z=y;
				continue;
			}	
			
			}
			
			/* Another floating point check */	
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
						
					if (input[y] == '0'&& (input[y+1] == 'X' || input[y+1] == 'x'))
					{
						break;
					}
				}
				
				Token *floatingpointtoken = Create(input,"Floating Point",y,z);
				printf("%s ", floatingpointtoken->tokenType);
				printf("%s\n", floatingpointtoken->data);
				DestroyToken(floatingpointtoken);
				z=y;
				continue;
			}
			else
			{
				Token *malformedtoken = Create(input,"Malformed Token",0,0);
				printf("%s ", malformedtoken->tokenType);
				printf("%s\n", malformedtoken->data);
				DestroyToken(malformedtoken);
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
				{ 
					y++;
					break;
				}
			}
			Token *word = Create(input,"word",y,z);
			printf("%s ", word->tokenType);
			printf("%s\n", word->data);
			DestroyToken(word);
			z=y;
			continue;
			
		}
		/*Does regular digits*/
		else if (isdigit(input[z]) && input[z+1]!='.')
		{
			y = z+1;
			int h = 0;
			
			/* in this statement we need to have something for floating point? */
			while (isdigit(input[y])) 
			{
				/*breaks if it detects a hexadecimal */
				if (input[y]=='0' && (input[y+1]=='x' || input[y+1] == 'X'))
				{
					break;
				}
				
				y++;
				
				/*For floating point and floating point with E*/
				if (input[y] == '.' || input[y] == 'E' || input[y] == 'e' )
				{
					h++;
				}
				
				/* Null character check */
				else if (input[y] == '\0')
				{ 
					y++;
					break;
				}

			}
			
			if (h == 0)
			{
				Token *decimaltoken = Create(input,"Decimal",y,z);
				printf("%s ", decimaltoken->tokenType);
				printf("%s\n", decimaltoken->data);
				DestroyToken(decimaltoken);
				z=y;
			}
			
			/* Another floating point check for floating points that
			come after a long string of decimal digits */
			
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
						
					if (input[y] == '0' && (input[y+1] == 'X' || input[y+1] == 'x'))
					{
						break;
					}
				}
				
				Token *floatingpointtoken = Create(input,"Floating Point",y,z);
				printf("%s ", floatingpointtoken->tokenType);
				printf("%s\n", floatingpointtoken->data);
				DestroyToken(floatingpointtoken);
				z=y;
				continue;
			}	
		}
		/* Another floating point check */
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
						
				/*Checks for hexadecimal */
				else if (input[y] == '0' && (input[y+1] == 'X' || input[y+1] == 'x'))
				{
					break;
				}
			}
				
				Token *floatingpointtoken = Create(input,"Floating Point",y,z);
				printf("%s ", floatingpointtoken->tokenType);
				printf("%s\n", floatingpointtoken->data);
				DestroyToken(floatingpointtoken);
				z=y;
				continue;
		}
		
		/* Dual and triple operator check */
		if (input[z]=='<' && input[z+1]=='<' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Left Shift and Assignment",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='>' && input[z+1]=='>' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Right Shift and Assignment",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		
		
		else if (input[z]=='+' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Plus Equals",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='&' && input[z+1]=='&')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Logical And",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='-' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Minus Equals",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='=' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Comparison",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='*' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Multiplication Assignment",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='/' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Division Assignment",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='%' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Remainder Assignment",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='&' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Bitwise And Assignment",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='^' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Bitwise Exclusive Or Assignment",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='|' && input[z+1]=='=')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Bitwise Inclusive Or Assignment",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);			
			z=y;
			continue;
		}
		else if (input[z]=='|' && input[z+1]=='|')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Logical Or",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);	
			z=y;
			continue;
		}
		else if (input[z]=='<' && input[z+1]=='<')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Left Shift",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);	
			z=y;
			continue;
		}
		else if (input[z]=='>' && input[z+1]=='>')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Right Shift",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);	
			z=y;
			continue;
		}
		else if (input[z]=='-' && input[z+1]=='-')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Decrement",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);	
			z=y;
			continue;
		}
		else if (input[z]=='+' && input[z+1]=='+')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Increment",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='?' && input[z+1]=='-')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Conditional Expression",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		else if (input[z]=='-' && input[z+1]=='>')
		{
			y=z+2;
			Token *specialtoken = Create(input,"Structure Pointer",y,z);
			printf("%s ", specialtoken->tokenType);
			printf("%s\n", specialtoken->data);
			DestroyToken(specialtoken);
			z=y;
			continue;
		}
		
		
		/*Contains single character operators*/	
		switch (input[z])
		{
			case '+' :
				y=z+1;
				Token *specialtokenaddition = Create(input,"Addition",y,z);
				printf("%s ", specialtokenaddition->tokenType);
				printf("%s\n", specialtokenaddition->data);
				DestroyToken(specialtokenaddition);
				z=y;
				break;
			case '-' :
				y=z+1;
				Token *specialtokensubtraction = Create(input,"Subtraction",y,z);
				printf("%s ", specialtokensubtraction->tokenType);
				printf("%s\n", specialtokensubtraction->data);
				DestroyToken(specialtokensubtraction);
				z=y;
				break;
			case '*' :
				y=z+1;
				Token *specialtokenmultiplication = Create(input,"Multiplication",y,z);
				printf("%s ", specialtokenmultiplication->tokenType);
				printf("%s\n", specialtokenmultiplication->data);
				DestroyToken(specialtokenmultiplication);
				z=y;
				break;
			case '%' :
				y=z+1;
				Token *specialtokenmodulus = Create(input,"Modulus",y,z);
				printf("%s ", specialtokenmodulus->tokenType);
				printf("%s\n", specialtokenmodulus->data);
				DestroyToken(specialtokenmodulus);
				z=y;
				break;
			case '=' :
				y=z+1;
				Token *specialtoken = Create(input,"Assignment",y,z);
				printf("%s ", specialtoken->tokenType);
				printf("%s\n", specialtoken->data);
				DestroyToken(specialtoken);
				z=y;
				break;
			case '>' :
				y=z+1;
				Token *specialtokengreaterthan = Create(input,"Greater Than",y,z);
				printf("%s ", specialtokengreaterthan->tokenType);
				printf("%s\n", specialtokengreaterthan->data);
				DestroyToken(specialtokengreaterthan);
				z=y;
				break;
			case '<' :
				y=z+1;
				Token *specialtokenlessthan = Create(input,"Less Than",y,z);
				printf("%s ", specialtokenlessthan->tokenType);
				printf("%s\n", specialtokenlessthan->data);
				DestroyToken(specialtokenlessthan);
				z=y;
				break;
			case '|' :
				y=z+1;
				Token *specialtokeninclusiveor = Create(input,"Bitwise Inclusive Or / Line",y,z);
				printf("%s ", specialtokeninclusiveor->tokenType);
				printf("%s\n", specialtokeninclusiveor->data);
				DestroyToken(specialtokeninclusiveor);
				z=y;
				break;
			case '&' :
				y=z+1;
				Token *specialtokenand = Create(input,"Bitwise And / Ampersand",y,z);
				printf("%s ", specialtokenand->tokenType);
				printf("%s\n", specialtokenand->data);
				DestroyToken(specialtokenand);
				z=y;
				break;
			case '^' :
				y=z+1;
				Token *specialtokenexclusiveor = Create(input,"Exclusive Or / Carret",y,z);
				printf("%s ", specialtokenexclusiveor->tokenType);
				printf("%s\n", specialtokenexclusiveor->data);
				DestroyToken(specialtokenexclusiveor);
				z=y;
				break;
			case '?' :
				y=z+1;
				Token *specialtokenquestion = Create(input,"Question Mark",y,z);
				printf("%s ", specialtokenquestion->tokenType);
				printf("%s\n", specialtokenquestion->data);
				DestroyToken(specialtokenquestion);
				z=y;
				break;
			case ':' :
				y=z+1;
				Token *specialtokencolon = Create(input,"Conditional Expression / Colon",y,z);
				printf("%s ", specialtokencolon->tokenType);
				printf("%s\n", specialtokencolon->data);
				DestroyToken(specialtokencolon);
				z=y;
				break;
			case ',' :
				y=z+1;
				Token *specialtokencomma = Create(input,"Comma",y,z);
				printf("%s ", specialtokencomma->tokenType);
				printf("%s\n", specialtokencomma->data);
				DestroyToken(specialtokencomma);
				z=y;	
				break;
			case ';' :
				y=z+1;
				Token *specialtokensemicolon = Create(input,"End of Expression / Semi Colon",y,z);
				printf("%s ", specialtokensemicolon->tokenType);
				printf("%s\n", specialtokensemicolon->data);
				DestroyToken(specialtokensemicolon);
				z=y;
				break;
			case '/' :
				y=z+1;
				Token *specialtokenslash = Create(input,"Slash",y,z);
				printf("%s ", specialtokenslash->tokenType);
				printf("%s\n", specialtokenslash->data);
				DestroyToken(specialtokenslash);
				z=y;
				break;
			case '\\' :
				y=z+1;
				Token *specialtokenbackslash = Create(input,"Backslash",y,z);
				printf("%s ", specialtokenbackslash->tokenType);
				printf("%s\n", specialtokenbackslash->data);
				DestroyToken(specialtokenbackslash);
				z=y;
				break;
			case '[' :
				y=z+1;
				Token *specialtokenleftbrace = Create(input,"Left Brace",y,z);
				printf("%s ", specialtokenleftbrace->tokenType);
				printf("%s\n", specialtokenleftbrace->data);
				DestroyToken(specialtokenleftbrace);
				z=y;
				break;
			case ']' :
				y=z+1;
				Token *specialtokenrightbrace = Create(input,"Right Brace",y,z);
				printf("%s ", specialtokenrightbrace->tokenType);
				printf("%s\n", specialtokenrightbrace->data);
				DestroyToken(specialtokenrightbrace);
				z=y;
				break;
			case '{' :
				y=z+1;
				Token *specialtokenleftbracket = Create(input,"Left Bracket",y,z);
				printf("%s ", specialtokenleftbracket->tokenType);
				printf("%s\n", specialtokenleftbracket->data);
				DestroyToken(specialtokenleftbracket);
				z=y;
				break;
			case '}' :
				y=z+1;
				Token *specialtokenrightbracket = Create(input,"Right Bracket",y,z);
				printf("%s ", specialtokenrightbracket->tokenType);
				printf("%s\n", specialtokenrightbracket->data);
				DestroyToken(specialtokenrightbracket);
				z=y;
				break;
			case '_' :
				y=z+1;
				Token *specialtokenunderscore = Create(input,"Underscore",y,z);
				printf("%s ", specialtokenunderscore->tokenType);
				printf("%s\n", specialtokenunderscore->data);
				DestroyToken(specialtokenunderscore);
				z=y;
				break;
			case '#' :
				y=z+1;
				Token *specialtokenhash = Create(input,"Hash",y,z);
				printf("%s ", specialtokenhash->tokenType);
				printf("%s\n", specialtokenhash->data);
				DestroyToken(specialtokenhash);
				z=y;
				break;
			case '!' :
				y=z+1;
				Token *specialtokenexclamation = Create(input,"Not / Exclamation",y,z);
				printf("%s ", specialtokenexclamation->tokenType);
				printf("%s\n", specialtokenexclamation->data);
				DestroyToken(specialtokenexclamation);
				z=y;
				break;
			case '`' :
				y=z+1;
				Token *specialtokentilde = Create(input,"Tilde",y,z);
				printf("%s ", specialtokentilde->tokenType);
				printf("%s\n", specialtokentilde->data);
				DestroyToken(specialtokentilde);
				z=y;
				break;
			case '(' :
				y=z+1;
				Token *specialtokenleftparenth = Create(input,"Left Parenthesis",y,z);
				printf("%s ", specialtokenleftparenth->tokenType);
				printf("%s\n", specialtokenleftparenth->data);
				DestroyToken(specialtokenleftparenth);
				z=y;
				break;
			case ')' :
				y=z+1;
				Token *specialtokenrightparenth = Create(input,"Right Parenthesis",y,z);
				printf("%s ", specialtokenrightparenth->tokenType);
				printf("%s\n", specialtokenrightparenth->data);
				DestroyToken(specialtokenrightparenth);
				z=y;
				break;
			/* If not recognized, dont print anything and just keep going */
			default :
				z++;
				break;
		}
	}
}

int main(int argc, char **argv) 
{
	/* For no input */
	if (argv[1]==NULL || strlen(argv[1])==0)
	{
		printf("%s\n", "No Argument");
		return 0;
	}
	
	else if (argc>2)
	{
		printf("%s\n", "Too many arguments or argument not enclosed in commas.");
	}

  	populateTokenList(argv[1]);	
  	return 0;
}

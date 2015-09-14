#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Token 
{
	char *data;
	char *tokenType;	
};

typedef struct Token Token;

Token *Create(char * input, char * type, int y, int z) 
{

	int TokenStart = z;
	int TokenLength = y-z;
	char *NewToken=malloc((TokenLength+1)*sizeof(char*));
	NewToken[TokenLength]='\0';
	
				
	int b = 0;
	for (TokenStart=z; TokenStart<y; TokenStart++)
	{
		NewToken[b] = input[TokenStart];
		b++;
	}	
	
		Token *newToken=(struct Token*)malloc(sizeof(Token));
       	newToken->data=NewToken;
		newToken->tokenType=type;
		return newToken;

}

void DestroyToken( Token * tk ){
	free(tk);
}

char *GetNextToken( Token * tk ) 
{
  return NULL;
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
				Token *octaltoken = Create(input,"Octal",y,z);
				printf("%s ", octaltoken->tokenType);
				printf("%s\n", octaltoken->data);
				DestroyToken(octaltoken);
				z=y;
				}
				else if (r!=0){			
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
				
				Token *floatingpointtoken = Create(input,"Floating Point",y,z);
				printf("%s ", floatingpointtoken->tokenType);
				printf("%s\n", floatingpointtoken->data);
				DestroyToken(floatingpointtoken);
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
			Token *word = Create(input,"word",y,z);
			printf("%s ", word->tokenType);
			printf("%s\n", word->data);
			DestroyToken(word);
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
			Token *decimaltoken = Create(input,"Decimal",y,z);
			printf("%s ", decimaltoken->tokenType);
			printf("%s\n", decimaltoken->data);
			DestroyToken(decimaltoken);
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
				
				Token *floatingpointtoken = Create(input,"Floating Point",y,z);
				printf("%s ", floatingpointtoken->tokenType);
				printf("%s\n", floatingpointtoken->data);
				DestroyToken(floatingpointtoken);
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
				
				Token *floatingpointtoken = Create(input,"Floating Point",y,z);
				printf("%s ", floatingpointtoken->tokenType);
				printf("%s\n", floatingpointtoken->data);
				DestroyToken(floatingpointtoken);
				z=y;
				continue;
		}
		
		
		
		if (input[z]==' ')
		{
			z++;
		}
		
		
	}
}


int main(int argc, char **argv) 
{
  populateTokenList(argv[1]);	
  return 0;
}

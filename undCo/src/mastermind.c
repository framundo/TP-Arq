#include "../include/extras.h"
#include "../include/libc.h"

void generator(int valores[]);

int dificultad(void);

void
check_input(int pasos , int valores[] , int digitos);

int
check2( char input[] , int digitos );

int
main(void)
{	
	int valores[10] = {0,1,2,3,4,5,6,7,8,9};
	
	int DIF_SET , digitos;
	
	generator(valores);
	
	//DIF_SET = dificultad();
	DIF_SET=1;
	do
	{
		scanf("Ingrese digitos: ", &digitos);
		
		if ( digitos < 0 && digitos > 10 )
		{
			printf("ERROR!!\n");
		}
	
	} while( digitos < 0 && digitos > 10 );
	
	check_input(DIF_SET,valores,digitos);
	
	return 0;
}

void
generator(int valores[])
{
	int i , j , aux;
	
	srand(4);
	
	for ( i = 0 ; i < 5 ; i++ )
	{
		j = rand() % ( 10 - i ) + i;
		
		aux = valores[i];
	
		valores[i] = valores[j];
		
		valores[j] = aux;
		
		printf("%d",valores[i]);
	}
	putchar('\n');
}
/*
int
dificultad(void)
{
	int dif;
	
	do
	{
		dif = getint("<<Choose your destiny>>\n(1)Please, I'm too young to die\n(2)Bring it on bitch!!\n(3)Nightmare\n");
	}
	while( dif != 1 && dif != 2 && dif != 3);
	
	switch (dif)
	{
		case 1: dif = 25;break;
		case 2: dif = 20;break;
		case 3: dif = 10;break;
	}
	
	printf("Let the show begin...\n");

	return dif;
}
*/
void
check_input(int pasos , int valores[] , int digitos)
{
	char input[digitos+2];
	
	int i ,j , bien = 0 , regular = 0 , valido, len =0;
	
	char c;
	
	//input = calloc( (digitos + 2) , sizeof(char) );
	
	do
	{
		bien = 0;
		
		regular = 0;
		
		printf("%d more and you'll be out of this...\n" , pasos);
		
		do
		{
			valido = 1;
			
			scanf("%s",input);
			
			if ( strlen(input) != digitos )
			{
				valido = 0;
			}
			
			else
			{
				valido = check2(input,digitos);
			}
			
			
			while ( getchar() != '\n' )
			{
				;
			}
			
			if ( !valido )
			{
				printf("ERROR!!\n");
			}
			
			
		} while( !valido );
		
		for ( i = 0 ; i < 5 ; i++ )
		{
			for ( j = 0 ; j < 5 ; j++ )
			{
				if ( valores[i] == ( input[j] - '0' ) && i == j)
				{
					bien++;
				}
				
				else if ( valores[i] == ( input[j] - '0' ) && i != j )
				{
					regular++;
				}
				
			}
		}
		
		printf("Good %d\n",bien);
		
		printf("Regular %d\n",regular);
	
		pasos--;
    }
    while( pasos > 0 && bien != 5);
    
    if ( bien == 5 )
	{
		printf("You won this one, you'll be mine next time!!\n");
	}
	
	else
	{
		printf("LOSER!! Try again if you dare bitch!!\n");
	}
}

int
check2( char input[] , int digitos )
{
	int i , j;
	
	for ( i = 0 ; i < digitos ; i++ )
	{
		for ( j = i + 1 ; j < digitos ; j++ )
		{
			if ( input[i] == input[j] )
			{
				return 0;
			}
			
			else if ( !(input[j]<='9'&& input[j]>='0') )
			{	
				return 0;
			}
		}
	}
	
	return 1;
}



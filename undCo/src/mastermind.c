#include "../include/libc.h"
#include "../include/extras.h"
#include "../include/mastermind.h"

int
mastermind()
{	
	int valores[10] = {0,1,2,3,4,5,6,7,8,9};
	
	int DIF_SET;
	
	generator(valores);
	
	DIF_SET = dificultad();
	
	check_input(DIF_SET,valores);
	
	return 0;
}

void
generator(int valores[])
{
	int i , j , aux;
	
	srand(getmin());
	
	for ( i = 0 ; i < 5 ; i++ )
	{
		j = rand() % ( 10 - i ) + i;
		
		aux = valores[i];
	
		valores[i] = valores[j];
		
		valores[j] = aux;
		
		//printf("%d",valores[i]);
	}
	putchar('\n');
}

int
dificultad(void)
{
	int dif;
	
	do
	{
		printf("<<Choose your destiny>>\n(1)Please, I'm too young to die\n(2)Bring it on bitch!!\n(3)Nightmare\n");
		scanf("%d", &dif);
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

void
check_input(int pasos , int valores[])
{
	char input[7] = {0};
	
	int i ,j , bien = 0 , regular = 0 , valido;
	
	
	do
	{
		bien = 0;
		
		regular = 0;
		
		printf("%d more and you'll be out of this...\n" , pasos);
		
		do
		{
			valido = 1;
			
			scanf("%s",input);
			
			if ( strlen(input) != 5 )
			{
				valido = 0;
			}
			
			else
			{
				valido = check2(input);
			}
			
			
			if ( !valido )
			{
				printf("ERROR!! Enter a valid number\n");
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
		printf("LOSER!! Try again if you dare sucker!!\n");
	}
}

int
check2( char input[] )
{
	int i , j;
	
	for ( i = 0 ; i < 5 ; i++ )
	{
		for ( j = i + 1 ; j < 5 ; j++ )
		{
			if ( input[i] == input[j] )
			{
				return 0;
			}
			
			else if ( !(input[j]<='9' && input[j]>='0' ) )
			{	
				return 0;
			}
		}
	}
	
	return 1;
}



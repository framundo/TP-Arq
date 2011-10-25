#include "../include/kc.h"
#include "../include/stdio.h"

/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*24*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=BLACK_TXT;
		i++;
	};
}

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}

void putchar(char c){
	__write(1,&c,1);
}

char getchar(){
	char c;
	do{
		__read(0,&c,1);
	}while(c==0);
	putchar(c);
	return c;
}

void prints(char* string){
	int i;
	for(i=0;string[i];i++){
		putchar(string[i]);
	}
}
char* itoa(int val, char* buffer)
{	
	int pos=0, start;
	char c;
	if(val<0){
		buffer[pos++]='-';
		val=-val;
	}
	start=pos;
	while(val!=0){
		buffer[pos++]=val%10 + '0';
		val/=10;
	}
	buffer[pos--]=0;
	while(pos>start)
	{
		c=buffer[start];
		buffer[start]=buffer[pos];
		buffer[pos]=c;
		pos--;
		start++;
	}
	return buffer;
}
void printf(char * format, ...)
{	
	char buffer[50];
	va_list args;
	va_start(args, format);
	while(*format!=0)
	{
		if(*format=='%')
		{
			format++;
			switch(*format)
			{
				case 'd':
					prints(itoa(va_arg(args, int), buffer));
					break;				
			}
		}
		else
		{
			putchar(*format);
		}
	format++;					
	}

	va_end(args);
}

char gethour(){
	char h;
	__hour(&h);
	/* ZONA GMT-3*/
	h-=3;
	if(h<0){
		h+=24;
	}
	
	return h;
}

char getmin(){
	char m;
	__min(&m);
	return m;
}

#include "../include/kc.h"
#include "../include/stdio.h"
#define SCREEN 1
#define SPEAKER 4
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


int out_stream = SCREEN;

void putchar(char c){
	__write(out_stream,&c,1);
}

void set_out_stream(int i){
	out_stream=i;
}

int strcmp(char* str1, char* str2){
	int ans;
	int i;
	for(i=0; str1[i]||str2[i];i++){
		ans=str1[i]-str2[i];
		if(ans!=0){
			return ans;
		}
	}
	return 0;
}

int substr(char* str1, char* str2){
	int i;
	for(i=0; str1[i];i++){
		if(str1[i]!=str2[i]){
			return 0;
		}
	}
	return 1;
}

char getchar(){
	char c;
	do{
		__read(0,&c,1);
	}while(c==0);
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

int pow(int b,int e){
	int i;
	int ans=1;
	for(i=0;i<e;i++){
		ans*=b;
	}
	return ans;
}

int strlen(char* s){
	int count=0;
	int i;
	for(i=0;s[i];i++){
		count++;
	}
	return count;
}

int atoi(char* a){
	int i;
	int number=0;
	int len=strlen(a);
	for(i=0;a[i];i++){
		number+=(a[i]-'0')*pow(10,len-i-1);
	}
	return number;
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
				case 's':
					prints(va_arg(args,char*));
					break;
				case 'c':
					putchar(va_arg(args,char));
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
	h-=3;
	return h;
}

char getmin(){
	char m;
	__min(&m);
	return m;
}

char* gets(char* buffer){
	do{
		*buffer=getchar();
	}while(*buffer++!=' ');
	*(buffer-1)=0;
	return buffer;
}

int scanf(const char* format, ...){
	char buffer[50];
	int count;
	va_list args;
	va_start(args, format);
	void* p;
	while(*format!=0)
	{
		if(*format=='%')
		{
			format++;
			p=va_arg(args,void*);
			switch(*format)
			{
				case 'c':
					*(char*)p=getchar();
					count++;
					break;
				case 's':
					gets((char*)p);
					count++;
					break;
				case 'd':
					gets(buffer);
					*(int*)p=atoi(buffer);
					count++;
					break;
			}
		}
	format++;					
	}
	va_end(args);
	return count;
}

void memcpy(void* dest, void* source, int count){
	int i;
	for(i=0;i<count;i++){
		*(char*)(dest+i)=*(char*)(source+i);
	}
}

/*void * malloc(int size)
{
	__malloc
}*/

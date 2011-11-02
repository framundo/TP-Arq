#include "../include/stdarg.h"
#include "../include/libc.h"
#include "../include/systemcalls.h"

int out_stream = 1;

void putchar(char c){
	__write(out_stream,&c,1);
}

void putc(int outstream, char c){
	__write(outstream, &c, 1);
}

void set_out_stream(int i){
	out_stream=i;
}

int stack_count(){
	return __stack_count();
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

void speak(char*s)
{
	int i;
	for(i=0; s[i];i++)
	{
		putc(4, s[i]);
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
	if(val==0){
		buffer[pos++]='0';
	}
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

char* xtoa(int mem, char* buffer){
	int i;
	int tmp;
	buffer[0]='0';
	buffer[1]='x';
	for(i=0;i<8;i++){
		tmp=(mem>>(i*4))&0x000F;
		if(tmp<10){
			tmp+='0';
		}
		else{
			tmp+=-10+'A';
		}
		/*LITTLE ENDIAN*/
		buffer[7-i+2]=(char)tmp;
	}
	buffer[10]=0;
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
				case 'X':
					prints(xtoa(va_arg(args, int), buffer));
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
	//h-=3;
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

void* malloc()
{
	return (void*)__malloc();
}

void* calloc()
{
	return (void*)__calloc();
}

int free(void* page)
{
	return __free(page);
}

int heap_count(){
	return __heap_count();
}

void set_scancode(int i){
	__set_scancode(i);
}

#include "../include/kasm.h"
#include "../include/defs.h"

#define BUFFER_SIZE 10

char SCAN_CODES[60]={'\x1B','@','1','2','3','4','5','6','7','8','9','0','-','+','\x08','\t','q','w','e','r','t','y','u','i','o','p','{','}','\n','@','a','s','d','f','g','h','j','k','l','+','@','@','@','@','z','x','c','v', 'b','n','m',',','.','@','@','@','@',' '};
char SHIFT_SCAN_CODES[60]={'\x1B','@','!','\"','#','$','?','&','?','/','(',')','_', '=','\x08','\t','Q','W','E','R','T','Y','U','I','O','P','[',']','\n','@','A','S','D','F','G','H','J','K','L','\\','\"','@','@','@','Z','X','C','V','B','N','M',';',':','/','@','@','@',' '};

/*BUFFER CIRCULAR*/
char buffer[BUFFER_SIZE]; 
int head=0;
int tail=0;

void buffer_putchar(char c){
	buffer[head++]=c;
	if(head==BUFFER_SIZE){
		head=0;
	}
}

char buffer_getchar(){
	char next;
	if(head==tail){
		/*VACIO*/
		return 0;
	}
	next=buffer[tail++];
	if(tail==BUFFER_SIZE){
		tail=0;
	}
	return next;
}

/*INT 09 rutine*/

int shift=0;
int caps=0;

void int_09(){
	int scanCode=_IO_in(0x60);
	if(scanCode & 0x80){
		/*RELEASED KEY*/
		if(scanCode==0xAA||scanCode==0xB6){
			/*SHIFT*/
			shift=0;
		}
	} else {
		/*PRESSED KEY*/
		if(scanCode==0x2a||scanCode==0x36){
			/*SHIFT*/
			shift=1;
		}
		else if(scanCode==0x3A){
			/*CAPS*/
			caps=(caps+1)%2;
		}
		else{
			/*ORDINARY KEYS*/
			char ascii;
			if(caps==shift){
				ascii=SCAN_CODES[scanCode];
			}
			else{
				ascii=SHIFT_SCAN_CODES[scanCode];
			}
			buffer_putchar(ascii);
		}
	}
}

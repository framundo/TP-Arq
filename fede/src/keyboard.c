#include "../include/kasm.h"
#include "../include/defs.h"

char SCAN_CODES[60]={'\x1B','@','1','2','3','4','5','6','7','8','9','0','-','+','\x08','\t','q','w','e','r','t','y','u','i','o','p','{','}','\n','@','a','s','d','f','g','h','j','k','l','+','@','@','@','@','z','x','c','v', 'b','n','m',',','.','@','@','@','@',' '};
char SHIFT_SCAN_CODES[60]={'\x1B','@','!','\"','#','$','?','&','?','/','(',')','_', '=','\x08','\t','Q','W','E','R','T','Y','U','I','O','P','[',']','\n','@','A','S','D','F','G','H','J','K','L','\\','\"','@','@','@','Z','X','C','V','B','N','M',';',':','/','@','@','@',' '};

/*INT 09 rutines*/

int shift=0;
int caps=0;

void int_09(){
	int scanCode=_IO_in(0x60);
	if(scanCode & 0x80){
		/*RELEASED KEY*/
		/*SHIFT*/
		if(scanCode==0xAA||scanCode==0xB6){
			shift=0;
		}
	} else {
		/*PRESSED KEY*/
		/*SHIFT*/
		if(scanCode==0x2a||scanCode==0x36){
			shift=1;
		}
		/*CAPS*/
		else if(scanCode==0x3A){
			caps=(caps+1)%2;
		}
		/*ORDINARY KEYS*/
		else{
			char ascii;
			if(caps==shift){
				ascii=SCAN_CODES[scanCode];
			}
			else{
				ascii=SHIFT_SCAN_CODES[scanCode];
			}
			put(&ascii);
		}
	}
}

#include "../include/kasm.h"
#include "../include/defs.h"

void put(char* c);

int tickpos=2;

/*INT 80 rutines*/

void put(char* c){
    char *video = (char *) 0xb8000;
    video[tickpos+=2]=*c;
}

void int_80(REG registers) {
    if(registers.ebx==1){
		char *c=(char*)registers.ecx;
		put(c);
    }
}

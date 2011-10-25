#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/systemcalls.h"

#define WIDTH 80

int cursor_x=0;
int cursor_y=0;

/*INT 80 RUTINE*/

void int_80(REG registers) {
	//while(1){};
	char *c;
	switch(registers.ebx){
		case 1:
			c=(char*)registers.ecx;
			write(*c);
			break;
		case 2:
			c=(char*)registers.ecx;
			read(c);
			break;
		case 3:
			c=(char*)registers.ecx;
			hour(c);
			break;
		case 4:
			c=(char*)registers.ecx;
			min(c);
			break;
		case 5:
			c=(char*)registers.ecx;
			setcolor(*c);
			break;
	}  
}

/* SCREEN FUNCTIONS */

char current_color=0x07;

int cursor_index(){
	return (cursor_y * WIDTH + cursor_x);
}

void update_cursor(void)
{
    int index;
	index= cursor_index();
    _IO_out(0x3D4, 14);
    _IO_out(0x3D5, index >> 8);
    _IO_out(0x3D4, 15);
    _IO_out(0x3D5, index);
}

void write(char c){
    char *video = (char *) 0xb8000;
    if(c=='\n'){
		cursor_y++;
		cursor_x=0;
	}
	else if(c=='\b'){
		if(cursor_x!=0) cursor_x--;
	}
	else if(c=='\r'){
		cursor_x=0;
	}
    else {
		video[cursor_index()*2]=c;
		video[cursor_index()*2+1]=current_color;
		cursor_x++;
	}
    
    /* Control del cursor */
    if(cursor_x>=WIDTH){
		cursor_y++;
		cursor_x=0;
	}
	update_cursor();
}

void setcolor(char c){
	current_color=c;
}

/* BUFFER FUNCTIONS */

void read(char *c){
	*c=buffer_getchar();
}

/* TIME FUNCTIONS */

void hour(char* hp){
	_IO_out(0x70, 0x04);
	char hour=_IO_in(0x71);
	*hp=hour;
}

void min(char* mp){
	_IO_out(0x70, 0x02);
	char min=_IO_in(0x71);
	*mp=min;
}

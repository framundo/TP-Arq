#include "../include/speaker.h"
#include "../include/kernel.h"
#include "../include/timertick.h"

char CODES [36]={0x8F, 0x90, 0x94, 0x70, 0x20, 0x84, 0x78, 0x80, 0x40, 0x8D, 0x74, 0x88, 
0x58, 0x50, 0x7C, 0x8C, 0x9A, 0x68, 0x60, 0x30, 0x64, 0x18, 0x6C, 0x92, 0x96, 0x98, 0xBF, 
0xAF, 0xA7, 0xA3, 0xA1, 0xA0, 0xB0, 0xB8, 0xBC, 0xBE};

void sys_speak(char c)
{
	int index;
	if(c>='0' && c<='9'){
		index=26+c-'0';
	}
	else if(c>='a' && c<='z')
	{
		index=c-'a';
	}
	else if(c>='A' && c<='Z')
	{
		index=c-'A';
	}
	else{
		return;
	}
	int i=0;
	int sound;
	int cant = getCant(CODES[index]);
	for(i=0; i<cant; i++){
		sound=CODES[index]>>(4-i);
		sound=sound&0x01;
		if(sound==1){
			long_beep();
		}else{
			short_beep();
		}
		//timer_wait(500);
		i=0;
		while(i<10000){
			i++;
		}
	}
	i=0;
		while(i<20000){
			i++;
		}
	//timer_wait(750);
		
}

 void play_sound(int nFrequence) 
 {
 	int Div;
 	char tmp;
  	Div = 1193180 / nFrequence;
 	_IO_out(0x43, 0xb6);
 	_IO_out(0x42, (char) (Div) );
 	_IO_out(0x42, (char) (Div >> 8));
  	tmp = _IO_in(0x61);
  	if (tmp != (tmp | 3)) {
 		_IO_out(0x61, tmp | 3);
 	}
 }
 
 void nosound() 
 {
 	char tmp = (_IO_in(0x61) & 0xFC);
 
 	_IO_out(0x61, tmp);
 }
 
 void short_beep() {
 	 play_sound(10000);
 	 //timer_wait(250);
 	 int i=0;
		while(i<10000){
			i++;
		}
 	 nosound();
 }
 
 
 void long_beep() {
 	 play_sound(10000);
 	 //timer_wait(500);
		int i=0;
		while(i<20000){
			i++;
		}
 	 nosound();
 }
 
 int getCant(char c){
	 return c>>5;
 }
 

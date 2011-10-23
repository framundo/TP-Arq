#include "../include/kasm.h"
#include "../include/defs.h"

char ticker='*';

/* TIMER TICK */

void int_08() {
    char *video = (char *) 0xb8000;
    if(ticker=='*'){
		ticker='-';
	}
	else{
		ticker='*';
	}
    video[0]=ticker;
}

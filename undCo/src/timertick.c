#include "../include/kasm.h"
#include "../include/defs.h"

/* TIMER TICK */

void int_08() {
    char *video = (char *) 0xb8000;
    int clock_index=(24*80+74)*2;
    
    char hour=gethour();
    char min=getmin();
    
    video[clock_index+=2]=(hour/10+'0');
    video[clock_index+=2]=(hour%10+'0');
	video[clock_index+=2]=(':');
	video[clock_index+=2]=(min/10+'0');
    video[clock_index+=2]=(min%10+'0');
}

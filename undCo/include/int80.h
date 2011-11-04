#ifndef _systemcalls_
#define _systemcalls_

/* Tiempo*/
typedef struct {
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;
} time_t;

void sys_print(char c);
void sys_read(char *c);
void sys_hour(char* hp);
void sys_min(char* mp);
void sys_setcolor(char c);
int sys_heap_count();

#endif

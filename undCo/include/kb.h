#ifndef __KB__
#define __KB__

void kb_init();
void int_09();
char buffer_getchar();
void buffer_putchar(char c);
void sys_set_scancode(int i);
void update_leds(char status);
#endif

#ifndef __SYSCALLS__
#define __SYSCALLS__

void __hour(char* hp);
void __min(char* mp);
void* __malloc();
void* __calloc();
int __free(void* i);
int __stack_count();
void __setcolor(char* colorp);
void __set_scancode(int i);
int __heap_count();

/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
int __write(int fd, const void* buffer, int count);

/* __read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
int __read(int fd, void* buffer, int count);

#endif

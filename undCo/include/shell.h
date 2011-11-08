#ifndef __SHELL__
#define __SHELL__

#define MAX_CMD_SIZE 70
#define CMD_MEMORY 5
#define SCREEN 1
#define SPEAKER 4

char color(char* color_name);
void set_out_stream_command(char* c);
void print_memory();
void shell();
void help();

#endif

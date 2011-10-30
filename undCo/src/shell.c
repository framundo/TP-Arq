/* SHELL */

#define MAX_CMD_SIZE 40
#define SCREEN 1
#define SPEAKER 4



char color(char* color_name){
	if(strcmp("blue",color_name)==0){
		return 0x01;
	}else if(strcmp("green",color_name)==0){
		return 0x02;
	}else if(strcmp("cyan",color_name)==0){
		return 0x03;
	}else if(strcmp("red",color_name)==0){
		return 0x04;
	}else if(strcmp("magenta",color_name)==0){
		return 0x05;
	}else if(strcmp("brown",color_name)==0){
		return 0x06;
	}else if(strcmp("light gray",color_name)==0){
		return 0x07;
	}else if(strcmp("dark gray",color_name)==0){
		return 0x08;
	}else if(strcmp("light blue",color_name)==0){
		return 0x09;
	}else if(strcmp("light green",color_name)==0){
		return 0x0A;
	}else if(strcmp("light cyan",color_name)==0){
		return 0x0B;
	}else if(strcmp("light red",color_name)==0){
		return 0x0C;
	}else if(strcmp("light magenta",color_name)==0){
		return 0x0D;
	}else if(strcmp("light brown",color_name)==0){
		return 0x0E;
	}else if(strcmp("white",color_name)==0){
		return 0x0F;
	}else{
		return 0;
	}
}

void set_out_stream_command(char* c){
	if(strcmp(c, "screen")==0){
		set_out_stream(SCREEN);
	}else if(strcmp(c, "speaker")==0){
		set_out_stream(SPEAKER);
	}else{
		printf("invalid out stream\n");
	}
}

void print_memory(){
	int s = stack_count();
	int h = heap_count();
	printf("\nSTACK:\n %d bytes used\n", s);
	printf("\n HEAP:\n %d pages used -> %d bytes\n\n", h, h*4096);
}

void shell(){
	char c;
	char * s;
	char buffer[MAX_CMD_SIZE];
	int i;
	char shell_color=0x09;
	char user_color=0x07;
																					
	while(1){
		__setcolor(&shell_color);
		printf("Shell->: ");
		__setcolor(&user_color);
		i=0;
		do{
			c=getchar();
			if(c=='\b'){
				if(i>0){
					i--;
					putchar(c);
				}
			}
			else{
				putchar(c);
				buffer[i]=c;
				i++;
			}
		}while(c!='\n');
		buffer[i-1]=0;
		if(substr("echo ", buffer)){
			printf("%s\n",buffer+5);
		}
		else if(substr("color ", buffer)){
		  char tmp=color(buffer+6);
		  if(tmp==0){
		    printf("Invalid color name\n");
		  }
		  else{
		    user_color=tmp;
		  }
		}
		else if(strcmp("time",buffer)==0){
			printf("%d:%d\n",gethour(),getmin());
		}
		else if(substr("outstream ", buffer)){
			set_out_stream_command(buffer + 10);
		}
		else if(substr("keyboard ", buffer)){
			if(strcmp("ESP", buffer+9)==0){
				set_scan_code(1);
			}else if(strcmp("ENG", buffer+9)==0){
				set_scan_code(2);
			}else{
				printf("unsuported layout\n");
			}
		}
		else if(strcmp("memory status", buffer)==0){
			print_memory();
		}
		else if(substr("allocate memory", buffer)){
			if(strcmp(" -0", buffer+14)==0){
				calloc();
			}else{
				malloc();
			}
			printf("memory allocated\n");
		}
		else if(substr("free ", buffer)){
			i=atoi(buffer+5);
			free((i+530)*4096);
		}
		else{
			printf("Command not found\n");
		}
		
	}
}


/* SHELL */

#define MAX_CMD_SIZE 40
#define SCREEN 1
#define SPEAKER 4



char color(char* color_name){
	if(strcmp("black",color_name)==0){
		return 0x70;
	}
	else{
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
	char shell_color=0x05;
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
		else if(strcmp("memory", buffer)==0){
			void* m=(void*)malloc();
			print_memory();
			free(m);
		}
		else{
			printf("Command not found\n");
		}
	}
}


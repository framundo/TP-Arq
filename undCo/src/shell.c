/* SHELL */

#define MAX_CMD_SIZE 40

void color(char* color_name, char * color_change){
	if(strcmp("black",color_name)==0){
		*color_change=0x70;
	}
	else{
		printf("Invalid color name\n");
		return;
	}
}



void shell(){
	char c;
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
			color(buffer+6, &user_color);
		}
		else if(strcmp("time",buffer)==0){
			printf("%d:%d\n",gethour(),getmin());
		}
		else{
			printf("Command not found\n");
		}
	}
}


/* SHELL */

void shell(){
	printf("Shell~: ");
	while(1){
		char c;
		c=getchar();
		putchar(c);
		if(c=='\n'){
			printf("Shell~: ");
		}
	}
}

/* SHELL */

void shell(){
	printf("Shell->: ");
	//printf("tengo %d amigos", 10);
	while(1){
		char c;
		c=getchar();
		putchar(c);
		if(c=='\n'){
			printf("Shell->: ");
		}
	}
}

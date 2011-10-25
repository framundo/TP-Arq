/* SHELL */

void shell(){
	printf("Shell->: ");
	while(1){
		char c;
		c=getchar();
		if(c=='\n'){
			printf("Shell->: ");
		}
	}
}

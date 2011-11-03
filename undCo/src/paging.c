#define MEM_START 0x00200000
#define PAGE_SIZE 4096
#define KERNEL_PAGES 530
#define USER_PAGES 1024-KERNEL_PAGES

#include "../include/kasm.h"
#include "../include/int80.h"

int* dir = (void*)MEM_START;
int** page_table = (void*)MEM_START + PAGE_SIZE;
char page_present[USER_PAGES];
int current_page_num=1;

void page_init(){
	int i;
	for(i=0; i<USER_PAGES; i++){
		page_present[i]=0;
	}
	_lcr3(dir);
	*dir=(int)page_table;
	(*dir)=(*dir)|0x00000001;
	_fill_page1();
	_epag();
}

void * sys_malloc(int bytes)
{	
	int j, start;
	int cant=(bytes/PAGE_SIZE)+1;
	if(bytes%PAGE_SIZE==0){
		cant--;
	}
	int i, acum=0;
	for(i=0; i<510; i++){
		if(page_present[i]==0){
			acum++;
		}else{
			acum=0;
		}
		if(acum==cant){
			start=i-cant+1;
			for(j=start; j<=i; j++){
				page_present[j]=current_page_num;
				page_table[j+KERNEL_PAGES]=(int*)((int)(page_table[j+KERNEL_PAGES])|0x00000001);
			}
			current_page_num++;
			return (void*)((start+KERNEL_PAGES)*PAGE_SIZE);
		}
	}
	return 0;
}

void * sys_calloc(int bytes){
	int i;
	int * p = sys_malloc(bytes);
	if(p==0){
		return 0;
	}
	for(i=0; i<bytes/4; i++){
		p[i]=0;
	}
	return (void*)(p);
}

int sys_free(void * adress){
	int i=(int)adress/PAGE_SIZE - KERNEL_PAGES;
	if(i>=0&&i<USER_PAGES&&page_present[i]!=0){
		int actual_num=page_present[i];
		while(page_present[i]==actual_num){
			page_present[i] = 0;
			page_table[i+KERNEL_PAGES]=(int*)((int)(page_table[i+514])&0xFFFFFFFE);
			i++;
		}	
		return 1;
	}else{
		return 0;
	}
}

int sys_heap_count(){
	int count=0;
	int i;
	for(i=0; i<USER_PAGES; i++){
		if(page_present[i]){
			count++;
		}
	}
	return count;
}

void page_fault(int fault){
	char* s="\npage fault";
	int i;
	for(i=0;i<11;i++){
		sys_write(s[i]);
	}
	char p=(fault&0x00000001)+'0';
	sys_write(p);
	char w=((fault>>1)&0x00000001)+'0';
	sys_write(w);
	while(1);
}

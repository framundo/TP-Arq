#define MEM_START 0x00200000
#define PAGE_SIZE 4096
#define KERNEL_PAGES 530
#define USER_PAGES 1024-KERNEL_PAGES

#include "../include/kasm.h"
#include "../include/int80.h"

int* dir = (void*)MEM_START;
int** page_table = (void*)MEM_START + PAGE_SIZE;
char page_present[USER_PAGES];

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

void * sys_malloc()
{
	int i;
	for(i=0; i<510; i++){
		if(page_present[i]==0){
			page_present[i]=1;
			page_table[i+KERNEL_PAGES]=(int*)((int)(page_table[i+KERNEL_PAGES])|0x00000001);
			return (void*)((i+KERNEL_PAGES)*PAGE_SIZE);
		}
	}
	return 0;
}

void * sys_calloc(){
	int i;
	int * p = sys_malloc();
	for(i=0; i<PAGE_SIZE/4; i++){
		p[i]=0;
	}
	return (void*)(p);
}

int sys_free(void * page){
	int i=(int)page/PAGE_SIZE - KERNEL_PAGES;
	if(i>=0&&i<USER_PAGES&&page_present[i]==1){
		page_present[i] = 0;
		page_table[i+KERNEL_PAGES]=(int*)((int)(page_table[i+514])&0xFFFFFFFE);
		return 1;
	} else{
		return 0;
	}
}

int sys_heap_count(){
	int count=0;
	int i;
	for(i=0; i<USER_PAGES; i++){
		if(page_present[i]==1){
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

#define MEM_START 0x00200000
#define PAGE_SIZE 4096

int* dir = (void*)MEM_START;
int** page_table = (void*)MEM_START + PAGE_SIZE;
char page_present[510];

void page_init(){
	int i;
	for(i=0; i<510; i++){
		page_present[i]=0;
	}
	_lcr3(dir);
	*dir=((int)page_table/PAGE_SIZE)<<12;
	(*dir)=(*dir)|0x00000001;
	_fill_page1();
	_epag();
}

void print_pageinfo(){
	printf("Directory adress: %X\n",dir);
	printf("Page table adress: %X\n", page_table);
	printf("Directory entry: %X\n", *dir);
}

void * sys_malloc()
{
	int i;
	for(i=0; i<510; i++){
		if(page_present[i]==0){
			page_present[i]=1;
			page_table[i+514]=(int*)((int)(page_table[i+514])|0x00000001);
			return (void*)((i+514)*PAGE_SIZE);
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

void sys_free(void * page){
	int i=(int)page/PAGE_SIZE - 514;
	page_present[i] = 0;
	page_table[i+514]=(int*)((int)(page_table[i+514])&0xFFFFFFFE);
}

int heap_count(){
	int count=0;
	int i;
	for(i=0; i<510; i++){
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

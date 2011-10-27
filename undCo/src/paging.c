#define MEM_START 0x00200000
#define PAGE_SIZE 4096


int* dir = (void*)MEM_START;
int** pages = (void*)MEM_START + PAGE_SIZE;

void page_init(){
	int i;
	_lcr3(dir);
	*dir=((int)pages/PAGE_SIZE)<<12;
	(*dir)=(*dir)|0x00000001;
	_fill_page1();
	_epag();
}

void print_pageinfo(){
	int i;
	printf("Directory adress: %X\n",dir);
	printf("Page table adress: %X\n", pages);
	printf("Directory entry: %X\n", *dir);
}

void * sys_malloc()
{
	
}

void page_fault(){
	while(1);
}

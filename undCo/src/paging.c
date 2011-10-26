#define MEM_START 0x00200000
#define PAGE_SIZE 4096

typedef struct{
	int adress: 20;
	int avail:3;
	int zero : 2; 
	int dirty : 1;
	int A :1;
	int zero_2:2;
	int user:1;
	int read_write:1;
	int present : 1;
}entry_t;

entry_t* dir = (void*)MEM_START;
entry_t** pages = (void*)MEM_START + PAGE_SIZE;

void page_init()
{
	_epag();
	int i, direction;
	_lcr3(dir);
	dir->adress=(int)pages/PAGE_SIZE;
	for(i=0; i<1024; i++)
	{
		direction=i*PAGE_SIZE;
		pages[i]->adress=direction;
		if(direction<MEM_START)
		{
			pages[i]->present=1;
		}else{
			pages[i]->present=0;
		}
	}
}


void * sys_malloc()
{
	
}

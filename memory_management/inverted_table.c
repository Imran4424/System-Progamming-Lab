#include <stdio.h>
#include <stdlib.h>

const main_memory = 32;
const frame_size = 4;
const page_table_size = main_memory/frame_size;

int checker[] = {0};

int ram[] = {3, 5, 6, 2, 6, 1, 11, 10, 6, 100, 1, -11, 77, 34, 19, 9, 22, 10, 6, 33, 12, 06, 28, 68,29, 28, 59, 22, 85, 36};

typedef struct page_table{
	int pID;
	int page_number;
} ptable;


ptable table[page_table_size];

void g_page_table()
{
	int j = 10000;

	for(int i = 0;i<page_table_size;i++)
	{
		table[i].pID = rand() % 3 + j;
		table[i].page_number = i % 2;

		j += 3;
	}
}


int main()
{
	g_page_table();

	printf("insert an pID and logical address\n");
	int pID, logical_address;

	scanf("%d %d",&pID,&logical_address);

	int p = logical_address / frame_size;
	int d = logical_address % frame_size;

	int i = 0;
 
	while(table[i].pID != pID || table[i].page_number != p)
	{
		i++;
	}

	printf("frame no: %d  offset no: %d\n",i,d);

	printf("Data is: %d \n",ram[i*frame_size+ d - 1]);

	return 0;
}


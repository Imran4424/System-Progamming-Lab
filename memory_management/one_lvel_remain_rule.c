#include <stdio.h>
#include <math.h>

const logical_memory = 32;
const page_size = 4;
const logical_address_space = 8;


int main()
{
	int logical_address;
	
	scanf("%d",&logical_address);
	
	int p = logical_address/page_size;
	int d = logical_address%page_size;
	
	return 0;
}

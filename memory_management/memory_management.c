#include <stdio.h>

int a ,b;

void func1()
{
	int x,y;
	static int r,s;
	
	printf("a:%p, b:%p\n",&a,&b);
	printf("x:%p, y:%p\n",&x,&y);
	printf("r:%p, s:%p\n",&r,&s);

}


int main(int argc,char *argv[])
{
	int x,y;
	static int r,s;
	
	printf("a:%p, b:%p\n",&a,&b);
	printf("x:%p, y:%p\n",&x,&y);
	printf("r:%p, s:%p\n",&r,&s);
	
	int i;
	printf()
	
	
	
	printf("argc: %p, argv: %p\n\n", &argc,&argv);

	func1();
	
	return 0;
}

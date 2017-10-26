#include <test.h>
#include <types.h>
#include <lib.h>

int hellotest(int nargs, char **args){
	(void)nargs;
	(void)args;
	
	kprintf("Hello Test");

	return 0;
}

#include <test.h>
#include <types.h>
#include <lib.h>

int hellotest(int nargs, char **args){
	(void)nargs;
	
	kprintf("Hello Test %s \n", args[1] );

	return 0;
}

/*
 * Thread Fun test code.
 */
#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

static struct semaphore *tsem = NULL;

static
void
init_sem(void)
{
	if (tsem==NULL) {
		tsem = sem_create("tsem", 0);
		if (tsem == NULL) {
			panic("threadtest: sem_create failed\n");
		}
	}
}

static
void
funthread(void *junk, unsigned long num )
{
	 int ch = '0' + num;

	 (void)junk;
	 
	 putch(ch);
    
	 V(tsem);
}

static
void
runthreads(int NTHREADS)
{

	char name[16];
	int i, result;

	for (i=0; i<NTHREADS; i++) {
		snprintf(name, sizeof(name), "threadtest%d", i);
		result = thread_fork(name, NULL, funthread, NULL, i);
		if (result) {
			panic("threadtest: thread_fork failed %s)\n", 
			      strerror(result));
		}
	}

	for (i=0; i<NTHREADS; i++) {
		P(tsem);
	}
}


int
threadfun(int nargs, char **args)
{	
	
	int NTHREADS = 10;

	if( nargs > 1 ){
		int num = atoi( args[1] );
		NTHREADS = num;
	}

	init_sem();
	kprintf("\nStarting thread fun...\n\n");
	runthreads(NTHREADS);
	kprintf("\n\nThread fun done.\n");

	return 0;
}

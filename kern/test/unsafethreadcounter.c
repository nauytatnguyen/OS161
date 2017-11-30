/*
 * Unsafe Thread Counter.
 */
#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

static struct semaphore *tsem = NULL;
static unsigned long COUNTER = 0;

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
unsafethread(void *junk, unsigned long num )
{
    
    (void)junk;
    
     for( unsigned long i = num; i > 0; i--){
        COUNTER++; 
     }
     
	 V(tsem);
}

static
void
runthreads(int NTHREADS, int INCREMENTS)
{

	char name[16];
	int i, result;

	for (i=0; i<NTHREADS; i++) {
		snprintf(name, sizeof(name), "threadtest%d", i);
		result = thread_fork(name, NULL, unsafethread, NULL, INCREMENTS);
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
unsafethreadcounter(int nargs, char **args)
{	
	
	int NTHREADS = 10;
    int INCREMENTS = 1;

	if( nargs > 1 ){
		NTHREADS = atoi( args[1] );
        if( nargs == 3 ){
            INCREMENTS = atoi( args[2] );
        }
	}

	init_sem();
	kprintf("\n---Starting Unsafe Thread---\n\n");
    kprintf("Counter expected value: %d\n", INCREMENTS*NTHREADS);
	runthreads(NTHREADS, INCREMENTS);
    kprintf("Actual counter value: %lu\n", COUNTER);
	kprintf("\n---Unsafe Thread done---\n\n");

	return 0;
}

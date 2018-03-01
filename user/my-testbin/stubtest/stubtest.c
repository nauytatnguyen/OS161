
#include <stdio.h>
#include <unistd.h>


int
main()
{
  pid_t pid;

        printf("Test call for fork stub\n");
        pid = fork();
        printf("pid: %d\n", pid);
        
        printf("Test call for getpid stub\n");
        pid = getpid();
        printf("pid: %d\n", pid);

        printf("Test call for waitpid stub\n");
        pid = waitpid(pid, 0 ,0);
        printf("pid: %d\n", pid); 
        return 0; 
}





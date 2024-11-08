#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid;
    int i,s;

    // Create 5 child processes
    for (i = 0; i < 5; i++) 
	{
        pid = fork();
        if (pid == 0) 
		{
            for (int count = 1; count <= 5; count++) 
			{
                printf("Child PID: %d, Count: %d\n", getpid(), count);
                sleep(1);
            }
            exit(0);
        }
    }
    for (i = 0; i < 5; i++) 
	{
        wait(&s);
    }

    printf("All child processes have completed.\n");
    return 0;
}

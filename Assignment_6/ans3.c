/* Find max number of child processes that can be created on Linux using C program? Hint: use fork() in inﬁnite loop (wisely). */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    int pid;
    int count = 0;

	while (1)
	{
    	pid = fork();

		if (pid == -1)

		{
    		printf("fork Failed!\n");
    		printf("Maximum number of processes created : %d\n", count);

   		 	exit(1);

		}

		else if (pid > 0)
		{
    		count++;
		}

		else
		{
    		exit(0);
		}

   	}

  return 0;

}

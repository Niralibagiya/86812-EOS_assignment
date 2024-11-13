#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    int pid1, pid2;

    if (pipe(pipefd) == -1)
	{
        perror("pipe() failed");
        return 1;
    }

    pid1 = fork();
    if (pid1 == -1)
	{
        perror("fork() failed");
        return 1;
    }

    if (pid1 == 0)
	{
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

		execlp("who", "who", (char *)NULL);
        perror("execlp() failed for who");
        return 1;
    }

    pid2 = fork();
    if (pid2 == -1)
	{
        perror("fork() failed");
        return 1;
    }

    if (pid2 == 0)
	{
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        
		execlp("wc", "wc", (char *)NULL);
        perror("execlp() failed for wc");
        return 1;
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}


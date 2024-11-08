/* From a parent process (A) create a child process (B). The child (B) in turn creates new child process (C) and it (C) in turn create new child (D). All these processes should run concurrently for 5 seconds and cleaned up properly upon termination. */


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    int i, pidB, pidC, pidD;
    int statusB, statusC, statusD;

    pidB = fork();

    if (pidB == 0)
    { // Child B
        pidC = fork();
        if (pidC == 0)
         { // Child C
            pidD = fork();
            if (pidD == 0)
             { // Child D
                for (i = 1; i <= 5; i++)
                 {
                    printf("child D: %d\n", i);
                    sleep(1);
                }
                _exit(0);
            } else
            { // Child C
                for (i = 1; i <= 5; i++)
                 {
                    printf("child C: %d\n", i);
                    sleep(1);
                }
                waitpid(pidD, &statusD, 0);
                _exit(0);
            }
        } else
        { // Child B
            for (i = 1; i <= 5; i++)
            {
                printf("child B: %d\n", i);
                sleep(1);
            }
            waitpid(pidC, &statusC, 0);
            _exit(0);
        }
    } else
    {
        // Parent A
        for (i = 1; i <= 5; i++)
        {
            printf("parent A: %d\n", i);
            sleep(1);
        }
        waitpid(pidB, &statusB, 0);
}
    return 0;
}


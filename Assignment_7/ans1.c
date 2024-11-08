#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int signal_number, pid;

    printf("Enter the signal number: ");
    scanf("%d", &signal_number);

    printf("Enter the process ID: ");
    scanf("%d", &pid);

    if (kill(pid, signal_number) == 0) {
        printf("Signal %d sent to process %d.\n", signal_number, pid);
    } else {
        perror("kill");
    }

    return 0;
}

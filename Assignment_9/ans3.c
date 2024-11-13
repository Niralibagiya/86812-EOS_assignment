#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int pipefd[2];
    ssize_t buffer_size;

    if (pipe(pipefd) == -1) {
        perror("pipe() failed");
        return 1;
    }

    buffer_size = fcntl(pipefd[0], F_GETPIPE_SZ);
    if (buffer_size == -1) {
        perror("fcntl() failed");
        return 1;
    }

    printf("The size of the pipe buffer is: %ld bytes\n", buffer_size);

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}


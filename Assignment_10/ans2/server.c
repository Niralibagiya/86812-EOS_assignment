#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MSG_SIZE 256
#define FIFO_NAME "fifo_file_transfer"

struct msg_buffer {
    long msg_type;
    char fifo_name[50];
    char file_name[200];
};

int main() {
    int msgid;
    struct msg_buffer message;
    char buffer[1024];
    int fd;
    ssize_t bytes_read;

    // Create a message queue
    msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while (1) {
        // Receive message from client
        msgrcv(msgid, &message, sizeof(message), 1, 0);

        // Create FIFO for file transfer
        mkfifo(message.fifo_name, 0666);

        // Open the specified file
        fd = open(message.file_name, O_RDONLY);
        if (fd == -1) {
            perror("open");
            continue;
        }

        // Send the file to the client via FIFO
        int fifo_fd = open(message.fifo_name, O_WRONLY);
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            write(fifo_fd, buffer, bytes_read);
        }

        close(fifo_fd);
        close(fd);
    }

    // Cleanup
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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

    // Create a message queue
    msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Specify FIFO name and file name
    printf("Enter the FIFO name: ");
    scanf("%s", message.fifo_name);
    printf("Enter the file name to send: ");
    scanf("%s", message.file_name);

    // Send message to server
    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message), 0);

    // Create FIFO to receive file
    mkfifo(message.fifo_name, 0666);

    // Open FIFO for reading
    int fifo_fd = open(message.fifo_name, O_RDONLY);
    char buffer[1024];
    ssize_t bytes_read;

    // Receive the file and save it
    FILE *output_file = fopen("received_file", "wb");
    while ((bytes_read = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes_read, output_file);
    }

    fclose(output_file);
    close(fifo_fd);

    // Cleanup
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}

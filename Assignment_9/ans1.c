#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MQ_KEY  0x1234

typedef struct msg {
    long id;
    int data[2];  // Array to hold two integers
} msg_t;

int main() {
    int mqid, pid, s, ret;

    // Create a message queue
    mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
    if (mqid < 0) {
        perror("msgget() failed");
        _exit(1);
    }

    // Create child process
    pid = fork();
    if (pid == 0) {  // Child process
        msg_t m1;
        m1.id = 101;

        printf("Child: Enter two numbers: ");
        scanf("%d %d", &m1.data[0], &m1.data[1]);

        // Send the numbers to the parent process
        ret = msgsnd(mqid, &m1, sizeof(msg_t) - sizeof(long), 0);
        if (ret < 0) {
            perror("child: msgsnd() failed");
        }

        // Receive the sum from the parent
        ret = msgrcv(mqid, &m1, sizeof(msg_t) - sizeof(long), 102, 0);
        if (ret < 0) {
            perror("child: msgrcv() failed");
        } else {
            printf("Child: Received sum from parent: %d\n", m1.data[0]);
        }
    }
    else {  // Parent process
        msg_t m2;

        // Parent: Waiting for message from child
        printf("Parent: Waiting for message from child...\n");

        // Receive the two numbers from the child
        ret = msgrcv(mqid, &m2, sizeof(msg_t) - sizeof(long), 101, 0);
        if (ret < 0) {
            perror("parent: msgrcv() failed");
        }

        // Calculate the sum
        int sum = m2.data[0] + m2.data[1];

        // Send the sum back to the child
        m2.id = 102;  // Set a different message ID for the response
        m2.data[0] = sum;
        ret = msgsnd(mqid, &m2, sizeof(msg_t) - sizeof(long), 0);
        if (ret < 0) {
            perror("parent: msgsnd() failed");
        }

        // Wait for child process to complete
        waitpid(pid, &s, 0);
    }

    // Cleanup: Destroy the message queue (if desired, commented out)
    // msgctl(mqid, IPC_RMID, NULL);

    return 0;
}


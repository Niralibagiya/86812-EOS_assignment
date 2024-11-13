#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ret, arr1[2], arr2[2], s;
    int num1, num2, sum = 0;

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    if (pipe(arr1) < 0) {
        perror("pipe() failed");
        _exit(1);
    }
    if (pipe(arr2) < 0) {
        perror("pipe() failed");
        _exit(1);
    }

    ret = fork();
    if (ret == 0) {
        close(arr1[0]);
        close(arr2[1]);
        write(arr1[1], &num1, sizeof(num1));
        write(arr1[1], &num2, sizeof(num2));
        close(arr1[1]);
        read(arr2[0], &sum, sizeof(sum));
        printf("Child: Sum received from parent: %d\n", sum);
        close(arr2[0]);
    }
    else {
        close(arr1[1]);
        close(arr2[0]);
        read(arr1[0], &num1, sizeof(num1));
        read(arr1[0], &num2, sizeof(num2));
        close(arr1[0]);
        sum = num1 + num2;
        write(arr2[1], &sum, sizeof(sum));
        close(arr2[1]);
        waitpid(ret, &s, 0);
    }

    return 0;
}


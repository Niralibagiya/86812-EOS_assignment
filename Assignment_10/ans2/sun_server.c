#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCK_FILE   "/tmp/mysock"

int main() {
    int ret, serv_fd, cli_fd;
    struct sockaddr_un serv_addr, cli_addr;
    socklen_t socklen = sizeof(cli_addr);
    char msg[512];
    //1. create server socket
    serv_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    //2. bind the address
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCK_FILE);
    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //3. listen to server socket
    listen(serv_fd, 5);
    //6. accept client connection
    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
    
      //8. read data from client
        read(cli_fd, msg, sizeof(msg));
        printf("client: %d %d\n", msg[0],msg[1]);
         
         //operation :addition
         msg[2]=msg[0]+msg[1];
        write(cli_fd, msg, sizeof(msg));
    
    //12. close client socket
    close(cli_fd);
    //13. shutdown server socket
    shutdown(serv_fd, SHUT_RDWR);
    //14. delete the socket file
    unlink(SOCK_FILE);
    return 0;
}


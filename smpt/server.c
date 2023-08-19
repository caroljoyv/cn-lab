#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){

    char *ip = "127.0.0.1";
    int port = 25;
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t clientaddr_len;
    char buffer[1024];
    int n;

    //create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0){
        perror("[-]Socket error");
        exit(1);
    }
    printf("\nServer Socket created");

    memset(&server_addr,'\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //bind server socket to port number and ip address
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0){
        perror("[-]Bind error");
        exit(1);
    }
    printf("[+]Bind to the port number: %d\n", port);

    //listening
    printf("Listening...\n");
    listen(server_sock, 5);   


    //accept connection request from client
    clientaddr_len = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &clientaddr_len);

    


    //close connections
    close(server_sock);
    close(client_sock);

    return 0;
}

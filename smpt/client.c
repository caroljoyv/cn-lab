#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){

    int sock;
    int port = 2500;
    char * ip = "127.0.0.1";
    struct  sockaddr_in sock_addr;
    socklen_t addr_size;
    char buffer[1024];

    //socket creation
    sock = socket(AF_INET, SOCK_STREAM,0);
    if(sock < 0){
        perror("socket error");
        exit(1);
    }
    printf("\nsocket created");

    memset(&sock_addr, '\0', sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = port;
    sock_addr.sin_addr.s_addr = inet_addr(ip);

    //connet
    connect(sock, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
    printf("/nconnected to the server");

    //sending
    bzero(buffer, 1024);
    strcpy(buffer, "HELLO, THIS IS CLIENT.");
    printf("Client: %s\n", buffer);
    send(sock, buffer, strlen(buffer), 0);

    
    //receiving
    bzero(buffer, 1024);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);
    







    //close
    close(sock);
    printf("\nconnection closed");
    return 0;
}
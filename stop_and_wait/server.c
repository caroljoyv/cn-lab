#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

int main()
{
    char *ip = "127.0.0.1";
    int port = 2200;
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addrlen;
    int n;

    //socket creation
    server_sock = socket(AF_INET,SOCK_STREAM,0);
    if(server_sock < 0){
        perror("\nsocket error");
        exit(0);
    }
    printf("\nServer socket created");

    memset(&server_addr,'\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);


    //bind socket to ip address and port number
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(n < 0){
        perror("\nBind error");
        exit(0);
    }
    printf("\nServer socket bound to ip address and port number");

    //listen for connection requests
    printf("\nServer socket listening for connections");
    listen(server_sock, 6);
    

    //accept connection request from client
    addrlen = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addrlen);
    printf("\nConnected to client socket\n\n");

    int m, frame, ack,temp;

    //receive the total number of frames
    recv(client_sock,&m, sizeof(int),0);
    printf("\nNumber of frames = %d, received from client", m);

    //generate a random number to simulate a lost frame
    temp = (rand()%m) - 1;

    while(1){

        //receive frame number from client
        recv(client_sock, &frame, sizeof(frame), 0);
        printf("\nFrame received: %d", frame);

        //determine acknowledgement number
        ack = frame + 1;
        if(frame == temp){
            ack = 100;
            temp --;
        }
        printf("Acknowledgement send back : %d", ack);

        //send ack back
        send(client_sock, &ack, sizeof(ack), 0);

        if(ack == m){
            break;
        }

    }

    //close connection
    close(server_sock);
    close(client_sock);

    return 0;
}




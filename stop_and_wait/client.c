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
    int sock;
    struct sockaddr_in addr;

    //socket creation
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("\nsocket error");
        exit(0);
    }
    printf("\nClient socket created");

    memset(&addr,'\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    //send connection request to server
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("\nConnected to the server");


    int n, frame[100];
    printf("\nEnter the number of frames");
    scanf("%d", &n);

    //populate the frame array
    for(int i = 0; i < n; i++){
        frame[i] = i;
    }

    int i = 0, ack;

    //send the total number of frames to the server
    send(sock, &n, sizeof(n), 0);

    while(1){

        //send frame to server
        send(sock, &frame[i], sizeof(int), 0);
        printf("\nFrame sent: %d", frame[i]);

        //receive acknowledgement from server
        recv(sock, &ack, sizeof(int), 0);

        if(ack == frame[i + 1]){  
            printf("\nAcknowledgement received successfully");
            i ++;
        }
        else if(ack == n){  //exit condition
            printf("\nAcknowledgement received successfully");
            break;
        }
        else{
            sleep(5);
            printf("\nTimeout");
            
        }
        
    }

    //close connection
    close(sock);

    return 0;
}

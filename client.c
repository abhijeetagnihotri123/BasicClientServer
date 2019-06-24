#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#define PORT 8080
int main(int argc,char *argv[])
{   
    int sock,valread;
    char hello[51];
    char buffer[1024];
    strcpy(hello,"Hello World from client!\n");
    struct sockaddr_in serv_addr;
    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        printf("socket cannot be initialised\n");
    }
    else
    {
        printf("Socket initialization completed\n");
    }
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr) <=0)
    {
        printf("Invalid address\n");
    }
    else
    {
        printf("Valid address\n");
    }
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection failed\n");
    }
    else
    {
        printf("Connection established\n");
    }
    send(sock,hello,strlen(hello),0);
    printf("Hello World sent\n");
    valread=read(sock,buffer,1024); 
    return 0;
}
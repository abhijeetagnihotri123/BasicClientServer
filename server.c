#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080
int main(int argc,char *argv[])
{   
    int sock;
    int client_sock;
    int opt=1;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t client_addr_length;
    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        printf("Server failed to initialise it's socket\n");
    }
    if(setsockopt(sock,SOL_SOCKET,opt,&opt,sizeof(opt))!=0)
    {
        printf("Error\n");
    }
    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_port=htons(PORT);
    if(bind(sock,(struct sockaddr*)&server,sizeof(server))<0)
    {
        printf("Cannot bind\n");
    }
    if(listen(sock,1) < 0)
    {
        printf("Server unable to listen\n");
    }
    else
    {
        printf("Server ready to listen to a client\n");
    }
    client_addr_length=sizeof(client);
    client_sock=accept(sock,(struct sockaddr*)&client,&client_addr_length);
    if(client_sock<0)
    {
        printf("accept failure\n");
    }
    else
    {
        printf("server accepted a client\n");
        close(client_sock);
    }
    close(sock);
    return 0;
}
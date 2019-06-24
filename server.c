#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define port 3940
int main(int argc,char *argv[])
{   
    int server_sock,new_socket,valread;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    char buffer[1024];
    char message[51];
    strcpy(message,"hello from server\n");
    int opt=1;
    strcpy(message,"Hello From Server\n");
    server_sock=socket(AF_INET,SOCK_STREAM,0);
    if(server_sock <= 0)
    {
        printf("Socket cannot be initialized\n");
    }
    else
    {
        printf("Socket initialized \n");
    }
    if(setsockopt(server_sock,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt)) < 0)
    {
        printf("Connection error\n");
    }
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    address.sin_addr.s_addr=INADDR_ANY;
    if(bind(server_sock,(struct sockaddr*)&address,sizeof(address)) < 0)
    {
        printf("Bind cannot be done\n");
    }
    if(listen(server_sock,3)<0)
    {
        printf("Cannot listen\n");
    }
    if((new_socket = accept(server_sock, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
    {
        printf("Problem in accepting\n");
    }
    valread = read(new_socket,buffer,1024);
    printf("%s\n",buffer);
    send(new_socket,message,strlen(message),0);
    printf("Message sent\n");
    return 0;
}

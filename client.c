#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
int main(int argc,char *argv[])
{   
    char *SERVER_ADDR="localhost";   
    int sock;
    struct sockaddr_in serv_addr;
    struct hostent *he = gethostbyname(SERVER_ADDR);
	unsigned long serv_addr_no = *(unsigned long *)(he->h_addr_list[0]);

    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        printf("Socket initialisation failed\n");
    }
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=serv_addr_no;
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
    {
        printf("Connection failed\n");
    }
    else
    {
        printf("connection has been established\n");
    }
    close(sock);
    return 0;
}
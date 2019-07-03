#include "cilent_pack.h"


int main(int argc, char *argv[])
{
    int sock,ret;
    pid_t pid;
    //char buf[1024+2];
    struct sockaddr_in con_fd;
    
    sock = tcp_link(argv[1], argv[2],&con_fd);
    if(connect(sock,(struct sockaddr*)&con_fd,sizeof(con_fd)) < 0)
    {
        perror("connect !");
        exit(1);
    }
    //socket ok!
    pid = fork();
    while(1)
    {
        if(pid == 0)
        {//cilent
           recvpack(sock,NULL);
        }
        else
        {
            sendpack(sock, NULL, SELECT);
            break;
        }
    }
}


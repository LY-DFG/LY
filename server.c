#include "epoll_ctl.h"

char recvbuf[1024];

int main(int argc, char *argv[])
{
    int tcp_soket,epoll_fd,e_size,cliaddrlen,udp_soket;
    int fd,revfd,file_fd,i;
    struct sockaddr_in my_addr,cliaddr;
    struct epoll_event events[20],ev;
    struct in_addr i_addr;
    
    tcp_soket = tcp_link(argv[1], argv[2],&my_addr);
    //socket ok!
    if(bind(tcp_soket,(struct sockaddr *) &my_addr,sizeof(my_addr)) == -1)
    {
        perror("error bind !£º");
        exit(1);
    }
    if(listen(tcp_soket,5) == -1)
    {
        perror("listrn error !");
        exit(1);
    }

    epoll_fd = epoll_create(5);
    do_epoll(epoll_fd,tcp_soket,EPOLLIN|EPOLLET,EPOLL_CTL_ADD);

    while(1)
    {
        e_size = (int)epoll_wait(epoll_fd,events,1,-1);       
        for(i = 0; i < e_size; i++)
        {
            fd = events[i].data.fd; 
            if(fd == tcp_soket&&events[i].events == EPOLLIN)
            {
                printf("socket accept!\n");
                do_accept(fd,epoll_fd);
            }
            else if(events[i].events == EPOLLIN)
            {
                printf("socket roead!\n");
                do_read(fd);
            }
            else if(events[i].events == EPOLLOUT)
            {
                printf("socket write!\n");
                do_write(fd);
            }
            
        }
    }
}





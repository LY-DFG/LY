#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <mysql/mysql.h>



#define PORT 8888
#define ADDR_IN "172.19.247.166"
#define BUFFSIZE 1024 

struct socket_addr{
    int socket_fd;               
    struct in_addr sin_addr; 
    struct socket_addr *netx;
};

struct Pack{
    short type;
    char buf[1024];
};


void do_accept(int fd,int epollfd);
void do_read(int fd);
void do_write(int file_fd);
void do_epoll(int epollfd,int fd,int flog,int op);
void rcveclient(struct sockaddr_in *c_addr,int c_fd);

void do_sql(char *buff,int fd);
MYSQL* mysql_connt();


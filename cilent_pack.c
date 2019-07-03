#include "cilent_pack.h"


int sendpack(int fd,char *buf,int flog)
{
    char buff[1024+2];
    struct Pack *sendbuf;
    int len;
    switch(flog)
    {
        case INSINT:           
            break;
        case SELECT:
            memset(buff,'/0',sizeof(buff));
            sendbuf = (struct Pack*)buff;
            memcpy(sendbuf->buf,"select * from user2",sizeof("select * from user2"));
            //memcpy(sendbuf->len, strlen(sendbuf->buf),strlen(sendbuf->buf));
            if((len = write(fd,sendbuf,strlen(sendbuf))) < 0)
            {
                perror("write perror!");
                exit(1);
            }
            break;
        case DELETE:
            break;
        case UPDATA:
            break;
    }
    return (int)sendbuf->len;
}

int recvpack(int fd,char *buff)
{
    //struct Pack *recvbuff;
    char buf[1024+2];
    memset(buf,'\0',sizeof(buf));
    //read(int fd, void * buf, size_t count);
    //recv(fd,buf,sizeof(buf),0)
    if(recv(fd, buf, sizeof(buf), 0) < 0)
    {
        perror("recv erroe !");
        exit(1);
    }
    //recvbuff = (struct Pack*)buf;
    printf("%s\n",buf);
    return 1;
}



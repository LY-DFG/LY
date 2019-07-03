#include "epoll_ctl.h"

void do_accept(int fd,int epollfd)
{
    int ret,c_len;
    struct sockaddr_in c_addr;
    struct epoll_event ev;   
    c_len = sizeof(struct sockaddr);
    if((ret = accept(fd,(struct sockaddr*) &c_addr,(socklen_t *) &c_len)) == -1)
    {
         perror("accept error !");
         exit(1);
    }
    
    /*accept ok! 
    ev.data.fd = ret;
    ev.events = EPOLLIN;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,ret,&ev);   //add
    */
    
    do_epoll(epollfd,ret,EPOLLIN|EPOLLET,EPOLL_CTL_ADD );
    //rcveclient(c_addr,);
}

void rcveclient(struct sockaddr_in * c_addr, int c_fd)// Î´Íê³É
{
    struct socket_addr addr;
    addr.socket_fd = c_fd;
    addr.sin_addr = c_addr->sin_addr;
    //addr->netx = 
}

void do_write(int file_fd)
{
    char buf[1024];
    if(file_fd == -1)
    {
        perror("open error");
        exit(1);
    }
    if(write(file_fd,buf,sizeof(buf))==-1)
    {
        perror("write error !");
        exit(1);
    }
}

void do_epoll(int epollfd,int fd,int flog,int op)
{
    int epoll_flog;
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = flog; 
    
    if(EPOLL_CTL_MOD == op)
        epoll_flog = EPOLL_CTL_MOD ;
    else if(EPOLL_CTL_ADD  == op)
        epoll_flog = EPOLL_CTL_ADD;
    else
        epoll_flog = EPOLL_CTL_DEL;
    
    if(epoll_ctl(epollfd,epoll_flog,ev.data.fd,&ev) < 0)
    {
        perror("epoll_ctl_add error !");
        exit(1);
    }
}



void do_read(int fd)
{
    struct Pack *repack;
    int file_fd;
    char Logbuf[BUFFSIZE];
    memset(Logbuf,'\0',sizeof(Logbuf));
    if(recv(fd,Logbuf,sizeof(Logbuf)-1,0) < 0)
    {
        perror("recv erroe !");
        exit(1);
    }
    repack = (struct Pack *)Logbuf;
    switch(repack->type)
    {
        case 1:
            break;
        ....
    }
    do_sql(Logbuf, fd);
    //file_fd = open("log.txt",O_WRONLY|O_CREAT|O_APPEND,0644);
    printf("client: %s size: %d\n",Logbuf,strlen(Logbuf));
}


MYSQL* mysql_connt()
{
    
     MYSQL *con = mysql_init(NULL);
     if(NULL == con)
     {
            fprintf(stderr,"%s\n",mysql_error(con));
            return-1;
     }
     if(NULL == mysql_real_connect(con,"localhost","root","6982875414","test",0,NULL,0))
     {
        perror("mysql connect error!");
     }
     //link ok!
     //mysql_query(con, "SET NAMES UTF8"); 
     return con;
}

void do_sql(char * buff, int fd)
{
    struct Pack *recv,sendpack;
    MYSQL *con;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char sendbuf[1024];
    int num_fields,i,len = 0;

    recv = (struct Pack*)buff;
    //memset(sendbuf,'\0',sizeof(struct Pack));
    bzero(sendbuf, 1024);
    con = mysql_connt();
    //mysql_query(con,"DROP TABLE IF EXISTS Phones")
    if(mysql_query(con,recv->buf))
    {
        perror("mysql_query error!");
    }

    
    result = mysql_store_result(con);
    if(result == NULL)
    {
        if(mysql_error(con))
        {
            perror("mysql_error!\n");
        }
        else{
            printf("ok!\n");
        }
    }
    else
    {     
        num_fields = mysql_num_fields(result);
        while((row = mysql_fetch_row(result)))
        {
            for(i = 0;i < num_fields ;i++){
                printf("%s ",row[i] ? row[i] : "NULL");
                memcpy(sendbuf + len ,row[i],strlen(row[i]));
                len += strlen(row[i]);
            }
            //memcpy(sendbuf.b,"\n",1);
        }
    }
     mysql_free_result(result);
     mysql_close(con);
     //sendbuf.len = strlen(sendbuf.buf);
     if(write(fd,sendbuf,sizeof(sendbuf)) < 0)
     {
        perror("Return result error !");
        exit(1);
     }
     printf("%s\n",sendbuf);
     //return 0;
}


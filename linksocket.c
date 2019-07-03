#include "linksocket.h"

int tcp_link(char *addr,char *port,struct sockaddr_in *my_addr)
{
    int soket;
    //char *buff = NULL;   
    //init_printf();
    soket = socket(AF_INET,SOCK_STREAM,0);
    bzero(my_addr,sizeof(struct sockaddr_in));
    my_addr->sin_family=AF_INET;
    //(inet_aton(argv[1], (struct in_addr *) &dest.sin_addr.s_addr) == 0)        
    if(addr == NULL){
        if(inet_aton(ADDR_IN, (struct in_addr *) &my_addr->sin_addr.s_addr) == 0)
        {
            perror("inet_aton !");
            exit(1);
        }    
        if(port == NULL){
            my_addr->sin_port = PORT;
        }
    }
    else
    {
        if(port!=NULL)
            my_addr->sin_port = htons(atoi(port));
        if(addr!=NULL)
            my_addr->sin_addr.s_addr = inet_addr(addr);
            /*if(inet_aton(argv[1], (struct in_addr *) &my_addr.sin_addr.s_addr) == 0)
            {
                perror("inet_aton !");
                exit(1);
            }*/
    }

    return soket;
}

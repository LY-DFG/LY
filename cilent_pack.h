#include "epoll_ctl.h"

#define INSINT 0x1
#define SELECT 0x2
#define UPDATA 0x3
#define DELETE 0x4



int sendpack(int fd,char *buf,int flog);
int recvpack(int fd,char *buf);


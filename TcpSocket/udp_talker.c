#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
/*  要连接的端口*/
#define MYPORT 5000
int main(int argc, char *argv[])
{
int sockfd;
/*  连接者的地址信息*/
struct sockaddr_in their_addr;
struct hostent *he;
int numbytes;
if (argc != 3)
{
/*  检测是否有所须参数，如没有，则显示使用方法后退出*/
fprintf(stderr,“ usage: talker hostname message\n” );
exit(1);
}
if ((he=gethostbyname(argv[1])) == NULL)
{ 
/*  取得主机的信息，如果失败则显示错误信息后退出*/
herror(“ gethostbyname” );
exit(1);
}
if（(sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
{
/*  申请一个数据报套接字描述符，失败则退出*/
perror (“ socket” );
exit(1);
}
/*  主机字节顺序*/
their_addr.sin_family = AF_INET;
/*  网络字节顺序，短整型*/
their_addr.sin_port = htons(MYPORT);
their_addr.sin_addr = *((struct in_addr *)he->h_addr);
/*  将结构中未用的部分清零*/
bzero(&(their_addr.sin_zero), 8);
if ((numbytes=sendto(sockfd, argv[2], strlen(argv[2]), 0,
(struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
{
/*  把信息发送到指定的主机指定端口，如出错则提示退出*/
perror(“ recvfrom” );
exit(1);
}
printf(“ sent %d bytes to %s\n” ,numbytes,inet_ntoa(their_addr.sin_addr));
/*  关闭套接字描述符后退出*/
close(sockfd);
return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
/*  要连接到的端口号*/
#define MYPORT 5000
/*  能够接收的最长数据*/
#define MAXBUFLEN 100
main()
{
int sockfd;
/*  本机的地址信息*/
struct sockaddr_in my_addr;
/*  连接这的地址信息*/
struct sockaddr_in their_addr;
int addr_len, numbytes;
char buf[MAXBUFLEN];
/*  取得一个套接字描述符*/
if（(sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1）
{
/*  如果取得套接字描述符失败，则给出错误信息，退出*/
perror(“ socket” );
exit(1);
}
/*  主机字节顺序*/
my_addr.sin_family = AF_INET;
/*  网络字节顺序，短整型*/
my_addr.sin_port = htons(MYPORT);
/*  自动设置为自己的 IP */
my_addr.sin_addr.s_addr = INADDR_ANY;
/*  将结构的其余空间清零*/
bzero(&(my_addr.sin_zero), 8);
/*  绑定端口*/
if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
{
/*  如果绑定端口出错，则显示错误信息然后退出*/
perror(“ bind” );
exit(1);
}
addr_len = sizeof(struct sockaddr);
/*  接收数据*/
if ((numbytes=recvfrom(sockfd, buf, MAXBUFLEN, 0,
(struct sockaddr *)&their_addr, &addr_len)) == -1)
{
/*  如果 recvfrom()调用出错，则显示错误信息后退出*/
perror(“ recvfrom” );
exit(1);
}
/*  显示接收到的数据*/
printf(“ got packet from %s\n” ,inet_ntoa(their_addr.sin_addr));
printf(“ packet is %d bytes long\n” ,numbytes);
buf[numbytes] = ‘ \0’;
printf(“ packet contains \” %s\“ \n” ,buf);
/*  关闭套接字连接*/
close(sockfd);
}
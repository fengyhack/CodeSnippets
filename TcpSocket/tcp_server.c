#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MYPORT 4000 

#define BACKLOG 10 

int main(void)
{
	int sock_fd, new_fd ;
	
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);

	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

if (bind(sockfd, (struct sockaddr *)&my_addr,
sizeof(struct sockaddr)) == -1)
{
/*  如果调用 bind()失败，则给出错误提示，退出*/
perror(“ bind” );
exit(1);
}
/*  这里是我们一直强调的错误检查！！*/
if (listen(sockfd, BACKLOG) == -1)
{
/*  如果调用 listen 失败，则给出错误提示，退出*/
perror(“ listen” );
exit(1);
}
while(1)
{ 
/*  这里是主 accept()循环*/
sin_size = sizeof(struct sockaddr_in);
/*  这里是我们一直强调的错误检查！！*/
if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
{
/*  如果调用 accept()出现错误，则给出错误提示，进入下一个循环*/
perror(“ accept” );
continue;
}
/*  服务器给出出现连接的信息*/
printf（“ server: got connection from %s\n” , inet_ntoa(their_addr.sin_addr)）;
/*  这里将建立一个子进程来和刚刚建立的套接字进行通讯*/
if (!fork())
/*  这里是子进程*/
/*  这里就是我们说的错误检查！*/
if (send(new_fd,  “Hello, world!\n” , 14, 0) == -1)
{
/*  如果错误，则给出错误提示，然后关闭这个新连接，退出*/
perror(“ send” );
close(new_fd);
exit(0);
}
/*  关闭 new_fd 代表的这个套接字连接*/
close(new_fd);
}
}
/*  等待所有的子进程都退出*/
while(waitpid(-1,NULL,WNOHANG) > 0);
}
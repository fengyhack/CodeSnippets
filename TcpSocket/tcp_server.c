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
/*  ������� bind()ʧ�ܣ������������ʾ���˳�*/
perror(�� bind�� );
exit(1);
}
/*  ����������һֱǿ���Ĵ����飡��*/
if (listen(sockfd, BACKLOG) == -1)
{
/*  ������� listen ʧ�ܣ������������ʾ���˳�*/
perror(�� listen�� );
exit(1);
}
while(1)
{ 
/*  �������� accept()ѭ��*/
sin_size = sizeof(struct sockaddr_in);
/*  ����������һֱǿ���Ĵ����飡��*/
if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
{
/*  ������� accept()���ִ��������������ʾ��������һ��ѭ��*/
perror(�� accept�� );
continue;
}
/*  �����������������ӵ���Ϣ*/
printf���� server: got connection from %s\n�� , inet_ntoa(their_addr.sin_addr)��;
/*  ���ｫ����һ���ӽ������͸ոս������׽��ֽ���ͨѶ*/
if (!fork())
/*  �������ӽ���*/
/*  �����������˵�Ĵ����飡*/
if (send(new_fd,  ��Hello, world!\n�� , 14, 0) == -1)
{
/*  ������������������ʾ��Ȼ��ر���������ӣ��˳�*/
perror(�� send�� );
close(new_fd);
exit(0);
}
/*  �ر� new_fd ���������׽�������*/
close(new_fd);
}
}
/*  �ȴ����е��ӽ��̶��˳�*/
while(waitpid(-1,NULL,WNOHANG) > 0);
}
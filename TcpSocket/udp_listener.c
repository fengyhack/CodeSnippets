#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
/*  Ҫ���ӵ��Ķ˿ں�*/
#define MYPORT 5000
/*  �ܹ����յ������*/
#define MAXBUFLEN 100
main()
{
int sockfd;
/*  �����ĵ�ַ��Ϣ*/
struct sockaddr_in my_addr;
/*  ������ĵ�ַ��Ϣ*/
struct sockaddr_in their_addr;
int addr_len, numbytes;
char buf[MAXBUFLEN];
/*  ȡ��һ���׽���������*/
if��(sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1��
{
/*  ���ȡ���׽���������ʧ�ܣ������������Ϣ���˳�*/
perror(�� socket�� );
exit(1);
}
/*  �����ֽ�˳��*/
my_addr.sin_family = AF_INET;
/*  �����ֽ�˳�򣬶�����*/
my_addr.sin_port = htons(MYPORT);
/*  �Զ�����Ϊ�Լ��� IP */
my_addr.sin_addr.s_addr = INADDR_ANY;
/*  ���ṹ������ռ�����*/
bzero(&(my_addr.sin_zero), 8);
/*  �󶨶˿�*/
if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
{
/*  ����󶨶˿ڳ�������ʾ������ϢȻ���˳�*/
perror(�� bind�� );
exit(1);
}
addr_len = sizeof(struct sockaddr);
/*  ��������*/
if ((numbytes=recvfrom(sockfd, buf, MAXBUFLEN, 0,
(struct sockaddr *)&their_addr, &addr_len)) == -1)
{
/*  ��� recvfrom()���ó�������ʾ������Ϣ���˳�*/
perror(�� recvfrom�� );
exit(1);
}
/*  ��ʾ���յ�������*/
printf(�� got packet from %s\n�� ,inet_ntoa(their_addr.sin_addr));
printf(�� packet is %d bytes long\n�� ,numbytes);
buf[numbytes] = �� \0��;
printf(�� packet contains \�� %s\�� \n�� ,buf);
/*  �ر��׽�������*/
close(sockfd);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PROT 8888

/*
搭建UDP服务器步骤：
1. 创建(socket)套接字
2. 绑定(bind)IP地址
4. 阻塞方式接收客户端发来的数据
*/
int main(int argc,char **argv)
{
	  int socketfd;
	  int Clientsocketfd;
	  struct sockaddr_in ServerSocket;
	  struct sockaddr_in ClientSocket;
	  socklen_t socklen;
	 /*1. 创建(socket)套接字*/
	 socketfd=socket(PF_INET,SOCK_DGRAM,0); 
	 if(socketfd<0)
	 	{
	 	   printf("服务器创建失败!\n");	
	 	   exit(-1);
	 	}
	 /*2. 绑定IP地址*/
	 ServerSocket.sin_family=PF_INET; //协议
	 ServerSocket.sin_port=htons(PROT); //端口 >1024
	 ServerSocket.sin_addr.s_addr=INADDR_ANY;  //表示本地所有IP
	 bzero(ServerSocket.sin_zero,8); //初始化空间
	 if(bind(socketfd,(const struct sockaddr *)&ServerSocket,sizeof(struct sockaddr))!=0)
	 	{
	 	   printf("服务器绑定失败!\n");	
	 	   exit(-1);	
	 	}
	 
	 /*3. 阻塞方式接收数据*/
	 int len=0;
	 char buff[1024];
	 size_t addrlen=sizeof(struct sockaddr);
	 while(1)
	 {
		  	len=recvfrom(socketfd,buff,1024,0,(struct sockaddr *)&ClientSocket,&addrlen);
		  	buff[len]='\0';
		  	printf("Rx: %s,len=%d\n",buff,len);
		  	printf("数据发送方IP地址:%s\n",inet_ntoa(ClientSocket.sin_addr));
		  	printf("数据发送方端口号:%d\n",ntohs(ClientSocket.sin_port));	   	
	 }

	 /*4. 关闭文件描述符*/
	 close(Clientsocketfd);
	 close(socketfd);
	 return 0;
}


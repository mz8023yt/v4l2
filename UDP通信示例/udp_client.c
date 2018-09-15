#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PROT 8888

/*
搭建UDP客户端步骤：
1. 创建(socket)套接字
2. 向指定UDP服务器发送数据
*/
int main(int argc,char **argv)
{
	 if(argc!=2)
	 {
	    printf("传参格式: ./app <服务器IP地址>\n");	
	 	  exit(-1);	
	 }
	  int socketfd;
	  struct sockaddr_in ServerSocket;
	  
	 /*1. 创建(socket)套接字*/
	 socketfd=socket(PF_INET,SOCK_DGRAM,0); 
	 if(socketfd<0)
	 	{
	 	   printf("服务器创建失败!\n");	
	 	   exit(-1);
	 	}
	 	
	 /*2. 向UDP协议服务器发送数据*/
	 ServerSocket.sin_family=PF_INET; //协议
	 ServerSocket.sin_port=htons(PROT); //端口
	 ServerSocket.sin_addr.s_addr=inet_addr(argv[1]);  //表示服务器的IP地址
	 bzero(ServerSocket.sin_zero,8); //初始化空间
	 
	 char buff[]="1234567890";
	 int len=0;
	 while(1)
	 {
	  	 len=sendto(socketfd,buff,strlen(buff),0,(const struct sockaddr*)&ServerSocket,sizeof(struct sockaddr));
	  	 printf("Tx: %d\n",len); 
	  	 sleep(1); 	 	
	 }

   /*3. 关闭文件描述符*/
   close(socketfd);
	 return 0;
}



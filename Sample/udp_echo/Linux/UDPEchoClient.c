#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     

int main(int argc, char *argv[])
{
    int sock;                        //소켓 descriptor
    struct sockaddr_in ServerAddr;   //서버 주소
    struct sockaddr_in RecvAddr;     //응답 받은 서버 주소
    unsigned short ServPort;         //서버 Port 번호
    unsigned int DataSize;           //recv data 크기
    char *ServerIp;                  //서버 IP
    char *SendData;                  //보낼 데이터
    char recvBuffer[1024];           //받은 데이터
    int sendLength;                  //보낼 데이터 길이 
    int recvLength;                  //받은 데이터 길이

    ServerIp = "127.0.0.1";        //서버의 IP 주소
    SendData = "Hello world";   //서버에 보낼 데이터
    ServPort = 8080;  //서버의 port 번호

    //UDP 소켓 생성
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        printf("socket 생성 실패");


    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;                 // Server - Ipv4 설정
    ServerAddr.sin_addr.s_addr = inet_addr(ServerIp);  // Server - addr 설정
    ServerAddr.sin_port = htons(ServPort);     // Server - port 설정

    //서버에 Data 보내기
    if ((sendLength = sendto(sock, SendData, strlen(SendData), 0, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)))!= strlen(SendData))
	printf("send data differ 'SendData'\n");
  
	printf("[send] : %s\n",SendData);

    //서버로부터 Data 받기
    int size = sizeof(RecvAddr);

    if ((recvLength = recvfrom(sock, recvBuffer, 1024, 0, (struct sockaddr *) &RecvAddr, &size)) < 0)
	printf("data receive error\n");
	
        recvBuffer[recvLength] = '\0';
	printf("[recv] : %s\n", recvBuffer);

    if (ServerAddr.sin_addr.s_addr != RecvAddr.sin_addr.s_addr)
        printf("[send] data received from unknown source\n");
	
        
    close(sock);
    exit(0);
}

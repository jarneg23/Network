#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */


int main(int argc, char *argv[])
{

    int sock;                  //서버 소켓 descriptor
    struct sockaddr_in ServerAddr;   //서버 주소
    struct sockaddr_in ClientAddr;   //클라이언트 주소
    unsigned short ServPort;         //서버 Port 번호
    char *ServerIp;                  //서버 IP
    char *SendData;                  //보낼 데이터
    char recvBuffer[1024];           //받은 데이터
    int sendLength;                  //보낼 데이터 길이 
    int recvLength;                  //받은 데이터 길이

    ServerIp = "127.0.0.1";        //서버의 IP 주소
    SendData = "Hello world";   //서버에 보낼 데이터
    ServPort = 8080;  //서버의 port 번호

  char* SendData2 = "aa";

    //TCP 소켓 생성
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	printf("socket create fail \n");

    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;                 // Server - Ipv4 설정
    ServerAddr.sin_addr.s_addr = inet_addr(ServerIp);  // Server - addr 설정
    ServerAddr.sin_port = htons(ServPort);     // Server - port 설정

    //Server에 접속을 요청한다.
    if (connect(sock, (struct sockaddr *) & ServerAddr, sizeof(ServerAddr)) < 0)
    	printf("connect error \n");

    sendLength = strlen(SendData);

    //서버에 데이터 보내기
    if (send(sock, SendData, sendLength, 0) != sendLength)
        printf("send error \n");
	printf("[send] %s \n",SendData);


    //서버로부터 데이터를 받기
    if(recv(sock, recvBuffer, sendLength, 0) <0)
 	printf("recv error \n");
	printf("[recv] %s : \n", recvBuffer);

    close(sock);
    exit(0);
}

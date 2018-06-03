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
    struct sockaddr_in ClientAddr;   //클라이언트 주소
    char recvBuffer[1024];           //받은 데이터
    //char* recvBuffer;           //받은 데이터
    int recvLength;                  //받은 데이터 길이
    int sendLength;                  //보낼 데이터 길이 

    unsigned short ServPort;         //서버 Port 번호
    ServPort = 8080;

    // UDP socket 생성
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	printf("sock create Error\n");


    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;                // Server - Ipv4 설정
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 Ip로부터 오는 data 받기
    ServerAddr.sin_port = htons(ServPort);          // Server - port 설정

    //Socket에 프로그램을 구별 하기 위한 port번호를 묶어 주기
    if (bind(sock, (struct sockaddr *) &ServerAddr, sizeof(ServerAddr)) < 0)
        printf("socket bind() Error \n");
  
    for (;;)
    {
        int size = sizeof(ClientAddr);
	
	//클라이언트로부터 data 받기
        if ((recvLength = recvfrom(sock, recvBuffer, 1024, 0, (struct sockaddr *) &ClientAddr, &size)) < 0)
	    printf("data receive Error()\n");

        printf("Handling client %s\n", inet_ntoa(ClientAddr.sin_addr));
	printf("[recv] : %s\n",recvBuffer);

	//클라이언트에 응답 보내기
        if ((sendLength = sendto(sock, recvBuffer, strlen(recvBuffer), 0, (struct sockaddr *) &ClientAddr, sizeof(ClientAddr))) != recvLength)
	printf("send data not same recv data\n");
        printf("Handling client %s\n", inet_ntoa(ClientAddr.sin_addr));
	printf("[send] : %s\n",recvBuffer);

    }


}

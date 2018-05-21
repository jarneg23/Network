#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib");

#include <stdio.h>      
#include <winsock.h>    
#include <stdlib.h>     
#include <string.h>

void main(int argc, char *argv[])
{
    int sock;                        //소켓 descriptor
    struct sockaddr_in ServerAddr;   //서버 주소
    struct sockaddr_in ClientAddr;   //클라이언트 주소
    char recvBuffer[1024];           //받은 데이터
    //char* recvBuffer;           //받은 데이터
    int recvLength;                  //받은 데이터 길이
    int sendLength;                  //보낼 데이터 길이 

    unsigned short ServPort;         //서버 Port 번호

    WSADATA wsaData;
    ServPort = 8080;
    WSAStartup(MAKEWORD(2, 0), &wsaData);


    // UDP socket 생성
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;                // Server - Ipv4 설정
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 Ip로부터 오는 data 받기
    ServerAddr.sin_port = htons(ServPort);     // Server - port 설정

                                               //Socket에 프로그램을 구별 하기 위한 port번호를 묶어 주기
    bind(sock, (struct sockaddr *) &ServerAddr, sizeof(ServerAddr));


    for (;;)
    {
        //client로 부터 data 받기
        int size = sizeof(ClientAddr);
        recvLength = recvfrom(sock, recvBuffer, 1024, 0, (struct sockaddr *) &ClientAddr, &size);
        if (recvLength <= 0) { printf("[Recv] Error or 0\n"); }
        else { printf("[Recv] %s , %d byte\n", inet_ntoa(ClientAddr.sin_addr), recvLength); }

        recvBuffer[recvLength] = '\0';
        //client에 요청에 대한 응답 보내기
        sendLength = sendto(sock, recvBuffer, strlen(recvBuffer), 0, (struct sockaddr *) &ClientAddr, sizeof(ClientAddr));
        if (sendLength <= 0) { printf("[Send] error or 0\n"); }
        else { 
            printf("[Recv] addr : %s\n", inet_ntoa(ClientAddr.sin_addr));
            printf("[Send] %s : %d byte\n", recvBuffer, sendLength); 
        }
    }

}

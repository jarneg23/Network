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
    struct sockaddr_in RecvAddr;     //응답 받은 서버 주소
    unsigned short ServPort;         //서버 Port 번호
    unsigned int DataSize;           //recv data 크기
    char *ServerIp;                  //서버 IP
    char *SendData;                  //보낼 데이터
    char recvBuffer[1024];           //받은 데이터
    int sendLength;                  //보낼 데이터 길이 
    int recvLength;                  //받은 데이터 길이

    WSADATA wsaData;                 //window socket을 위한 socket structure

    ServerIp = "127.0.0.1";
    ServPort = 8080;
    SendData = "Hey";

    WSAStartup(MAKEWORD(2, 0), &wsaData);

    // UDP socket 생성
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) { printf("Socket create Error\n"); }

    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;                 // Server - Ipv4 설정
    ServerAddr.sin_addr.s_addr = inet_addr(ServerIp);  // Server - addr 설정
    ServerAddr.sin_port = htons(ServPort);     // Server - port 설정

                                               //Server에 data 보내기
    sendLength = sendto(sock, SendData, strlen(SendData), 0, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr));
    printf("[Send] %s : %d byte\n", SendData, sendLength);

    int size = sizeof(RecvAddr);

    //Server에 보낸 data에 대한 응답 받기
    recvLength = recvfrom(sock, recvBuffer, 1024, 0, (struct sockaddr *) &RecvAddr, &size);

    if (recvLength <= 0) { printf("[Recv] error or 0\n"); }
    else 
    {
        recvBuffer[recvLength] = '\0';
        printf("[Recv] %s : %d byte\n", recvBuffer, recvLength); 
    }


    closesocket(sock);
    printf("Close Sock");

    WSACleanup();  /* Cleanup Winsock */

    exit(0);
}

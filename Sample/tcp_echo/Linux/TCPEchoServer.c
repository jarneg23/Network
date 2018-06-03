#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     

#define MAXPENDING 5    


void ClientHandling(int ClientSock);  //Client 처리 함수


void ClientHandling(int ClientSock)
{
    
   char recvData[1024]; 
    int recvLength = 1;      
    int clienLength;
    int sendLength = 1;
    //클라이언트로부터 데이터를 받기


while(recvLength >0)
{

	if(recvLength = recv(ClientSock, recvData, 1024, 0) == 0 ) break;
	printf("[recv] %s , %d\n",recvData,recvLength);

        sendLength = send(ClientSock, recvData, strlen(recvData), 0);
	printf("[send] %s , %d\n",recvData,sendLength);

}

    close(ClientSock);    /* Close client socket */

}



int main(int argc, char *argv[])
{

    int ServerSock;                  //서버 소켓 descriptor
    int ClientSock;		     //클라이언트 소켓 descriptor
    struct sockaddr_in ServerAddr;   //서버 주소
    struct sockaddr_in ClientAddr;   //클라이언트 주소
    unsigned short ServPort;         //서버 Port 번호

    ServPort = 8080;


    if ((ServerSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
 	printf("ServerSock create failed\n");
      

    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;                // Server - Ipv4 설정
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 Ip로부터 오는 data 받기
    ServerAddr.sin_port = htons(ServPort);          // Server - port 설정

    //Socket에 서버의 포트번호를 묶어 준다 (서버 프로그램을 구별하기 위해서)

    if (bind(ServerSock, (struct sockaddr *) & ServerAddr, sizeof(ServerAddr)) < 0)
	printf("bind() error\n");

    //Client의 연결을 기다린다
    if (listen(ServerSock, MAXPENDING) < 0)
	printf("Listen Error \n");

    for (;;) /* Run forever */
    {

        int ClientAddrLength = sizeof(ClientAddr);

	//클라이언트가 연결을 시도하면 클아이언트의 연결을 받는다.
        if ((ClientSock = accept(ServerSock, (struct sockaddr *) &ClientAddr,&ClientAddrLength)) < 0)
	    printf("accept Error\n");

        printf("Accept client %s\n", inet_ntoa(ClientAddr.sin_addr));

        ClientHandling(ClientSock);

    }

}

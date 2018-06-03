#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     

/*
broadCast는 특정 네트워크에 연결된 모든 host들에게 Packet을 보내는 네트워킹 방식
*/

int main(int argc, char *argv[])
{
    int sock;                         
    struct sockaddr_in broadcastAddr; 
    unsigned short broadcastPort;     
    char recvData[1025]; 
    int recvDataLength;     

    broadcastPort = 8099;  //broadcast 포트 번호
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	printf("Socket 생성 에러");


    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   
    broadcastAddr.sin_family = AF_INET;                 
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    broadcastAddr.sin_port = htons(broadcastPort); 

    //내가 속한 네트워크의 모든 sender로부터 data를 받기 때문에 address == INADDR_ANY로 설정한다.
    if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0)
	printf("bind() 에러");

    for(;;)
    {
    	if ((recvDataLength = recvfrom(sock, recvData, 1024, 0, NULL, 0)) < 0)
	printf("[recv] Error");

	recvData[recvDataLength] = '\0'; // 스트링의 마지막에 \0을 추가해주는 것으로 끝을 설정한다.
	printf("[recv]: %s\n", recvData);    /* Print the received string */
    }
    close(sock);
    exit(0);
}

#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     

int main(int argc, char *argv[])
{
    int sock;                         
    struct sockaddr_in broadcastAddr; 
    char* broadcastIP;                
    unsigned short broadcastPort;    
    char* sendData;                 
    int broadcastOption;	//broadcast 옵션을 위한 값
    unsigned int sendDataLength; //sendData의 길이
   
    broadcastIP = "255.255.255.255";   //local broadcast에 사용되는 고정 IP주소
    broadcastPort = 8080;    /* Second arg:  broadcast port */
    sendData = "Hello world";             /* Third arg:  string to broadcast */


    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	printf("Socket 생성 에러\n");

    broadcastOption = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) & broadcastOption, sizeof(broadcastOption)) < 0)
	printf("socket 옵션 설정 에러\n");


    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   
    broadcastAddr.sin_family = AF_INET;                 
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);
    broadcastAddr.sin_port = htons(broadcastPort);         

    sendDataLength = strlen(sendData);
    for (;;) 
    {
         if (sendto(sock, sendData, sendDataLength, 0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) != sendDataLength)
             printf("[send] error\n");
	printf("[send] : %s\n",sendData);
        sleep(3);   
    }
}

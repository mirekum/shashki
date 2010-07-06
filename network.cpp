#include "board.h"
#include "network.h"

/* methods of class of the network player */

// chooses partial half-move
MOVE NETWORK_PLAYER::getMove(BOARD board) {
	// request partial half-move
	exit(1);
	
	return result;
}


bool NETWORK_PLAYER::create_Server()
{

      struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, "eth0");

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    ioctl(sock, SIOCGIFADDR, &ifr);
    close(sock);

    struct sockaddr_in *sa = (struct sockaddr_in*)&ifr.ifr_addr;
    
//    printf("addr = %s\n", inet_ntoa(sa->sin_addr));
  


    int listener;
    struct sockaddr_in addr;
/*
    char buf[1024];
    int bytes_read;
*/

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        return 0;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(27015);
    addr.sin_addr.s_addr = inet_addr(inet_ntoa(sa->sin_addr));
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return 0;
    }

    listen(listener, 1);
    
    
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            return 0;
        }
/*
        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            send(sock, buf, bytes_read, 0);
	    printf("addr = %s\n", buf);
        }
    
        close(sock);
    }
 */   
    return 1;


}



bool NETWORK_PLAYER::create_Line()
{
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, "eth0");
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    ioctl(sock, SIOCGIFADDR, &ifr);
    close(sock);
    struct sockaddr_in *sa = (struct sockaddr_in*)&ifr.ifr_addr;
    printf("addr = %s\n", inet_ntoa(sa->sin_addr));
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return 0;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(27015);
    addr.sin_addr.s_addr = inet_addr( inet_ntoa(sa->sin_addr));
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        return 0;
    }
/*
    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(message), 0);
    close(sock);
    printf("addr = %s\n", buf);
*/
    return 1;
}

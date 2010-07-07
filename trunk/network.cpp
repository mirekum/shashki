#include "board.h"
#include "network.h"

/* methods of class of the network player */
void NETWORK_PLAYER::giveLastMuves(MOVE lastMove[maxCountYouShaSh]) {
printf("seee send");
int i=0;
while(i<maxCountYouShaSh){
	send(sock, &lastMove[i], sizeof(lastMove[i]), 0);
i++;
}
printf("send out");

};




// chooses partial half-move
MOVE NETWORK_PLAYER::getMove(BOARD board) {
	 printf("seee send");
MOVE tmp;
int i=0;
while(i<maxCountYouShaSh){
		std::cout << "x1 = "; std::cout << result.from.x;
		std::cout << "y1 = "; std::cout << result.from.y;
		std::cout << "x2 = "; std::cout << result.to.x;
		std::cout << "y2 = "; std::cout << result.to.y;
		recv(sock, &result, sizeof(result), 0);	
		std::cout << board << std::endl;
		
		if(board.move(result)){
		tmp=result;
		}
		board.canMove();
		
	
i++;
}
		   printf("send in");
		
		
	return tmp;

}


bool NETWORK_PLAYER::createServer(){
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, "eth0");

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    ioctl(sock, SIOCGIFADDR, &ifr);
    close(sock);

    struct sockaddr_in *sa = (struct sockaddr_in*)&ifr.ifr_addr;
    
   printf("addr = %s\n", inet_ntoa(sa->sin_addr));
  


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
    isitServer=1;
    return 1;


}
bool NETWORK_PLAYER::sendServerOrClient(){
		char res[2];
                std::cout << "do you wont create server game [y/n]:"; std::cin >>res;
		if(res[0]=='y'){
		createServer();
		}
		else if(res[0]=='n'){
		createLine();
		}
		else{
		exit(1);
		}		
}
NETWORK_PLAYER::NETWORK_PLAYER(){
     		type = NONE;
  		sendServerOrClient();
		}

NETWORK_PLAYER::~NETWORK_PLAYER(){
		close(sock);
		}

bool NETWORK_PLAYER::createLine(){
    char inetServAdr[16]="0.0.0.0";
    std::cout << "select inet adr:"; std::cin >>inetServAdr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(27015);
    addr.sin_addr.s_addr = inet_addr(inetServAdr);
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
    isitServer=0;
    return 1;
}

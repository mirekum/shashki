#include "Model/board.h"
#include "Players/network.h"

/* methods of class of the network player */
void NETWORK_PLAYER::sendToError(char send){

	switch (send) {
		case 1:
			perror("socket");
		case 2:
			perror("bind");;
		case 3:
			perror("accept"); ;
		case 4:
			perror("connect");;
		default:
			exit(1);
	}
};


void NETWORK_PLAYER::giveLastMoves(MOVE lastMove[maxFiguresNumber]) {
int i=0;
while(i<maxFiguresNumber){
	send(sock, &lastMove[i], sizeof(lastMove[i]), 0);
	lastMove[i].from.x=0;
	lastMove[i].from.y=0;
	lastMove[i].to.x=0;
	lastMove[i].to.y=0;
	i++;
	}

};




// chooses partial half-move
MOVE NETWORK_PLAYER::getMove(BOARD board) {

do{
		recv(sock, &result, sizeof(result), 0);	
		if (board.move(result)) break;
		}while (1);
return result;
};


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
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
	sendToError(1);
        return 0;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(27015);
    addr.sin_addr.s_addr = inet_addr(inet_ntoa(sa->sin_addr));
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
	sendToError(2);
        return 0;
    }

    listen(listener, 1);
    

	sock = accept(listener, NULL, NULL);
	if(sock < 0)
	{
		sendToError(3);
		return 0;
	}
    isitServer=1;
    return 1;


};
bool NETWORK_PLAYER::sendServerOrClient(){
		char res[2];
                std::cout << "do you wont create server game [y/n]:"; std::cin >>res;
		if(res[0]=='y'){
		return true;
		}
		else if(res[0]=='n'){
		return false;
		}
		else{
		exit(1);
		}		
}
NETWORK_PLAYER::NETWORK_PLAYER(){
     		type = NONE;
  		if(sendServerOrClient())createServer();
		else createLine();
		};

NETWORK_PLAYER::~NETWORK_PLAYER(){
		close(sock);
		};

bool NETWORK_PLAYER::giveAdres(std::string&adr){

    std::cout << "select inet adr:"; std::cin >>adr;
    return true;
}
bool NETWORK_PLAYER::createLine(){
    std::string inetServAdr="0.0.0.0";
    giveAdres(inetServAdr);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        sendToError(1);
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(27015);
    addr.sin_addr.s_addr = inet_addr(inetServAdr.c_str());
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        sendToError(4);
        return 0;
    }
    isitServer=0;
    return 1;
}

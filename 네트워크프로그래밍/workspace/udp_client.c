#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define BOARD_SIZE 5
#define GAME_REQ 1
#define GAME_RES 2
#define GAME_END 3

typedef struct{
  int cmd;
  char ch;
}REQ_PACKET;

typedef struct{
  int cmd;
  char board[BOARD_SIZE][BOARD_SIZE];
  int result;
}RES_PACKET;

void error_handling(char *message);
void printBoard(char board[][BOARD_SIZE]);
int main(int argc, char *argv[])
{
	int sock;
	socklen_t adr_sz;
	REQ_PACKET req_packet;
	RES_PACKET res_packet;
	srand(time(NULL));
	memset(&req_packet, 0, sizeof(REQ_PACKET));
	memset(&res_packet, 0, sizeof(RES_PACKET));
	//char board[BOARD_SIZE][BOARD_SIZE];
	printf("------------------------------\n");
	printf(" Finding Alphabet Game Client\n");
	printf("------------------------------\n");
	struct sockaddr_in serv_adr, from_adr;
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_DGRAM, 0);   
	if(sock==-1)
		error_handling("socket() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

	// STUB
	struct sockaddr_in temp_adr;
	memset(&temp_adr, 0, sizeof(temp_adr));
	temp_adr.sin_family=AF_INET;
	temp_adr.sin_addr.s_addr=inet_addr("0.0.0.0");
	temp_adr.sin_port=htons(54192);

	bind(sock, (struct sockaddr *)&temp_adr, sizeof(temp_adr));
	while(1){
		req_packet.cmd = GAME_REQ;
		req_packet.ch = 'A' + (rand()%26);
		sendto(sock, &req_packet, sizeof(REQ_PACKET), 0, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
		printf("[Client] TX cmd = %d ch = %c\n", req_packet.cmd, req_packet.ch);
		recvfrom(sock, &res_packet, sizeof(RES_PACKET), 0, (struct sockaddr*)&from_adr, &adr_sz);
		printf("[Client] RX cmd = %d result = %d\n", res_packet.cmd, res_packet.result);
		
		if(res_packet.cmd == GAME_END){
			printf("No empty space, Exit this program\n");
			break;
		}	
		printBoard(res_packet.board);
		//sleep(1);
	}
	close(sock);
	printf("Exit Client Program\n");
	return 0;
	
}

void printBoard(char ans[][BOARD_SIZE]){
	for(int i = 0; i < BOARD_SIZE; i++){
		printf("+-----------------------+\n");
		for(int j = 0; j < BOARD_SIZE; j++){
			if(ans[i][j] == 0)
				printf("|   |");
			else
				printf("|%2c |", ans[i][j]);
		}
		printf("\n");
	}	
	printf("+-----------------------+\n\n");

}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

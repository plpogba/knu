#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <stdbool.h>

#define BUF_SIZE 30
#define BOARD_SIZE 5
#define GAME_REQ 1
#define GAME_RES 2
#define GAME_END 3

typedef struct{
  int cmd;
  char ch;
}REQ_PACKET;//client -> server

typedef struct{
  int cmd;
  char board[BOARD_SIZE][BOARD_SIZE];
  int result;
}RES_PACKET;//server -> client

void error_handling(char *message);
void setBoard(char board[][BOARD_SIZE]);
void printBoard(char board[][BOARD_SIZE], char ans[][BOARD_SIZE]);
int compareBoard(char c, char board[][BOARD_SIZE], char ans[][BOARD_SIZE]);
bool isDone(char ans[][BOARD_SIZE]);


int main(int argc, char *argv[])
{
	int serv_sock;
	char board[BOARD_SIZE][BOARD_SIZE];
	char ans[BOARD_SIZE][BOARD_SIZE];
	int correctAlpha;

	printf("------------------------------\n");
	printf(" Finding Alphabet Game Server\n");
	printf("------------------------------\n");

	memset(board, 0, sizeof(board));
	memset(ans, 0, sizeof(ans));

	socklen_t clnt_adr_sz;
	
	struct sockaddr_in serv_adr, clnt_adr;
	RES_PACKET res_packet;
	REQ_PACKET req_packet;
	memset(&res_packet, 0, sizeof(RES_PACKET));
	memset(&req_packet, 0, sizeof(REQ_PACKET));

	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_DGRAM, 0);
	if(serv_sock==-1)
		error_handling("UDP socket creation error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	setBoard(board);
	printBoard(board, ans);
	


	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	

	while(!isDone(ans)) 
	{
		clnt_adr_sz=sizeof(clnt_adr);
		recvfrom(serv_sock, &req_packet, sizeof(REQ_PACKET), 0, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		printf("[Server] RX cmd=%d, ch = %c\n", req_packet.cmd, req_packet.ch);
		correctAlpha = compareBoard(req_packet.ch, board, ans);
		res_packet.cmd = GAME_RES;
		if(req_packet.cmd == GAME_REQ){
			res_packet.result = correctAlpha;
			memcpy(res_packet.board, ans, sizeof(ans));
			printf("[Server] TX cmd=%d, result = %d\n", res_packet.cmd, res_packet.result);
			printBoard(board, ans);
			//sleep(1);
			sendto(serv_sock, &res_packet, sizeof(res_packet), 0, (struct sockaddr*)&clnt_adr, clnt_adr_sz);
		}
		else
			error_handling("wrong access\n");
	}	
	res_packet.cmd = GAME_END;
	res_packet.result = 0;
	printf("[Server] TX cmd=%d, result = %d\n", res_packet.cmd, res_packet.result);
	printf("No empty space, Exit this program\n");
	sendto(serv_sock, &res_packet, sizeof(res_packet), 0, (struct sockaddr*)&clnt_adr, clnt_adr_sz);

	close(serv_sock);

	printf("Exit Server Program\n");

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void setBoard(char board[][BOARD_SIZE]){
  srand(time(NULL));
  for(int i = 0; i < BOARD_SIZE; i++){
  	for(int j = 0; j < BOARD_SIZE; j++)
  		 board[i][j] = 'A' + ((rand()%26));
  }
}

int compareBoard(char c, char board[][BOARD_SIZE], char ans[][BOARD_SIZE]){
	int cnt = 0;
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			if(board[i][j] == c){
				ans[i][j] = c;
				cnt += 1;
			}
		}
	}
	return cnt;
}
bool isDone(char ans[][BOARD_SIZE]){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			if( ans[i][j] == 0)
				return false;
		}
	}
	return true;
}
void printBoard(char board[][BOARD_SIZE], char ans[][BOARD_SIZE]){
	for(int i = 0; i < BOARD_SIZE; i++){
		printf("+-----------------------+  +-----------------------+\n");
		for(int j = 0; j < BOARD_SIZE; j++){
			printf("|%2c |", board[i][j]);
		}
		printf("  ");
		for(int j = 0; j < BOARD_SIZE; j++){
			if(ans[i][j] == 0)
				printf("|   |");
			else
				printf("|%2c |", ans[i][j]);
		}
		printf("\n");
	}	
	printf("+-----------------------+  +-----------------------+\n\n");

}

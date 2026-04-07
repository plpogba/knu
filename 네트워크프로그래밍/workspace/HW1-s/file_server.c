//2022112332 jinoo kang

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

#define BUF_SIZE 100
#define SEQ_START 1000

typedef struct{
  int seq;
  int ack;
  int buf_len;
  char buf[BUF_SIZE+1];
}Packet;
void error_handling(char *message);
int actualLength(char *message);
int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	int str_len, fd, total_len=0;
	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	socklen_t clnt_adr_sz;
	Packet packet;
	memset(&packet, 0, sizeof(Packet));
	char title[BUF_SIZE];
	
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(serv_sock==-1)
		error_handling("socket() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	printf("------------------------------------\n");
	printf("     File Transmission Server\n");
	printf("------------------------------------\n");
	printf("waiting for client...\n");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_adr_sz=sizeof(clnt_adr);

	
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	if(clnt_sock==-1)
		error_handling("accept() error");
	else
		printf("Connected client\n");
		
		
        read(clnt_sock, &packet, sizeof(Packet));
        strcpy(title, packet.buf);
        fd = open(packet.buf, O_RDONLY);
        if(fd == -1){
          packet.seq = 0;
          packet.ack = 0;
          printf("%s File Not Found\n", title);
          packet.buf_len = strlen("File Not Found\n");
          strcpy(packet.buf, "File Not Found\n");
          write(clnt_sock, &packet, sizeof(packet));
          
        }
        else{
          packet.seq = SEQ_START;
          packet.ack = 0;
          printf("[Server] sending %s\n\n", title);
          while((str_len=read(fd, packet.buf, BUF_SIZE))){
            packet.buf_len = str_len;
            total_len += str_len;
	    write(clnt_sock, &packet, sizeof(Packet));
	    printf("[Server] Tx: SEQ: %d, %d byte data\n", packet.seq, str_len);
	    if(str_len < BUF_SIZE) break;
	    read(clnt_sock, &packet, sizeof(Packet));
	    printf("[Server] Rx ACK: %d\n\n", packet.ack);
	    packet.seq = packet.ack;
	  }
	printf("%s sent (%d Bytes)\n", title, total_len);
	close(fd);
        }
	close(clnt_sock);
	printf("Exit Server\n");
	close(serv_sock);
	return 0;
}
int actualLength(char* message){
  int i;
  for(i = 0; message[i]; i++);
  return i;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

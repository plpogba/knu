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

int actualLength(char* message);
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char message[BUF_SIZE], title[BUF_SIZE];
	int total_len=0;
	struct sockaddr_in serv_adr;
	int fd, size=0;
        Packet packet;
        memset(&packet, 0, sizeof(Packet));
	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(sock==-1)
		error_handling("socket() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));
	
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect() error!");
	else
		puts("Connected...........");
	

	fputs("Input file name:(Q to quit) ", stdout);
	fgets(message, BUF_SIZE, stdin);
	int k = actualLength(message);
	strncpy(packet.buf, message, k-1);
	strncpy(title, message, k-1);
	packet.buf_len = k-1;
	printf("[Client] request %s\n", title);
        write(sock, &packet, sizeof(Packet));
        read(sock, &packet, sizeof(Packet));
        
        if(strcmp(packet.buf, "File Not Found\n")==0){
	    printf("File Not Found\n");
	}
	else{
	  fd = open(title, O_CREAT|O_WRONLY|O_TRUNC,0644);
          while(1){
            printf("[Client] Rx SEQ: %d, len: %d bytes\n", packet.seq, packet.buf_len);
            size = write(fd, packet.buf, packet.buf_len);
            total_len += size;
            int tmp = packet.seq + packet.buf_len + 1;
            if(packet.buf_len < BUF_SIZE) break;
            packet.ack = tmp;
            write(sock, &packet, sizeof(Packet));
            printf("[Client] Tx ACK: %d\n\n", packet.ack);
            read(sock, &packet, sizeof(Packet));
            
          }
          printf("%s received (%d Bytes)\n", title, total_len);
          close(fd);
	}
	printf("Exit Client\n");
	close(sock);
	
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

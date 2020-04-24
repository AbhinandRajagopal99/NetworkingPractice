#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>


int main(){
	int s_socket, s_server;
	char buf[100];
	s_socket= socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server, other;

	memset(&server,0,sizeof(server));
	memset(&other, 0,sizeof(other));

	server.sin_family = AF_INET;
	server.sin_port = htons(9009);
	server.sin_addr.s_addr= INADDR_ANY;

	if(bind(s_socket, (struct sockaddr*)&server, sizeof(server)) == -1){
		printf("Bind error");
		return 0;	//exit(1);
	}
	listen(s_socket, 5);

	socklen_t add;
	add=sizeof(other);
	s_server=accept(s_socket, (struct sockaddr*)&other, &add);

	int size;

	char charbuf[1];
	FILE *fp;
	fp=fopen("server.png","w"); // open a text file in read mode and store the file handle into fp
	//fopen("tab.txt","wb");
	char endoffile = '0';
	int check = 0;
	while(check==0)
	{
		recv(s_server, &endoffile, sizeof(&endoffile), 0);
		if(endoffile=='1')
		{
			check=1;
			break;
		}
		else
		{
			recv(s_server, charbuf, sizeof(charbuf), 0);
			fputc(charbuf[0],fp);
		}
	}
	printf("File received successfully\n");
	printf("Data Copied to server.png file\n");
	fclose(fp);

	close(s_server);
	close(s_socket);

	return 0;

}	
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

	read(s_server, buf, sizeof(buf));	//send(s_server, buf, sizeof(buf),0);

	FILE *fp;
	fp=fopen("add.txt","w");
	fprintf(fp, "%s", buf);

	printf("File Recieved Successfully");
	printf("Data copied in add.txt file");

	fclose(fp);

	close(s_server);
	close(s_socket);

	return 0;

}	
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>


int main(){
	int c_socket;
	//char msg[100];
	//printf("Enter Message: ");
	//scanf("%s",msg);
	char buf[100]="Hello Venkat";
	c_socket=socket(AF_INET, SOCK_STREAM, 0);	// AF_INET:

	struct sockaddr_in client;
	memset(&client,0,sizeof(client));

	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = inet_addr("172.16.17.90");



	if(connect(c_socket, (struct sockaddr*)&client, sizeof(client))==-1){
		printf("Connection Issue");
		return 0;
	}


	while(1){
		recv(c_socket,buf,sizeof(buf),0);
		printf("Message from Serverw: %s",buf);
		printf("Message: ");
		scanf("%s", buf);
		send(c_socket,buf,sizeof(buf),0);
		
		}

	// send(c_socket, buf, sizeof(buf), 0);
	// recv(c_socket, buf, sizeof(buf), 0);
	//printf("msg from server: %s \n", msg);
	close(c_socket);
	return 0;

}

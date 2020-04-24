#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>


int main(){
	int s_socket, s_server;
	//char msg[100];
	char buf[100] ="Hello Client";
	s_socket= socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server, other;
	memset(&server,0,sizeof(server));
	memset(&other, 0,sizeof(other));

	server.sin_family = AF_INET;
	server.sin_port = htons(9009);
	server.sin_addr.s_addr= INADDR_ANY;

	bind(s_socket, (struct sockaddr*)&server, sizeof(server));
	listen(s_socket, 5);

	socklen_t add;
	add=sizeof(other);
	s_server=accept(s_socket, (struct sockaddr*)&other, &add);

	int o=1;
	int ans;
	int x, y;

	while(1){

		ins:
		 

		printf("Message for Client: ");

		strcpy(buf, "\nEnter Appropriate Inputs : Enter x: ");
		send(s_server, buf, sizeof(buf),0);	//s1

		recv(s_server, buf, sizeof(buf),0);	//r1
		if(strcmp(buf, "quit")==0)
			break;
		else
			sscanf(buf, "%d", &x);

		strcpy(buf, "Enter y: ");
		send(s_server, buf, sizeof(buf),0);	//s2

		recv(s_server, buf, sizeof(buf),0); //r2
		if(strcmp(buf, "quit")==0)
			break;
		else
			sscanf(buf, "%d", &y);

		strcpy(buf, "Enter Operation: \n 1.Addition,\n 2.Subtraction,\n 3.Multiplication,\n 4.Integer Quotient: ");
		send(s_server, buf, sizeof(buf),0);	//s3

		recv(s_server, buf, sizeof(buf),0);	//r3
		if(strcmp(buf, "quit")==0)
			break;
		if(strcmp(buf,"1")==0)
			ans=x+y;
		else if(strcmp(buf,"2")==0)
			ans=x-y;
		else if(strcmp(buf,"3")==0)
			ans=x*y;
		else if(strcmp(buf,"4")==0)
			ans=x/y;
		else
			goto ins;
		

		sprintf(buf,"%d", ans);
		printf("Result: %s\n", buf);
		send(s_server, buf, sizeof(buf),0);	//s4


		strcpy(buf, "Do you want to perform again: 0/1: ");
		send(s_server, buf, sizeof(buf),0);	//s5

		recv(s_server, buf, sizeof(buf),0);	//r4
		if(strcmp(buf, "quit")==0)
			break;
		if(strcmp(buf, "0")==0)
			break;
		//printf("Message from Client: %s\n",buf);
	}

	// send(s_server, buf, sizeof(buf),0);
	// recv(s_server, buf, sizeof(buf),0);

	// printf("Message from client: %s \n", buf);
	close(s_server);
	close(s_socket);

	return 0;



}	
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
	char buf[100]="Hello Server";
	c_socket=socket(AF_INET, SOCK_STREAM, 0);	// AF_INET:

	struct sockaddr_in client;
	memset(&client,0,sizeof(client));

	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = INADDR_ANY;



	if(connect(c_socket, (struct sockaddr*)&client, sizeof(client))==-1){
		printf("Connection Issue");
		return 0;
	}


	while(1){

		ins:

		recv(c_socket,buf,sizeof(buf),0);	//r1
		printf("Message from Server: %s\n",buf);

		printf("Message for Server: ");
		scanf("%s", buf);
		send(c_socket,buf,sizeof(buf),0);	//s1

		if(strcmp(buf, "quit")==0){
			break;
		}

		recv(c_socket,buf,sizeof(buf),0);	//r2
		printf("Message from Server: %s\n",buf);

		printf("Message for Server: ");
		scanf("%s", buf);
		send(c_socket,buf,sizeof(buf),0);	//s2

		if(strcmp(buf, "quit")==0){
			break;
		}
		
		recv(c_socket,buf,sizeof(buf),0);	//r3
		printf("Message from Server: %s\n",buf);

		printf("Message for Server: ");
		scanf("%s", buf);
		send(c_socket,buf,sizeof(buf),0);	//s3

		if(strcmp(buf, "quit")==0){
			break;
		}
		if(strcmp(buf, "1")!=0 && strcmp(buf, "2")!=0 && strcmp(buf, "3")!=0 && strcmp(buf, "4")!=0)
			goto ins;
		
		recv(c_socket,buf,sizeof(buf),0);	//r4
		printf("Message from Server: %s\n",buf);

		recv(c_socket,buf,sizeof(buf),0);	//r5
		printf("Message from Server: %s\n",buf);


		printf("Message for Server: ");
		scanf("%s", buf);
		send(c_socket,buf,sizeof(buf),0);	//s4

		if(strcmp(buf, "quit")==0){
			break;
		}
		if(strcmp(buf, "0")==0){
			break;
		}

		
		
		
	}

	// send(c_socket, buf, sizeof(buf), 0);
	// recv(c_socket, buf, sizeof(buf), 0);
	//printf("msg from server: %s \n", msg);
	close(c_socket);
	return 0;

}

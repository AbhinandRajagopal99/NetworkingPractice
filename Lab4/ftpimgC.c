#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>


int main(){
	int c_socket;
	char buf[100];
	c_socket=socket(AF_INET, SOCK_STREAM, 0);	// AF_INET:

	struct sockaddr_in client;

	memset(&client,0,sizeof(client));

	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = INADDR_ANY;

	if(connect(c_socket, (struct sockaddr*)&client, sizeof(client))==-1){
		printf("Connection Issue");
		return 0;	//exit(1);
	}

	//---------

	FILE *fp;
	fp = fopen("client.png", "r");
	//fscanf(fp, "%s", buf);

	char endoffile = '0';
	char charbuf[1];
	while(!feof(fp))
	{
		charbuf[0]=fgetc(fp);
		send(c_socket, &endoffile, sizeof(&endoffile), 0);
		send(c_socket, charbuf, sizeof(charbuf), 0);
	}

	printf("Image File Ended \n");
	endoffile = '1';
	send(c_socket, &endoffile, sizeof(&endoffile), 0);
	printf("Image send Successful\n");
	fclose(fp);

	close(c_socket);
	return 0;
}
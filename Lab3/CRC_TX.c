#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>


char crc[100];

void CRC_Generate(char *databit, char *divisor){

	
	int divlen= strlen(divisor);
	char dividend[100];

	char interm[divlen];

	strcpy(dividend, databit);
	for(int i=0; i<divlen-1; i++)
		strcat(dividend,"0");

	for(int i=0; i<divlen; i++)
		interm[i]=dividend[i];
	

	int j;
	for(int i=0; i<strlen(dividend)-divlen+2; i++){
		if(interm[0]=='0'){
			for(j=1; j<divlen; j++){
				if(interm[j]=='1')
					interm[j-1]='1';
				else
					interm[j-1]='0';
			}
		}
		else{
			for(j=1; j<divlen; j++){
				if(interm[j]==divisor[j])
					interm[j-1]='0';
				else
					interm[j-1]='1';
			}
		}
		interm[j-1] = dividend[j+i-1];
		interm[divlen]='\0';
		printf("%d %s\n", i, interm );
		
	}

	for(int i=0; i<j-1; i++)
		crc[i] = interm[i];

	printf("%s\n", crc);

}

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
	char databit[100];
	char divisor[100];
	char datacrc[100];

	while(1){
		data:

		recv(c_socket,buf,sizeof(buf),0);	//r1
		printf("Message from Server: %s\n",buf);

		printf("Message for Server: ");
		scanf("%s", buf);
		send(c_socket,buf,sizeof(buf),0);	//s1

		// for(int i=0; i<strlen(buf); i++)
		// 	if(buf[i]!=1 && buf[i]!=0)
		// 		goto data;

		strcpy(databit, buf);

		divs:

		recv(c_socket,buf,sizeof(buf),0);	//r2
		printf("Message from Server: %s\n",buf);

		printf("Message for Server: ");
		scanf("%s", buf);
		send(c_socket,buf,sizeof(buf),0);	//s2

		// for(int i=0; i<strlen(buf); i++)
		// 	if(buf[i]!=1 && buf[i]!=0)
		// 		goto divs;

		strcpy(divisor, buf);

		CRC_Generate(databit,divisor);

		
		strcpy(buf, crc);

		send(c_socket,buf,sizeof(buf),0);	//s3

		break;

	}
	
	close(c_socket);
	return 0;
}
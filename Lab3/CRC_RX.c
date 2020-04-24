#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>



int CRC_Check(char *databit, char *divisor, char *crc){


	int divlen= strlen(divisor);
	char dividend[100];

	char interm[divlen];

	strcpy(dividend, databit);
	strcat(dividend, crc);

	for(int i=0; i<divlen; i++)
		interm[i]=dividend[i];
	interm[divlen]='\0';

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
		printf("%d %s\n", i, interm );
		
	}

	int flag =0;
	for(int i=0; i<j-1; i++){
		if(interm[i]!=0)
			flag=1;
	}

	printf("%s\n", interm);
	if(flag==1)
		return 1;
	return 0;

}

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
		printf("bind error");
		return 0;	//exit(1);
	}
	listen(s_socket, 5);

	socklen_t add;
	add=sizeof(other);
	s_server=accept(s_socket, (struct sockaddr*)&other, &add);

	char databit[100];
	char divisor[100];
	char crc[100];

	while(1){

		data:
		 
		printf("Message for Client: ");

		strcpy(buf, "\nEnter Appropriate Inputs :\n Enter Data bits you want to send: ");
		send(s_server, buf, sizeof(buf),0);	//s1

		recv(s_server, databit, sizeof(databit),0);	//r1

		// for(int i=0; i<strlen(buf); i++)
		// 	if(buf[i]!=1 && buf[i]!=0)
		// 		goto data;

		//strcpy(databit, buf);
		printf("Data Bits: %s", databit);

		divs:

		strcpy(buf, "Enter Appropriate Divisor: ");

		send(s_server, buf, sizeof(buf),0);	//s2

		recv(s_server, divisor, sizeof(divisor),0);	//r2
		//strcpy(divisor, buf);

		// for(int i=0; i<strlen(buf); i++)
		// 	if(buf[i]!=1 && buf[i]!=0)
		// 		goto divs;

		printf("\nDivisor: %s", divisor);

		recv(s_server, crc, sizeof(crc),0);	//r3

		//x	strcpy(crc, buf);
		int ch=CRC_Check(databit,divisor, crc);

		if(ch==0)
			printf("Error");
		else
			printf("No Error");


		break;



		
	}

	close(s_server);
	close(s_socket);

	return 0;

}	
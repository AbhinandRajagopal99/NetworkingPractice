#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

#include<math.h>

char data[20];
int m;
int r;

int packet[20];
char pack[20];

void Read();
void Redundant();

void Read(){
	printf("Enter Message you wanted to send: ");
	scanf("%s",data);

	m= strlen(data);

	for(int i=1; i<=20; i++){
		if(pow(2, i)>= (m+i+1)){
			r=i;
			break;
		}
	}
	printf("M: %d R: %d\n", m, r);

	for(int i=0; i<m+r; i++){
		packet[i]=0;
		pack[i]='0';
	}
	for(int i=0; i<r; i++){
		packet[(int)pow(2,i)-1] = -4;
		pack[(int)pow(2,i)-1] = 'r';
	}
	int q=m-1;
	for(int i=0; i<m+r; i++){
		if(packet[i]!=-4){
			packet[i]=data[q]-48;
			pack[i] = data[q];
			q--;
		}
	}
	for(int i=m+r-1; i>=0; i--)
		printf("%c", pack[i]);

	for(int i=0; i<m+r; i++){
		if(packet[i]==-4)
			packet[i]=0;
	}

	printf("\n");
}

void Redundant(){
	int q=1;
	int c=0;

	while(q<m+r){
		//printf("q: %d:: ",q);
		for(int i=q-1; i<m+r; i+=q*2){
			for(int j=i; j<i+q; j++){
				if(j<m+r){
					packet[q-1]^=packet[j];
					//printf("%d ",j);
				}
			}
		}
		//printf("\n");
		if(packet[q-1]==0)
			pack[q-1]='0';
		else if(packet[q-1]==1)
			pack[q-1]='1';

		c++;
		q=pow(2,c);
	}
	
	for(int i=m+r-1; i>=0; i--)
		printf("%c", pack[i]);
	printf(" is Send to Channel\n");
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

	if(connect(c_socket, (struct sockaddr *)&client, sizeof(client))==-1){
		printf("Connection Issue");
		return 0;	//exit(1);
	}


	char msize[5];
	char rsize[5];

	Read();
	sprintf(msize,"%d", m);
	send(c_socket,msize,sizeof(msize),0);	//s1
	sprintf(rsize,"%d", r);
	send(c_socket,rsize,sizeof(rsize),0);	//s2

	Redundant();
	send(c_socket,pack,sizeof(pack),0);		//s3

	close(c_socket);
	return 0;
}
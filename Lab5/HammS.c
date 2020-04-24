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
char inipack[20];
char pack[20];
int check[20];

void Read();
int HammDist(char inipack[], char pack[]);
void Check();

void Read(){
	printf("Packet Recieved: ");
	for(int i=m+r-1; i>=0; i--)
		printf("%c",pack[i]);

	printf("\nM: %d R: %d\n", m, r);

	for(int i=0; i<m+r; i++){
		if(pack[i]=='0')
			packet[i]=0;

		else if(pack[i]=='1')
			packet[i]=1;
	}

	
	for(int i=m+r-1; i>=0; i--)
		printf("%d", packet[i]);

	printf("\n");
}

int HammDist(char inipack[], char pack[]){
	int dist=0;
	for(int i=0; i<m+r; i++){
		if(inipack[i]!=pack[i])
			dist++;
	}

	return dist;

}
void Check(){
	int q=1;
	int c=0;
	int checksum=0;

	while(q<m+r){
		//printf("q: %d:: ",q);
		for(int i=q-1; i<m+r; i+=q*2){
			for(int j=i; j<i+q; j++){
				if(j<m+r){
					check[c]^=packet[j];
					//printf("%d ",j);
				}
			}
		}
		//printf("\n");
		checksum+=check[c];

		c++;
		q=pow(2,c);
	}
	
	for(int i=0; i<c; i++)
		printf("%d: %d \n",i+1, check[i]);

	if(HammDist(inipack, pack)==1){
	
		if(checksum>0){
			printf("Error Detected at Position\n");

			int bin=0;
			for(int i=c-1; i>=0; i--){
				bin*=2;
				bin += check[i];
			}

			printf("%d\n", bin);

			printf("Correction: ");
			if(pack[bin-1] =='0')
				pack[bin-1]='1';
			else
				pack[bin-1]='0';

			for(int i=m+r-1; i>=0; i--)
				printf("%c", pack[i]);
			printf("\n");
		}
	}

	else if(HammDist(inipack, pack)==2 && checksum>0)
		printf("Error Detected\n");

	else
		printf("No Error\n");

	int p=0;
	int k=0;
	for(int i=0; i<m+r; i++){
		if((i+1)== (int)pow(2,p))
			p++;
		else{
			data[k]=pack[i];
			//printf("%c, %d, %d\n",pack[i], i, k);
			k++;
		}
	}
	printf("Message: ");
	for(int i=m-1; i>=0; i--)
		printf("%c", data[i]);
	printf("\n");
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

	if(bind(s_socket, (struct sockaddr *)&server, sizeof(server)) == -1){
		printf("Bind error");
		return 0;	//exit(1);
	}
	listen(s_socket, 5);

	socklen_t add;
	add=sizeof(other);
	s_server=accept(s_socket, (struct sockaddr *)&other, &add);

	
	char msize[5];
	char rsize[5];

	recv(s_server, msize, sizeof(msize),0);		//r1
	sscanf(msize, "%d", &m);
	recv(s_server, rsize, sizeof(rsize),0);		//r2
	sscanf(rsize, "%d", &r);

	recv(s_server, pack, sizeof(pack),0);		//r3
	
	strcpy(inipack, pack);
	pack[7]='1';

	Read();

	Check();


	close(s_server);
	close(s_socket);

	return 0;

}	
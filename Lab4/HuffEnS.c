#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>



struct node
{
	char c;
	int Frequency;
	struct node *lcptr;
	struct node *rcptr;	
};

int size=0;

struct node Leaf[100];
struct node *temp;

struct lookup{
	char c[1];
	char Frequency[20];
}lup[128];

struct stack
{
	int a[100];
	int top; 
}s;


int assignment[128][10];


void sort(int start, int end){
	for(int i=start+1; i<end; i++)
	{
		for(int j=i; j>start; j--)
		{	
			if(Leaf[j].Frequency<Leaf[j-1].Frequency)
			{
				
				int tmpf=Leaf[j].Frequency;
				Leaf[j].Frequency=Leaf[j-1].Frequency;
				Leaf[j-1].Frequency=tmpf;

				char tmpc=Leaf[j].c;
				Leaf[j].c=Leaf[j-1].c;
				Leaf[j-1].c=tmpc;

				struct node *tmp= malloc (sizeof(struct node));
				tmp->lcptr = Leaf[i].lcptr;
				Leaf[j].lcptr = Leaf[j-1].lcptr;
				Leaf[j-1].lcptr = tmp->lcptr;

				tmp->rcptr = Leaf[i].rcptr;
				Leaf[j].rcptr = Leaf[j-1].rcptr;
				Leaf[j-1].rcptr = tmp->rcptr;
			}
			else
				break;
		}
	}
}

char Text[100]; 


//void Read();
void BuildTree();
//void CodeAssignment();
void Decode();
void FixedDecode();


int character;


int l=0;

void print(struct node *ptr)
{
	if(ptr!=NULL)
	{
		if(ptr->lcptr!=NULL)
		{
			s.top++;
			s.a[s.top]=0;
			print(ptr->lcptr);
			s.top--;
		}
		
		

		
		if(ptr->c !='\0')
		{
			int k=0;
			lup[l].c[0] = ptr->c;
			character=(int)ptr->c;
			for(int i=0;i<=s.top;i++)
				assignment[character][i]=s.a[i];
			assignment[character][s.top+1]=-666;
			
				
			printf("code for %c is : ",ptr->c);
			
			for(int i=0;1;i++)
			{
				if(assignment[character][i]==-666)
					break;
				else{
					printf("%d", assignment[character][i]);
										
				}
				k++;
			}
			printf("\n");
			l++;

			
		}
				
			
		if(ptr->rcptr!=NULL)
		{
			s.top++;
			s.a[s.top]=1;
			print(ptr->rcptr);
			s.top--;
		}
		

	}
}


void BuildTree()
{
	sort(0,size);
	
	for(int i=0;i<size;i++)
		printf("%c -- %d \n",Leaf[i].c, Leaf[i].Frequency);
		
	int count=size;
	
	int start=0;
	int end=count;	
	
	while(end-start >1)
	{			
			
		Leaf[count].Frequency=Leaf[start].Frequency+Leaf[start+1].Frequency;
		Leaf[count].lcptr=&Leaf[start];
		Leaf[count].rcptr=&Leaf[start+1];
		
		count++;
		start+=2;
		end+=1;
		
		sort(start,end);
			
		printf("\n");
			
	}
	
	
	temp=&Leaf[end-1];
	//struct node *temp=&Leaf[end-1];
	print(temp);

	// for(int i=0; i<l; i++){
	// 	printf("%c %s\n", lup[i].c[0], lup[i].encoded);
	// }
	
	
}

char encodedstring[100];

char decodedstring[100];
void Decode()
{
	// char code[50]; 
	// printf("\nEnter the code to decode : ");
	// scanf("%s",code);
	
	struct node *root=temp;
	
	printf("The decoded text is      : ");
	
	int label;
	int k=0;
	for(int i=0;i<strlen(encodedstring);i++)
	{
		label=(int)encodedstring[i] - 48;
		if(label==1)
			root=root->rcptr;
		else if(label==0)
			root=root->lcptr;
			
		if(root->lcptr==NULL && root->rcptr==NULL)
		{
			printf("%c",root->c);
			decodedstring[k]=root->c;
			k++;
			root=temp;
		}
	}
	decodedstring[k]='\0';
	printf("\n");
	
}


void FixedDecode(){
	sort(0,size);

	printf("%d\n", size);
	for(int i=0;i<size;i++){
		char p[20];
		printf("%c -- %d \n",Leaf[i].c, Leaf[i].Frequency);
		lup[i].c[0] = Leaf[i].c;
		sprintf(p,"%d", Leaf[i].Frequency);
		strcpy(lup[i].Frequency, p);
	}

	char bytes[size][10];
	char revbytes[size][10];

	for(int i=0; i<size; i++){
		for(int j=0; j<=ceil(log2(size))-1; j++){
				bytes[i][j]='0';
		}
	}
	int k;
	for(int i=0; i<size; i++){
		for(int j=ceil(log2(size))-1; j>=0; j--){
			k=i>>j;

			if(k&1)
				bytes[i][j]='1';
			else
				bytes[i][j]='0';
		}
	}

	for(int i=0; i<size; i++){
		for(int j=ceil(log2(size))-1; j>=0; j--){
				printf("%c",bytes[i][j]);
		}
		printf("\t");
	}
	printf("\n");

	for(int i=0; i<size; i++){
		for(int j=0; j<=ceil(log2(size))-1; j++){
			revbytes[i][j] = bytes[i][(int)(ceil(log2(size)))-1-j];
			printf("%c",revbytes[i][j]);
		}
		printf("\t");
	}
	printf("\n");

	int encsize = strlen(encodedstring);
	int bitsize = ceil(log2(size));
	printf("%d\n\n", bitsize);

	int q=0;
	k=0;
	char dechar[10][10];
	for(int i=0; i<encsize; i++){
		if(i%bitsize == 0){
			printf("\n");
			dechar[q][k]='\0';
			k=0;
			q++;
		}
		dechar[q][k] = encodedstring[i];
		k++;
		printf("%c",encodedstring[i]);
	}
	dechar[q][k]='\0';

	for(int i=0; i<=q; i++){
		printf("\n---\n%s\n", dechar[i]);
	}
	int s=0;
	
	for(int r=0; r<=q; r++){
		for(int i=0; i<size; i++){
			if(strcmp(dechar[r], revbytes[i])==0){
				decodedstring[s] = Leaf[i].c;
				s++;
			}
		}
		
	}
	decodedstring[s]='\0';
	printf("%s\n\n", decodedstring);
}

int main()
{
	s.top=-1;
	for(int i=0;i<128;i++)
	for(int j=0;j<10;j++)
		assignment[i][j]=-666;

	int l;

	char op[1];

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
	//bind(s_socket, (struct sockaddr*)&server, sizeof(server));
	listen(s_socket, 5);

	socklen_t add;
	add=sizeof(other);
	s_server=accept(s_socket, (struct sockaddr*)&other, &add);


	//---------

	recv(s_server, op, sizeof(op),0);			//r0
	printf("op: %s\n", op);

	recv(s_server, encodedstring, sizeof(encodedstring),0);	//recv(s_server, buf, sizeof(buf),0);	//r1

	recv(s_server, buf, sizeof(buf),0);		//r2

	//printf("this is bug%s\n", buf);
	sscanf(buf, "%d", &l);
	printf("%d ",l);

	char pc[1];
	for(int i=0; i<l; i++){			//r3 to r(l+2)
		recv(s_server, pc, sizeof(pc),0);
		//printf("PC-%s\n ", pc);
		recv(s_server, lup[i].Frequency, sizeof(lup[i].Frequency),0);
		lup[i].c[0] = pc[0];

		Leaf[i].c = lup[i].c[0];
		sscanf(lup[i].Frequency, "%d", &Leaf[i].Frequency);
		Leaf[i].lcptr=NULL;
		Leaf[i].rcptr=NULL;

		//printf("%c %d\n", Leaf[i].c, Leaf[i].Frequency);

	}
	size = l;
	if(op[0]=='1'){
		
		printf("encodedstring: %s\n", encodedstring);
		if(size==1){
			decodedstring[0]=Leaf[0].c;
		}
		else{
			BuildTree();
			Decode();
		}
	}

	else if(op[0]=='2'){
		printf("Fixed Huffman\n");
		FixedDecode();
	}

	FILE *fp;
	fp=fopen("encodeserver.txt","w");
	fprintf(fp, "%s", decodedstring);		//buf to be updated



	printf("\nText Recieved Successfully\n");
	printf("Data copied in encodeserver.txt file\n");

	fclose(fp);

	close(s_server);
	close(s_socket);

	return 0;
}


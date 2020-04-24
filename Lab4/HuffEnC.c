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
char inputstring[100];

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


void Read();
void BuildTree();
void CodeAssignment();
void Decode();
void FixedEncode();


void Read()
{
	// printf("Enter the string : ");
	// scanf("%s",Text);
	
	strcpy(Text, inputstring);

	int flag;
	
	for(int i=0;i<strlen(Text);i++)
	{
		flag=0;
		for(int j=0;j<size;j++)
		{
			if(Leaf[j].c==Text[i])
			{
				Leaf[j].Frequency++;
				flag=1;
				break;
			}
		}
		
		if(flag==0)
		{
			Leaf[size].c=Text[i];
			Leaf[size].Frequency=1;
			Leaf[size].lcptr=NULL;
			Leaf[size].rcptr=NULL;
			size++;
		}
	}
}

int character;


//int l=0;

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
			//int k=0;
			//lup[l].c[0] = ptr->c;
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
					// if(assignment[character][i] == 0)
					// 	lup[l].encoded[k]='0';
					// else
					// 	lup[l].encoded[k]='1';
					
				}
				//k++;
			}
			printf("\n");
			//l++;

			
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
	printf("%d-----\n",size);
	sort(0,size);
	
	for(int i=0;i<size;i++){
		char p[20];
		printf("%c -- %d \n",Leaf[i].c, Leaf[i].Frequency);
		lup[i].c[0] = Leaf[i].c;
		sprintf(p,"%d", Leaf[i].Frequency);
		strcpy(lup[i].Frequency, p);
	}
		
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

void CodeAssignment()
{
	printf("\nThe encoding value : ");

	int k=0;

	for(int i=0;i<strlen(Text);i++)
	{
		character=(int)Text[i];
		for(int j=0;1;j++)
		{
			if(assignment[character][j]==-666)
				break;
			else{
				printf("%d",assignment[character][j]);
				if(assignment[character][j] == 0)
					encodedstring[k]='0';
				else
					encodedstring[k]='1';
				k++;
			}
		}	
	}
	
	printf("\n");
	
}

void FixedEncode(){
	sort(0,size);

	for(int i=0;i<size;i++){
		char p[20];
		printf("%c -- %d \n",Leaf[i].c, Leaf[i].Frequency);
		lup[i].c[0] = Leaf[i].c;
		sprintf(p,"%d", Leaf[i].Frequency);
		strcpy(lup[i].Frequency, p);
	}

	char bytes[size][10];

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
	int r=0;
	for(int i=0; i<strlen(inputstring); i++){
		for(int j=0; j<size; j++){
			if(inputstring[i]==Leaf[j].c){
				for(int k=ceil(log2(size))-1; k>=0; k--){
					encodedstring[r]=bytes[j][k];
					r++;
				}
			}
		}
	}

	printf("%s\n", encodedstring);

}

/*
void Decode()
{
	char code[50]; 
	printf("\nEnter the code to decode : ");
	scanf("%s",code);
	
	struct node *root=temp;
	
	printf("The decoded text is      : ");
	
	int label;
	for(int i=0;i<strlen(code);i++)
	{
		label=(int)code[i] - 48;
		if(label==1)
			root=root->rcptr;
		else if(label==0)
			root=root->lcptr;
			
		if(root->lcptr==NULL && root->rcptr==NULL)
		{
			printf("%c",root->c);
			root=temp;
		}
	}
	
	printf("\n");
	
}
*/

int main()
{
	s.top=-1;
	for(int i=0;i<128;i++)
	for(int j=0;j<10;j++)
		assignment[i][j]=-666;


	int l;

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

	char op[1];


	FILE *fp;
	fp = fopen("encodeclient.txt", "r");
	fscanf(fp, "%s", buf);

	strcpy(inputstring, buf);

	printf("Enter Option: 1. variable , 2. Fixed: ");
	scanf("%s", op);
	Read(inputstring);
	printf("%s\n",op );
	send(c_socket, op, sizeof(op),0);			//s0
	if(strcmp(op,"1")==0){
	
		BuildTree();
		if(size==1){
			strcpy(encodedstring, "1");
		}
		else{
		
		CodeAssignment();
		//Decode();
		}
	}
	else if(strcmp(op,"2")==0){
		FixedEncode();

	}

	send(c_socket, encodedstring, sizeof(encodedstring),0);			//s1
	
	l=size;
	
	sprintf(buf,"%d", l);
	printf("%s\n", buf);
	send(c_socket, buf, sizeof(buf),0);		//s2

	for(int i=0; i<l; i++){			//s3 to s(l+2)
		send(c_socket, lup[i].c, sizeof(lup[i].c),0);
		send(c_socket, lup[i].Frequency, sizeof(lup[i].Frequency),0);
	}

	printf("Text send Successful\n");
	fclose(fp);

	close(c_socket);

	return 0;
}


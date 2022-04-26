#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 1024

char buffer[SIZE];
pthread_mutex_t mymutex;
int new_sock;

void send_file(FILE *fp, int sockfd)
{
    char data[SIZE] = {0};

    while(fgets(data, SIZE, fp)!=NULL)
    {
        if(send(sockfd, data, sizeof(data), 0)== -1)
        {
            perror("[-] Error in sending data");
            exit(1);
        }
        bzero(data, SIZE);
    }
    return;
}

void * thread_fn_no_param(void *arg)
{
	pthread_mutex_lock(&mymutex);
	
	char cmd[100];
   	strcpy(cmd,"./intersection_teams.sh actual_team.txt client_team.txt");
   	system(cmd);
   	
   	FILE *fp;
   	char *filename = "file.txt";
   	fp = fopen(filename, "r");
   	
   	if (fp == NULL) 
   	{
    		perror("[-]Error in reading file.");
    		exit(1);
  	}
  	send_file(fp, new_sock);
  	fclose(fp);
   	pthread_mutex_unlock(&mymutex);
}

void * thread_fn_no_param1(void *arg)
{
	pthread_mutex_lock(&mymutex);
	
	char cmd[100];
   	strcpy(cmd,"./intersection_teams.sh actual_team.txt client_team.txt");
   	system(cmd);
   	
   	FILE *fp;
   	char *filename = "file.txt";
   	fp = fopen(filename, "r");
   	
   	if (fp == NULL) 
   	{
    		perror("[-]Error in reading file.");
    		exit(1);
  	}
  	send_file(fp, new_sock);
  	fclose(fp);
   	pthread_mutex_unlock(&mymutex);
}

void write_file(int sockfd)
{
  printf("Hello\n");
  int n;
  FILE *fp;
  char *filename = "client_team.txt";
  
  char buffer[SIZE];
  //bzero(buffer,SIZE);
  fp = fopen(filename, "w+");
  
  bzero(buffer,1024);
  while (buffer[0]!='`') 
  {
    bzero(buffer,1024);
    n = recv(sockfd, buffer, SIZE, 0);
    if(buffer[0]=='`')
    	break;
    printf("%s\n",buffer);
    if(n<=0)
    	return;
    fprintf(fp, "%s", buffer);
    //  while (fscanf(fp, "%s ", buffer) == 1);
  }
  printf("Hello1\n");
  pthread_t threadID;
  int err = pthread_create (&threadID, NULL, thread_fn_no_param, NULL);
  
  printf("Hello2\n");
  
  if (err != 0)
	printf("cant create thread: %s\n", strerror(err));
  int ret;
  
  ret = pthread_mutex_init(&mymutex, NULL);
  printf("Hello3\n");
  pthread_join(threadID, NULL);
  
  printf("Ding Ding!\n");
  fclose(fp);
  
  ret = pthread_mutex_destroy(&mymutex);
  
  return;
}

void write_text(int sockfd)
{
  printf("Hello\n");
  int n;
  FILE *fp;
  char *filename = "testcase.txt";
  
  char buffer[SIZE];
  //bzero(buffer,SIZE);
  fp = fopen(filename, "w+");
  
  bzero(buffer,1024);
  while (buffer[0]!='`') 
  {
    bzero(buffer,1024);
    n = recv(sockfd, buffer, SIZE, 0);
    if(buffer[0]=='`')
    	break;
    printf("%s\n",buffer);
    if(n<=0)
    	return;
    fprintf(fp, "%s", buffer);
     while (fscanf(fp, "%s ", buffer) == 1);
  }
  printf("Hello1\n");
  pthread_t threadID;
  int err = pthread_create (&threadID, NULL, thread_fn_no_param1, NULL);
  
  printf("Hello2\n");
  
  if (err != 0)
	printf("cant create thread: %s\n", strerror(err));
  int ret;
  
  ret = pthread_mutex_init(&mymutex, NULL);
  printf("Hello3\n");
  pthread_join(threadID, NULL);
  
  printf("Ding Ding!\n");
  fclose(fp);
  
  ret = pthread_mutex_destroy(&mymutex);
  
  return;
}

int main(){
	
  int port = 8080;
  int e;
  char *ip = "127.0.0.1";
  int sockfd;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  
  printf("[+]Binding successfull.\n");

  if(listen(sockfd, 5) == 0)
  {
	printf("[+]Listening....\n");
  }
  else
  {	
	perror("[-]Error in listening");
        exit(1);
  }
  for(int i=1;i<=6;i++)
  {
  	
  	addr_size = sizeof(new_addr);
        new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
        
        FILE *design;
  	char *designname = "rules.txt";
  	design = fopen(designname, "r");
  	send_file(design,new_sock); // send design.txt to client
  	
  	bzero(buffer,1024);
    	strcpy(buffer,"`");
    	send(new_sock, buffer, strlen(buffer), 0);
  
  	fclose(design);
  	
  	bzero(buffer,1024);
    	// recv(new_sock, buffer, sizeof(buffer), 0); // receive the choice
    	// printf("%s\n",buffer);
    	
    	// if(buffer[0]=='3')
    	// {
    	// 	write_file(new_sock); // receive the file xyz.c
    	// } 
    	
    	// else if(buffer[0]=='1' || buffer[0]=='2')
    	// {
    	// 	write_text(new_sock); // receive the file xyz.txt
    	// } 

        write_file(new_sock);
  	
  	printf("[+]Data written in the file successfully.\n");
  	
  	if(listen(sockfd, 5) == 0)
  	{
		printf("[+]Listening....\n");
	}
	else
	{
		perror("[-]Error in listening");
    		exit(1);
	}
	
	bzero(buffer, 1024);
    	strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!\n");
    	printf("Server: %s\n", buffer);
    	send(new_sock, buffer, strlen(buffer), 0);
    	
    	bzero(buffer,1024);
    	strcpy(buffer,"`");
    	send(new_sock, buffer, strlen(buffer), 0);
    	
    	close(new_sock);
  }
  return 0;
}

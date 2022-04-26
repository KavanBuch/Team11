#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

void red()
{
    printf("\033[1;31m");
}
void green()
{
    printf("\033[0;32m");
}
void yellow()
{
    printf("\033[1;33m");
}
void blue()
{
    printf("\033[0;34m");
}
void purple()
{
    printf("\033[0;35m");
}
void reset()
{
    printf("\033[0m");
}

#define SIZE 1024

char buffer[SIZE];
pthread_mutex_t mymutex;
int new_sock;

void send_file(FILE *fp, int sockfd)
{
    char data[SIZE] = {0};

    while (fgets(data, SIZE, fp) != NULL)
    {
        if (send(sockfd, data, sizeof(data), 0) == -1)
        {
            perror("[-] Error in sending data");
            exit(1);
        }
        bzero(data, SIZE);
    }
    return;
}

void *thread_fn_no_param(void *arg)
{
    pthread_mutex_lock(&mymutex);
    char cmd[100];
    strcpy(cmd, "./intersection_teams.sh actual_team.txt client_team.txt");
    system(cmd);
    pthread_mutex_unlock(&mymutex);
}

void write_file(int sockfd)
{
    int n;
    FILE *fp;
    char *filename = "client_team.txt";

    char buffer[SIZE];
    fp = fopen(filename, "w+");

    bzero(buffer, SIZE);
    while (buffer[0] != '~')
    {
        bzero(buffer, SIZE);
        n = recv(sockfd, buffer, SIZE, 0);
        if (buffer[0] == '~')
            break;
        if (n <= 0)
            return;
        fprintf(fp, "%s", buffer);
    }
    pthread_t threadID;
    int err = pthread_create(&threadID, NULL, thread_fn_no_param, NULL);

    if (err != 0)
        printf("Cannot create thread: %s\n", strerror(err));
    int ret;

    ret = pthread_mutex_init(&mymutex, NULL);
    pthread_join(threadID, NULL);
    fclose(fp);
    ret = pthread_mutex_destroy(&mymutex);
    return;
}

int main()
{
    int port = 8080;
    int e;
    char *ip = "127.0.0.1";
    int sockfd;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    green();
    printf("\n[+]Server socket created successfully.\n");
    reset();

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e < 0)
    {
        red();
        perror("[-]Error in bind");
        reset();
        exit(1);
    }
    green();
    printf("[+]Binding successfull.\n");
    reset();

    if (listen(sockfd, 5) == 0)
    {
        yellow();
        printf("[+]Listening....\n");
        reset();
    }
    else
    {
        red();
        perror("[-]Error in listening");
        reset();
        exit(1);
    }

    for (int i = 1; i <= 6; i++)
    {
        addr_size = sizeof(new_addr);

        //accept the request from client.
        new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);

        FILE *design;
        char *designname = "rules.txt";
        design = fopen(designname, "r");
        send_file(design, new_sock); // send result.txt to client

        bzero(buffer, SIZE);
        strcpy(buffer, "~");
        send(new_sock, buffer, strlen(buffer), 0);

        fclose(design);

        bzero(buffer, SIZE);

        write_file(new_sock);

        // run linux commands 
        system("gcc main.c -o main.out");
        system("./main.out");

        FILE *result;
        char *score = "result.txt";
        result = fopen(score, "r");
        send_file(result, new_sock); // send result.txt to client

        bzero(buffer, SIZE);
        strcpy(buffer, "~");
        send(new_sock, buffer, strlen(buffer), 0);

        fclose(result);

        bzero(buffer, SIZE);
        green();
        printf("[+]Data written in the file successfully.\n");
        reset();

        if (listen(sockfd, 5) == 0)
        {
            yellow();
            printf("[+]Listening....\n\n");
            reset();
        }
        else
        {
            red();
            perror("[-]Error in listening");
            reset();
            exit(1);
        }

        bzero(buffer, SIZE);
        yellow();
        strcpy(buffer, "The score has been sent successfully to the client.\n");
        reset();
        printf("Server: %s\n", buffer);
        send(new_sock, buffer, strlen(buffer), 0);

        bzero(buffer, 1024);
        strcpy(buffer, "~");
        send(new_sock, buffer, strlen(buffer), 0);

        close(new_sock);
    }
    return 0;
}

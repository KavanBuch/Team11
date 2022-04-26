#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024

char buffer[SIZE];

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
}

void send_message(int sockfd)
{
    char temp[SIZE];
    printf("Enter Choice : \n");
    scanf("%s", temp);
    bzero(buffer, 1024);
    strcpy(buffer, temp);
    send(sockfd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    return;
}

void write_file(int sockfd)
{
    int n;
    char buffer[SIZE];
    bzero(buffer, 1024);
    while (buffer[0] != '`')
    {
        bzero(buffer, 1024);
        n = recv(sockfd, buffer, SIZE, 0);
        if (buffer[0] == '`')
            break;
        printf("%s",buffer);
        if (n <= 0)
        {
            return;
        }
    }
}

int main()
{
    char *ip = "127.0.0.1";
    int port = 8080; // 8080
    int e;

    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    printf("[+]Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e == -1)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    printf("[+]Connected to Server.\n");

    write_file(sockfd);   // rules file
    // send_message(sockfd); // choice
    sleep(2);

    system("bash run_input.sh");

    FILE *fp;
    char *filename = "client_team.txt";

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("[-]Error in reading file.");
        exit(1);
    }

    // bzero(buffer,1024);
    send_file(fp, sockfd);

    bzero(buffer, 1024);
    strcpy(buffer, "`");
    send(sockfd, buffer, strlen(buffer), 0);

    fclose(fp);

    write_file(sockfd);

    printf("[+]File data sent successfully.\n");

    printf("[+]Closing the connection.\n");

    close(sockfd);

    return 0;
}

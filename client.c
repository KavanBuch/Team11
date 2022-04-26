#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

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

void send_file(FILE *fp, int sockfd)
{
    char data[SIZE] = {0};

    while (fgets(data, SIZE, fp) != NULL)
    {
        if (send(sockfd, data, sizeof(data), 0) == -1)
        {
            red();
            perror("[-] Error in sending data");
            reset();
            exit(1);
        }
        bzero(data, SIZE);
    }
}

void write_file(int sockfd)
{
    int n;
    char buffer[SIZE];
    bzero(buffer, SIZE);
    while (buffer[0] != '~')
    {
        bzero(buffer, SIZE);
        n = recv(sockfd, buffer, SIZE, 0);
        if (buffer[0] == '~')
        {
            break;
        }
        printf("%s", buffer);
        if (n <= 0)
        {
            return;
        }
    }
}

int main()
{
    char *ip = "127.0.0.1"; // local host
    int port = 9999;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    // create a socket network
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        red();
        perror("[-]Error in socket");
        reset();
        exit(1);
    }
    yellow();
    printf("[+]Client socket created successfully.\n");
    reset();

    // specify an address for the socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // check if connected or not.
    e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e == -1)
    {
        red();
        perror("[-]Error in socket");
        reset();
        exit(1);
    }

    green();
    printf("[+]Connected to Server.\n");
    reset();

    // receive rules.txt file from the server
    write_file(sockfd);
    sleep(2);

    system("bash run_input.sh");

    FILE *fp;
    char *filename = "client_team.txt";

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        red();
        perror("[-]Error in reading file.");
        reset();
        exit(1);
    }

    // send the output genrated by c program to the server
    send_file(fp, sockfd);

    //clear the buffer of the string if any
    bzero(buffer, SIZE);
    strcpy(buffer, "~");
    send(sockfd, buffer, strlen(buffer), 0);

    fclose(fp);
    printf("\n");
    write_file(sockfd);

    green();
    printf("\n[+]File data sent successfully.\n");
    reset();
    printf("[+]Closing the connection.\n\n");

    //close the socket
    close(sockfd);

    return 0;
}

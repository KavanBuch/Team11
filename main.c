#include <stdio.h>
#include <string.h>

#define DATA_SIZE 100
#define TEAM_SIZE 12

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

int main()
{
    FILE *filePointer;
    char dataToBeRead[DATA_SIZE];
    char players[TEAM_SIZE][DATA_SIZE];
    filePointer = fopen("intersection_team.txt", "r");
    if (filePointer == NULL)
    {
        red();
        printf("Failed to open the file\n\n");
        reset();
    }
    else
    {
        int counter = 0;
        while (fgets(dataToBeRead, DATA_SIZE, filePointer) != NULL)
        {
            for (int i = 0; i < strlen(dataToBeRead); i++)
            {
                players[counter][i] = dataToBeRead[i];
            }
            players[counter][strlen(dataToBeRead)]='\0';
            counter++;
        }
        fclose(filePointer);
    }
    return 0;
}

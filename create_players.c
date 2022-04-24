#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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
    filePointer = fopen("actual_team.txt", "r");
    if (filePointer == NULL)
    {
        red();
        printf("Failed to open the file\n\n");
        reset();
    }
    else
    {
        green();
        system("mkdir ./players");
        printf("\n\nCreating statistics for each player...\n\n");
        reset();
        while (fgets(dataToBeRead, DATA_SIZE, filePointer) != NULL)
        {
            printf("%s", dataToBeRead);
            FILE *player;
            char dataToBeWritten[DATA_SIZE];
            for (int i = 0; i <= strlen(dataToBeRead); i++)
            {
                dataToBeWritten[i] = dataToBeRead[i];
            }
            char file_path[2 * DATA_SIZE] = "players/";
            strcat(file_path, dataToBeRead);
            player = fopen(file_path, "w");
            if (player == NULL)
            {
                printf("%s failed to open.\n", dataToBeRead);
            }
            else
            {
                if (strlen(dataToBeWritten) > 0)
                {
                    fputs(dataToBeWritten, player);
                    fputs("\n", player);
                }

                fclose(player);
            }
        }
        fclose(filePointer);
    }
    return 0;
}

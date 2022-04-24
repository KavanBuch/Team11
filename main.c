#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<stdlib.h>

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

struct player_stats
{
    char name[DATA_SIZE];

    //batsman specific stats
    int runs_scored;
    int bowls_played;
    int boundaries;
    int sixes;
    int is_30_plus;
    int half_century;
    int century;
    int golden_duck_dismissal;

    //bowler specific stats
    int wickets_taken;
    int maiden_over;
    int five_wickets;
};

int main()
{
    FILE *filePointer;
    char dataToBeRead[DATA_SIZE];
    filePointer = fopen("intersection_team.txt", "r");
    if (filePointer == NULL)
    {
        red();
        printf("Failed to open the file\n\n");
        reset();
    }
    else
    {
        green();
        printf("\n\nCalculating your score...\n\n");
        reset();
        int counter = 0;
        while (fgets(dataToBeRead, DATA_SIZE, filePointer) != NULL)
        {
            printf("%s", dataToBeRead);
        }
        fclose(filePointer);
    }
    return 0;
}

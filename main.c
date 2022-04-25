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

struct player_stats
{
    char name[DATA_SIZE];

    // batsman specific stats
    int runs_scored;
    int bowls_played;
    int boundaries;
    int sixes;
    int is_30_plus;
    int half_century;
    int century;
    int golden_duck_dismissal;

    // bowler specific stats
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
        while (fgets(dataToBeRead, DATA_SIZE, filePointer) != NULL)
        {
            int points = 0;
            FILE *player_data;
            char stats[10];
            char file_path[2 * DATA_SIZE] = "players/";
            strcat(file_path, dataToBeRead);
            printf("%s", file_path);
            player_data = fopen(file_path, "r");
            if (player_data == NULL)
            {
                red();
                printf("Failed to open the player's file.\n\n");
                reset();
            }
            else
            {
                while (fgets(stats, 10, player_data) != NULL)
                {
                    printf("%s", stats);
                }
                fclose(player_data);
            }
        }
        fclose(filePointer);
    }
    return 0;
}

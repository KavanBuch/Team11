#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define DATA_SIZE 100
#define TEAM_SIZE 22

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

int random_num(int lower_limit, int higher_limit)
{
    return ((rand() % (higher_limit - lower_limit + 1)) + lower_limit);
}

struct player
{
    char name[DATA_SIZE];
    int points;
};

typedef struct player player;

player players[TEAM_SIZE];

int main()
{
    FILE *filePointer;
    char dataToBeRead[DATA_SIZE];
    int cnt = 0;
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
        printf("\n\nCalculating the score...\n\n");
        sleep(3);
        reset();
        while (fgets(dataToBeRead, DATA_SIZE, filePointer) != NULL)
        {
            for (int i = 0; i < strlen(dataToBeRead); i++)
            {
                players[cnt].name[i] = dataToBeRead[i];
            }
            players[cnt].name[strlen(dataToBeRead)] = '\0';
            players[cnt].points = random_num(0, 50);
            cnt++;
        }
    }
    fclose(filePointer);

    int total_score = 0;

    FILE *fp;
    char data[DATA_SIZE];
    fp = fopen("intersection_team.txt", "r");
    if (fp == NULL)
    {
        red();
        printf("Failed to open the file\n\n");
        FILE *output_file;
        int total_score = 0;
        output_file = fopen("result.txt", "w");
        if (output_file == NULL)
        {
            red();
            printf("Failed to open the file\n\n");
            reset();
        }
        else
        {
            char final[1000];
            sprintf(final, "Your final score is %d.It seems there is some glitch in your team selection.Please read the rules carefully.", total_score);
            fputs(final, output_file);
            fputs("\n", output_file);
        }
        fclose(output_file);
        reset();
    }
    else
    {
        green();
        reset();
        while (fgets(data, DATA_SIZE, fp) != NULL)
        {
            for (int i = 0; i < TEAM_SIZE; i++)
            {
                int error = 0;
                if (strlen(players[i].name) != strlen(data))
                    continue;
                for (int j = 0; j < strlen(players[i].name); j++)
                {
                    if (players[i].name[j] != data[j])
                    {
                        error = 1;
                        break;
                    }
                }
                if (!error)
                {
                    total_score += players[i].points;
                }
            }
        }
        FILE *output_file;
        output_file = fopen("result.txt", "w");
        if (output_file == NULL)
        {
            red();
            printf("Failed to open the file\n\n");
            reset();
        }
        else
        {
            char final[100];
            sprintf(final, "Your final score is %d.Thank you for playing!!!", total_score);
            fputs(final, output_file);
            fputs("\n", output_file);
        }
        fclose(output_file);
    }
    fclose(fp);
    return 0;
}

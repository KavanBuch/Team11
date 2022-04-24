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

int random_num(int lower_limit, int higher_limit)
{
    return ((rand() % (higher_limit - lower_limit + 1)) + lower_limit);
}

int max(int a, int b)
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
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
        printf("\n\nCreating statistics for each player...\nCheck players folder inside the direcotry.\n\n");
        reset();
        int remaining_wickets = 10, player_cnt = 0;
        while (fgets(dataToBeRead, DATA_SIZE, filePointer) != NULL)
        {
            player_cnt++;
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
                // srand(time(0));
                int runs = random_num(0, 110);
                char str[10];
                sprintf(str, "%d", runs);
                fputs(str, player);
                fputs("\n", player);

                int bowls;
                if (runs >= 60)
                {
                    bowls = random_num(max(1, runs / 6 + (runs % 6 > 0)), runs - 10);
                }
                else
                {
                    bowls = random_num(max(1, runs / 6 + (runs % 6 > 0)), runs + 10);
                }
                sprintf(str, "%d", bowls);
                fputs(str, player);
                fputs("\n", player);

                int boundaries = random_num(0, runs / 4);
                int sixers = random_num(0, (runs - 4 * boundaries) / 6);

                sprintf(str, "%d", boundaries);
                fputs(str, player);
                fputs("\n", player);

                sprintf(str, "%d", sixers);
                fputs(str, player);
                fputs("\n", player);

                int is_30_plus = (runs >= 30);
                sprintf(str, "%d", is_30_plus);
                fputs(str, player);
                fputs("\n", player);

                int half_century = (runs >= 50);
                sprintf(str, "%d", half_century);
                fputs(str, player);
                fputs("\n", player);

                int century = (runs >= 100);
                sprintf(str, "%d", century);
                fputs(str, player);
                fputs("\n", player);

                int golden_duck = (runs == 0);
                sprintf(str, "%d", golden_duck);
                fputs(str, player);
                fputs("\n", player);

                int wickets;
                if (remaining_wickets < 0)
                    wickets = 0;
                else
                    wickets = random_num(0, remaining_wickets);
                sprintf(str, "%d", wickets);
                fputs(str, player);
                fputs("\n", player);
                remaining_wickets--;
                if (player_cnt == 11)
                    wickets = remaining_wickets;

                int maiden = random_num(0, 1);
                sprintf(str, "%d", maiden);
                fputs(str, player);
                fputs("\n", player);

                int fiver = (wickets >= 5);
                sprintf(str, "%d", fiver);
                fputs(str, player);
                fputs("\n", player);

                fclose(player);
            }
        }
        fclose(filePointer);
    }
    return 0;
}

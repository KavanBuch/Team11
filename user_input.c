#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define TEAM_SIZE 31
#define DATA_SIZE 100

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

char *players[TEAM_SIZE] = {"Michael Hussey ", "Murali Vijay ", "Suresh Raina", "S Badrinath", "MS Dhoni", "Albie Morkel", "Dwayne Bravo", "Wriddhiman Saha", "Ravichandran Ashwin", "Doug Bollinger", "Shadab Jakati", "Deepak Chahar", "Shardul Thakur", "Josh Hazalwood","Morne Morkel", "Davy Jacob", "Aiden Blizzard", "Tirumalasetti Suman", "Ambati Rayudu", "Andrew Symonds", "Kieron Pollard", "Rajagopal Sathish", "Harbhajan Singh", "Lasith Malinga", "Abu Nechim", "Yuzvendra Chahal", "Rohit Sharma", "Ishan Kishan", "Dwayne Smith","Andrew Tye"};

int main()
{
    yellow();
    int team[TEAM_SIZE];
    for (int i = 1; i < TEAM_SIZE; i++)
    {
        team[i] = 0;
    }

    for (int i = 0; i < 11; i++)
    {
        printf("Enter your team players's number(between 1 to 30):\t ");
        int player_no;
        scanf("%d", &player_no);
        team[player_no] = 1;
    }
    reset();

    int sum1 = 0, sum2 = 0;
    for (int i = 1; i < 16; i++)
    {
        sum1 += team[i];
    }
    for (int i = 16; i < 31; i++)
    {
        sum2 += team[i];
    }

    int error = 0;
    for (int i = 1; i < TEAM_SIZE; i++)
    {
        if (team[i] > 1)
        {
            error = 1;
        }
    }

    if (sum1 > 7 || sum2 > 7)
    {
        red();
        printf("You cannot select more than 7 players from one team\n\n");
        reset();
    }
    else if (error == 1)
    {
        red();
        printf("No player can be selected more than once\n\n");
        reset();
    }
    else
    {
        FILE *input_file;
        input_file = fopen("client_team.txt", "w");
        if (input_file == NULL)
        {
            printf("failed to open.\n");
        }
        else
        {
            for (int i = 1; i < TEAM_SIZE; i++)
            {
                if (team[i] == 1)
                {
                    fputs(players[i-1], input_file);
                    fputs("\n", input_file);
                }
            }
        }
        fclose(input_file);
    }
    return 0;
}

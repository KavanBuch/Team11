#include <stdio.h>

// Functions to change the colour of the text:
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
    yellow();
    printf("\n\n");
    printf("*********************Welcome to Team11*********************\n\n");
    printf("Following are the rules for making your team:\n\n");
    reset();
    printf("You will be given a list of 30 available players from both of the teams(15 from each).You are supposed to choose any 11 out of them with some bounds as follows:\n\n");
    printf("(1)Total team size should be 11 and maximum of 7 players can be chosen from one team.\n\n");
    printf("(2)Your team can different combination of players.\n\n");
    printf("(3)Your team must follow the following criteria:\n");
    printf("\t(i)  Minimum of 1 and maximum of 4 wicket-keeper should be selected.\n");
    printf("\t(ii) Minimum of 3 and maximum of 6 batsman should be selected.\n");
    printf("\t(iii)Minimum of 1 and maximum of 4 all-rounder should be selected.\n");
    printf("\t(iv) Minimum of 3 and maximum of 6 bowler should be selected.\n");
    printf("\n");
    return 0;
}
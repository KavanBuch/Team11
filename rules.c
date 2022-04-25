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

    green();

    printf("You will be given a list of 30 available players from both of the teams(15 from each).You are supposed to choose any 11 out of them with some bounds as follows:\n\n");
    printf("(1)Total team size should be 11 and maximum of 7 players can be chosen from one team.\n\n");
    printf("(2)Your team can different combination of players.\n\n");
    printf("\n");

    red();
    printf("You have following choices:\n\n");
    printf("From Team1:\n\n");
    purple();
    printf("Michael Hussey\n"
           "Murali Vijay\n"
           "Suresh Raina\n"
           "S Badrinath\n"
           "MS Dhoni\n"
           "Albie Morkel\n"
           "Dwayne Bravo\n"
           "Wriddhiman Saha\n"
           "Ravichandran Ashwin\n"
           "Doug Bollinger\n"
           "Shadab Jakati\n"
           "Deepak Chahar\n"
           "Shardul Thakur\n"
           "Josh Hazalwood\n");
    red();
    printf("\nFrom Team2:\n\n");
    purple();
    printf("Davy Jacob\n"
           "Aiden Blizzard\n"
           "Tirumalasetti Suman\n"
           "Ambati Rayudu\n"
           "Andrew Symonds\n"
           "Kieron Pollard\n"
           "Rajagopal Sathish\n"
           "Harbhajan Singh\n"
           "Lasith Malinga\n"
           "Abu Nechim\n"
           "Yuzvendra Chahal\n"
           "Rohit Sharma\n"
           "Ishan Kishan\n"
           "Dwayne Smith\n");
    reset();
    return 0;
}
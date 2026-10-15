#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#define cols 29
#define rows 10

void gamestate(char x[][cols]);
void botstart(char bca[][cols], char bsh[][cols], char bcr[][cols], char bsu[][cols], char bde[][cols]);
void humstart(char hca[][cols], char hsh[][cols], char hcr[][cols], char hsu[][cols], char hde[][cols]);
void botturn(char bg[][cols]);
void humturn(char hg[][cols]);
int botwin(char gg[][cols]);
int humwin(char ggg[][cols]);
void check(int spotter[], char gamest[][cols]);
int findRow(char ship[][cols]);
int canShoot(char bg[][cols], int r, int c);
int blackLeft(char bg[][cols]);

int main()
{
    srand(time(0));
    char answer[10] = {0};

    int spot[10] = {0};
    char botcarr[10][cols] = {0};
    char botship[10][cols] = {0};
    char botcruis[10][cols] = {0};
    char botsub[10][cols] = {0};
    char botdes[10][cols] = {0};

    char humcarr[10][cols] = {0};
    char humship[10][cols] = {0};
    char humcruis[10][cols] = {0};
    char humsub[10][cols] = {0};
    char humdes[10][cols] = {0};
    printf("WELCOME TO BATTLESHIPS BY DANIEL, YOUR PLANET EARTH IS CURRENTLY BEING ATTACKED BY ALIENS FROM KEPLER AND YOUR MISSION IS TO ELIMINATE THEIR BATTLESHIPS. "
           "ARE YOU UP FOR THE TASK? (yes or no answer only please professor)\n");
    fgets(answer, sizeof(answer), stdin);

    if (strlen(answer) > 0 && answer[strlen(answer) - 1] == '\n')
    {
        answer[strlen(answer) - 1] = '\0';
    }

    for (int i = 0; answer[i] != '\0'; i++)
    {
        answer[i] = tolower(answer[i]);
    }

    if (strcmp(answer, "yes") == 0)
    {
        printf("GREAT ANSWER! YOUR JOB IS TO ELIMINATE ALL THE ALIEN SHIPS BY TYPING THE NUMBER AND THEN THE LETTER OF THE CORRESPONDING GPS GRID OF WHICH YOU WANT TO ATTACK. "
               "YOUR BATTLESHIPS ARE THE 'O'S. GOOD LUCK, HERO!\n");
    }
    else
    {
        printf("MISSION ABORTED. GOODBYE!\n");
        return 1;
    }

    botstart(botcarr, botship, botcruis, botsub, botdes);
    humstart(humcarr, humship, humcruis, humsub, humdes);

    spot[0] = findRow(humcarr);
    spot[1] = findRow(humship);
    spot[2] = findRow(humcruis);
    spot[3] = findRow(humsub);
    spot[4] = findRow(humdes);
    spot[5] = findRow(botcarr);
    spot[6] = findRow(botship);
    spot[7] = findRow(botcruis);
    spot[8] = findRow(botsub);
    spot[9] = findRow(botdes);

    char game[rows][cols] = {0};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j == 14)
            {
                game[i][j] = i + '0';
            }
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (humcarr[i][j] == 'O')
            {
                game[i][j] = humcarr[i][j];
            }
            if (humship[i][j] == 'O')
            {
                game[i][j] = humship[i][j];
            }

            if (humcruis[i][j] == 'O')
            {
                game[i][j] = humcruis[i][j];
            }
            if (humsub[i][j] == 'O')
            {
                game[i][j] = humsub[i][j];
            }
            if (humdes[i][j] == 'O')
            {
                game[i][j] = humdes[i][j];
            }
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (botcarr[i][j] == 'X')
            {
                game[i][j] = botcarr[i][j];
            }
            if (botship[i][j] == 'X')
            {
                game[i][j] = botship[i][j];
            }

            if (botcruis[i][j] == 'X')
            {
                game[i][j] = botcruis[i][j];
            }
            if (botsub[i][j] == 'X')
            {
                game[i][j] = botsub[i][j];
            }
            if (botdes[i][j] == 'X')
            {
                game[i][j] = botdes[i][j];
            }
        }
    }

    while (botwin(game) != 1 && humwin(game) != 1)
    {
        gamestate(game);
        humturn(game);
        check(spot, game);
        if (humwin(game) == 1)
        {
            break;
        }
        botturn(game);
        check(spot, game);
    }
    if (botwin(game) == 1)
    {
        printf("ALIENS WIN");
    }
    else if (humwin(game) == 1)
    {
        printf("YOU HAVE SAVED EARTH FROM ALIENS!!!!");
    }
}

void gamestate(char x[][cols])
{
    printf("  C  O  M  P  U  T  E  R                          H  U  M  A  N     \n");
    printf("-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -\n");
    printf("A  B  C  D  E  F  G  H  I  J  K  L  M  N     A  B  C  D  E  F  G  H  I  J  K  L  M  N\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (x[i][j] == '\0' || x[i][j] == 'X') // if you want to cheat just remove the " || x[i][j]=='X' "
            {
                printf("-  ");
            }
            else
            {
                printf("%c  ", x[i][j]);
            }
        }
        printf("\n");
    }
}

void botstart(char bca[][cols], char bsh[][cols], char bcr[][cols], char bsu[][cols], char bde[][cols])
{
    srand(time(0));
    int randver = 0;
    int randhor = 0;
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;
    int temp4 = 0;

    randver = rand() % 10;
    randhor = (rand() % (9 - 1 + 1)) + 1;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 4; j++)
        {
            if (i == randver)
            {
                bca[i][j] = 'X';
            }
        }
    }
    temp1 = randver;
    randver = rand() % 10;
    while (randver == temp1)
    {
        randver = rand() % 10;
    }
    randhor = (rand() % (10 - 1 + 1)) + 1;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 3; j++)
        {
            if (i == randver)
            {
                bsh[i][j] = 'X';
            }
        }
    }
    temp2 = randver;
    randver = rand() % 10;
    while (randver == temp1 || randver == temp2)
    {
        randver = rand() % 10;
    }
    randhor = (rand() % (11 - 1 + 1)) + 1;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 2; j++)
        {
            if (i == randver)
            {
                bcr[i][j] = 'X';
            }
        }
    }
    temp3 = randver;
    randver = rand() % 10;
    while (randver == temp1 || randver == temp2 || randver == temp3)
    {
        randver = rand() % 10;
    }
    randhor = (rand() % (11 - 1 + 1)) + 1;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 2; j++)
        {
            if (i == randver)
            {
                bsu[i][j] = 'X';
            }
        }
    }
    temp4 = randver;
    randver = rand() % 10;
    while (randver == temp1 || randver == temp2 || randver == temp3 || randver == temp4)
    {
        randver = rand() % 10;
    }
    randhor = (rand() % (12 - 1 + 1)) + 1;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 1; j++)
        {
            if (i == randver)
            {
                bde[i][j] = 'X';
            }
        }
    }
}

void humstart(char hca[][cols], char hsh[][cols], char hcr[][cols], char hsu[][cols], char hde[][cols])
{

    int randver = 0;
    int randhor = 0;
    int temp1 = 0;
    int temp2 = 0;
    int temp3 = 0;
    int temp4 = 0;

    randver = rand() % 10;
    randhor = (rand() % (24 - 16 + 1)) + 16;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 4; j++)
        {
            if (i == randver)
            {
                hca[i][j] = 'O';
            }
        }
    }
    temp1 = randver;
    randver = rand() % 10;
    while (randver == temp1)
    {
        randver = rand() % 10;
    }
    randhor = (rand() % (25 - 16 + 1)) + 16;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 3; j++)
        {
            if (i == randver)
            {
                hsh[i][j] = 'O';
            }
        }
    }
    temp2 = randver;
    randver = rand() % 10;
    while (randver == temp1 || randver == temp2)
    {
        randver = rand() % 10;
    }
    randhor = (rand() % (26 - 16 + 1)) + 16;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 2; j++)
        {
            if (i == randver)
            {
                hcr[i][j] = 'O';
            }
        }
    }
    temp3 = randver;
    randver = rand() % 10;
    while (randver == temp1 || randver == temp2 || randver == temp3)
    {
        randver = rand() % 10;
    }
    randhor = (rand() % (26 - 16 + 1)) + 16;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 2; j++)
        {
            if (i == randver)
            {
                hsu[i][j] = 'O';
            }
        }
    }
    temp4 = randver;
    randver = rand() % 10;
    while (randver == temp1 || randver == temp2 || randver == temp3 || randver == temp4)
    {
        randver = rand() % 10;
    }
    randhor = (rand() % (26 - 16 + 1)) + 16;

    for (int i = 0; i < 10; i++)
    {
        for (int j = randhor; j <= randhor + 1; j++)
        {
            if (i == randver)
            {
                hde[i][j] = 'O';
            }
        }
    }
}
int canShoot(char bg[][cols], int r, int c)
{
    if (r < 0 || r > 9)
    {
        return 0;
    }
    if (c < 15 || c > 28)
    {
        return 0;
    }
    if (bg[r][c] == '?' || bg[r][c] == '/')
    {
        return 0;
    }
    return 1;
}
int blackLeft(char bg[][cols])
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 15; c < cols; c++)
        {
            if (canShoot(bg, r, c) && (r + c) % 2 == 0)
            {
                return 1; // found one
            }
        }
    }
    return 0; // none left
}
void botturn(char bg[][cols])
{
    int bvert, bhor;
    int found = 0;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 15; c < cols; c++)
        {
            if (bg[r][c] == '/' && found == 0)
            {
                if (canShoot(bg, r, c - 1))
                {
                    bvert = r;
                    bhor = c - 1;
                    found = 1;
                }
                else if (canShoot(bg, r, c + 1))
                {
                    bvert = r;
                    bhor = c + 1;
                    found = 1;
                }
            }
        }
    }

    if (found == 0)
    {
        do
        {
            bvert = rand() % 10;
            bhor = (rand() % (28 - 15 + 1)) + 15;
        } while (!canShoot(bg, bvert, bhor) || (blackLeft(bg) && (bvert + bhor) % 2 != 0));
    }
    if (bg[bvert][bhor] == 'O')
    {
        bg[bvert][bhor] = 'X';
    }
    else
    {
        bg[bvert][bhor] = '?';
    }
}
void humturn(char hg[][cols])
{
    int hor = 0;
    int vert = 0;
    char gps[4] = {0};

    while (1)
    {
        printf("Enter a GPS grid to attack (e.g., 5a): ");
        if (fgets(gps, sizeof(gps), stdin) == NULL)
        {
            printf("Input error. Try again.\n");
            continue;
        }

        if (gps[strlen(gps) - 1] == '\n')
        {
            gps[strlen(gps) - 1] = '\0';
        }
        else
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
        }

        if (strlen(gps) != 2 || !isdigit(gps[0]) || !isalpha(gps[1]))
        {
            printf("Invalid input format. Try again.\n");
            continue;
        }

        vert = gps[0] - '0';
        hor = tolower(gps[1]) - 'a';

        if (vert < 0 || vert >= rows || hor < 0 || hor >= 14)
        {
            printf("Input out of bounds. Try again.\n");
            continue;
        }

        if (hg[vert][hor] == '?' || hg[vert][hor] == '/')
        {
            printf("You already attacked there. Try again.\n");
            continue;
        }

        break;
    }
    if (hg[vert][hor] == 'X')
    {
        hg[vert][hor] = 'O';
    }
    else
    {
        hg[vert][hor] = '?';
    }
}

int botwin(char gg[][cols])
{
    int cnt = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 15; j < cols; j++)
        {
            if (gg[i][j] == '/')
            {
                cnt++;
            }
        }
    }
    if (cnt == 17)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int humwin(char ggg[][cols])
{
    int cnt = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            if (ggg[i][j] == '/')
            {
                cnt++;
            }
        }
    }
    if (cnt == 17)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int findRow(char ship[][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (ship[i][j] != '\0')
            {
                return i;
            }
        }
    }
    return -1;
}

void check(int spotter[], char gamest[][cols])
{
    static int hits[10] = {0};
    static int sunk[10] = {0};
    const char *names[5] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    const int sizes[5] = {5, 4, 3, 3, 2};

    for (int s = 0; s < 10; s++)
    {
        int start = (s < 5) ? 15 : 0;
        int end = (s < 5) ? cols : 14;
        char hitMark = (s < 5) ? 'X' : 'O';
        const char *side = (s < 5) ? "Human" : "Alien";

        for (int j = start; j < end; j++)
        {
            if (gamest[spotter[s]][j] == hitMark)
            {
                gamest[spotter[s]][j] = '/';
                hits[s]++;
                printf("%s %s has been hit!!!\n", side, names[s % 5]);
            }
        }
        if (hits[s] == sizes[s % 5] && sunk[s] == 0)
        {
            sunk[s] = 1;
            printf("The %s %s has been sunk!!!!\n", side, names[s % 5]);
        }
    }
}

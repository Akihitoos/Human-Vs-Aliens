#include "FileHandler.h"

void FH_EmptyBuffer()
{
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF);
}

void FH_WriteScore(char *pathToHighscoreTxt, int score)
{
    FILE *highscoreFile = NULL;
    highscoreFile = fopen(pathToHighscoreTxt, "a");
    
    if (highscoreFile == NULL)
    {
        fprintf(stderr, "Cannot open file %s\n", pathToHighscoreTxt);
    }

    FH_EmptyBuffer();
    char buffer[BUFFER_USERNAME], *temp;
    fprintf(stdout, "Please enter your username (without special characters) : \n");
    fgets(buffer, BUFFER_USERNAME, stdin);
    if ((temp = strchr(buffer, '\n')) != NULL)
    {
        *temp = '\0';
        char *username = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (username != NULL)
        {
            fprintf(highscoreFile, "%s,%d;\n", buffer, score);
        }
        else
        {
            fprintf(stderr, "Malloc error in FH_WriteScore\n");
        }
    }
    else
    {
        fprintf(stderr, "Username too long\n");
    }
    fclose(highscoreFile);
}

void FH_DisplayAllScore(char *pathToHighscoreTxt)
{
    FILE *highscoreFile = NULL;
    highscoreFile = fopen(pathToHighscoreTxt, "r");
    if (highscoreFile == NULL)
    {
        fprintf(stderr, "Cannot open file %s\n", pathToHighscoreTxt);
        return;
    }

    int i = 0, j = 0, score = -1;
    char bufferLine[BUFFER_LINE], bufferUsername[BUFFER_USERNAME], bufferScore[BUFFER_SCORE];

    while (!feof(highscoreFile) )
    {
        i = 0, j = 0;

        fgets(bufferLine, BUFFER_LINE, highscoreFile);

        if(strcmp(bufferLine, "") == 0){
            return;
        }

        for (j = 0; bufferLine[i] != ','; i++, j++)
        {
            bufferUsername[j] = bufferLine[i];
        }
        bufferUsername[j] = '\0';

        for (j = 0, i++; bufferLine[i] != ';'; i++, j++)
        {
            bufferScore[j] = bufferLine[i];
        }
        score = (int)strtol(bufferScore, NULL, 10);
        fprintf(stdout, "User : %10s, Score : %6d\n", bufferUsername, score);
        strcpy(bufferLine, "");
    }

    fclose(highscoreFile);
}
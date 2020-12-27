#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#define PATH_TO_HIGHSCORE_TXT "Highscore.txt"
#define BUFFER_SCORE 6
#define BUFFER_USERNAME 50
#define BUFFER_LINE 256

#include "Entity.h"
#include <string.h>

void FH_EmptyBuffer();

void FH_WriteScore(char *pathToHighscoreTxt, int score);

void FH_DisplayAllScore(char *pathToHighscoreTxt);

#endif
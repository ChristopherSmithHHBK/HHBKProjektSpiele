#if !defined (START_GAME)
#define START_GAME

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bridges.h"

char extern sNick1[40];
char extern sNick2[40];
int extern iType;

int gt_viergewinnt();
int gt_bridges();
int gt_reversi();
int gt_checkers();


#endif
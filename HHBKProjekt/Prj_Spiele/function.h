#if !defined (FUNCTION)

#define FUNCTION

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sql_function.h"
#include "start_game.h"

char extern sNick1[40];
char extern sNick2[40];
int extern iType;

void enter_pw(char*);
int login();
int HauptMenue();

#endif
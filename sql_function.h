#if !defined (SQL_FUNC)

#define SQL_FUNC

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char extern sNick1[40];
char extern sNick2[40];
int extern iType;

int sql_global_stats();
int sql_login(char*,char*);
int sql_reg(char*,char*);
int sql_gstats(int);
int mysql_con();

#endif
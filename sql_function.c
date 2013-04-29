#include "sql_function.h"

int sql_reg(char sUser[40],char sPass[40])
{
	return 0;
}

int sql_gstats(int iGameid)
{
	return 0;
}

int sql_global_stats()
{
	return 0;
}

int mysql_con()
{
	char *server ="localhost";
    char *user = "root";
    char *password = "123456";
    char *database = "hhbk-prj";

	/*if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
		return -1;
    }*/
	return 0;
}

int sql_login(char* sUser,char* sPass)
{
	/*
		Das hier ist testweise bis die DB Schnittstelle korrekt steht!
	*/
	if(strcmp(sUser,"Smith")==0&&strcmp(sPass,"test")==0)
	{	
		if(iType=1)
		{
			strcpy(sNick1,sUser);
			return 1;
		}
		else
		{
			if(strcmp(sNick1,"")!=0)
			{
				if(strcmp(sNick1,sUser)==0)
				{
					return -1;
				}
				else
				{
					strcpy(sNick2,sUser);
				}
				return 1;
			}
			else
			{
				strcpy(sNick1,sUser);
				return 1;
			}
		}
	}
	return 0;
}
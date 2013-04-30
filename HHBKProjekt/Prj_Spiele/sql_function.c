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
	if((conn = mysql_init(NULL)) == NULL)
	{
		return -1;
	}

	if (!mysql_real_connect(conn, "csmith-design.de", "hhbk_user", "schule1234", "admin_hhbk_prj", 3306, NULL, 0)){
		return -1;
	}
	else {
		return 0;
	}
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
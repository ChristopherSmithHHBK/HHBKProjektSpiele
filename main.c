#include "function.h"

char sNick1[40];
char sNick2[40];
int iType=0;


void main(void)
{
	int iRepeat = 1;
	int iLogin = 1;
	do
	{
		if(mysql_con()==0)
		{
			iLogin=login();
			if(iLogin==1)
			{
				do
				{
					iLogin = HauptMenue();				
					if(iLogin==-1)
					{
						iLogin=0;
						iRepeat=0;
					}
				}while(iLogin==1);
			}
			if(iLogin == -1)
			{
				iRepeat = 0;
			}
		}
		else
		{
			printf("ERROR: MYSQL Datenbank nicht erreichbar bzw. Userdaten Falsch\n\nBitte starten Sie bzw. korrigieren Sie die Datenbank einstellungen!");
			getch();
		}
	}while(iRepeat==1);
}
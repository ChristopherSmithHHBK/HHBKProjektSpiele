#include "function.h"

void enter_pw(char* buffer)
{
	int iX=0;
	char c;
	while(iX<40)
	{
		c = getch();
		if(c == '\r')
			break;
		buffer[iX] = c;
		putch('*');
		iX++;
	}
	buffer[iX] = 0;
}

int login()
{
	int iLoginu1;
	int iLoginu2;
	int iAuswahl;
	char sUsername1[40];
	char sUsername2[40];
	char sPasswort1[40] = "\0";
	char sPasswort2[40] = "\0";
	
	printf("Herzlich Willkommen\n");
	do
	{
		printf("Bitte wählen Sie aus:\n1. Login (Sie gegen Ki)\n2. Login (Multiplayer)\n3. Registrieren\n4. Beenden\n\nEingabe: ");
		fflush(stdin);
		scanf("%i",&iAuswahl);
		if(iAuswahl<1||iAuswahl>4){
			system("cls");
			printf("Ihre Eingabe war Falsch bitte wiederholen.\n\n");
		}
	}while(iAuswahl<1||iAuswahl>4);
	system("cls");

	switch(iAuswahl)
	{
		case 1:
			iType=1;
			do
			{
				printf("Zum Abbrechen -1 eingeben.\n\nBitte Username fuer den ersten User eingeben:\n");
				fflush(stdin);
				scanf("%s",sUsername1);
				if(strcmp(sUsername1,"-1")==0)
				{
					system("cls");
					return 0;
				}
				printf("Bitte Passwort fuer den ersten User eingeben:\n");
				enter_pw(sPasswort1);
				if(strcmp(sPasswort1,"-1")==0)
				{
					system("cls");
					return 0;
				}
				iLoginu1 = sql_login(sUsername1,sPasswort1);
				if(iLoginu1==0){
					system("cls");
					printf("Username oder Passwort waren Falsch.\n\n");
				}
			}while(iLoginu1==0);
			return 1;
			break;
		case 2:
			iType=2;
			do
			{
				printf("Zum Abbrechen -1 eingeben.\n\nBitte Username fuer den ersten User eingeben:\n");
				fflush(stdin);
				scanf("%s",sUsername1);
				if(strcmp(sUsername1,"-1")==0)
				{
					system("cls");
					return 0;
				}
				printf("Bitte Passwort fuer den ersten User eingeben:\n");
				enter_pw(sPasswort1);
				if(strcmp(sPasswort1,"-1")==0)
				{
					system("cls");
					return 0;
				}
				iLoginu1 = sql_login(sUsername1,sPasswort1);
				if(iLoginu1==0){
					system("cls");
					printf("Username oder Passwort für den ersten User waren Falsch.\n\n");
				}
			}while(iLoginu1==0);
			do
			{
				printf("Zum Abbrechen -1 eingeben.\n\nBitte Username fuer den zweiten User eingeben:\n");
				fflush(stdin);
				scanf("%s",sUsername2);
				if(strcmp(sUsername2,"-1")==0)
				{
					system("cls");
					return 0;
				}
				printf("Bitte Passwort fuer den zweiten User eingeben:\n");
				enter_pw(sPasswort2);
				if(strcmp(sPasswort2,"-1")==0)
				{
					system("cls");
					return 0;
				}
				iLoginu2 = sql_login(sUsername2,sPasswort2);
				if(iLoginu2==0)
				{
					system("cls");
					printf("Username oder Passwort für den zweiten User waren Falsch.\n\n");
				}
				if(iLoginu2==-1)
				{
					system("cls");
					printf("Der gleiche User darf sich nicht 2. mal anmelden.\n\n");
					iLoginu2 = 0;
				}
			}while(iLoginu2==0);
			return 1;
			break;
		case 3:
			printf("Zum Abbrechen -1 eingeben.\n\nRegistrierung\n\nBitte Username eingeben:\n");
			fflush(stdin);
			scanf("%s",sUsername1);
			if(strcmp(sUsername1,"-1")==0)
			{
				system("cls");
				return 0;
			}
			printf("Bitte Passwort eingeben:\n");
			fflush(stdin);
			scanf("%s",sPasswort1);
			if(strcmp(sPasswort1,"-1")==0)
			{
				system("cls");
				return 0;
			}
			break;
		case 4:
			return -1;
			break;
	}
	return -1;
}

int HauptMenue()
{
	int iAuswahl;
	system("cls");
	do
	{
		printf("Hauptmenue\n\nBitte waehlen Sie eine der folgenden Optionen:\n\n1. Bridges spielen\n2. 4 Gewinnt spielen\n3. Riversi spielen\n4. Checkers spielen\n5. Statistik\n6. Logout\n7. Beenden\n\nEingabe: ");
		fflush(stdin);
		scanf("%i",&iAuswahl);
		if(iAuswahl<1||iAuswahl>7)
		{
			system("cls");
			printf("Ihre Eingabe war falsch. Bitte wieder holen.");
		}
	}while(iAuswahl<1||iAuswahl>7);
	system("cls");
	switch(iAuswahl)
	{
		case 1:
			gt_bridges();
			break;
		case 2:
			gt_viergewinnt();
			break;
		case 3:
			gt_riversi();
			break;
		case 4:
			gt_checkers();
			break;
		case 5:
			sql_global_stats();
			break;
		case 6:
			return 0;
			break;
		case 7:
			return -1;
			break;
	}
	return 1;
}
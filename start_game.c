#include "start_game.h"

int gt_viergewinnt()
{
	int iAuswahl;
	system("cls");
	do
	{
		printf("Sie haben 4 Gewinnt gewaehlt\n\nBitte waehlen Sie:\n\n1. 4 Gewinnt spielen\n2. Spielregeln anschauen\n3. Statistik anschauen\n4. Zurueck zum Hauptmenue\n\nEingabe: ");
		fflush(stdin);
		scanf("%i",&iAuswahl);
		if(iAuswahl<1||iAuswahl>4)
		{
			system("cls");
			printf("Ihre Eingabe war leider Falsch bitte wiederholen!\n\n");
		}
	}while(iAuswahl<1||iAuswahl>4);

	switch(iAuswahl)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			sql_gstats(1);
			break;
		case 4:
			return 0;
			break;
	}
	return 0;
}

int gt_bridges()
{
	int iAuswahl;
	system("cls");
	do
	{
		printf("Sie haben Bridges gewaehlt\n\nBitte waehlen Sie:\n\n1. Bridges spielen\n2. Spielregeln anschauen\n3. Statistik anschauen\n4. Zurueck zum Hauptmenue\n\nEingabe: ");
		fflush(stdin);
		scanf("%i",&iAuswahl);
		if(iAuswahl<1||iAuswahl>4)
		{
			system("cls");
			printf("Ihre Eingabe war leider Falsch bitte wiederholen!\n\n");
		}
	}while(iAuswahl<1||iAuswahl>4);

	switch(iAuswahl)
	{
		case 1:
			playBridges();

			break;
		case 2:
			break;
		case 3:
			sql_gstats(2);
			break;
		case 4:
			return 0;
			break;
	}
	return 0;
}

int gt_checkers()
{
	int iAuswahl;
	system("cls");
	do
	{
		printf("Sie haben Checkers gewaehlt\n\nBitte waehlen Sie:\n\n1. 4 Gewinnt spielen\n2. Spielregeln anschauen\n3. Statistik anschauen\n4. Zurueck zum Hauptmenue\n\nEingabe: ");
		fflush(stdin);
		scanf("%i",&iAuswahl);
		if(iAuswahl<1||iAuswahl>4)
		{
			system("cls");
			printf("Ihre Eingabe war leider Falsch bitte wiederholen!\n\n");
		}
	}while(iAuswahl<1||iAuswahl>4);

	switch(iAuswahl)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			sql_gstats(4);
			break;
		case 4:
			return 0;
			break;
	}
	return 0;
}

int gt_riversi()
{
	int iAuswahl;
	system("cls");
	do
	{
		printf("Sie haben 4 Gewinnt gewaehlt\n\nBitte waehlen Sie:\n\n1. 4 Gewinnt spielen\n2. Spielregeln anschauen\n3. Statistik anschauen\n4. Zurueck zum Hauptmenue\n\nEingabe: ");
		fflush(stdin);
		scanf("%i",&iAuswahl);
		if(iAuswahl<1||iAuswahl>4)
		{
			system("cls");
			printf("Ihre Eingabe war leider Falsch bitte wiederholen!\n\n");
		}
	}while(iAuswahl<1||iAuswahl>4);

	switch(iAuswahl)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			sql_gstats(3);
			break;
		case 4:
			return 0;
			break;
	}
	return 0;
}
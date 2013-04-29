/*
===============================================================================
	Autor			: Fabian Wunsch
	Klasse			: FA3
	Dateiname		: Reversi.c
	Datum			: 31.05.2011
	Version			: 1.3
	Beschreibung	: Startet das Spiel Reversi
===============================================================================
*/
/* 
===============================================================================
	Eigene Header
===============================================================================
*/
#include"Reversi.h"

/*
===============================================================================
	Funktion:		starteReversi()
	in:				-
	out:			float
					1   = Spieler 1 hat gewonnen
					0   = Spieler 2 hat gewonnen
					0.5 = Unentschieden
					-1  = Spiel wurde abbebrochen
	Beschreibung:	Startet Reversi
===============================================================================
*/


float starteReversi() 
{
	int iHilfe; // Sollen die Möglichen Züge angezeigt werden
	char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y];
	int iRun = 1;
	int iSpieler = 0; // 0 = Spieler 1, 1 = Spieler 2
	int iMoeglich = 1; // Spieler kann einen Zug machen
	char cFeld[FELD_GROESSE_X][FELD_GROESSE_Y];

	srand((unsigned int) time(NULL));

	init(cSpielfeld);

	iHilfe = frageNachHilfe();

	while (iRun == 1)
	{
		int iEingabe = 0; // 0 = Eingabe ok, 1 = Falsche Eingabe, 2 = Ungültiger Zug, 
						  //3 = Kein Zug Möglich, 4 = Neues Spiel, 5 = Hilfe anzeigen
		char cEingabe[3];

		
		// Prüft ob ein Spielzug gemacht werden kann
		if (berechneGueltigkeiten(cSpielfeld, iSpieler))
		{
			iMoeglich = 1;
			do
			{
				iEingabe = frageEingabe(cFeld, cSpielfeld, iHilfe, cEingabe, iSpieler, iEingabe);
			}
			while (iEingabe == 1 || iEingabe == 2);
		}
		else
		{
			erstelleFeld(cFeld, cSpielfeld, iHilfe);
			zeigeFeld(cFeld);
			printf("\nSpieler %i kann keinen gueltigen Zug absolvieren.\nSpieler %i wird uebersprungen.", 
				iSpieler + 1, iSpieler + 1);
			fflush(stdin);
			getchar();

			if (!iMoeglich)
			{
				iRun = 0;
			}

			iMoeglich = 0;
		}

		// Spielabbruch
		if (iEingabe == -1)
			return -1;

		// Neues Spiel
		if (iEingabe == 4)
			iSpieler = 0;
		// Spielzug berechnen
		else if (iEingabe != 5 )
		{
			berechneSpielzug(cEingabe, cSpielfeld, iSpieler);
			iSpieler = !iSpieler;
		}
	}

	return berechneGewinner(cSpielfeld);
}

/*
===============================================================================
	Funktion:		frageNachHilfe()
	in:				-
	out:			int
					0 = keine Hilfe,
					1 = Hilfe eingeschaltet
	Beschreibung:	Frag nach Hilfe, um die Möglichkeiten der Züge anzugeben
===============================================================================
*/
int frageNachHilfe()
{
	char cEingabe = 'j';
	do
	{
		if (cEingabe != 'j' && cEingabe != 'n')
		{
			printf("Falsche Eingabe. Bitte geben Sie 'j' oder 'n' ein.");
		}

		printf("\n\tWollen Sie die moeglichen Spielzuege markiert haben (j/n)?");
		fflush(stdin);
		scanf("%c", &cEingabe);
	}
	while (cEingabe != 'j' && cEingabe != 'n');

	if (cEingabe == 'j')
		return 1;
	else
		return 0;
}

/*
===============================================================================
	Funktion:		berechneGueltigkeiten()
	in:				cSpielfeld[][], iSpieler
	out:			int
					1 = Spieler kann einen Zug machen, 
					0 =  Spieler kann keinen Zug machen
	Beschreibung:	Überprüft, ob der Spieler noch einen Zug machen kann
===============================================================================
*/
int berechneGueltigkeiten(char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], int iSpieler)
{
	int y, x, iMoeglich = 0;
	for (y = 0; y < SPIELFELD_GROESSE_X; y++)
	{
		for (x = 0; x < SPIELFELD_GROESSE_Y; x++)
		{
			
			// Ersetzt die Möglichen Sielzüge durch Leeres Feld
			if (cSpielfeld[x][y] == 'M')
				cSpielfeld[x][y] = 'L';
			// Berechnet die möglichen Zugmöglichkeiten
			if (iMoeglich)
				berechneZugmoeglichkeit(cSpielfeld, x, y, iSpieler, 0, 0);
			// Berechnet die möglichen Zugmöglichkeiten, wenn noch keine gefunden wurden und 
			// speichert ob welche gefunden wurden
			else
				iMoeglich = berechneZugmoeglichkeit(cSpielfeld, x, y, iSpieler, 0, 0);
		}
	}

	return iMoeglich;
}

/*
===============================================================================
	Funktion:		gueltigerSpielzug()
	in:				cSpielfeld[][], cEingabe[3], iSpieler
	out:			int
					0 = Ok, 
					1 = falsche Eingabezeichen, 
					2 = Falsche Koordinaten
	Beschreibung:	Überprüft ob die Eingabe für ein Spielzug korrekt war.
					Sind die Koordinaten im Bereich des Feldes und kann der 
					Spielstein gesetzt werden.
===============================================================================
*/
int gueltigerSpielzug(char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], char cEingabe[3], int iSpieler) // return: 0 = ok, 1 = falsche Eingabe, 2 = ungültiger Zug
{
		if (cEingabe[1] > 48 && cEingabe[1] < 48+9)
		{
			int x = -1;
			int y = cEingabe[1] - 49;
			if (cEingabe[0] > 64 && cEingabe[0] < 64+9)
			{
				x = cEingabe[0] - 65;
			}
			else if (cEingabe[0] > 96 && cEingabe[0] < 96+9)
			{
				x = cEingabe[0] - 97;
			}

			if ( x > -1)
			{
				if (cSpielfeld[x][y] == 'M')
				return 0;
			}
			
			return 2;
		}
			
	return 1;
}

/*
===============================================================================
	Funktion:		berechneZugmoeglichkeit()
	in:				cSpielfeld[][], x, y, iSpieler, iRichtung, iMode
	out:			int
					0 = keine Zugmöglichkeiten gefunden, 
					1 = Zugmöglichkeit gefunden, 
					2 = Stein vom gleichen Spieler gefunden 
					(Nicht beim Rekusionsstufe 1 möglich)
	Beschreibung:	Berechnet, ob der Computer-Gegner einen Zug machen kann
===============================================================================
*/
int berechneZugmoeglichkeit(char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], int x, int y, int iSpieler, int iRichtung, int iMode)
{
	int i;

	// Erstaufruf für das Feld
	if (iRichtung == 0) 
	{
		// Kein Spielstein
		if (cSpielfeld[x][y] == 'L')
		{
			for (i = 1; i < 9; i++)
			{
				// Alle Möglichen Richtungen für ein gültigen Spielzug werden überprüft
				if (berechneZugmoeglichkeit(cSpielfeld, x , y, iSpieler, i, iMode) == 1)
				{
					// Wurde ein Spielzug gefunden, wird das Feld auf 'M' gesetzt
					cSpielfeld[x][y] = 'M';
					return 1;
				}	
			}
		}

		return 0;
	}
	// Überprüft weiter in eine bestimmte Richtung ob ein Zug stat finden könnte
	else
	{
		int koor[2] = { x, y };
		ermittleRichtung(iRichtung, koor);
		x = koor[0];
		y = koor[1];

		if (x >= 0 && y >= 0 && x < 8 && y < 8)
		{
			// Spielerstein wurde gefunden
			if (g_cSpSymbol[iSpieler] == cSpielfeld[x][y])
				return 2;

			// Feindstein wurde gefunden
			if (g_cSpSymbol[!iSpieler] == cSpielfeld[x][y])
			{
				int iMoeglich = 0;
				iMoeglich = berechneZugmoeglichkeit(cSpielfeld, x, y, iSpieler, iRichtung, iMode);

				// Spielerstein wurde gefunden oder es wurde ein Zug gefunden
				if (iMoeglich == 2 || iMoeglich == 1)
				{
					// Bei 1 werden die Steine auch umgedreht
					if (iMode == 1)
						cSpielfeld[x][y] = g_cSpSymbol[iSpieler];

					return 1;
				}
			}
		}
	}

	return 0;

}

/*
===============================================================================
	Funktion:		erstelleFeld()
	in:				cFeld[][], cSpielfeld[][], iHilfe
	out:			-
	Beschreibung:	Erstellt das fertige Feld für die Ausgabe
===============================================================================
*/
void erstelleFeld(char cFeld[FELD_GROESSE_X][FELD_GROESSE_Y], char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], int iHilfe)
{	
	int i, j;
	erstelleFeldTemplate(cFeld);
	for (i = 0; i < SPIELFELD_GROESSE_X; i++)
	{
		for (j = 0; j < SPIELFELD_GROESSE_Y; j++)
		{

			// Übertragung des Spielfeldes auf das ganze Feld
			if (cSpielfeld[i][j] == 'O' || cSpielfeld[i][j] == 'X' || (iHilfe && cSpielfeld[i][j] == 'M'))
			{
				// Obere und untere Zeile 
				int x = 4 + (i * 7);
				int y = 3 + (j * 5);
				int xMax = x + 3;

				while(x < xMax)
				{
					cFeld[y][x] = cSpielfeld[i][j];
					cFeld[y+2][x] = cSpielfeld[i][j];
					x++;   
				}

				// Mittlere Zeile
				x = 3 + (i * 7);
				y = 4 + (j * 5);
				xMax = x + 5;

				while(x < xMax)
				{
					cFeld[y][x] = cSpielfeld[i][j];
					x++;   
				}
			}
		}
	}
}

/*
===============================================================================
	Funktion:		erstelleFeldTemplate()
	in:				cFeld[][]
	out:			-
	Beschreibung:	Das Standartfeld wird erzeugt. Es ist ohne Spielsteine 
					gefüllt.
===============================================================================
*/
void erstelleFeldTemplate(char cFeld[FELD_GROESSE_X][FELD_GROESSE_Y])
{
	int i, j;
	int fieldTyp = 0;
	int z = 0;
	int a = 0;
	strcpy(cFeld[0], "     A      B      C      D      E      F      G      H   ");
	cFeld[0][1] = 0xb3;
	strcpy(cFeld[1], "                                                          ");
	for (i = 2; i < FELD_GROESSE_X; i++)
	{
		strcpy(cFeld[i], "                                                          ");
		// Zeilennummerierung
		if ((i + 1) % 5 == 0)		
		{
			cFeld[i][0] = 48 + ((i + 1)/5);
		}
		// Jede 5 zeilen soll das Feld sich ändern
		if (a > 4)
		{
			a = 0;
			fieldTyp = !fieldTyp;
		}
		for (j = 2; j < FELD_GROESSE_Y - 1; j++) 
			{
				// Jede 6 Spalten soll sich das Feld ebenfalls ändern
				if (z > 6)
				{
					fieldTyp = !fieldTyp;
					z = 0;
				}
				
				if (fieldTyp == 0)
				{
					cFeld[i][j] = 0xb1;
				} 
				else 
				{
					cFeld[i][j] = 0xb0;
				}
				z++;
			}
		a++;
	}

	// Linie für die Zeilenangaben
	for (i = 2; i < FELD_GROESSE_X; i++)
	{
		cFeld[i][1] = 0xb3;
	}

	// Linie für die Spaltenangaben
	for (i = 0; i < FELD_GROESSE_Y - 1; i++)
	{
		cFeld[1][i] = 0xc4;
	}
	cFeld[1][1] = 0xc5;
}

/*
===============================================================================
	Funktion:		zeigeFeld()
	in:				cFeld[][]
	out:			-
	Beschreibung:	Gibt das Feld in der Konsole aus.
===============================================================================
*/
void zeigeFeld(char cFeld[FELD_GROESSE_X][FELD_GROESSE_Y])
{	
	int i,j;
	system("cls");

	printf("================================================================================");
	printf("              $$$$$$$  $$$$$ $$  $$ $$$$$ $$$$$$  $$$$$   $$                    ");
	printf("             $$    $$ $$    $$  $$ $$    $$   $$ $$      $$                     ");
	printf("            $$ $$$$  $$$$$ $$  $$ $$$$$ $$ $$$$ $$$$$$  $$                      ");      
	printf("           $$   $$  $$    $$ $$$ $$    $$  $$      $$  $$                       ");
	printf("          $$    $$ $$$$$  $$$$$ $$$$$ $$   $$ $$$$$$  $$                        ");
	printf("================================================================================");
	printf("\n");
	for (i = 0; i < FELD_GROESSE_X; i++)
	{
		printf("\t");
		for (j = 0; j < FELD_GROESSE_Y - 1; j++)
		{

			// Je nach Spieler werden die Spielsteine farbig markiert
			if (cFeld[i][j] == 'X')
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			else if (cFeld[i][j] == 'O')
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			else 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN |FOREGROUND_INTENSITY);

			printf("%c", cFeld[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("          x:Hauptmenue          s:Hilfe          w:Neues Spiel");
}

/*
===============================================================================
	Funktion:		erhalteEingabe()
	in:				cEingabe[], iSpieler
	out:			-
	Beschreibung:	Speichert die Eingabe für die Spielzüge in einem Char-Array
===============================================================================
*/
void erhalteEingabe(char cEingabe[3], int iSpieler)
{
	char cSpieler[32];
	if (!iSpieler)
	{
		strcpy(cSpieler, g_cSpieler1);
		strcat(cSpieler, " (Blau)");
	} 
	else
	{
		strcpy(cSpieler, g_cSpieler2);
		strcat(cSpieler, " (Rot)");
	} 
	printf("\n\n          %s ist am Zug:", cSpieler);
	printf("\n          X: ");
	fflush(stdin);
	scanf("%c", &cEingabe[0]);
	if (cEingabe[0] == 'x' || cEingabe[0] == 'X')
		return;
	if (cEingabe[0] == 'w' || cEingabe[0] == 'w')
		return;
	if (cEingabe[0] == 's' || cEingabe[0] == 's')
		return;
	printf("\ty: ");
	fflush(stdin);
	scanf("%c", &cEingabe[1]);
}

/*
===============================================================================
	Funktion:		berechneSpielzug()
	in:				cEingabe[], cSpielfeld[][], iSpieler
	out:			-
	Beschreibung:	Berechnet welche Spielsteine umgedreht werden
===============================================================================
*/
void berechneSpielzug(char cEingabe[3], char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], int iSpieler)
{
	int x, y, i;
	// Umwandlung der Ascii-Zeichen in die x und y Koordinaten
	x = cEingabe[0] - 65; 
	y = cEingabe[1] - 49;
	// Bei Großbuchstabe
	if (x > 10)
	{
		x -= 32;
	}

	cSpielfeld[x][y] =  g_cSpSymbol[iSpieler];

	for (i = 1; i < 9; i++)
	{
		berechneZugmoeglichkeit(cSpielfeld, x, y, iSpieler, i, 1);
	}
}

/*
===============================================================================
	Funktion:		berechneGewinner()
	in:				cSpielfeld[][]
	out:			float
					1 = Spieler 1 gewinnt, 0 = Spieler 2 gewinnt, 
					0.5 = unentschieden, -1 = Spiel wurde abgebrochen
	Beschreibung:	Steuerung des Logins.
					Muss in eine eigene Funktion ausgelagert werden, damit man 
					aus dem Hauptmenue zurück zum Login kommen kann.
===============================================================================
*/
float berechneGewinner(char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y])
{
	int x,y;
	int iPunkte1 = 0, iPunkte2 = 0;
	for (x = 0; x < SPIELFELD_GROESSE_X; x ++)
		for (y = 0; y < SPIELFELD_GROESSE_Y; y++)
		{
			if (cSpielfeld[x][y] == 'X')
				iPunkte1++;
			else if (cSpielfeld[x][y] == 'O')
				iPunkte2++;
		}
	if (iPunkte1 > iPunkte2)
	{
		ausgebenEndeMeldung(1);
		//printf("%c hat das Spiel gewonnen.\n", g_cSpieler1);
		//system("pause");
		return 1;
	}
	if (iPunkte2 > iPunkte1)
	{
		ausgebenEndeMeldung(2);
		//printf("%c hat das Spiel gewonnen.\n", g_cSpieler2);
		//system("pause");
		return 0;
	}
	
	//printf("Das Spiel ging unentschieden aus.");
	//system("pause");
	ausgebenEndeMeldung(4);
	return 0.5;
}

/*
===============================================================================
	Funktion:		ermittleRichtung()
	in:				iRichtung, koordinaten[]
	out:			-
	Beschreibung:	Ermittelt die X und Y-Koordinaten für die Richtungen
===============================================================================
*/
void ermittleRichtung(int iRichtung, int koordinaten[2]) 
{
	int x = koordinaten[0];
	int y = koordinaten[1];

	switch (iRichtung)
	{
		case 1:
			x--;
			break;
		case 2:
			x--;
			y--;
			break;
		case 3:
			y--;
			break;
		case 4:
			x++;
			y--;
			break;
		case 5:
			x++;
			break;
		case 6:
			x++;
			y++;
			break;
		case 7:
			y++;
			break;
		case 8:
			x--;
			y++;
			break;
	}

	koordinaten[0] = x;
	koordinaten[1] = y;
}

/*
===============================================================================
	Funktion:		init()
	in:				cSpielfeld[][]
	out:			-
	Beschreibung:	Initialisiert das Spielfed
					Wird bei jeden neuen Spiel ausgeführt
===============================================================================
*/
void init(char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y])
{
	int i, j;
	// Spielfeldzellen werden auf 'L' für Leer gesetzt
	for (i = 0; i < SPIELFELD_GROESSE_X; i++)
		for (j = 0; j < SPIELFELD_GROESSE_Y; j++)
			cSpielfeld[i][j] = 'L';

	// Startspielsteine werden gesetzt
	cSpielfeld[4][4] = 'X';
	cSpielfeld[3][4] = 'O';
	cSpielfeld[4][3] = 'O';
	cSpielfeld[3][3] = 'X';
}

/*
===============================================================================
	Funktion:		generiereEingabeLeicht()
	in:				cSpielfeld[][], cEingabe[], iSpieler
	out:			-
	Beschreibung:	Generierung der Eingabe für den Computer Leicht
===============================================================================
*/
void generiereEingabeLeicht(char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], char cEingabe[3], int iSpieler)
{
	int y, x, z = 0;
	int iZahl, xZahl, yZahl;

	// Zählt wie viele Möglichkeiten es gibt
	for (x = 0; x < SPIELFELD_GROESSE_X; x++)
	{
		for (y = 0; y < SPIELFELD_GROESSE_Y; y++)
		{
			if (cSpielfeld[x][y] == 'M')
				z++;
		}
	}
	// Sucht eine der Möglichkeiten zufällig aus
	iZahl = (rand() % z) + 1;
	z = 0;

	// zählen bis die Moeglichkeit gefunden wurde
	for (x = 0; x < SPIELFELD_GROESSE_X; x++)
	{
		for (y = 0; y < SPIELFELD_GROESSE_Y; y++)
		{
			if (cSpielfeld[x][y] == 'M')
			{
				z++;
				if (z == iZahl)
				{
					xZahl = x;
					yZahl = y;
					x = SPIELFELD_GROESSE_X;
					y = SPIELFELD_GROESSE_Y;
				}
			}
		}
	}

	// Eingabe setzten
	cEingabe[0] = xZahl + 65;
	cEingabe[1] = yZahl + 49;
}

/*
===============================================================================
	Funktion:		generiereEingabeMittel()
	in:				cSpielfeld[][], cEingabe[], iSpieler
	out:			-
	Beschreibung:	Generierung der Eingabe für den Computer Mittel
===============================================================================
*/
void generiereEingabeMittel(char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], char cEingabe[3], int iSpieler)
{
	int y, x;
	int xZahl, yZahl;
	int iMaxPunkte = 0;

	// Überprüft welche Möglichkeit am meisten Punkte
	for (x = 0; x < SPIELFELD_GROESSE_X; x++)
		for (y = 0; y < SPIELFELD_GROESSE_Y; y++)
		{
			if (cSpielfeld[x][y] == 'M')
			{
				int iPunkte = 0;
				if ((iPunkte = legeSteinMoeglich(x, y, cSpielfeld, iSpieler)) > iMaxPunkte)
				{
					iMaxPunkte = iPunkte;
					xZahl = x;
					yZahl = y;
				}
			}
		}

	// Eingabe setzten
	cEingabe[0] = xZahl + 65;
	cEingabe[1] = yZahl + 49;
}
/*
===============================================================================
	Funktion:		generiereEingabeSchwer()
	in:				cSpielfeld[][], cEingabe[], iSpieler
	out:			-
	Beschreibung:	Generierung der Eingabe für den Computer Schwer
===============================================================================
*/
void generiereEingabeSchwer(char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], char cEingabe[3], int iSpieler)
{
	// Eckstein möglich
		int iMaxPunkte = 0;
		int iTempPunkte;
		int i;
		// Links Oben
		if ((iTempPunkte = legeSteinMoeglich(0, 0, cSpielfeld, iSpieler)) > iMaxPunkte)
		{
			iMaxPunkte = iTempPunkte;
			cEingabe[0] = 0 + 65;
			cEingabe[1] = 0 + 49;
		}
		// Rechts Oben
		if ((iTempPunkte = legeSteinMoeglich(7, 0, cSpielfeld, iSpieler)) > iMaxPunkte)
		{
			iMaxPunkte = iTempPunkte;
			cEingabe[0] = 7 + 65;
			cEingabe[1] = 0 + 49;
		}
		// Links Unten
		if ((iTempPunkte = legeSteinMoeglich(0, 7, cSpielfeld, iSpieler)) > iMaxPunkte)
		{
			iMaxPunkte = iTempPunkte;
			cEingabe[0] = 0 + 65;
			cEingabe[1] = 7 + 49;
		}
		// Rechts Unten
		if ((iTempPunkte = legeSteinMoeglich(7, 7, cSpielfeld, iSpieler)) > iMaxPunkte)
		{
			iMaxPunkte = iTempPunkte;
			cEingabe[0] = 7 + 65;
			cEingabe[1] = 7 + 49;
		}

		// Kein Eckstein war möglich zu setzten, dannw erden die Ränder versucht zu setzten
		if (!iMaxPunkte)
		{
			//Linker Rand
			for (i = 0; i < SPIELFELD_GROESSE_X; i++)
			{
				if ((iTempPunkte = legeSteinMoeglich(0, i, cSpielfeld, iSpieler)) > iMaxPunkte)
				{
					iMaxPunkte = iTempPunkte;
					cEingabe[0] = 0 + 65;
					cEingabe[1] = i + 49;
				}
			}
			//Rechter Rand
			for (i = 0; i < SPIELFELD_GROESSE_X; i++)
			{
				if ((iTempPunkte = legeSteinMoeglich(7, i, cSpielfeld, iSpieler)) > iMaxPunkte)
				{
					iMaxPunkte = iTempPunkte;
					cEingabe[0] = 7 + 65;
					cEingabe[1] = i + 49;
				}
			}
			//Oberer Rand
			for (i = 0; i < SPIELFELD_GROESSE_Y; i++)
			{
				if ((iTempPunkte = legeSteinMoeglich(i, 0, cSpielfeld, iSpieler)) > iMaxPunkte)
				{
					iMaxPunkte = iTempPunkte;
					cEingabe[0] = i + 65;
					cEingabe[1] = 0 + 49;
				}
			}

			//unterer Rand
			for (i = 0; i < SPIELFELD_GROESSE_Y; i++)
			{
				if ((iTempPunkte = legeSteinMoeglich(i, 0, cSpielfeld, iSpieler)) > iMaxPunkte)
				{
					iMaxPunkte = iTempPunkte;
					cEingabe[0] = i + 65;
					cEingabe[1] = 7 + 49;
				}
			}
		}

		// Kein Zug möglich bisher, dann Mittlere Ki starten
		if (!iMaxPunkte)
			generiereEingabeMittel(cSpielfeld, cEingabe, iSpieler);
}

/*
===============================================================================
	Funktion:		auswertenPunkte()
	in:				cTempSpielfeld[][], iSpieler
	out:			iPunkte
	Beschreibung:	Wertet die Punkte für den Spieler aus
===============================================================================
*/
int auswertenPunkte(char cTempSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], int iSpieler)
{
	// Auswerten
	int i,j;
	int iPunkte = 0;
	for (i = 0; i < SPIELFELD_GROESSE_X; i ++)
	{
		for (j = 0; j < SPIELFELD_GROESSE_Y; j++)
		{
			if (cTempSpielfeld[i][j] == g_cSpSymbol[iSpieler])
				iPunkte++;
		}
	}
	return iPunkte;
} 

/*
===============================================================================
	Funktion:		kloneSpielfeld()
	in:				cSpielfeld[][], cTempSpielfeld[][]
	out:			-
	Beschreibung:	Klont das erste Char-Array in das zweite Char-Array
===============================================================================
*/
void kloneSpielfeld(char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], char cTempSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y])
{
	int i,j;
	for (i = 0; i < SPIELFELD_GROESSE_X; i++)
	{
		for (j = 0; j < SPIELFELD_GROESSE_Y; j++)
		{
			cTempSpielfeld[i][j] = cSpielfeld[i][j];
		}
	}
}

/*
===============================================================================
	Funktion:		legeSteinMoeglich()
	in:				x, y, cSpielfeld[][], iSpieler
	out:			0 - Spielzug nicht möglich
					sonst Punkte
	Beschreibung:	Versucht den Stein an einer Position zu legen und gibt 
					die meisten Punkte zurück
					
===============================================================================
*/
int legeSteinMoeglich(int x, int y, char cSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], int iSpieler)
{
	if (cSpielfeld[x][y] == 'M')
		{
			char cTempSpielfeld[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y];
			char cEingabe[3];
			kloneSpielfeld(cSpielfeld, cTempSpielfeld);
			cEingabe[0] = 65 + 0;
			cEingabe[1] = 49 + 0;
			berechneSpielzug(cEingabe, cTempSpielfeld, iSpieler);
			return auswertenPunkte(cTempSpielfeld, iSpieler);
		}

	return 0;
}

/*
===============================================================================
	Funktion:		frageEingabe()
	in:				cFeld[][], cSpielfeld[][], iHilfe, cEingabe[], iSpieler, iEingabe
	out:			-1 -  Spiel abbrechen
					4	-  Neues Spiel
					5	-  Hilfe aufrufen
	Beschreibung:	Eingabeabfrage für den Benutzer bzw. der Ki
===============================================================================
*/
int frageEingabe(char cFeld[42][59], char cSpielfeld[8][8], int iHilfe, char cEingabe[3], int iSpieler, int iEingabe)
{
	erstelleFeld(cFeld, cSpielfeld, iHilfe);
	zeigeFeld(cFeld);

	// Meldung: Falsche Eingabe
	if (iEingabe == 1)
	{
		printf("\n\tIhre Eingabe war falsch. ");
		printf("\n\tBitte wiederholen Sie Ihre Eingabe.");
	}

	// Meldung: Ungültige Zug
	if (iEingabe == 2)
	{
		printf("\n\tDieser Zug ist nicht moeglich. ");
		printf("\n\tBitte wiederholen Sie Ihre Eingabe.");
	}

	// Ki oder Spieler soll Eingabe machen
	if (iSpieler && g_iKI)
	{
		if (g_iKI == 1)
			generiereEingabeLeicht(cSpielfeld, cEingabe, iSpieler);
		else if (g_iKI == 2)
			generiereEingabeMittel(cSpielfeld, cEingabe, iSpieler);
		else
			generiereEingabeSchwer(cSpielfeld, cEingabe, iSpieler);
	}
	else
	{
		erhalteEingabe(cEingabe, iSpieler);
	}
				

	// Zugkoordinaten sind Korrekt oder möglich
	iEingabe  = gueltigerSpielzug(cSpielfeld, cEingabe, iSpieler);

	// Spiel abbrechen?
	if (cEingabe[0] == 'x' || cEingabe[0] == 'X' || cEingabe[1] == 'x' || cEingabe[1] == 'X')
	{
		ausgebenEndeMeldung(3);
		return -1;
	} 
	// Hilfe aufrufen
	else if (cEingabe[0] == 's' || cEingabe[0] == 'S' || cEingabe[1] == 's' || cEingabe[1] == 'S')
	{
		iEingabe = 5;
		system("start Reversi-Hilfe.html");
	}
	// Neues Spiel
	else if (cEingabe[0] == 'w' || cEingabe[0] == 'W' || cEingabe[1] == 'w' || cEingabe[1] == 'W')
	{
		iEingabe = 4;
		init(cSpielfeld);
	}

	return iEingabe;
}

/*
===============================================================================
   Funktion:		ausgebenWinMeldung()
   in:				cAktuellerSpieler, cKoordinate
   out:				-
   Beschreibung:	Gibt eine Meldung aus, wenn ein Spieler gewonnen hat, das 
					Spiel abgebrochen wurde oder das Spiel unentschieden 
					ausgegangen ist.
===============================================================================
*/
void ausgebenEndeMeldung(int iZahl)
{
	if(iZahl == 1)
	{
		system("cls");
		printf("===========================================================");
		printf("=====================");
		printf("         $$$$$$$   $$  $$  $$$$$$ $$$$$$   $$ $$$  $$$$$$ $");
		printf("$$$$$$  $$$$$$       ");
		printf("        $$    $$  $$  $$  $$     $$   $$  $$ $$   $$     $$");
		printf("    $$ $$            ");
		printf("       $$        $$$$$$  $$$$$  $$       $$$$$   $$$$   $$ ");
		printf("$$$$  $$$$$$$        ");
		printf("      $$    $$  $$  $$  $$     $$   $$  $$ $$   $$     $$  ");
		printf(" $$       $$         ");
		printf("      $$$$$$$  $$  $$  $$$$$$$ $$$$$$  $$   $$ $$$$$$ $$   ");
		printf(" $$ $$$$$$$          ");
		printf("===========================================================");
		printf("=====================");
		printf("\n\nHerzlichen Glueckwunsch.\n %s hat gewonnen!!\n\n", g_cSpieler1);
		printf("\n");
	}
	if(iZahl == 2)
	{
		system("cls");
		printf("===========================================================");
		printf("=====================");
		printf("         $$$$$$$   $$  $$  $$$$$$ $$$$$$   $$ $$$  $$$$$$ $");
		printf("$$$$$$  $$$$$$       ");
		printf("        $$    $$  $$  $$  $$     $$   $$  $$ $$   $$     $$");
		printf("    $$ $$            ");
		printf("       $$        $$$$$$  $$$$$  $$       $$$$$   $$$$   $$ ");
		printf("$$$$  $$$$$$$        ");
		printf("      $$    $$  $$  $$  $$     $$   $$  $$ $$   $$     $$  ");
		printf(" $$       $$         ");
		printf("      $$$$$$$  $$  $$  $$$$$$$ $$$$$$  $$   $$ $$$$$$ $$   ");
		printf(" $$ $$$$$$$          ");
		printf("===========================================================");
		printf("=====================");
		printf("\n\nHerzlichen Glueckwunsch.\n %s hat gewonnen!!\n\n", g_cSpieler2);
		printf("\n");
	}
	if(iZahl == 3)
	{
		system("cls");
		printf("================================================================================");
		printf("              $$$$$$$  $$$$$ $$  $$ $$$$$ $$$$$$  $$$$$   $$                    ");
		printf("             $$    $$ $$    $$  $$ $$    $$   $$ $$      $$                     ");
		printf("            $$ $$$$  $$$$$ $$  $$ $$$$$ $$ $$$$ $$$$$$  $$                      ");      
		printf("           $$   $$  $$    $$ $$$ $$    $$  $$      $$  $$                       ");
		printf("          $$    $$ $$$$$  $$$$$ $$$$$ $$   $$ $$$$$$  $$                        ");
		printf("================================================================================");
		printf("\n\n");
		printf("\t Sie haben das Spiel beendet. ");
		printf("\n");
		printf("\t Es findet keine Wertung statt.");
	}
	if(iZahl == 4)
	{
		system("cls");
		printf("================================================================================");
		printf("              $$$$$$$  $$$$$ $$  $$ $$$$$ $$$$$$  $$$$$   $$                    ");
		printf("             $$    $$ $$    $$  $$ $$    $$   $$ $$      $$                     ");
		printf("            $$ $$$$  $$$$$ $$  $$ $$$$$ $$ $$$$ $$$$$$  $$                      ");      
		printf("           $$   $$  $$    $$ $$$ $$    $$  $$      $$  $$                       ");
		printf("          $$    $$ $$$$$  $$$$$ $$$$$ $$   $$ $$$$$$  $$                        ");
		printf("================================================================================");
		printf("\n\n");
		printf("\t Das Spiel endete: Unentschieden");
	}
	printf("\n\n\t ");
    system("pause");
}
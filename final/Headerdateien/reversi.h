/*
============================================================================
	Autor : Fabian Wunsch
	Klasse : FA3
	Dateiname : Reversi.h
	Datum : 31.05.2011
	Beschreibung: 
	Version : 1.3
============================================================================
*/

/*
============================================================================
Präprozessoranweisungen
==============================================================================
*/
#define _CRT_SECURE_NO_DEPRECATE 1
#define SPIELFELD_GROESSE_X 8
#define SPIELFELD_GROESSE_Y 8
#define FELD_GROESSE_X 42
#define FELD_GROESSE_Y 59



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<time.h>


/*
============================================================================
globale Variablen
==============================================================================
*/

extern const char g_cSpSymbol[2];
extern char g_cSpieler1[25];
extern char g_cSpieler2[25];
extern int g_iKI;

/*
============================================================================
Funktionsprototypen
==============================================================================
*/

float starteReversi();
void zeigeFeld(char[FELD_GROESSE_X][FELD_GROESSE_Y]);
void erhalteEingabe(char[3], int);
int gueltigerSpielzug(char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
					char[3], int);
void berechneSpielzug(char[3], char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
						int);
int frageNachHilfe();
void erstelleFeld(char[FELD_GROESSE_X][FELD_GROESSE_Y], 
					char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_X], int);
void erstelleFeldTemplate(char[FELD_GROESSE_X][FELD_GROESSE_Y]);
int berechneGueltigkeiten(char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
							int);
int berechneZugmoeglichkeit(char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
							int, int, int, int, int);
void flipFeld(char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
							int, int, int, int);
float berechneGewinner(char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y]);
void ermittleRichtung(int, int[2]);
void init(char [SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y]);
void generiereEingabeLeicht(char [SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
							char[3], int iSpieler);
void generiereEingabeMittel(char [SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
							char[3], int iSpieler);
void generiereEingabeSchwer(char [SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
							char[3], int iSpieler);
int auswertenPunkte(char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], int);
void kloneSpielfeld(char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
							char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y]);
int legeSteinMoeglich(int, int, char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], 
					  int);
int setzenMoeglich(char[3]);
int frageEingabe(char[FELD_GROESSE_X][FELD_GROESSE_Y], 
				char[SPIELFELD_GROESSE_X][SPIELFELD_GROESSE_Y], int, char[3], int, int);
void ausgebenEndeMeldung(int);

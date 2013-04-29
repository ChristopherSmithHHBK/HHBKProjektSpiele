/*
================================================================================
Author		: Sebastian Weis
Firma		: TARGO IT Consulting GmbH
PGM			: Checkers.h
Version		: 1.0
Beschreibung: Das Spiel "Checkers".
================================================================================
*/
/*
================================================================================
Include Anweisungen
================================================================================
*/
#define _CRT_SECURE_NO_DEPRECATE 1
   /* Microsoft hat alle gängigen Ein- und Ausgabefunktionen
      als gefährlich eingestuft und durch neue Varianten ersetzt.
      Mit den neuen Funktionen sind die Programme aber nicht
      kompatible zu anderen Entwicklungsumgebungen.
      Bei Verwendung der alten Funktionen wird eine Warnung ausgegeben.
      Diese Warnung kann durch die obige Definition unterdrückt werden.
  */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>


/*
==============================================================================
   externe Variablen
==============================================================================
*/
	extern char g_cSpieler1[25];
	extern char g_cSpieler2[25];

/*
==============================================================================
	Globale Variablen
==============================================================================
*/
char g_cAktuellerSpieler[25];
char g_cSpielfeld[8][8]; // Spielfeld
char g_cAusgabe[42][58]; // Ausgabe Array
int g_iAnzahlSteine; //Anzahl der Spieler Spielsteine
int g_iAnzahlSpieler1;
int g_iAnzahlSpieler2;
int g_iPlayer; //akt. Spieler
int g_iStep; //Aktuelle Eingabe-Position
int g_iAktXPos, g_iAktYPos; // Aktuelle X & Y Position des fokusierten Steins
int g_iSteinX, g_iSteinY; // X & Y Position des gerade gesetzten Steins
char g_cBeenden; // Flag zum Beeden des Spiels
int g_iSprung;
int g_iBewegung;
char g_cNeustart;
int g_iExitFlag;
float g_fExitCode;
/*
================================================================================
	Funktionsprototypen
================================================================================
*/
float starteCheckers(void);

void setzeStartSpielfeld(void);
void schreibe(void);
void schreibeStein(int, int, char);
void fuelleReiheWeiss(int, int);
void fuelleReiheSchwarz(int, int);

void pruefeSpielsteinVorhanden(void);
void pruefeObSprungMoeglich(int, int, char);
void pruefeObBewegungMoeglich(int , int, char);
void pruefeObDamenSprung(int, int, int);

void waehleSpielstein(void);
void sprungSpielstein(char);

int pruefeYEingabe(char);
int pruefeXEingabe(char);

int zeigeMoeglichkeiten(int, int);
int zeigeDamenMoeglichkeiten(int, int);
int dameLinksOben(int, int);
int dameRechtsOben(int, int);
int dameLinksUnten(int, int);
int dameRechtsUnten(int, int);

void waehleZiel(void);
int pruefeZiel(int, int);

int setzeStein(int, int);
int setzeDame(int, int);

void wandleZuDame(void);
void wechselSpieler(void);

void beenden();



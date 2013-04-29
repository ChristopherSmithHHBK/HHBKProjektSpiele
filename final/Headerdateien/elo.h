/*
===============================================================================
   Autor       : Kay Schäfer
   Firma       : HHBK
   Dateiname   : elo.h
   Datum       : 04.06.2011
   Version     : 1.0
===============================================================================
*/

#if !defined (ELO_H)
#define ELO_H

#define _CRT_SECURE_NO_DEPRECATE 1
   /* Microsoft hat alle gängigen Ein- und Ausgabefunktionen
      als gefährlich eingestuft und durch neue Varianten ersetzt.
      Mit den neuen Funktionen sind die Programme aber nicht
      kompatible zu anderen Entwicklungsumgebungen.
      Bei Verwendung der alten Funktionen wird eine Warnung ausgegeben.
      Diese Warnung kann durch die obige Definition unterdrückt werden.
  */
#include "sql_anbindung.h"
#include <string.h>
#include <math.h>


/*
==============================================================================
   externe Variablen
==============================================================================
*/
extern char g_cSpieler1[25];
extern char g_cSpieler2[25];
extern int g_iKI;

/*
==============================================================================
   globale Variablen
==============================================================================
*/
char sBefehl[400];
char cID[30];
char cID2[30];
char cTabelleElo[4][10];
char cSpalte[4][20];
char cErgebnis[10];
char cErgebnis2[10];

float fBewertungS1neu;
float fBewertungS2neu;

float fBewertungS1;
float fBewertungS2;

int iVerbindung;

/*
==============================================================================
   Funktionsprototypen
==============================================================================
*/
void zeigeStatistikNachSpielende(float fErgebnis, int iSpieltyp);
void holeIDs();
void elo(float fErgebnis, int iSpieltyp);
void bewertungElo(float fPunkte);
void vorbereitung(int iSpieltyp);
void schreibeinDatenbank(float fErgebnis, int iSpieltyp);

#endif
/*
===============================================================================
   Autor       : Kay Schäfer
   Firma       : HHBK
   Dateiname   : eigeneBewertung.h
   Datum       : 04.06.2011
   Version     : 1.0
===============================================================================
*/


/*
   ========================================================================
   Include Dateien
   ========================================================================
*/
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
   ========================================================================
   S Q L
   ========================================================================
*/

extern MYSQL *conn;
extern MYSQL_RES *result;
extern MYSQL_ROW row;



/*
==============================================================================
   externe Variablen
==============================================================================
*/

extern char g_cSpieler1[25];
extern char g_cSpieler2[25];

/*
==============================================================================
   globale Variablen
==============================================================================
*/
float f4ge;
float fBri;
float fChe;
float fRev;
char cID[30];
char cID2[30];
char cTabelle[4][10];
char cSpalte[4][20];
char cBefehl[400];

int iVerbindung;


/*
   ========================================================================
   Funktionsprototypen
   ========================================================================
*/
void eigeneBewertungAllerSpiele(void);
void holeIDsEigeneB(void);
void kopfAusgeben(void);
void eigenebewertung(char ID[]);
void druckAusgabe(char* cSpieler);
void bewertung (float fPunkte, char[40]);




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
   externe Variaben
   ========================================================================
*/

extern char g_cSpieler1[25];
extern char g_cSpieler2[25];
extern int g_iKI;

/*
   ========================================================================
   globale Variaben
   ========================================================================
*/

char sBefehlRang[400];

char c4ge[1000][20];
char cBri[1000][20];
char cChe[1000][20];
char cRev[1000][20];

char cTabelle[4][10];
char cSpalte[4][20];

//char sTitelRang[40] = "";

int iVerbindung;
/*
   ========================================================================
   Prototypen
   ========================================================================
*/
void bewertungKomplett(void);
void rangliste(void);




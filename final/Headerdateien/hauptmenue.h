/*
===============================================================================
Autor : Monika Klein
Klasse : FA3
Dateiname : Hauptmenue.h
Datum : 26.05.2011
Beschreibung: 
Version : 1.0
===============================================================================
*/


#define _CRT_SECURE_NO_DEPRECATE 1
   /* Microsoft hat alle gängigen Ein- und Ausgabefunktionen
      als gefährlich eingestuft und durch neue Varianten ersetzt.
      Mit den neuen Funktionen sind die Programme aber nicht
      kompatible zu anderen Entwicklungsumgebungen.
      Bei Verwendung der alten Funktionen wird eine Warnung ausgegeben.
      Diese Warnung kann durch die obige Definition unterdrückt werden.
  */


/* 
===============================================================================
	Include-Anweisungen
===============================================================================
*/

#include "elo.h"
#include "Spielmenue.h"
#include "Rangliste.h"
#include "Statistik.h"
#include "EigeneBewertung.h"


/*
===============================================================================
Funktionsprototypen
===============================================================================
*/
void ausgabeHauptmenue(void);
void hauptmenue(void);
int starteLogin(int iLogout);
void zeigeGesamtStatistik(void);








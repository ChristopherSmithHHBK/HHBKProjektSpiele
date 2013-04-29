/*
============================================================================
	Autor : Richard Vrinssen
	Klasse : FA3
	Dateiname : 4Gewinnt.h
	Datum : 31.05.2011
	Beschreibung: 
	Version : 1.0
============================================================================
*/

#if !defined (VIER_GEWINNT_H)
#define VIER_GEWINNT_H
/*
===============================================================================
Include Anweisungen
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
/*
========================================================================
	Define - Variablen
========================================================================
*/
#define SPIELERLAENGE 25      // Laenge des Spielernamen
#define SPIELBRETTHOEHE 33    // Hoehe des Spielbretts(Ausgabe)
#define SPIELBRETTBREITE 52   // Breite des Spielbretts(Ausgabe)
#define SPIELFELDHOEHE 6      // Hoehe des logischen Spielfeldes
#define SPIELFELDBREITE 7     // Breite des logischen Spielfeldes
#define ZSPIELER1 'X'         // Zeichen fuer die Spielsteine von Spieler 1
#define ZSPIELER2 'O'         // Zeichen fuer die Spielsteine von Spieler 2
#define SPIELER1_FARBE "blau" // Spielerfarbe fuer Spieler1
#define SPIELER2_FARBE "rot"  // Spielerfarbe fuer Spieler2

/*
============================================================================
   externe Variaben
============================================================================
*/
extern char g_cSpieler1[SPIELERLAENGE];
extern char g_cSpieler2[SPIELERLAENGE];
extern int g_iKI;
/*
============================================================================   
	Funktionsprototypen
============================================================================
*/
float starte4Gewinnt(void);
int vorhandenGewinner(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int istSpielfeldVoll(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int setzeSpielstein(char cKoordinate,
					int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE], 
					char cAktuellerSpieler[SPIELERLAENGE], 
					char cNaechsterSpieler[SPIELERLAENGE],
					char cSpielerfarbe[10]);
void aufbereitenSpielbrett(char cBrett[SPIELBRETTHOEHE][SPIELBRETTBREITE], 
					int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
void ausgebenSpielbrett(char cBrett[SPIELBRETTHOEHE][SPIELBRETTBREITE]);
void spielfeldAusgeben(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
char sucheComputerzug(int iTiefe, int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE], 
					  int iMaxTiefe);
void entferneSpielstein(char cKoordinate, 
						int iSpielfeldKopie[SPIELFELDHOEHE][SPIELFELDBREITE]);
void initialisiereSpielfeld(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
void ausgebenWinMeldung(char cGewinner[SPIELERLAENGE], char cKoordinate);
#endif
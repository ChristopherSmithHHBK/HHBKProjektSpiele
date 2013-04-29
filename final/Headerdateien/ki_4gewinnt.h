
#if !defined (KI_VIER_GEWINNT_H)
#define KI_VIER_GEWINNT_H
 /*
============================================================================   
Praeprozessoranweisungen
 ============================================================================
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
#include <time.h>
/*
   ========================================================================
   Define - Variablen
   ========================================================================
*/
#define SPIELFELDHOEHE 6
#define SPIELFELDBREITE 7


/*
============================================================================   
Funktionsprototypen
 ============================================================================
*/
int sucheComputerZug (int iSchwierigkeit, 
					int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int kiLeicht (void);
int kiMittel (int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int kiSchwer (int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int pruefe4SteineAComputer(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int pruefe4SteineASpieler(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int pruefe4SteineISpieler(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int pruefe4SteineIComputer(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int pruefe2SteineComputer(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int pruefe2SteineSpieler(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int pruefe3SteineComputer(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);
int pruefe3SteineSpieler(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE]);

#endif
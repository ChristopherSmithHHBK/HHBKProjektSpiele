/*
============================================================================
Autor		: Tobias Niggemann
Klasse		: FA13
Dateiname	: bridges.h
Datum		: 
Beschreibung: header-Datei für bridges.c
Version		: 1
============================================================================
*/

/*
================================================================================
Include Anweisungen
================================================================================
*/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

/*
============================================================================
   externe Variaben
============================================================================
*/
extern char g_cSpieler1[25];
extern char g_cSpieler2[25];

/*
============================================================================
   globale Variaben
============================================================================
*/
char cBrettBridges[40][54]; 
float g_fReturnBridges;

/*
============================================================================
   Funktionsprototypen
============================================================================
*/
float starteBridges(void);
float fbridges(void);
void fuelleArrayBridges(void);
void ausgabeArrayBridges(void);
void aufrufHilfeBridges(void);
void erneuerFeld(void);
void beendenBridges(void);
void zeigerFarbe(int iFarbwert); 
int neustartSpiel(void);
int spielzugBridges(int iSpieler);
int pruefeBridges(char cSpieler, int iBreite, int iHoehe, int iPruefArray[][54]);
int fehlzugBridges(int iBreite, int iHoehe);
int pruefeSiegBridges(char cSpieler, int iHoehe, int iBreite);
int spielabbruch(void);




	
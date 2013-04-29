/*
===============================================================================
	Autor			: Monika Klein
	Klasse			: FA3
	Dateiname		: Login.h
	Datum			: 01.06.2011
	Version			: 1.0
	Beschreibung	: Startpunkt des Programmes.
					  Loggt die Spieler ein und lässt den ersten Spieler seinen 
					  Gegner wählen
===============================================================================
*/

/*
===============================================================================
	Präprozessoranweisungen
===============================================================================
*/
#define _CRT_SECURE_NO_DEPRECATE 1
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <my_global.h>
#include <mysql.h>


#include "hauptmenue.h"
#include "sql_anbindung.h"

/*
===============================================================================
	globale Variablen
===============================================================================
*/
MYSQL *conn;
MYSQL_RES *result;
MYSQL_ROW row;
char g_cSpieler1[25];
char g_cSpieler2[25];
char const g_cSpSymbol[2] = { 'X', 'O' };
int g_iKI = 0;
int g_iVerbunden = 0;

char g_cBenutzerID[11];
int g_iLoginOK = 0; 
/*
===============================================================================
	Funktionsprototypen
===============================================================================
*/
int spielerLogin(int iSpielerNr, int iLogout);
int gegnerWaehlen();
int starteLogin(int iLogout);
void ausgebenText(int iLogout, int iSpielerNr, int iLoginNeu, 
				int iUngueltigesZeichen, int iUngueltigerName, 
				int iBereitsEingeloggt);
int registriereBenutzer(char cSpielerNeu[]);
int benutzerInSpieleEinfuegen(char cBenutzernameSuchen[]);
int pruefePasswortchar(char cName[SPIELERLAENGE]);
void initi(void);
int eingebenNickname(char cSpielerName[SPIELERLAENGE], int iSpieler);
int login(int iSpieler);
int pruefeSpielerName(char cSpielerName1[25], char cSpielerName2[25]);
void verschluesselPasswort(char cSpielerPasswort[SPIELERLAENGE], 
				char cVerschluesseltesPasswort[SPIELERLAENGE]);


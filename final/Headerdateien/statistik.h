/*
============================================================================
	Autor		: Fabian Wunsch
	Klasse		: FA3
	Dateiname	: statistik.h
	Datum		: 31.05.2011
	Beschreibung: 
	Version		: 1.3
============================================================================
*/

/*
============================================================================   
	Praeprozessoranweisungen
=============================================================================
*/
#define _CRT_SECURE_NO_DEPRECATE 1
#include "sql_anbindung.h"
/*
============================================================================   
	externe Variablen
============================================================================
*/
extern MYSQL *conn;
extern MYSQL_RES *result;
extern MYSQL_ROW row;
extern char g_cSpieler1[25];
extern char g_cSpieler2[25];

/*
============================================================================   
	Funktionsprototypen
============================================================================
*/
void anzahlSpiele(int);
void anzahlSpieleAlle();

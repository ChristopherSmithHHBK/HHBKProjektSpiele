
#if !defined (SQL_ANBINDUNG_H)
#define SQL_ANBINDUNG_H
 /*
============================================================================   
Praeprozessoranweisungen
 ============================================================================
*/
#include <stdio.h> 
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>
/*
============================================================================   
Variablen
============================================================================
*/
extern MYSQL *conn;
extern MYSQL_RES *result;
extern MYSQL_ROW row;
extern char g_cBenutzerID[11];
/*
============================================================================   
Funktionsprototypen
 ============================================================================
*/
void ausgebenFehlermeldung(char *cText);
int verbindeDB(void);
void schliesseDB(void);
int sucheSpielerInDb(char cName[]);
void holeSQLPruefeBenutzerStatement(char cStatement[], char cName[]);
void holeSQLPruefePasswortStatement(char cStatement[], char cName[], 
									char cPasswort[]);
void holeSQLNeuerBenutzerStatement(char cStatement[], char cName[], 
									char cPasswort[]);
void holeSQLStatistikSpielStatement(char cStatement[], char cID[], 
									char cTabelle[]);
#endif
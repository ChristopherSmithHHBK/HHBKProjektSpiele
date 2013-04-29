/*
   ========================================================================
   Autor       : Vrinssen
   Firma       : HHBK
   Dateiname   : sql_anbindung.c
   Datum       : 27.05.2011
   Version     : 1.0
   Compiler	   : Visual Studio
   Programmschnittstelle: int main(void)
                          Das Programm gibt den Wert 0 oder 1 zurueck.
                          Das Programm erwartet beim Aufruf keine Argumente
   ========================================================================
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

/*
   ========================================================================
   Define - Variablen
   ========================================================================
*/

/*
   ========================================================================
   Prototypen - Definition
   ========================================================================
*/
void  schliesseDB(void);
int  verbindeDB(void);



/*
   ========================================================================
   Funktion ausgebenFehlermeldung()
   ========================================================================
*/
void ausgebenFehlermeldung(char *cText)
{
	printf("Fehler: %s\n", cText);
	system("pause");
}

/*
   ========================================================================
   Funktion:	verbindeDB()
   Return:		0 - Fehler
				1 - Erfolgreich
   ========================================================================
*/
int verbindeDB(void)
{
	// MySQL-Objekt anlegen
	if((conn = mysql_init(NULL)) == NULL)
	{
		ausgebenFehlermeldung("Datenbankobjekt kann nicht angelegt werden");
		return 0;
	}

	// MySQL-Verbindung aufbauen
	if (!mysql_real_connect(conn, "db4free.net", "spielesammlung", "gruppea", "spielesammlung", 0, NULL, 0))
	{
		ausgebenFehlermeldung("Datenbankverbindung fehlgeschlagen.");
		return 0;
	}
	return 1;
}

/*
   ========================================================================
   Funktion schliesseDB()
   ========================================================================
*/
void  schliesseDB(void)
{
	// MySQL Verbindung beenden
	mysql_close(conn);
}

/*
===============================================================================
	Funktion:		sucheSpielerInDb()
	in:				cBenutzernameSuchen[]
	out:			iBenutzerInDbGefunden
	Beschreibung:	Datenbankabfrage, ob es einen Eintrag in der Tabelle mit
					dem eingegebenen Namen gibt.
===============================================================================
*/
int sucheSpielerInDb(char cName[]){
	int iBenutzerInDbGefunden = 0;
	int iAnzahlSpalten;
	int iFehler = 0;
	char cStatement[200];
	holeSQLPruefeBenutzerStatement(cStatement, cName);

	//Überprüfung, ob Spieler bereits registriert --> Select Befehl nach Benutzername
	if(mysql_query(conn, cStatement))
	{
		ausgebenFehlermeldung("Fehler bei der Suche des Benutzernamen ");
	}

	// Ergebnisse in MYSQL_RES ablegen
	if((result= mysql_store_result(conn)) == NULL)
	{
		//printf("Test: result ist null");
		if(mysql_errno(conn))
		{
			ausgebenFehlermeldung("Ergebnis Struktur konnte nicht angelegt werden.");
			iFehler = 1;
		}
		else
			ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
	}

	if(iFehler == 0)
	{
		// Anzahl der Ergebnisspalten ermitteln
		iAnzahlSpalten= mysql_num_fields(result);

		//printf("Test: AnzahlSpalten: %i\n\n", iAnzahlSpalten);

		// Pruefe, ob ein Benutzer gefunden wurde
		if((row= mysql_fetch_row(result)))
		{
			strcpy(g_cBenutzerID, row[0]);
			return 1;
		}
	}

	return 0;
}

/*
===============================================================================
	Funktion:		holeSQLPruefeBenutzerStatement()
	in:				cStatement[], cName[]
	out:			-
	Beschreibung:	SQL-Befehl für Benutzersuche wird zusammengestellt	
===============================================================================
*/
void holeSQLPruefeBenutzerStatement(char cStatement[], char cName[25])
{
	strcpy(cStatement, "select * from benutzer where ben_name = '");
	strcat(cStatement, cName);
	strcat(cStatement, "'");
}

/*
===============================================================================
	Funktion:		holeSQLPruefePasswortStatement()
	in:				cStatement[], cName[], cPasswort[]
	out:			-
	Beschreibung:	SQL-Befehl für Passwortüberprüfung wird zusammengestellt
===============================================================================
*/
void holeSQLPruefePasswortStatement(char cStatement[], char cName[], char cPasswort[])
{
	strcpy(cStatement, "select * from benutzer where ben_name = '");
	strcat(cStatement, cName);
	strcat(cStatement, "' and ben_passwort = '");
	strcat(cStatement, cPasswort);
	strcat(cStatement, "'");
}

/*
===============================================================================
	Funktion:		holeSQLNeuerBenutzerStatement()
	in:				cStatement[], cName[], cPasswort[]
	out:			-
	Beschreibung:	SQL-Befehl für das Einfügen des Benutzers wird 
					zusammengestellt
===============================================================================
*/
void holeSQLNeuerBenutzerStatement(char cStatement[], char cName[], char cPasswort[])
{
	strcpy(cStatement, "insert into benutzer (ben_name, ben_passwort) values ('");
	strcat(cStatement, cName);
	strcat(cStatement, "','");
	strcat(cStatement, cPasswort);
	strcat(cStatement, "')");
}

/*
===============================================================================
	Funktion:		holeSQLStatistikSpielStatement()
	in:				cStatement[], cID[], cTabelle[]
	out:			-
	Beschreibung:	SQL-Befehl für Statistik wird zusammengestellt	
===============================================================================
*/
void holeSQLStatistikSpielStatement(char cStatement[], char cID[], char cTabelle[])
{
	strcpy(cStatement, "select * from ");
	strcat(cStatement, cTabelle);
	strcat(cStatement, " where ben_id = ");
	strcat(cStatement, cID);
}
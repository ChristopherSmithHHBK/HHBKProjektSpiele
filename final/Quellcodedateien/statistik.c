/*
===============================================================================
   Autor       : Fabian Wunsch
   Firma       : HHBK
   Dateiname   : statistik.c
   Datum       : 04.06.2011
   Beschreibung: Ausgabe der Statistik für die Benutzer, wie viele Spiele sie
                 gewonnen oder verloren haben oder wie viele Remis sie hatten.
   Version     : 1.0
===============================================================================
*/

/*
==============================================================================
   Include Anweisungen
==============================================================================
*/
#include "Statistik.h"

/*
===============================================================================
   Funktion:      anzahlSpiele()
   in:            fErgebnis, iSpieltyp
   out:           -
   Beschreibung:  Gibt die Spielbewertung bzgl. Anzahl der Gewonnenen, 
                  Verlorenen Spiele und Remis der jeweiligen Spiels aus.
                  Diese Funktion wird   aus dem Spielmenü aufgerufen.
===============================================================================
*/
void anzahlSpiele(int iSpieltyp)
{
   char cStatement[200];
   char cTabelle[20];
   char cGewonnen[2][5];
   char cVerloren[2][5];
   char cRemi[2][5];
   int iAnzahlSpalten;

   switch(iSpieltyp)
   {
      case 0:
         strcpy(cTabelle, "4gewinnt");
         break;
      case 1:
         strcpy(cTabelle, "bridges");
         break;
      case 2:
         strcpy(cTabelle, "checkers");
         break;
      case 3:
         strcpy(cTabelle, "reversi");
         break;
   }

   // Spieler 1
   sucheSpielerInDb(g_cSpieler1);
   holeSQLStatistikSpielStatement(cStatement, g_cBenutzerID, cTabelle);

   // Führt das Statement aus
   if(mysql_query(conn, cStatement))
   {
      ausgebenFehlermeldung("Fehler bei der Suche des Benutzernamen ");
      return;
   }

   // Ergebnisse in MYSQL_RES ablegen
   if((result= mysql_store_result(conn)) == NULL)
   {
      //printf("Test: result ist null");
      if(mysql_errno(conn))
      {
         ausgebenFehlermeldung
			 ("Ergebnis Struktur konnte nicht angelegt werden.");   
         return;
      }
      else
      {
         ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
         return;
      }
   }

   // Anzahl der Ergebnisspalten ermitteln
   iAnzahlSpalten = mysql_num_fields(result);

   // Pruefe, ob ein Benutzer gefunden wurde
   if((row= mysql_fetch_row(result)))
   {
      strcpy(cGewonnen[0], row[1]);
      strcpy(cVerloren[0], row[2]);
      strcpy(cRemi[0], row[3]);
   }

   // Spieler 2
   if (strcmp(g_cSpieler2, "COMPUTER"))
   {
      sucheSpielerInDb(g_cSpieler2);
      holeSQLStatistikSpielStatement(cStatement, g_cBenutzerID, cTabelle);

      // Führt das Statement aus
      if(mysql_query(conn, cStatement))
      {
         ausgebenFehlermeldung("Fehler bei der Suche des Benutzernamen ");
         return;
      }

      // Ergebnisse in MYSQL_RES ablegen
      if((result= mysql_store_result(conn)) == NULL)
      {
         //printf("Test: result ist null");
         if(mysql_errno(conn))
         {
            ausgebenFehlermeldung
				("Ergebnis Struktur konnte nicht angelegt werden.");   
            return;
         }
         else
         {
            ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
            return;
         }
      }

      // Anzahl der Ergebnisspalten ermitteln
      iAnzahlSpalten = mysql_num_fields(result);

      // Pruefe, ob ein Benutzer gefunden wurde
      if((row= mysql_fetch_row(result)))
      {
         strcpy(cGewonnen[1], row[1]);
         strcpy(cVerloren[1], row[2]);
         strcpy(cRemi[1], row[3]);
      }
   }

   printf("\n%24s", cTabelle);
   if (strcmp(g_cSpieler2, "COMPUTER"))
      printf("\t%24s\n", cTabelle);
   printf("\n");

   printf("\tGewonnen: %14s\t", cGewonnen[0]);
   if (strcmp(g_cSpieler2, "COMPUTER"))
      printf("\tGewonnen: %14s\t", cGewonnen[1]);
   printf("\n");

   printf("\tVerloren: %14s\t", cVerloren[0]);
   if (strcmp(g_cSpieler2, "COMPUTER"))
      printf("\tVerloren: %14s\t", cVerloren[1]);
   printf("\n");

   printf("\tRemis   : %14s\t", cRemi[0]);
   if (strcmp(g_cSpieler2, "COMPUTER"))
      printf("\tRemis   : %14s\t", cRemi[1]);
   printf("\n\t");
   system("pause");
}

/*
===============================================================================
   Funktion:      anzahlSpieleAlle()
   in:            -
   out:         -
   Beschreibung:   Gibt das Ranking der beiden Spieler für alle Spiele aus 
               bzgl. Anzahl der Gewonnenen, Verlorenen Spiele und Remis.
===============================================================================
*/
void anzahlSpieleAlle(void)
{
   system("cls");
   printf("=====================================================");
   printf("===========================");
   printf("              $$$$$$$  $$$$$     $$$   $$ $$   $$ $$ ");
   printf(" $$$   $$  $$$$$$$         ");
   printf("             $$    $$ $$  $$    $$$$  $$ $$  $$$ $$  ");
   printf("$$$$  $$  $$               ");
   printf("            $$ $$$$  $$$$$$$   $$ $$ $$ $$$$$$  $$  $");
   printf("$ $$ $$  $$ $$$$           ");      
   printf("           $$   $$  $$    $$  $$  $$$$ $$  $$  $$  $$");
   printf("  $$$$  $$    $$           ");
   printf("          $$    $$ $$     $$ $$   $$$ $$   $$ $$  $$ ");
   printf("  $$$   $$$$$$$            ");
   printf("=====================================================");
   printf("===========================");

   printf("%24s", g_cSpieler1);

   if (strcmp(g_cSpieler2, "COMPUTER"))
   {
      printf("%24s", g_cSpieler2);
   }
   printf("\n");

   anzahlSpiele(0);
   anzahlSpiele(1);
   anzahlSpiele(2);
   anzahlSpiele(3);
}
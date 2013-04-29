/*
===============================================================================
   Autor       : Kay Schäfer
   Firma       : HHBK
   Dateiname   : eigeneBewertung.c
   Datum       : 04.06.2011
   Beschreibung: Gibt die eigene Punktebewertung der Spieler aus bzw. aller      
                 Spieler für alle Spiele aus
   Version     : 1.0
===============================================================================
*/

/*
==============================================================================
Include Anweisungen
==============================================================================
*/

#include "EigeneBewertung.h"

/*
===============================================================================
   Funktion:      eigeneBewertungAllerSpiele()
   in:            -
   out:           -
   Beschreibung:  Steuert die Anzeige der Statistikausgabe der eigenen 
                  Punktebewertungen.
===============================================================================
*/
void eigeneBewertungAllerSpiele(void) 
{
   system("cls");

   holeIDsEigeneB();
   kopfAusgeben();
   eigenebewertung(cID);
   druckAusgabe(g_cSpieler1);

   if(strcmp(g_cSpieler2, "COMPUTER"))
   {
      eigenebewertung(cID2);
      druckAusgabe(g_cSpieler2); 
   }
   printf("\t");
   system("pause");
}


/*
===============================================================================
   Funktion:      holeIDsEigeneB()
   in:            -
   out:           -
   Beschreibung:  Benutzer-ID aus der Tabelle „Benutzer“ der beiden Spieler          
                  auslesen (SQL-Abfragen).
===============================================================================
*/
void holeIDsEigeneB(void)
{
   // ID von Spieler 1 erfragen

   strcpy(cBefehl,"SELECT ben_id FROM benutzer WHERE ben_name = '");

   strcat(cBefehl, g_cSpieler1);
   strcat(cBefehl, "'");

    if(mysql_query(conn, cBefehl))
    {
        ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
    }
    else if((result = mysql_store_result(conn)) == NULL)
    {
        if(mysql_errno(conn))
        {
         ausgebenFehlermeldung
			 ("Ergebnis Struktur konnte nicht angelegt werden.");
        }
        else
        {
         ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
        }
    }

    while((row= mysql_fetch_row(result)))
    {
        strcpy(cID, row[0]);
    }

    // ID von Spieler 2 erfragen, wenn Spieler nicht Computer

   if(strcmp(g_cSpieler2, "COMPUTER"))
   {
      strcpy(cBefehl,"SELECT ben_id FROM benutzer WHERE ben_name = '");

      strcat(cBefehl, &g_cSpieler2[0]);
      strcat(cBefehl, "'");


      if(mysql_query(conn, cBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }
      else if((result = mysql_store_result(conn)) == NULL)
      {
         if(mysql_errno(conn))
         {
            ausgebenFehlermeldung
				("Ergebnis Struktur konnte nicht angelegt werden.");
         }
         else
         {
            ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
         }
      }

      while((row= mysql_fetch_row(result)))
      {
         strcpy(cID2, row[0]);
      }
   }
}

/*
===============================================================================
   Funktion:      kopfAusgeben()
   in:            -
   out:           -
   Beschreibung:  Gibt die Überschrift aus
===============================================================================
*/
void kopfAusgeben(void)
{
   printf("=================================================================");
   printf("===============");
   printf("              $$$$$$$  $$$$$     $$$   $$ $$   $$ $$  $$$   $$  $");
   printf("$$$$$$         ");
   printf("             $$    $$ $$  $$    $$$$  $$ $$  $$$ $$  $$$$  $$  $$");
   printf("               ");
   printf("            $$ $$$$  $$$$$$$   $$ $$ $$ $$$$$$  $$  $$ $$ $$  $$ ");
   printf("$$$$           ");      
   printf("           $$   $$  $$    $$  $$  $$$$ $$  $$  $$  $$  $$$$  $$  ");
   printf("  $$           ");
   printf("          $$    $$ $$     $$ $$   $$$ $$   $$ $$  $$   $$$   $$$$");
   printf("$$$            ");
   printf("=================================================================");
   printf("===============");
}
 
/*
===============================================================================
   Funktion:      eigenebewertung()
   in:            ID[]
   out:           -
   Beschreibung:  Liest aus den Spieletabellen für den Benutzer die 
                  Punktebewertung der Spiele aus
===============================================================================
*/
void eigenebewertung(char ID[])
{
   // 4 Gewinnt Punktezahl

   strcpy(cBefehl, "SELECT 4ge_bewertung from 4gewinnt where ben_id = ");
   strcat(cBefehl, ID);
   iVerbindung = verbindeDB();
      if(mysql_query(conn, cBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }
      else if((result = mysql_store_result(conn)) == NULL)
      {
         if(mysql_errno(conn))
         {
            ausgebenFehlermeldung("Ergebnis Struktur konnte nicht angelegt werden.");
         }
         else
         {
            ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
         }
      }

      while((row= mysql_fetch_row(result)))
      {
         f4ge = (float) atof(row[0]);
      }
   


   // Bridges Punktezahl

   strcpy(cBefehl, "SELECT bri_bewertung from bridges where ben_id = ");
   strcat(cBefehl, ID);
      if(mysql_query(conn, cBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }
      else if((result = mysql_store_result(conn)) == NULL)
      {
         if(mysql_errno(conn))
         {
            ausgebenFehlermeldung
				("Ergebnis Struktur konnte nicht angelegt werden.");
         }
         else
         {
            ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
         }
      }

      while((row= mysql_fetch_row(result)))
      {
         fBri = (float) atof(row[0]);
      }
  


   // Checkers Punktezahl

   strcpy(cBefehl, "SELECT che_bewertung from checkers where ben_id = ");
   strcat(cBefehl, ID);
      if(mysql_query(conn, cBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }
      else if((result = mysql_store_result(conn)) == NULL)
      {
         if(mysql_errno(conn))
         {
            ausgebenFehlermeldung(
				"Ergebnis Struktur konnte nicht angelegt werden.");
         }
         else
         {
            ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
         }
      }

      while((row= mysql_fetch_row(result)))
      {
         fChe = (float) atof(row[0]);
      }
   

   // Reversi Punktezahl

   strcpy(cBefehl, "SELECT rev_bewertung from reversi where ben_id = ");
   strcat(cBefehl, ID);
      if(mysql_query(conn, cBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }
      else if((result = mysql_store_result(conn)) == NULL)
      {
         if(mysql_errno(conn))
         {
            ausgebenFehlermeldung
				("Ergebnis Struktur konnte nicht angelegt werden.");
         }
         else
         {
            ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
         }
      }

      while((row= mysql_fetch_row(result)))
      {
         fRev = (float) atof(row[0]);
      }
}


/*
===============================================================================
   Funktion:      druckAusgabe()
   in:            cSpieler
   out:           -
   Beschreibung:  Ausgabeaufbereitung
===============================================================================
*/
void druckAusgabe(char* cSpieler)
{
   char cTitel1[40];
   char cTitel2[40];
   char cTitel3[40];
   char cTitel4[40];
   bewertung(f4ge, cTitel1);
   bewertung(fBri, cTitel2);
   bewertung(fChe, cTitel3);
   bewertung(fRev, cTitel4);
   printf("Spieler :\t%s\n4 Gewinnt:\t%8.2f\t%s\n",cSpieler, f4ge, cTitel1);
   printf("Bridges:\t%8.2f\t%s\nCheckers:\t%8.2f\t", fBri, cTitel2, fChe);
   printf("%s\n", cTitel3);
   printf("Reversi:\t%8.2f\t%s\n\n\n", fRev, cTitel4);
}

/*
===============================================================================
   Funktion:      bewertung()
   in:            fPunkte, sTitel[]
   out:           -
   Beschreibung:  Bewertung der Spieler wird ermittelt  Ranking
===============================================================================
*/
void bewertung (float fPunkte, char sTitel[40])
{
   strcpy(sTitel,"");
//   fPunkte = 2345;

   if (fPunkte < 1000.0)
   {
      strcpy(sTitel, "Anfaenger");
   }
   if (1000.0 <= fPunkte && fPunkte <= 1199.0)
   {
      strcpy(sTitel, "Gelegenheitsspieler");
   }
   if (1200.0 <= fPunkte && fPunkte <= 1399.0)
   {
      strcpy(sTitel, "durchschnittlicher Hobbyspieler");
   }
   if (1400.0 <= fPunkte && fPunkte <= 1599.0)
   {
      strcpy(sTitel, " Ueberdurchschnittlicher Spieler");
   }
   if (1600.0 <= fPunkte && fPunkte <= 1799.0)
   {
      strcpy(sTitel, "starker Freizeitspieler");
   }
   if (1800.0 <= fPunkte && fPunkte <= 1999.0)
   {
      strcpy(sTitel, "sehr guter Vereinsspieler");
   }
   if (2000.0 <= fPunkte && fPunkte <= 2099.0)
   {
      strcpy(sTitel, "Experte");
   }
   if (2100.0 <= fPunkte && fPunkte <= 2199.0)
   {
      strcpy(sTitel, "Meisteranwärter");
   }
   if (2200.0 <= fPunkte && fPunkte <= 2299.0)
   {
      strcpy(sTitel, "Candidate Master");
   }
   if (2300.0 <= fPunkte && fPunkte <= 2399.0)
   {
      strcpy(sTitel, "Meister");
   }
   if (2400.0 <= fPunkte && fPunkte <= 2499.0)
   {
      strcpy(sTitel, "Internationaler Meister");
   }
   if (2500.0 <= fPunkte && fPunkte <= 2699.0)
   {
      strcpy(sTitel, "Grossmeister");
   }
   if (fPunkte >= 2700.0)
   {
      strcpy(sTitel, "Super-Grossmeister");
   }
}


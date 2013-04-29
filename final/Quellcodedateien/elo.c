/*
===============================================================================
   Autor       : Kay Schäfer
   Firma       : HHBK
   Dateiname   : elo.c
   Datum       : 04.06.2011
   Beschreibung: Berechnung der ELO Punktebewertung für ein gewonnenes, 
				 verlorenes oder unentschiedenes Spiel
   Version     : 1.0
===============================================================================
*/

/*
==============================================================================
   Include Anweisungen
==============================================================================
*/

#include "Elo.h"

/*
===============================================================================
   Funktion:		zeigeStatistikNachSpielende()
   in:				fErgebnis, iSpieltyp
   out:				-
   Beschreibung:    Steuert die Statistikanzeige nach dem Spiel und die 
                    Berechnung der Punkte
===============================================================================
*/
void zeigeStatistikNachSpielende(float fErgebnis, int iSpieltyp)
{
   strcpy(sBefehl, "");

   vorbereitung(iSpieltyp);
   holeIDs();
   elo(fErgebnis,iSpieltyp);
   schreibeinDatenbank(fErgebnis, iSpieltyp);

   printf("\t");
   system("pause");
}

/*
===============================================================================
   Funktion:      vorbereitung()
   in:            iSpieltyp
   out:           -
   Beschreibung:  Initialisiert alle nötigen Parameter.
===============================================================================
*/
void vorbereitung (int iSpieltyp)
{
   strcpy(cTabelleElo[0], "4gewinnt");
   strcpy(cTabelleElo[1], "bridges");
   strcpy(cTabelleElo[2], "checkers");
   strcpy(cTabelleElo[3], "reversi");

   switch(iSpieltyp)
   {
   case 0:
      strcpy(cSpalte[0], "4ge_partien");
      strcpy(cSpalte[1], "4ge_bewertung");
      strcpy(cSpalte[2], "4ge_gewonnen");
      strcpy(cSpalte[3], "4ge_verloren");
      strcpy(cSpalte[4], "4ge_unentschieden");
   break;

   case 1:
      strcpy(cSpalte[0], "bri_partien");
      strcpy(cSpalte[1], "bri_bewertung");
      strcpy(cSpalte[2], "bri_gewonnen");
      strcpy(cSpalte[3], "bri_verloren");
      strcpy(cSpalte[4], "bri_unentschieden");
   break;

   case 2:
      strcpy(cSpalte[0], "che_partien");
      strcpy(cSpalte[1], "che_bewertung");
      strcpy(cSpalte[2], "che_gewonnen");
      strcpy(cSpalte[3], "che_verloren");
      strcpy(cSpalte[4], "che_unentschieden");
   break;

   case 3:
      strcpy(cSpalte[0], "rev_partien");
      strcpy(cSpalte[1], "rev_bewertung");
      strcpy(cSpalte[2], "rev_gewonnen");
      strcpy(cSpalte[3], "rev_verloren");
      strcpy(cSpalte[4], "rev_unentschieden");
   break;

    default:
      printf("Ungültiger Spieltyp-Parameter!");
    break;

   }
}

/*
===============================================================================
   Funktion:      holeIDs()
   in:            -
   out:           -
   Beschreibung:  Benutzer-ID aus der Tabelle „Benutzer“ der beiden Spieler 
                  auslesen (SQL-Abfragen)
===============================================================================
*/
void holeIDs(void)
{
   // ID von Spieler 1 erfragen

   strcpy(sBefehl,"SELECT ben_id FROM benutzer WHERE ben_name = '");

   strcat(sBefehl, &g_cSpieler1[0]);
   strcat(sBefehl, "'");

   iVerbindung = verbindeDB();
   if(iVerbindung == 1)
   {
      if(mysql_query(conn, sBefehl))
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
   }

      // ID von Spieler 2 erfragen, wenn Spieler nicht Computer

   if(strcmp(g_cSpieler2, "COMPUTER"))
   {
      strcpy(sBefehl,"SELECT ben_id FROM benutzer WHERE ben_name = '");

      strcat(sBefehl, &g_cSpieler2[0]);
      strcat(sBefehl, "'");

      iVerbindung = verbindeDB();
      if(iVerbindung == 1)
      {
         if(mysql_query(conn, sBefehl))
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
}

/*
===============================================================================
   Funktion:      elo()
   in:            fErgebnis, iSpieltyp
   out:           -
   Beschreibung:  Liest die Partienzahl der eingeloggten Spieler aus der       
                  Tabelle und erhöht diese nach gespieltem Spiel.
                  Außerdem berechnet diese Funktion die Punkte nach ELO und 
                  schreibt das neue Ergebnis in die Tabellen.
===============================================================================
*/
void elo (float fErgebnis, int iSpieltyp)
{
   float fErgebnisS2;

   float fBewertungS1;
   float fBewertungS2;

   float fErwartetesErgebnis;
   float fBewertungsdifferenz;

   int iFaktorS1;
   int iFaktorS2;

   char sDruckErgebnis[3][9];

   int iDruckArraySwitchS1;
   int iDruckArraySwitchS2;

   int iPartienS1;
   int iPartienS2;
   
   // S Q L

   verbindeDB();

   // Partienzahl Spieler 1

   strcpy(sBefehl, "SELECT ");
   strcat(sBefehl, cSpalte[0]);
   strcat(sBefehl, " from ");
   strcat(sBefehl, cTabelleElo[iSpieltyp]);
   strcat(sBefehl, " WHERE ben_id = ");
   strcat(sBefehl, cID);
      
   if(mysql_query(conn, sBefehl))
   {
      ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
   }
   if((result = mysql_store_result(conn)) == NULL)
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
      iPartienS1 = atoi(row[0]); 
   }

// Partienzahl Spieler 2
   if(strcmp(g_cSpieler2, "COMPUTER"))
   {
      strcpy(sBefehl, "SELECT ");
      strcat(sBefehl, cSpalte[0]);
      strcat(sBefehl, " from ");
      strcat(sBefehl, cTabelleElo[iSpieltyp]);
      strcat(sBefehl, " WHERE ben_id = ");
      strcat(sBefehl, cID2);
      
      if(mysql_query(conn, sBefehl))
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
         iPartienS2 = atoi(row[0]); 
      }
   }
   else
   {
      switch(g_iKI)
      {
      case 1:
         iPartienS2 = 10;
      break;

      case 2:
         iPartienS2 =300;
      break;

      case 3:
         iPartienS2 =300;
      break;
      }
   }
   


   // Bewertung Spieler 1

   strcpy(sBefehl, "SELECT ");
   strcat(sBefehl, cSpalte[1]);
   strcat(sBefehl, " from ");
   strcat(sBefehl, cTabelleElo[iSpieltyp]);
   strcat(sBefehl, " WHERE ben_id = ");
   strcat(sBefehl, cID);
      
   if(mysql_query(conn, sBefehl))
   {
      ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
   }
   if((result = mysql_store_result(conn)) == NULL)
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
      fBewertungS1 = (float) atof(row[0]); 
   }

   // Bewertung Spieler 2


   if(strcmp(g_cSpieler2, "COMPUTER"))
   {
      strcpy(sBefehl, "SELECT ");
      strcat(sBefehl, cSpalte[1]);
      strcat(sBefehl, " from ");
      strcat(sBefehl, cTabelleElo[iSpieltyp]);
      strcat(sBefehl, " WHERE ben_id = ");
      strcat(sBefehl, cID2);
      
      if(mysql_query(conn, sBefehl))
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
         fBewertungS2 = (float) atof(row[0]); 
      }
   }
   else
   {
      switch(g_iKI)
      {
         case 1:
            fBewertungS2 = 1400.0;
         break;

         case 2:
            fBewertungS2 = 2300.0;
         break;

         case 3:
            fBewertungS2 = 2300.0;
         break;
      }
   }
   
   // Druckarray initialisieren

   strcpy(sDruckErgebnis[0], "Verloren");
   strcpy(sDruckErgebnis[1], "Gewonnen");
   strcpy(sDruckErgebnis[2], "Remis!  ");

   /* Bewertungsdifferenz Bdelta
   */
   fBewertungsdifferenz = fBewertungS2-fBewertungS1;

   /* Ergebis Spieler 2 ermitteln
   */

   if(fErgebnis == 1)
   {
      fErgebnisS2 = 0;
   }
   else
   {
      if(fErgebnis == 0)
      {
         fErgebnisS2 = 1;
      }
      else
      {
         fErgebnisS2 = 0.5;
      }
   }


   /* Berechnung erwartetes Ergebnis Ea
   */

   if (fBewertungsdifferenz > 400 || fBewertungsdifferenz < -400)
   {
      fErwartetesErgebnis = (float) (1.0/11.0);
   }
   else 
   {
      fErwartetesErgebnis = 
		  (float) (1.0/(1.0+(pow(10.0,(fBewertungsdifferenz)/400.0))));
   }

   /* Berechnung faktor k Spieler 1
   */

   if (fBewertungS1 > 2400)
   {
      iFaktorS1 = 10;
   }
   else
   {
      if    (iPartienS1 < 30)
      {
         iFaktorS1 = 25;
      }
      else
      {
         iFaktorS1 = 15;
      }
   }

   /* Berechnung faktor k Spieler 2
   */

   if (fBewertungS2 > 2400)
   {
      iFaktorS2 = 10;
   }
   else
   {
      if    (iPartienS2 < 30)
      {
         iFaktorS2 = 25;
      }
      else
      {
         iFaktorS2 = 15;
      }
   }

// Neue Bewertung S1 berechnen

   fBewertungS1neu = fBewertungS1+(iFaktorS1*(fErgebnis-fErwartetesErgebnis));

// Neue Bewertung S2 berechnen

   fBewertungS2neu = 
	   fBewertungS2+(iFaktorS2*(fErgebnisS2-fErwartetesErgebnis));

// Druckaufbereitung der Ergebnisse

   if(fErgebnis == 1)
   {
      iDruckArraySwitchS1 = 1;
      iDruckArraySwitchS2 = 0;
   }
   else
   {
      if(fErgebnis == 0)
      {
         iDruckArraySwitchS1 = 0;
         iDruckArraySwitchS2 = 1;
      }
      else
      {
         if(fErgebnis == 0.5)
         {
            iDruckArraySwitchS1 = 2;
            iDruckArraySwitchS2 = 2;
         }
      }
   }   


   // Ausgabe
   system("cls");
   printf("\n");
   printf("\tAlter Punktestand %s:\t%6.2f \n", g_cSpieler1, fBewertungS1); 
   printf("\tSpielausgang:\t\t\t%s \n", sDruckErgebnis[iDruckArraySwitchS1]);
   printf("\tNeuer Punktestand:\t\t%6.2f \n", fBewertungS1neu);
   printf("\tRang:\t\t\t\t");
   bewertungElo(fBewertungS1neu);

   if(strcmp(g_cSpieler2, "COMPUTER"))
   {
      printf("\n\n");
      printf("\tAlter Punktestand %s:\t%6.2f \n", g_cSpieler2, fBewertungS2); 
      printf("\tSpielausgang:\t\t\t%s \n", sDruckErgebnis[iDruckArraySwitchS2]);
      printf("\tNeuer Punktestand:\t\t%6.2f \n", fBewertungS2neu);
      printf("\tRang:\t\t\t\t");
      bewertungElo(fBewertungS2neu);
   }
}


/*
===============================================================================
   Funktion:      bewertungElo()
   in:            fPunkte
   out:           -
   Beschreibung:  Es wird nach dem Punktestand ein Ranking erstellt, wo dem       
                  Spieler, je nach Punktestand, eine Bewertung gegeben    
                  wird.
===============================================================================
*/
void bewertungElo(float fPunkte)
{
   char  sBewertung[40] = "";
   
//   fPunkte = 2345;

   if (fPunkte < 1000)
   {
      strcpy(sBewertung, "Anfaenger");
   }
   if (1000 <= fPunkte && fPunkte && fPunkte <= 1199)
   {
      strcpy(sBewertung, "Gelegenheitsspieler");
   }
   if (1200 <= fPunkte && fPunkte <= 1399)
   {
      strcpy(sBewertung, "durchschnittlicher Hobbyspieler");
   }
   if (1400 <= fPunkte && fPunkte <= 1599)
   {
      strcpy(sBewertung, "überdurchschnittlicher Spieler");
   }
   if (1600 <= fPunkte && fPunkte <= 1799)
   {
      strcpy(sBewertung, "starker Freizeitspieler");
   }
   if (1800 <= fPunkte && fPunkte <= 1999)
   {
      strcpy(sBewertung, "sehr guter Vereinsspieler");
   }
   if (2000 <= fPunkte && fPunkte <= 2099)
   {
      strcpy(sBewertung, "Experte");
   }
   if (2100 <= fPunkte && fPunkte <= 2199)
   {
      strcpy(sBewertung, "Meisteranwärter");
   }
   if (2200 <= fPunkte && fPunkte <= 2299)
   {
      strcpy(sBewertung, "Candidate Master");
   }
   if (2300 <= fPunkte && fPunkte <= 2399)
   {
      strcpy(sBewertung, "Meister");
   }
   if (2400 <= fPunkte && fPunkte <= 2499)
   {
      strcpy(sBewertung, "Internationaler Meister");
   }
   if (2500 <= fPunkte && fPunkte <= 2699)
   {
      strcpy(sBewertung, "Grossmeister");
   }
   if (fPunkte >= 2700)
   {
      strcpy(sBewertung, "Super-Grossmeister");
   }

   printf("%s\n", sBewertung);
}


/*
===============================================================================
   Funktion:      schreibeinDatenbank()
   in:            fErgebnis, iSpieltyp
   out:           -
   Beschreibung:  Die Bewertungen und die Anzahl der Partien, sowie die       
                  Anzahl der Gewonnen bzw. Verlorenen Spiele und der Remis       
                  werden in die Datenbank geschrieben.
===============================================================================
*/
void schreibeinDatenbank (float fErgebnis, int iSpieltyp)
{
   char cBewertungS1[40];
   char cBewertungS2[40];

   sprintf(cBewertungS1, "%f", fBewertungS1neu);
   sprintf(cBewertungS2, "%f", fBewertungS2neu);
/*
   ========================================================================
   Bewertung Spieler 1 in Datenbank schreiben
   ========================================================================
*/
   strcpy(sBefehl, "UPDATE ");
   strcat(sBefehl, cTabelleElo[iSpieltyp]);
   strcat(sBefehl, " SET ");
   strcat(sBefehl, cSpalte[1]);
   strcat(sBefehl, " = ");
   strcat(sBefehl, cBewertungS1);
   strcat(sBefehl, " WHERE ben_id = ");
   strcat(sBefehl, cID);
      
   if(mysql_query(conn, sBefehl))
   {
      ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
   }

/*
   ========================================================================
   Bewertung Spieler 2 in Datenbank schreiben, wenn nicht Computer
   ========================================================================
*/

   if(strcmp(g_cSpieler2, "COMPUTER"))
   {
      strcpy(sBefehl, "UPDATE ");
      strcat(sBefehl, cTabelleElo[iSpieltyp]);
      strcat(sBefehl, " SET ");
      strcat(sBefehl, cSpalte[1]);
      strcat(sBefehl, " = ");
      strcat(sBefehl, cBewertungS2);
      strcat(sBefehl, " WHERE ben_id = ");
      strcat(sBefehl, cID2);
      
      if(mysql_query(conn, sBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }
   }

/*
   ========================================================================
   Partiezahl Spieler 1 erhöhen und in Datenbank schreiben
   ========================================================================
*/
   strcpy(sBefehl, "UPDATE ");
   strcat(sBefehl, cTabelleElo[iSpieltyp]);
   strcat(sBefehl, " SET ");
   strcat(sBefehl, cSpalte[0]);
   strcat(sBefehl, " = ");
   strcat(sBefehl, cSpalte[0]);
   strcat(sBefehl, " + 1 ");
   strcat(sBefehl, " WHERE ben_id = ");
   strcat(sBefehl, cID);
      
   if(mysql_query(conn, sBefehl))
   {
      ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
   }

/*
   ========================================================================
   Partiezahl Spieler 2 erhöhen und in Datenbank schreiben, 
   wenn nicht Computer
   ========================================================================
*/
   if(strcmp(g_cSpieler2, "COMPUTER"))
   {
      strcpy(sBefehl, "UPDATE ");
      strcat(sBefehl, cTabelleElo[iSpieltyp]);
      strcat(sBefehl, " SET ");
      strcat(sBefehl, cSpalte[0]);
      strcat(sBefehl, " = ");
      strcat(sBefehl, cSpalte[0]);
      strcat(sBefehl, " + 1 ");
      strcat(sBefehl, " WHERE ben_id = ");
      strcat(sBefehl, cID2);
      
      if(mysql_query(conn, sBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }
   }

   /*
   ========================================================================
   Gewinnzahl Spieler 1 verändern und in Datenbank schreiben
   ========================================================================
*/
   if(fErgebnis == 1.0)
   {
      strcpy(sBefehl, "UPDATE ");
      strcat(sBefehl, cTabelleElo[iSpieltyp]);
      strcat(sBefehl, " SET ");
      strcat(sBefehl, cSpalte[2]);
      strcat(sBefehl, " = ");
      strcat(sBefehl, cSpalte[2]);
      strcat(sBefehl, " + 1 ");
      strcat(sBefehl, " WHERE ben_id = ");
      strcat(sBefehl, cID);
         
      if(mysql_query(conn, sBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }

      
   }

   if(fErgebnis == 0.0)
   {
      strcpy(sBefehl, "UPDATE ");
      strcat(sBefehl, cTabelleElo[iSpieltyp]);
      strcat(sBefehl, " SET ");
      strcat(sBefehl, cSpalte[3]);
      strcat(sBefehl, " = ");
      strcat(sBefehl, cSpalte[3]);
      strcat(sBefehl, " + 1 ");
      strcat(sBefehl, " WHERE ben_id = ");
      strcat(sBefehl, cID);
         
      if(mysql_query(conn, sBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }
   }

   if(fErgebnis == 0.5)
   {
      strcpy(sBefehl, "UPDATE ");
      strcat(sBefehl, cTabelleElo[iSpieltyp]);
      strcat(sBefehl, " SET ");
      strcat(sBefehl, cSpalte[4]);
      strcat(sBefehl, " = ");
      strcat(sBefehl, cSpalte[4]);
      strcat(sBefehl, " + 1 ");
      strcat(sBefehl, " WHERE ben_id = ");
      strcat(sBefehl, cID);
         
      if(mysql_query(conn, sBefehl))
      {
         ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
      }
   }

/*
   ========================================================================
   Gewinnzahl Spieler 2 verändern und in Datenbank schreiben
   ========================================================================
*/
   if(strcmp(g_cSpieler2, "COMPUTER"))
   {
      if(fErgebnis == 1.0){
         strcpy(sBefehl, "UPDATE ");
         strcat(sBefehl, cTabelleElo[iSpieltyp]);
         strcat(sBefehl, " SET ");
         strcat(sBefehl, cSpalte[2]);
         strcat(sBefehl, " = ");
         strcat(sBefehl, cSpalte[2]);
         strcat(sBefehl, " + 1 ");
         strcat(sBefehl, " WHERE ben_id = ");
         strcat(sBefehl, cID2);
            
         if(mysql_query(conn, sBefehl))
         {
            ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
         }
      }

      if(fErgebnis == 0.0)
      {
         strcpy(sBefehl, "UPDATE ");
         strcat(sBefehl, cTabelleElo[iSpieltyp]);
         strcat(sBefehl, " SET ");
         strcat(sBefehl, cSpalte[3]);
         strcat(sBefehl, " = ");
         strcat(sBefehl, cSpalte[3]);
         strcat(sBefehl, " + 1 ");
         strcat(sBefehl, " WHERE ben_id = ");
         strcat(sBefehl, cID2);
            
         if(mysql_query(conn, sBefehl))
         {
            ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
         }
      }

      if(fErgebnis == 0.5)
      {
         strcpy(sBefehl, "UPDATE ");
         strcat(sBefehl, cTabelleElo[iSpieltyp]);
         strcat(sBefehl, " SET ");
         strcat(sBefehl, cSpalte[4]);
         strcat(sBefehl, " = ");
         strcat(sBefehl, cSpalte[4]);
         strcat(sBefehl, " + 1 ");
         strcat(sBefehl, " WHERE ben_id = ");
         strcat(sBefehl, cID2);
            
         if(mysql_query(conn, sBefehl))
         {
            ausgebenFehlermeldung("SQL Anfrage fehlgeschlagen");
         }
      }
   }
}
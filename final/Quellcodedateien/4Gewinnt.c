/*
===============================================================================
   Autor       : Vrinssen
   Firma       : FA13
   Dateiname   : 4gewinnt.c
   Datum       : 01.05.2011
   Version     : 1.0
   Compiler	   : Visual Studio
   Programmschnittstelle: int starte4Gewinnt(void)
===============================================================================
*/

/*
==============================================================================
Include Anweisungen
==============================================================================
*/
#include "4Gewinnt.h"
#include "ki_4gewinnt.h"

/*
===============================================================================
   Funktion vierGewinnt()
   Diese Funktion beinhaltet den Spielablauf von 4-Gewinnt
   In: -
   Out: -1 - Spielabbruch
		 0 - Spieler 1 hat verloren, Spieler 2 hat gewonnen
	   0,5 - Unentschiedenes Spiel
	     1 - Spieler 1 hat gewonnen, Spieler 2 hat verloren
===============================================================================
*/
float starte4Gewinnt(void)
{
   // ein Ausgabefeld ist 5*7 Zeichen groß +
   // 2 Zeilen und Spalten für die Legende
   char cBrett[SPIELBRETTHOEHE][SPIELBRETTBREITE];
   // ein logisches Spielfeld, auf dem alle Pruefungen
   //und Funktionen ausgefuehrt werden
   int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE];
   char cAktuellerSpieler[SPIELERLAENGE];
   char cNaechsterSpieler[SPIELERLAENGE];
   // temporaere Spielervariable fuer den Spielerwechsel
   char cTempSpieler[SPIELERLAENGE];
   char cGewinner[SPIELERLAENGE];
   char cKoordinate;
   char cSpielerfarbe[10];
   // Variable fuer den Rueckgabewert der Funktion setzeSpielstein
   int iSetzeSpielstein;
   int iSpielende;

   char cComputerKoordinate;

   // Initialisieren der noetigen Variablen:
   // - fuelle Spielervariablen
   // - setze Gewinner auf '\0'
   // - setze Spielende auf 0
   // - setze Spielstein auf 0 fuer ersten Durchlauf
   // - initialisiere und bereite Spielfeld auf
   // - setze Computereinwurfkoordinate auf 'a'
   // - setze Spielerfarbe fuer den 1ten Spieler
   strcpy(cAktuellerSpieler, g_cSpieler1);
   strcpy(cNaechsterSpieler, g_cSpieler2);
   strcpy(cSpielerfarbe, SPIELER1_FARBE);
   cGewinner[0] = '\0';
   iSpielende = 0;
   iSetzeSpielstein = 0;
   initialisiereSpielfeld(iSpielfeld);
   aufbereitenSpielbrett(cBrett, iSpielfeld);
   cComputerKoordinate = 'a';

   do
   {
      system("cls");
      ausgebenSpielbrett(cBrett);
      printf("\n");
      // Auswahl des Textausgabe, Spielstein einwerfen,
      // falsche Spalte, Spalte voll
      switch(iSetzeSpielstein)
      {
         case 0:
         case 3:
            printf("          %s(%s), wo moechten Sie den Spielstein einwerfen?\n",
                  cAktuellerSpieler, cSpielerfarbe);
            break;
         case 1:
            printf("          %s(%s), Sie ", cAktuellerSpieler, cSpielerfarbe);
            printf("haben eine falsche Spalte angegeben,\n");
            printf("bitte wiederholen Sie die Eingabe.\n");
            break;
         case 2:
            printf("          %s(%s), die ", cAktuellerSpieler, cSpielerfarbe);
            printf("Spalte ist voll, bitte waehlen Sie eine andere.\n");
            break;
         case 4:
            system("cls");
            initialisiereSpielfeld(iSpielfeld);
            strcpy(cAktuellerSpieler, g_cSpieler1);
            strcpy(cSpielerfarbe, SPIELER1_FARBE);
            aufbereitenSpielbrett(cBrett, iSpielfeld);
            ausgebenSpielbrett(cBrett);
            printf("          Spiel neugestartet\n");
            printf("          %s(%s), wo ", cAktuellerSpieler, cSpielerfarbe);
            printf("moechten Sie den Spielstein einwerfen?\n");
            break;
         default:
            printf("          Nicht erklaerbarer Fehler an der Stelle: ");
            printf("          Koordinateneingabe-SetzeSpielstein!\n");
      }
      // Eingabe der Koordinate
      if(!strcmp(cAktuellerSpieler, "COMPUTER") == 0)
      {
         // Bei Spielerzug
         printf("          Spalte:");
		 fflush(stdin);
         scanf("%c", &cKoordinate);
         fflush(stdin);
         iSetzeSpielstein = setzeSpielstein(cKoordinate, iSpielfeld,
                              cAktuellerSpieler, cNaechsterSpieler,
							  cSpielerfarbe);
      }
      else
      {
         // Bei Computerzug
         iSetzeSpielstein = setzeSpielstein(cComputerKoordinate+
                           sucheComputerZug(g_iKI, iSpielfeld),
                           iSpielfeld, cAktuellerSpieler,
                           cNaechsterSpieler, cSpielerfarbe);
      }


      // Wenn Spielstein richtig gesetzt, dann arbeite weiter,
      // ansonste wiederhole Eingabe
      if(iSetzeSpielstein == 0)
      {
         aufbereitenSpielbrett(cBrett, iSpielfeld);
         // Wenn Spielfeld voll, setze Gewinner auf '\0' und Abbruch
         if(istSpielfeldVoll(iSpielfeld) == 1)
         {
            iSetzeSpielstein = -1;
            cGewinner[0] = '\0';
         }
         // Wenn Gewinner vorhanden, egal ob Spielfeld voll oder nicht,
         // setze aktuellen Spieler als Gewinner und Abbruch
         // Ansonsten Spielerwechsel
         if(vorhandenGewinner(iSpielfeld) == 1)
         {
            // setze Gewinner und Endeflag
            strcpy(cGewinner, cAktuellerSpieler);
            iSetzeSpielstein = -1;
         }
         else
         {
            // Spielerwechsel
            strcpy(cTempSpieler, cAktuellerSpieler);
            strcpy(cAktuellerSpieler, cNaechsterSpieler);
            strcpy(cNaechsterSpieler, cTempSpieler);
			if(strcmp(cAktuellerSpieler, g_cSpieler2) == 0)
			{
               strcpy(cSpielerfarbe, SPIELER2_FARBE);
			}
			else
			{
			   strcpy(cSpielerfarbe, SPIELER1_FARBE);
			}
         }
      }
   }while(iSetzeSpielstein != -1);
   system("cls");
   ausgebenSpielbrett(cBrett);
   system("Pause");
   // Wenn Spielbrett voll und kein Gewinner --> Unentschieden
   // gebe 0,5 als Return-Wert zurueck
   // Wenn Gewinner, gibt Gewinnernachricht aus und gebe 1 zurueck,
   // wenn Spieler1 gewonnen hat und 0, wenn Spieler2 gewonnen hat
   if(iSetzeSpielstein == -1 && !(cKoordinate == 'x' || cKoordinate == 'X'))
   {
      ausgebenWinMeldung(cGewinner, cKoordinate);
      if(cGewinner[0] == '\0')
      {
         return 0.5;
      }
      else
      {
         if(strcmp(cGewinner, g_cSpieler1) == 0)
         {
            return 1.0;
         }
         else
         {
            return 0.0;
         }
      }
   }
   // return -1 bei Spielabbruch
   ausgebenWinMeldung(cGewinner, cKoordinate);
   return -1.0;
}

/* 
===============================================================================
   Funktion setzeSpielstein()
   Diese Funktion setzt den Spielstein auf die Eingabekoordinate, fängt
   Fehler ab und startet das Spiel aufgrund der Eingabe neu oder ruft
   die Hilfe auf.
   Return: 0 Eingabe richtig
		   1 Eingabe falsch
		   2 Spalte voll
		   3 Hilfe aufgerufen
		   4 Spiel neu gestartet
   in: cKoordinate, iSpielfeld, cAktuellerSpieler, cNaechsterSpieler
   out: iStatus
===============================================================================
*/
int setzeSpielstein(char cKoordinate,
                    int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE],
					char cAktuellerSpieler[SPIELERLAENGE],
					char cNaechsterSpieler[SPIELERLAENGE],
					char cSpielerfarbe[10])
{
   switch(cKoordinate)
   {
      int i;
      // Aufgrund der Eingabekoordinate wird geprueft ob noch Platz
      // in der Spalte ist. Wenn ja fuege Spielstein ein und gibt
      // Returncode 0 zurueck. Wenn Spalte voll gib Returncode 2
      // zurück. Bei einer falschen Spalteneingabe wird Returncode 1
      // zurueckgeliefert.
      case 'a':
      case 'A':
         for(i=5; i>=0; i--)
         {
            if(iSpielfeld[i][0] == 0)
            {
               if(strcmp(cAktuellerSpieler, g_cSpieler1) == 0)
               {
                  iSpielfeld[i][0] = 1;
                  return 0;
               }
               else
               {
                  iSpielfeld[i][0] = 2;
                  return 0;
               }
            }
         }
         return 2;
         break;
      case 'b':
      case 'B':
         for(i=5; i>=0; i--)
         {
            if(iSpielfeld[i][1] == 0)
            {
               if(strcmp(cAktuellerSpieler, g_cSpieler1) == 0)
               {
                  iSpielfeld[i][1] = 1;
                  return 0;
               }
               else
               {
                  iSpielfeld[i][1] = 2;
                  return 0;
               }
            }
         }
         return 2;
         break;
      case 'c':
      case 'C':
         for(i=5; i>=0; i--)
         {
            if(iSpielfeld[i][2] == 0)
            {
               if(strcmp(cAktuellerSpieler, g_cSpieler1) == 0)
               {
                  iSpielfeld[i][2] = 1;
                  return 0;
               }
               else
               {
                  iSpielfeld[i][2] = 2;
                  return 0;
               }
            }
         }
         return 2;
         break;
      case 'd':
      case 'D':
         for(i=5; i>=0; i--)
         {
            if(iSpielfeld[i][3] == 0)
            {
               if(strcmp(cAktuellerSpieler, g_cSpieler1) == 0)
               {
                  iSpielfeld[i][3] = 1;
                  return 0;
               }
               else
               {
                  iSpielfeld[i][3] = 2;
                  return 0;
               }
            }
         }
         return 2;
         break;
      case 'e':
      case 'E':
         for(i=5; i>=0; i--)
         {
            if(iSpielfeld[i][4] == 0)
            {
               if(strcmp(cAktuellerSpieler, g_cSpieler1) == 0)
               {
                  iSpielfeld[i][4] = 1;
                  return 0;
               }
               else
               {
                  iSpielfeld[i][4] = 2;
                  return 0;
               }
            }
         }
         return 2;
         break;
      case 'f':
      case 'F':
         for(i=5; i>=0; i--)
         {
            if(iSpielfeld[i][5] == 0)
            {
               if(strcmp(cAktuellerSpieler, g_cSpieler1) == 0)
               {
                  iSpielfeld[i][5] = 1;
                  return 0;
               }
               else
               {
                  iSpielfeld[i][5] = 2;
                  return 0;
               }
            }
         }
         return 2;
         break;
      case 'g':
      case 'G':
         for(i=5; i>=0; i--)
         {
            if(iSpielfeld[i][6] == 0)
            {
               if(strcmp(cAktuellerSpieler, g_cSpieler1) == 0)
               {
                  iSpielfeld[i][6] = 1;
                  return 0;
               }
               else
               {
                  iSpielfeld[i][6] = 2;
                  return 0;
               }
            }
         }
         return 2;
         break;
      case 'x':
      case 'X':
         return -1;
         break;
      case 'w':
      case 'W':
         initialisiereSpielfeld(iSpielfeld);
         strcpy(cAktuellerSpieler, g_cSpieler1);
         strcpy(cNaechsterSpieler, g_cSpieler2);
		 strcpy(cSpielerfarbe, SPIELER1_FARBE);
         return 4;
         break;
      case 's':
      case 'S':
         system("start 4Gewinnt-Hilfe.html");
         return 3;
         break;
      default:
         return 1;
   }
}

/* 
===============================================================================
	Funktion:		initialisiereSpielfeld()
	in:	iSpielfeld
	out:
	Beschreibung:	Diese Funktion initialisiert das logische Spielfeld. Alle 
					Felder werden mit 0 vorbelegt, dies entspricht einem leeren 
					Feld.
===============================================================================
*/
void initialisiereSpielfeld(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;

   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         iSpielfeld[i][j] = 0;
      }
   }
}

/* 
===============================================================================
   Funktion vorhandenGewinner()
   Diese Funktion prüft, ob ein Gewinner vorhanden ist.
   Returns: 0 kein Gewinner vorhanden
			1 Gewinner vorhanden
   in: iSpielfeld
   out: iGewinnerVorhanden
===============================================================================
*/
int vorhandenGewinner(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;

   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // waagerecht pruefen
         if(j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == iSpielfeld[i][j+1] &&
               iSpielfeld[i][j] == iSpielfeld[i][j+2] &&
               iSpielfeld[i][j] == iSpielfeld[i][j+3] &&
               iSpielfeld[i][j] != 0)
            {
               return 1;
            }
         }

         // senkrecht pruefen
         if(i+3 < SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == iSpielfeld[i+1][j] &&
               iSpielfeld[i][j] == iSpielfeld[i+2][j] &&
               iSpielfeld[i][j] == iSpielfeld[i+3][j] &&
               iSpielfeld[i][j] != 0)
            {
               return 1;
            }
         }


         // digonal rechts-unten pruefen
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == iSpielfeld[i+1][j+1] &&
               iSpielfeld[i][j] == iSpielfeld[i+2][j+2] &&
               iSpielfeld[i][j] == iSpielfeld[i+3][j+3] &&
               iSpielfeld[i][j] != 0)
            {
               return 1;
            }
         }

         // diagonal rechts-oben pruefen
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == iSpielfeld[i-1][j+1] &&
               iSpielfeld[i][j] == iSpielfeld[i-2][j+2] &&
               iSpielfeld[i][j] == iSpielfeld[i-3][j+3] &&
               iSpielfeld[i][j] != 0)
            {
               return 1;
            }
         }
      }
   }
   return 0;
}

/* 
===============================================================================
   Funktion istSpielfeldVoll()
   Diese Funktion prüft, ob das Spielfeld voll ist.
   Returns: 0 nicht voll
			1 voll
   in: iSpielfeld
   out: iVoll
===============================================================================
*/
int istSpielfeldVoll(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;
   int iVoll;

   // Annahme Spielfeld ist voll
   iVoll = 1;

   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // Setze iVoll nur auf 0, wenn ein Feld frei ist
         if(iSpielfeld[i][j] == 0)
         {
            iVoll = 0;
         }
      }
   }
   return iVoll;
}

/*
===============================================================================
   Funktion aufbereitenSpielbrett()
   Diese Funktion bereitet das Ausgabespielbrett mit den noetigen Zeichen vor.
   in: cBrett, iSpielfeld
   out: -
===============================================================================
*/
void aufbereitenSpielbrett(char cBrett[SPIELBRETTHOEHE][SPIELBRETTBREITE],
						   int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   // Zaehlvariablen
   int i;
   int j;
   int c;

   // Variablen fuer Spielbrettzeichen
   char cHell;
   char cDunkel;
   char cSenkrecht;
   char cWaagerecht;
   char cKreuz;
   char cBuchstabe = 65;
   char cZahl = 49;

   // Helles Feld
   cHell = '\xB0';

   // Dunkles Feld
   cDunkel = '\xB1';

   // Senkrechter Strich
   cSenkrecht = '\xB3';

   // Waagerechter Strich
   cWaagerecht = '\xC4';

   // Kreuz
   cKreuz = '\xC5';

   // Mit Leerzeichen initialisieren
   for(i = 0; i < SPIELBRETTHOEHE; i++)
   {
      for(j = 0; j < SPIELBRETTBREITE; j++)
      {
         cBrett[i][j] = ' ';
      }
   }

   // Erste Zeile mit den Buchstaben füllen
   cBrett[0][0] = ' ';
   cBrett[0][1] = cSenkrecht;
	
   for (j=5; j<SPIELBRETTBREITE; j+=7)
   {
      cBrett[0][j] = cBuchstabe;
      cBuchstabe++;
   }

   // Zweite Zeile füllen
   cBrett[1][0] = cWaagerecht;
   cBrett[1][1] = cKreuz;
	
   for (j=2; j<SPIELBRETTBREITE; j++)
   {
      cBrett[1][j] = cWaagerecht;
   }

   // Linke Spalten mit Zahlen fuellen
   cZahl = 49;
   for (i=4; i<SPIELBRETTHOEHE; i=i+5) 
   {
      cBrett[i-1][0] = ' ';
      cBrett[i][0] = cZahl;
      cBrett[i+1][0] = ' ';
      cBrett[i+2][0] = ' ';
      cBrett[i+3][0] = ' ';
      cZahl++;
   }

   // Senkrechte Trennlinie
   for (i=2; i<SPIELBRETTHOEHE; i=i++) 
   {
      cBrett[i][1] = cSenkrecht;
   }


   // Spielbrettfelder fuellen, leeres Feld mit Spielstein Spieler1
   // oder Spieler2
   // Berechnung der Indizes: 
   //				Zeile - i * Feldhoehe + Seitenhoehe + Feldzeile
   //				Spalte - j * Feldbreite + Seitenbreite + Feldspalte
   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         if(iSpielfeld[i][j] == 0)
         {
            for(c=0; c<7; c++)
            {
               cBrett[i*5+2][j*7+2+c] = cHell;
            }
            cBrett[i*5+2+1][j*7+2] = cHell;
            cBrett[i*5+2+1][j*7+2+1] = cHell;
            cBrett[i*5+2+1][j*7+2+2] = cDunkel;
            cBrett[i*5+2+1][j*7+2+3] = cDunkel;
            cBrett[i*5+2+1][j*7+2+4] = cDunkel;
            cBrett[i*5+2+1][j*7+2+5] = cHell;
            cBrett[i*5+2+1][j*7+2+6] = cHell;
            cBrett[i*5+2+2][j*7+2] = cHell;
	        cBrett[i*5+2+2][j*7+2+1] = cDunkel;
            cBrett[i*5+2+2][j*7+2+2] = cDunkel;
            cBrett[i*5+2+2][j*7+2+3] = cDunkel;
            cBrett[i*5+2+2][j*7+2+4] = cDunkel;
            cBrett[i*5+2+2][j*7+2+5] = cDunkel;
            cBrett[i*5+2+2][j*7+2+6] = cHell;
            cBrett[i*5+2+3][j*7+2] = cHell;
            cBrett[i*5+2+3][j*7+2+1] = cHell;
            cBrett[i*5+2+3][j*7+2+2] = cDunkel;
            cBrett[i*5+2+3][j*7+2+3] = cDunkel;
            cBrett[i*5+2+3][j*7+2+4] = cDunkel;
            cBrett[i*5+2+3][j*7+2+5] = cHell;
            cBrett[i*5+2+3][j*7+2+6] = cHell;
            for(c=0; c<7; c++)
            {
               cBrett[i*5+2+4][j*7+2+c] = cHell;
            }
         }
         if(iSpielfeld[i][j] == 1)
         {
            for(c=0; c<7; c++)
            {
               cBrett[i*5+2][j*7+2+c] = cHell;
            }
            cBrett[i*5+2+1][j*7+2] = cHell;
            cBrett[i*5+2+1][j*7+2+1] = cHell;
            cBrett[i*5+2+1][j*7+2+2] = ZSPIELER1;
            cBrett[i*5+2+1][j*7+2+3] = ZSPIELER1;
            cBrett[i*5+2+1][j*7+2+4] = ZSPIELER1;
            cBrett[i*5+2+1][j*7+2+5] = cHell;
            cBrett[i*5+2+1][j*7+2+6] = cHell;
            cBrett[i*5+2+2][j*7+2] = cHell;
            cBrett[i*5+2+2][j*7+2+1] = ZSPIELER1;
            cBrett[i*5+2+2][j*7+2+2] = ZSPIELER1;
            cBrett[i*5+2+2][j*7+2+3] = ZSPIELER1;
            cBrett[i*5+2+2][j*7+2+4] = ZSPIELER1;
            cBrett[i*5+2+2][j*7+2+5] = ZSPIELER1;
            cBrett[i*5+2+2][j*7+2+6] = cHell;
            cBrett[i*5+2+3][j*7+2] = cHell;
            cBrett[i*5+2+3][j*7+2+1] = cHell;
            cBrett[i*5+2+3][j*7+2+2] = ZSPIELER1;
            cBrett[i*5+2+3][j*7+2+3] = ZSPIELER1;
            cBrett[i*5+2+3][j*7+2+4] = ZSPIELER1;
            cBrett[i*5+2+3][j*7+2+5] = cHell;
            cBrett[i*5+2+3][j*7+2+6] = cHell;
            for(c=0; c<7; c++)
            {
               cBrett[i*5+2+4][j*7+2+c] = cHell;
            }
         }
         if(iSpielfeld[i][j] == 2)
         {
            for(c=0; c<7; c++)
            {
               cBrett[i*5+2][j*7+2+c] = cHell;
            }
            cBrett[i*5+2+1][j*7+2] = cHell;
            cBrett[i*5+2+1][j*7+2+1] = cHell;
            cBrett[i*5+2+1][j*7+2+2] = ZSPIELER2;
            cBrett[i*5+2+1][j*7+2+3] = ZSPIELER2;
            cBrett[i*5+2+1][j*7+2+4] = ZSPIELER2;
	        cBrett[i*5+2+1][j*7+2+5] = cHell;
            cBrett[i*5+2+1][j*7+2+6] = cHell;
            cBrett[i*5+2+2][j*7+2] = cHell;
            cBrett[i*5+2+2][j*7+2+1] = ZSPIELER2;
            cBrett[i*5+2+2][j*7+2+2] = ZSPIELER2;
            cBrett[i*5+2+2][j*7+2+3] = ZSPIELER2;
            cBrett[i*5+2+2][j*7+2+4] = ZSPIELER2;
            cBrett[i*5+2+2][j*7+2+5] = ZSPIELER2;
            cBrett[i*5+2+2][j*7+2+6] = cHell;
            cBrett[i*5+2+3][j*7+2] = cHell;
            cBrett[i*5+2+3][j*7+2+1] = cHell;
            cBrett[i*5+2+3][j*7+2+2] = ZSPIELER2;
            cBrett[i*5+2+3][j*7+2+3] = ZSPIELER2;
            cBrett[i*5+2+3][j*7+2+4] = ZSPIELER2;
            cBrett[i*5+2+3][j*7+2+5] = cHell;
            cBrett[i*5+2+3][j*7+2+6] = cHell;
            for(c=0; c<7; c++)
            {
               cBrett[i*5+2+4][j*7+2+c] = cHell;
            }
         }	
      }
   }
}


/*
===============================================================================
   Funktion ausgebenSpielbrett()
   Diese Funktion gibt das Spielbrett aus.
   in: cBrett
   out: -
===============================================================================
*/

void ausgebenSpielbrett(char cBrett[SPIELBRETTHOEHE][SPIELBRETTBREITE])
{
   int i;
   int j;

   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                           FOREGROUND_RED | FOREGROUND_GREEN |
                           FOREGROUND_BLUE | FOREGROUND_INTENSITY);
   printf("================================================================================");
   printf("    444        $$$$$$   $$$$$$$$$ $$     $$ $$ $$$  $$ $$$  $$ $$$$$$$$         ");
   printf("   444    44  $$       $$$       $$     $$ $$ $$$$ $$ $$$$ $$    $$             ");
   printf("  444444444  $$ $$$$  $$$$$$$$$ $$  $  $$ $$ $$ $$$$ $$ $$$$    $$              ");
   printf("       444  $$    $$ $$$       $$ $$$ $$ $$ $$  $$$ $$  $$$    $$               ");
   printf("      444    $$$$$$ $$$$$$$$$ $$$$$$$$$ $$ $$   $$ $$   $$    $$                ");
   printf("================================================================================");

   for (i = 0; i < SPIELBRETTHOEHE-1; i++)
   {
      printf("\t");
      for (j = 0; j < SPIELBRETTBREITE-1; j++)
      {
         if(cBrett[i][j] == ZSPIELER1 || cBrett[i][j] == ZSPIELER2)
         {
            if(cBrett[i][j] == ZSPIELER1)
            {
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                       FOREGROUND_BLUE | FOREGROUND_INTENSITY);
               printf("%c", cBrett[i][j]);
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                       FOREGROUND_RED | FOREGROUND_GREEN |
                                       FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            else
            {
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                       FOREGROUND_RED | FOREGROUND_INTENSITY);
               printf("%c", cBrett[i][j]);
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                       FOREGROUND_RED | FOREGROUND_GREEN |
                                       FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
         }
         else
         {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                    FOREGROUND_RED | FOREGROUND_GREEN |
                                    FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            printf("%c", cBrett[i][j]);
         }
      }
      printf("\n");
   }
   printf("\n");
   printf("          x:Hauptmenue          s:Hilfe          w:Neues Spiel\n");
}

/*
===============================================================================
   Funktion:		ausgebenWinMeldung()
   Diese Funktion gibt eine Gewinner- oder Abbruchmeldung aus.
   in:				cAktuellerSpieler, cKoordinate
   out: -
===============================================================================
*/
void ausgebenWinMeldung(char cGewinner[SPIELERLAENGE], char cKoordinate)
{
   if(cGewinner[0] != '\0' && (cKoordinate != 'x' || cKoordinate != 'X'))
   {
      system("cls");
      system("cls");
		printf("===========================================================");
		printf("=====================");
		printf("         $$$$$$$   $$  $$  $$$$$$ $$$$$$   $$ $$$  $$$$$$ $");
		printf("$$$$$$  $$$$$$       ");
		printf("        $$    $$  $$  $$  $$     $$   $$  $$ $$   $$     $$");
		printf("    $$ $$            ");
		printf("       $$        $$$$$$  $$$$$  $$       $$$$$   $$$$   $$ ");
		printf("$$$$  $$$$$$$        ");
		printf("      $$    $$  $$  $$  $$     $$   $$  $$ $$   $$     $$  ");
		printf(" $$       $$         ");
		printf("      $$$$$$$  $$  $$  $$$$$$$ $$$$$$  $$   $$ $$$$$$ $$   ");
		printf(" $$ $$$$$$$          ");
		printf("===========================================================");
		printf("=====================");
        printf("\n\n\t\t\tHerzlichen Glueckwunsch.\n \t\t%s hat gewonnen!!\n\n",
             cGewinner);
		printf("\n");
   }
   else
   {
      if(cKoordinate == 'x' || cKoordinate == 'X')
      {
         system("cls");
         printf("========================================================");
         printf("========================");
         printf("    444        $$$$$$   $$$$$$$$$ $$     $$ $$ $$$  $$ $");
         printf("$$  $$ $$$$$$$$         ");
         printf("   444    44  $$       $$$       $$     $$ $$ $$$$ $$ $$");
         printf("$$ $$    $$             ");      
         printf("  444444444  $$ $$$$  $$$$$$$$$ $$  $  $$ $$ $$ $$$$ $$ ");
         printf("$$$$    $$              ");
         printf("       444  $$    $$ $$$       $$ $$$ $$ $$ $$  $$$ $$  ");
         printf("$$$    $$               ");
         printf("      444    $$$$$$ $$$$$$$$$ $$$$$$$$$ $$ $$   $$ $$   ");
         printf("$$    $$                ");
         printf("========================================================");
         printf("========================");
         printf("\n\n");
		 printf("\t Sie haben das Spiel beendet. ");
		 printf("\n");
		 printf("\t Es findet keine Wertung statt.");
      }
      else
      {
         system("cls");
         printf("========================================================");
         printf("========================");
         printf("    444        $$$$$$   $$$$$$$$$ $$     $$ $$ $$$  $$ $");
         printf("$$  $$ $$$$$$$$         ");
         printf("   444    44  $$       $$$       $$     $$ $$ $$$$ $$ $$");
         printf("$$ $$    $$             ");      
         printf("  444444444  $$ $$$$  $$$$$$$$$ $$  $  $$ $$ $$ $$$$ $$ ");
         printf("$$$$    $$              ");
         printf("       444  $$    $$ $$$       $$ $$$ $$ $$ $$  $$$ $$  ");
         printf("$$$    $$               ");
         printf("      444    $$$$$$ $$$$$$$$$ $$$$$$$$$ $$ $$   $$ $$   ");
         printf("$$    $$                ");
         printf("========================================================");
         printf("========================");
         printf("\n\n");
		 printf("\t Das Spiel endete: Unentschieden");
      }
   } 
   printf("\n\n\t ");
   system("pause");
}
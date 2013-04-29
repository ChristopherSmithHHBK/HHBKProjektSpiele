/*
   ========================================================================
   Autor       : Vrinssen
   Firma       : HHBK
   Dateiname   : ki_4gewinnt.c
   Datum       : 30.05.2011
   Version     : 1.0
   Compiler	   : Visual Studio
   Programmschnittstelle: int sucheComputerZug(int iSchwierigkeit,
						  int iSpielfeld)
                          Das Programm gibt den Wert 0 bis 6 zurueck.
   ========================================================================
*/
#include "ki_4gewinnt.h"
/*
   ========================================================================
   Funktion sucheComputerZug()
   ========================================================================
*/

int sucheComputerZug (int iSchwierigkeit,
					  int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   switch(iSchwierigkeit)
   {
      case 1:
         return kiLeicht(); // Aufruf des leichten Gegners
         break;
      case 2:
         return kiMittel(iSpielfeld); // Aufruf des mittleren Gegners
         break;
      case 3:
         return kiSchwer(iSpielfeld); // Aufrud des schweren Gegners
         break;
      default:
         return -1;
   }
}

/*
   ========================================================================
   Funktion kiLeicht(void)
   Diese Funktion generiert einen Zufallszug und gibt diesen zurueck
   ========================================================================
*/

int kiLeicht (void)
{
   srand((unsigned char) time(NULL));
   return rand() % 7;
}

/*
   ========================================================================
   Funktion kiMittel(int iSpielfeld)
   Diese Funktion prueft, ob einer der beiden Spieler mit dem nächsten Zug
   gewinnen kann. Wenn der Computer gewinnen kann, wird die dazu noetige
   Koordinate zurueckgegeben, wenn der Spieler gewinnen kann, wird die
   Koordinate zurueckgegeben um dies zu verhindern. Ansonsten wird eine
   Zufallskoordinate zurueckgegeben.
   ========================================================================
*/

int kiMittel (int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int rueckComputer;
   int rueckComputer2;
   int rueckSpieler;
   int rueckSpieler2;
   // pruefe auf 4er(Computer) mit moeglichen Ausseneinwurfkoordinaten
   rueckComputer = pruefe4SteineAComputer(iSpielfeld);
   // pruefe auf 4er(Computer) mit moeglichen Inneneinwurfkoordinaten
   rueckComputer2 = pruefe4SteineIComputer(iSpielfeld);
   // pruefe auf 4er(Spieler) mit moeglichen Ausseneinwurfkoordinaten
   rueckSpieler = pruefe4SteineASpieler(iSpielfeld);
   // pruefe auf 4er(Spieler) mit moeglichen Inneneinwurfkoordinaten
   rueckSpieler2 = pruefe4SteineISpieler(iSpielfeld);

   if(rueckComputer != -1)
   {
      return rueckComputer;
   }

   if(rueckComputer2 != -1)
   {
      return rueckComputer2;
   }

   if(rueckSpieler != -1)
   {
      return rueckSpieler;
   }

   if(rueckSpieler2 != -1)
   {
      return rueckSpieler2;
   }

   srand((unsigned char) time(NULL));
   return rand() % 7;
}

/*
   ========================================================================
   Funktion kiSchwer(int iSpielfeld)
   Diese Funktion prueft in folgender Reihenfolge, falls kein Ergebnis
   vorhanden ist, wird eine Zufallskoordinate zurueckgegeben:
   1. 4er(Computer) mit moeglichen Aussenkoordinaten
   2. 4er(Computer) mit moeglichen Innenkoordinaten
   3. 4er(Spieler) mit moeglichen Aussenkoordinaten
   4. 4er(Spieler) mit moeglichen Innenkoordinaten
   5. 3er(Computer)
   6. 3er(Spieler)
   7. 2er(Computer)
   8. 2er(Spieler)
   ========================================================================
*/

int kiSchwer (int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   if(pruefe4SteineAComputer(iSpielfeld) != -1)
   {
      return pruefe4SteineAComputer(iSpielfeld);
   }
   if(pruefe4SteineASpieler(iSpielfeld) != -1)
   {
      return pruefe4SteineASpieler(iSpielfeld);
   }
   if(pruefe4SteineIComputer(iSpielfeld) != -1)
   {
      return pruefe4SteineIComputer(iSpielfeld);
   }
   if(pruefe4SteineISpieler(iSpielfeld) != -1)
   {
      return pruefe4SteineISpieler(iSpielfeld);
   }
   if(pruefe3SteineComputer(iSpielfeld) != -1)
   {
      return pruefe3SteineComputer(iSpielfeld);
   }
   if(pruefe3SteineSpieler(iSpielfeld) != -1)
   {
      return pruefe3SteineSpieler(iSpielfeld);
   }
   if(pruefe2SteineComputer(iSpielfeld) != -1)
   {
      return pruefe2SteineComputer(iSpielfeld);
   }
   if(pruefe2SteineSpieler(iSpielfeld) != -1)
   {
      return pruefe2SteineSpieler(iSpielfeld);
   }

   srand((unsigned char) time(NULL));
   return rand() % 7;
}

/*
   ========================================================================
   Funktion pruefe4SteineAComputer()
   Prueft, ob der Computer mit dem naechsten Zug gewonnen hat, es werden
   nur aeussere freie Felder beruecksichtiegt.
   Beispiel: 0XXX000, wobei 0 ein freies Feld darstellt
   Returns: -1 - Kann nicht gewinnen
			0 - 6 - Zug zum gewinnen
   ========================================================================
*/
int pruefe4SteineAComputer(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;
   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // waagerecht pruefen; rechts frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 2 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 0)
            {
               return j+3;
            }
         }

         // waagerecht pruefen; rechts frei
         if(j+3 < SPIELFELDBREITE && i+1 <SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 2 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 0 &&
               iSpielfeld[i+1][j+3] != 0)
            {
               return j+3;
            }
         }

         // waagerecht pruefen; links frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 2 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 2)
            {
               return j;
            }
         }

         // waagerecht pruefen; links frei
         if(j+3 < SPIELFELDBREITE && i+1 < SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 2 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 2 &&
               iSpielfeld[i+1][j] != 0)
            {
               return j;
            }
         }

         // senkrecht pruefen
         if(i+3 < SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j] == 2 &&
               iSpielfeld[i+2][j] == 2 &&
               iSpielfeld[i+3][j] == 2)
            {
               return j;
            }
         }


         // digonal rechts-unten pruefen; unten frei; erste Reihe
         if(i+3 == SPIELFELDHOEHE-1 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i+1][j+1] == 2 &&
               iSpielfeld[i+2][j+2] == 2 &&
               iSpielfeld[i+3][j+3] == 0)
            {
               return j+3;
            }
         }

         // digonal rechts-unten pruefen; unten frei
         if(i+4 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i+1][j+1] == 2 &&
               iSpielfeld[i+2][j+2] == 2 &&
               iSpielfeld[i+3][j+3] == 0 &&
               iSpielfeld[i+4][j+3] != 0)
            {
               return j+3;
            }
         }

         // digonal rechts-unten pruefen; oben frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j+1] == 2 &&
               iSpielfeld[i+2][j+2] == 2 &&
               iSpielfeld[i+3][j+3] == 2 &&
               iSpielfeld[i+1][j] != 0)
            {
               return j;
            }
         }

         // diagonal rechts-oben pruefen; oben frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i-1][j+1] == 2 &&
               iSpielfeld[i-2][j+2] == 2 &&
               iSpielfeld[i-3][j+3] == 0 &&
               iSpielfeld[i-2][j+3] != 0)
            {
               return j+3;
            }
         }

         // diagonal rechts-oben pruefen; unten frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i-1][j+1] == 2 &&
               iSpielfeld[i-2][j+2] == 2 &&
               iSpielfeld[i-3][j+3] == 2 &&
               iSpielfeld[i-1][j] != 0)
            {
               return j;
            }
         }
      }
   }
   return -1;
}

/*
   ========================================================================
   Funktion pruefe4SteineASpieler()
   Prueft, ob der Spieler mit dem naechsten Zug gewonnen hat, es werden
   nur aeussere freie Felder beruecksichtiegt.
   Beispiel: 0XXX000, wobei 0 ein freies Feld darstellt
   Returns: -1 - Kann nicht gewinnen
			0 - 6 - Zug um Gewinn zu verhindern
   ========================================================================
*/
int pruefe4SteineASpieler(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;
   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // waagerecht pruefen rechts; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 1 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 0)
            {
               return j+3;
            }
         }

         // waagerecht pruefen; rechts
         if(j+3 < SPIELFELDBREITE && i+1 <SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 1 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 0 &&
               iSpielfeld[i+1][j+3] != 0)
            {
               return j+3;
            }
         }

         // waagerecht pruefen; links frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 1 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 1)
            {
               return j;
            }
         }

         // waagerecht pruefen; links frei
         if(j+3 < SPIELFELDBREITE && i+1 < SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 1 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 1 &&
               iSpielfeld[i+1][j] != 0)
            {
               return j;
            }
         }

         // senkrecht pruefen
         if(i+3 < SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j] == 1 &&
               iSpielfeld[i+2][j] == 1 &&
               iSpielfeld[i+3][j] == 1)
            {
               return j;
            }
         }


         // digonal rechts-unten pruefen; unten frei; erste Reihe
         if(i+3 == SPIELFELDHOEHE-1 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i+1][j+1] == 1 &&
               iSpielfeld[i+2][j+2] == 1 &&
               iSpielfeld[i+3][j+3] == 0)
            {
               return j+3;
            }
         }

         // digonal rechts-unten pruefen; unten frei
         if(i+4 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i+1][j+1] == 1 &&
               iSpielfeld[i+2][j+2] == 1 &&
               iSpielfeld[i+3][j+3] == 0 &&
               iSpielfeld[i+4][j+3] != 0)
            {
               return j+3;
            }
         }

         // digonal rechts-unten pruefen; oben frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j+1] == 1 &&
               iSpielfeld[i+2][j+2] == 1 &&
               iSpielfeld[i+3][j+3] == 1 &&
               iSpielfeld[i+1][j] != 0)
            {
               return j;
            }
         }

         // diagonal rechts-oben pruefen; oben frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i-1][j+1] == 1 &&
               iSpielfeld[i-2][j+2] == 1 &&
               iSpielfeld[i-3][j+3] == 0 &&
               iSpielfeld[i-2][j+3] != 0)
            {
               return j+3;
            }
         }

         // diagonal rechts-oben pruefen; unten frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i-1][j+1] == 1 &&
               iSpielfeld[i-2][j+2] == 1 &&
               iSpielfeld[i-3][j+3] == 1 &&
               iSpielfeld[i-1][j] != 0)
            {
               return j;
            }
         }
      }
   }
   return -1;
}

/*
   ========================================================================
   Funktion pruefe4SteineISpieler()
   Prueft, ob der Spieler mit dem naechsten Zug gewonnen hat, es werden
   nur innere freie Felder beruecksichtiegt.
   Beispiel: 0X0XX00, wobei 0 ein freies Feld darstellt
   Returns: -1 - Kann nicht gewinnen
			0 - 6 - Zug um Gewinn zu verhindern
   ========================================================================
*/
int pruefe4SteineISpieler(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;
   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // waagerecht pruefen; mitte links frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 1)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; mitte links frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 1 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; mitte rechts frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 1 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 1)
            {
               return j+2;
            }
         }

         // waagerecht pruefen; mitte rechts frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 1 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 1 &&
               iSpielfeld[i-1][j+2] != 0)
            {
               return j+2;
            }
         }

         // digonal rechts-unten pruefen; mitte unten frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i+1][j+1] == 1 &&
               iSpielfeld[i+2][j+2] == 0 &&
               iSpielfeld[i+3][j+3] == 1 &&
               iSpielfeld[i+3][j+2] != 0)
            {
               return j+2;
            }
         }

         // digonal rechts-unten pruefen; mitte oben frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i+1][j+1] == 0 &&
               iSpielfeld[i+2][j+2] == 1 &&
               iSpielfeld[i+3][j+3] == 1 &&
               iSpielfeld[i+2][j+1] != 0)
            {
               return j+1;
            }
         }

         // diagonal rechts-oben pruefen; mitte unten frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i-1][j+1] == 1 &&
               iSpielfeld[i-2][j+2] == 0 &&
               iSpielfeld[i-3][j+3] == 1 &&
               iSpielfeld[i-1][j+2] != 0)
            {
               return j+2;
            }
         }

         // diagonal rechts-oben pruefen; mitte oben frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i-1][j+1] == 0 &&
               iSpielfeld[i-2][j+2] == 1 &&
               iSpielfeld[i-3][j+3] == 1 &&
               iSpielfeld[i][j+1] != 0)
            {
               return j+1;
            }
         }
      }
   }
   return -1;
}

/*
   ========================================================================
   Funktion pruefe4SteineIComputer()
   Prueft, ob der Computer mit dem naechsten Zug gewonnen hat, es werden
   nur innere freie Felder beruecksichtiegt.
   Beispiel: 0X0XX00, wobei 0 ein freies Feld darstellt
   Returns: -1 - Kann nicht gewinnen
			0 - 6 - Zug um Gewinn zu verhindern
   ========================================================================
*/
int pruefe4SteineIComputer(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;
   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // waagerecht pruefen; mitte links frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 2)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; mitte links frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 2 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; mitte rechts frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 2 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 2)
            {
               return j+2;
            }
         }

         // waagerecht pruefen; mitte rechts frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 2 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 2 &&
               iSpielfeld[i-1][j+2] != 0)
            {
               return j+2;
            }
         }

         // digonal rechts-unten pruefen; mitte unten frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i+1][j+1] == 2 &&
               iSpielfeld[i+2][j+2] == 0 &&
               iSpielfeld[i+3][j+3] == 2 &&
               iSpielfeld[i+3][j+2] != 0)
            {
               return j+2;
            }
         }

         // digonal rechts-unten pruefen; mitte oben frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i+1][j+1] == 0 &&
               iSpielfeld[i+2][j+2] == 2 &&
               iSpielfeld[i+3][j+3] == 2 &&
               iSpielfeld[i+2][j+1] != 0)
            {
               return j+1;
            }
         }

         // diagonal rechts-oben pruefen mitte unten frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i-1][j+1] == 2 &&
               iSpielfeld[i-2][j+2] == 0 &&
               iSpielfeld[i-3][j+3] == 2 &&
               iSpielfeld[i-1][j+2] != 0)
            {
               return j+2;
            }
         }

         // diagonal rechts-oben pruefen; mitte oben frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i-1][j+1] == 0 &&
               iSpielfeld[i-2][j+2] == 2 &&
               iSpielfeld[i-3][j+3] == 2 &&
               iSpielfeld[i][j+1] != 0)
            {
               return j+1;
            }
         }
      }
   }
   return -1;
}

/*
   ========================================================================
   Funktion pruefe3SteineComputer()
   Prueft, ob der Computer mit dem naechsten Zug gewonnen hat, es werden
   nur aeussere freie Felder beruecksichtiegt.
   Beispiel: 0XXX000, wobei 0 ein freies Feld darstellt
   Returns: -1 - Kann nicht gewinnen
			0 - 6 - Zug zum gewinnen
   ========================================================================
*/
int pruefe3SteineComputer(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;
   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // waagerecht pruefen; rechts frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 2 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 0)
            {
               return j+2;
            }
         }

         // waagerecht pruefen; links frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 2)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; mitte frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; rechts frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 2 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 0 &&
               iSpielfeld[i+1][j+2] != 0)
            {
               return j+2;
            }
         }

         // waagerecht pruefen; links frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 2 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; mitte
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 2 &&
               iSpielfeld[i][j+3] == 0 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+1;
            }
         }

         // senkrecht pruefen
         if(i+3 < SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j] == 0 &&
               iSpielfeld[i+2][j] == 2 &&
               iSpielfeld[i+3][j] == 2)
            {
               return j;
            }
         }


         // digonal rechts-unten pruefen; unten frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i+1][j+1] == 2 &&
               iSpielfeld[i+2][j+2] == 0 &&
               iSpielfeld[i+3][j+3] == 0 &&
               iSpielfeld[i+3][j+2] != 0)
            {
               return j+2;
            }
         }
			
         // digonal rechts-unten pruefen; oben frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j+1] == 0 &&
               iSpielfeld[i+2][j+2] == 2 &&
               iSpielfeld[i+3][j+3] == 2 &&
               iSpielfeld[i+2][j+1] != 0)
            {
               return j+1;
            }
         }

         // diagonal rechts-oben pruefen; oben frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i-1][j+1] == 2 &&
               iSpielfeld[i-2][j+2] == 0 &&
               iSpielfeld[i-3][j+3] == 0 &&
               iSpielfeld[i-1][j+2] != 0)
            {
               return j+2;
            }
         }

         // diagonal rechts-oben pruefen; unten frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i-1][j+1] == 0 &&
               iSpielfeld[i-2][j+2] == 2 &&
               iSpielfeld[i-3][j+3] == 2 &&
               iSpielfeld[i][j+1] != 0)
            {
               return j+1;
            }
         }
      }
   }
   return -1;
}

/*
   ========================================================================
   Funktion pruefe3SteineSpieler()
   Prueft, ob der Computer mit dem naechsten Zug gewonnen hat, es werden
   nur aeussere freie Felder beruecksichtiegt.
   Beispiel: 0XXX000, wobei 0 ein freies Feld darstellt
   Returns: -1 - Kann nicht gewinnen
			0 - 6 - Zug zum gewinnen
   ========================================================================
*/
int pruefe3SteineSpieler(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;
   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // waagerecht pruefen; rechts frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 1 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 0)
            {
               return j+2;
            }
         }

         // waagerecht pruefen; links frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 1)
            {
               return j+1;
            }
         }
			
         // waagerecht pruefen; mitte frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; rechts frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 1 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 0 &&
               iSpielfeld[i+1][j+2] != 0)
            {
               return j+2;
            }
         }

         // waagerecht pruefen; links frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 1 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; mitte frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 1 &&
               iSpielfeld[i][j+3] == 0 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+1;
            }
         }

         // senkrecht pruefen
         if(i+3 < SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j] == 0 &&
               iSpielfeld[i+2][j] == 1 &&
               iSpielfeld[i+3][j] == 1)
            {
               return j;
            }
         }


         // digonal rechts-unten pruefen; unten frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i+1][j+1] == 1 &&
               iSpielfeld[i+2][j+2] == 0 &&
               iSpielfeld[i+3][j+3] == 0 &&
               iSpielfeld[i+3][j+2] != 0)
            {
               return j+2;
            }
         }
			
         // digonal rechts-unten pruefen; oben frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j+1] == 0 &&
               iSpielfeld[i+2][j+2] == 1 &&
               iSpielfeld[i+3][j+3] == 1 &&
               iSpielfeld[i+2][j+1] != 0)
            {
               return j+1;
            }
         }

         // diagonal rechts-oben pruefen; oben frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i-1][j+1] == 1 &&
               iSpielfeld[i-2][j+2] == 0 &&
               iSpielfeld[i-3][j+3] == 0 &&
               iSpielfeld[i-1][j+2] != 0)
            {
               return j+2;
            }
         }

         // diagonal rechts-oben pruefen; unten frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i-1][j+1] == 0 &&
               iSpielfeld[i-2][j+2] == 1 &&
               iSpielfeld[i-3][j+3] == 1 &&
               iSpielfeld[i][j+1] != 0)
            {
               return j+1;
            }
         }
      }
   }
   return -1;
}

/*
   ========================================================================
   Funktion pruefe2SteineComputer()
   Prueft, ob der Computer mit dem naechsten Zug gewonnen hat, es werden
   nur aeussere freie Felder beruecksichtiegt.
   Beispiel: 0XXX000, wobei 0 ein freies Feld darstellt
   Returns: -1 - Kann nicht gewinnen
			0 - 6 - Zug zum gewinnen
   ========================================================================
*/
int pruefe2SteineComputer(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;
   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // waagerecht pruefen; rechts frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; links frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 2)
            {
               return j+2;
            }
         }

         // waagerecht pruefen; rechts frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 0 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; links frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 2 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+2;
            }
         }

         // senkrecht pruefen
         if(i+3 < SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j] == 0 &&
               iSpielfeld[i+2][j] == 0 &&
               iSpielfeld[i+3][j] == 2)
            {
               return j;
            }
         }


         // digonal rechts-unten pruefen; unten frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i+1][j+1] == 0 &&
               iSpielfeld[i+2][j+2] == 0 &&
               iSpielfeld[i+3][j+3] == 0 &&
               iSpielfeld[i][j+1] != 0)
            {
               return j+1;
            }
         }
			
         // digonal rechts-unten pruefen; oben frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j+1] == 0 &&
               iSpielfeld[i+2][j+2] == 0 &&
               iSpielfeld[i+3][j+3] == 2 &&
               iSpielfeld[i+1][j+2] != 0)
            {
               return j+2;
            }
         }

         // diagonal rechts-oben pruefen; oben frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 2 &&
               iSpielfeld[i-1][j+1] == 0 &&
               iSpielfeld[i-2][j+2] == 0 &&
               iSpielfeld[i-3][j+3] == 0 &&
               iSpielfeld[i][j+1] != 0)
            {
               return j+1;
            }
         }

         // diagonal rechts-oben pruefen; unten frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i-1][j+1] == 0 &&
               iSpielfeld[i-2][j+2] == 0 &&
               iSpielfeld[i-3][j+3] == 2 &&
               iSpielfeld[i-1][j+2] != 0)
            {
               return j+2;
            }
         }
      }
   }
   return -1;
}

/*
   ========================================================================
   Funktion pruefe2SteineSpieler()
   Prueft, ob der Computer mit dem naechsten Zug gewonnen hat, es werden
   nur aeussere freie Felder beruecksichtiegt.
   Beispiel: 0XXX000, wobei 0 ein freies Feld darstellt
   Returns: -1 - Kann nicht gewinnen
			0 - 6 - Zug zum gewinnen
   ========================================================================
*/
int pruefe2SteineSpieler(int iSpielfeld[SPIELFELDHOEHE][SPIELFELDBREITE])
{
   int i;
   int j;
   for(i=0; i<SPIELFELDHOEHE; i++)
   {
      for(j=0; j<SPIELFELDBREITE; j++)
      {
         // waagerecht pruefen; rechts frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; links frei; erste Reihe
         if(j+3 < SPIELFELDBREITE && i == SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 1)
            {
               return j+2;
            }
         }

         // waagerecht pruefen; rechts frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 0 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+1;
            }
         }

         // waagerecht pruefen; links frei
         if(j+3 < SPIELFELDBREITE && i != SPIELFELDHOEHE-1)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i][j+1] == 0 &&
               iSpielfeld[i][j+2] == 0 &&
               iSpielfeld[i][j+3] == 1 &&
               iSpielfeld[i+1][j+1] != 0)
            {
               return j+2;
            }
         }

         // senkrecht pruefen
         if(i+3 < SPIELFELDHOEHE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j] == 0 &&
               iSpielfeld[i+2][j] == 0 &&
               iSpielfeld[i+3][j] == 1)
            {
               return j;
            }
         }


         // digonal rechts-unten pruefen; unten frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i+1][j+1] == 0 &&
               iSpielfeld[i+2][j+2] == 0 &&
               iSpielfeld[i+3][j+3] == 0 &&
               iSpielfeld[i][j+1] != 0)
            {
               return j+1;
            }
         }
			
         // digonal rechts-unten pruefen; oben frei
         if(i+3 < SPIELFELDHOEHE && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i+1][j+1] == 0 &&
               iSpielfeld[i+2][j+2] == 0 &&
               iSpielfeld[i+3][j+3] == 1 &&
               iSpielfeld[i+1][j+2] != 0)
            {
               return j+2;
            }
         }

         // diagonal rechts-oben pruefen; oben frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 1 &&
               iSpielfeld[i-1][j+1] == 0 &&
               iSpielfeld[i-2][j+2] == 0 &&
               iSpielfeld[i-3][j+3] == 0 &&
               iSpielfeld[i][j+1] != 0)
            {
               return j+1;
            }
         }

         // diagonal rechts-oben pruefen; unten frei
         if(i-3 >= 0 && j+3 < SPIELFELDBREITE)
         {
            if(iSpielfeld[i][j] == 0 &&
               iSpielfeld[i-1][j+1] == 0 &&
               iSpielfeld[i-2][j+2] == 0 &&
               iSpielfeld[i-3][j+3] == 1 &&
               iSpielfeld[i-1][j+2] != 0)
            {
               return j+2;
            }
         }
      }
   }
   return -1;
}
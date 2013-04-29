/*
============================================================================
Autor		: Tobias Niggemann
Klasse		: FA13
Dateiname	: bridges.c
Datum		: 
Beschreibung: 
Version		: 1
============================================================================
*/

/*
==============================================================================
Include Anweisungen
==============================================================================
*/

#include "bridges.h"

/*
============================================================================
Erklärung Return-Werte der Funktion Spielzug():
0  - Spieler 2 gewinnt. Das Spiel wird beendet.
1  - Spieler 1 gewinnt. Das Spiel wird beendet.
3  - Normal verlaufener Spielzug. Nächster Spieler ist am Zug.
4  - Spiel neustart
5  - Auswahl "n" bei Spielabbruch. Spielzug wird wiederholt.
-1 - Auswahl "j" bei Spielabbruch. Spielzug wird abgebrochen.
============================================================================
*/


/*
============================================================================
Funktion:		starteBridges()
in:				-
out:			Gewinnvalidierung:
				0  - Spieler 2 gewinnt. Das Spiel wird beendet.
				1  - Spieler 1 gewinnt. Das Spiel wird beendet.
				-1 - Auswahl "j" bei Spielabbruch. Spielzug wird abgebrochen.
Beschreibung:	Hauptfunktion, aus der die Spielzüge aufgerufen werden.
============================================================================
*/
float starteBridges(void)
{

   int iSpielzug;
   int iNeustart = 0;
   
   
   while(1)
   {
         
      fuelleArrayBridges();

	  /*
	  ===============================================================
	  Wenn die Neustartvariable geändert wird, wir die Schleife
	  verlassen. In diesem Fall wird das Array innerhalb der while(1)
	  Schleife neu gefüllt und quasi resetted.
	  ==============================================================
	  */

      while(iNeustart == 0)		
      {   
         iSpielzug = 5;   // Zurücksetzen der Variable.

         while(iSpielzug == 5)
            {
               iSpielzug = spielzugBridges(1);   // s. "Erklärung Return-Werte der Funktion Spielzug()"
               if( iSpielzug == 1)	
				  { g_fReturnBridges = 1;
				   beendenBridges();					// Spiel wurde gewonnen.
                  return 1;
				  }
               if( iSpielzug == -1)				// Spiel wurde abgebrochen
                   { g_fReturnBridges = -1;
					beendenBridges();					
					return -1;
				  }
               if(iSpielzug == 4)				// Spiel wird neugestartet.
                  iNeustart = 1;
            }


         iSpielzug = 5;

         if(iNeustart == 0)			
            {
               while(iSpielzug == 5)
                  {
                     iSpielzug = spielzugBridges(2); // s. "Erklärung Return-Werte der Funktion Spielzug()"
                     if( iSpielzug == 0)	// Spiel wurde gewonnen.
					  { g_fReturnBridges = 0;
						beendenBridges();					
						return 0;
				  }
                     if( iSpielzug == -1)	// Spiel wurde abgebrochen
                         { g_fReturnBridges = -1;
							beendenBridges();					
							return -1;
				  }
                     if(iSpielzug == 4)		// Spiel wird neugestartet.
                        iNeustart = 1;
                  }
            }
      }
      iNeustart = 0;
   }
   
}

/*
============================================================================
Funktion:		fuelleArrayBridges()
in:				-
out:			-
Beschreibung:	Initiale Füllung des Arrays mit dem Schachbrettmuster. Aufruf 
				bei Spielstart oder Neustart.
============================================================================
*/



void fuelleArrayBridges()
{
   int i, j, k;            // zählvariablen
    // Definition der Feldfarben:
   char cWeiss = '0';	      // Weiss
   char cBlau  = '1';	      // Blau
   char cRot   = '2';	      // Rot
   char cSenkrecht = '\xB3';  //senkrechter Strich
   char cWaagerecht = '\xC4'; //waagerechter Strich
   char cKreuz = '\xC5';      //Kreuz
   char cBuchstabe = 65;	  // ASCII - Code für 'A'-Ausgabe Buchstaben-Leiste
   char cZahl = 49;			  // ASCII - Code für 1 - Ausgabe Zahlen-Leiste

   cBrettBridges[0][2] = cSenkrecht;    // erste Zeile mit den Buchstaben füllen
   
   for (j=4; j<54; j+=3)				// Buchstabendefinition
   {
      cBrettBridges[0][j+1] = ' ';		// Leerzeichen zwischen den Buchstaben
      cBrettBridges[0][j] = cBuchstabe; // Definition des Buchstabens
      cBuchstabe++;						// Hochzählen des ASCII - Codes -> Nächster Buchstabe
   }

   // zweite Zeile füllen - Waagerechte Trennlinie 

   for (j=0; j<58; j++)
   {
      cBrettBridges[1][j] = cWaagerecht;
   }

   cBrettBridges[1][2] = cKreuz;	  //  Trennkreuz


   // linke Spalten mit Zahlen
   for (i=2; i<57; i=i+2) 
   {
      if(cZahl > 57) 
		  // ASCII 57 = Nummerisch 9.
		  // Ab 10: Ausgabe der Einerstelle mit '1' davor. 
         {
            cBrettBridges[i][0] = 49;
            cBrettBridges[i][1] = cZahl-10;
         }

      else
		 // Bis 10: Nur Ausgabe der Einerstelle. Zeichen davor wir Leerstelle.
         {
               cBrettBridges[i][1] = cZahl;
         }

         cZahl++; 
		 // Hochzählen des ASCII - Wertes. 
   }


   // Senkrechte Trennlinie
   j = 0;
   for (i=2; i<42; i=i++) 
      {
         cBrettBridges[i][2] = cSenkrecht;
      }


   // Array mit Spielerwerten füllen.
   for (i=2; i <= 35; i++)
   {
   // Zeilen, die blau benutzen: Alle ungraden Zeilen.
   // Werte sind die tatsächlichen Werte im Array.
   // Ein Feld ist drei Zeichen breit
       if (i == 2 ||i == 3 ||i == 6 ||i == 7 ||i == 10 ||i == 11 ||i == 14 ||i == 15 ||i == 18
          ||i == 19||i == 22||i == 23||i == 26||i == 27||i == 30||i == 31||i == 34||i == 35)
         {
         for (j=3;j<=55;j+=6)
            {
			// Farbverlauf aller Spalten, außer der letzten.
            if (j!=51) 
               {
                  cBrettBridges[i][j] = cWeiss;
                  cBrettBridges[i][j+1] = cWeiss;
                  cBrettBridges[i][j+2] = cWeiss;


                  cBrettBridges[i][j+3] = cBlau;
                  cBrettBridges[i][j+4] = cBlau;
                  cBrettBridges[i][j+5] = cBlau;
               }

            // letzte Spalte muss weiß sein, wenn sie mit Blau beginnt.
             else               
               {
                  cBrettBridges[i][j] = cWeiss;
                  cBrettBridges[i][j+1] = cWeiss;
                  cBrettBridges[i][j+2] = cWeiss;
               }

            }
         }


	    // Zeilen, die rot benutzen: Alle graden Zeilen.
		// Werte sind die tatsächlichen Werte im Array.
	    // Ein Feld ist drei Zeichen breit.
      else 
         {
         for (k=3; k<=54; k+=6)
            {
               if (k != 51)
               {
                  cBrettBridges[i][k] = cRot;
                  cBrettBridges[i][k+1] = cRot;
                  cBrettBridges[i][k+2] = cRot;

                  cBrettBridges[i][k+3] = cWeiss;
                  cBrettBridges[i][k+4] = cWeiss;
                  cBrettBridges[i][k+5] = cWeiss;
                  }
			   // letzte Spalte muss rot sein
               else 
               {   
                  cBrettBridges[i][k] = cRot;
                  cBrettBridges[i][k+1] = cRot;
                  cBrettBridges[i][k+2] = cRot;
               }
            }
         }
      cBrettBridges[2][0] = ' ';
   }
      
}


/*
============================================================================
Funktion:		ausgabeArrayBridges()
in:				-
out:			 -
Beschreibung:	Ausgabe des Schachbrettmusters
============================================================================
*/

void ausgabeArrayBridges()
{
   // Zählvariablen
   int i;
   int j;


   // Ausgabe des Headers.
   printf("================================================================================");
   printf("              $$$$$$$  $$$$$$$  $$ $$$$$  $$$$$$  $$$$$$ $$$$$$                 ");
   printf("             $$    $$ $$    $$ $$ $$  $$ $$      $$     $$                      ");
   printf("            $$ $$$$  $$ $$$$$ $$ $$  $$ $$ $$$  $$$$$$ $$$$$$                   ");
   printf("           $$   $$  $$  $$   $$ $$  $$ $$   $$ $$         $$                    ");
   printf("          $$$$$$$  $$   $$  $$ $$$$$    $$$$  $$$$$$ $$$$$$                     ");
   printf("================================================================================");
   printf("\n");


   for (i = 0; i < 36; i++)
   {
	   printf("\t");
      for (j = 0; j < 54; j++)
      {
		  if (i != 0 && i!=1 &&  j != 0 && j!=1 && j!=2)
		  {

		  switch(cBrettBridges[i][j])
			 {
				 // Setzen der Zeigerfarbe auf Weiss.
				 // Wenn Feldwert = 0 dann Ausgabe weisses Feld
				case '0': 
				
				   zeigerFarbe(0);
				   printf("\xB2");
				   break;  

				
				// Setzen der Zeigerfarbe auf Blau.
				// Wenn Feldwert = 1 dann Ausgabe blaues Feld
				case '1':
				   zeigerFarbe(1);
				   printf("\xB1");
				   zeigerFarbe(0);
				   break;

				// Setzen der Zeigerfarbe auf Rot.
				// Wenn Feldwert = 0 dann Ausgabe rotes Feld
				case '2':
				   zeigerFarbe(2);
				   printf("\xB1");
				   zeigerFarbe(0);
				   break;
			 }
      
		  }

		  else
			  {
				 // Setzen der Zeigerfarbe auf Weiss.
				 zeigerFarbe(0);
				 printf("%c", cBrettBridges[i][j]);
			  }
		 }
      printf("\n");
      
   }
   // Setzen der Zeigerfarbe auf Weiss.
   zeigerFarbe(0);
   printf("\n");
   printf("          x:Hauptmenue          s:Hilfe          w:Neues Spiel\n");
}


/*
============================================================================
Funktion:		spielzugBridges()
in:				iSpieler 
out:			-
Beschreibung:	Abfragen der Spielereingaben und Ändern der array-Werte
============================================================================
*/


int spielzugBridges(int iSpieler)
   {
      int iPruefArray[40][54];         //Prüf-Array, identisch zu cBrettBridges. 
      int iEingabeHoehe, i, k, iHoehe = 0 , iBreite = 0;
      char cSpieler, cEingabe_Breite;
      char cWeiss = '0';  // Weiss
      char cBlau = '1';   // Blau
      char cRot = '2' ;   // Rot

	  // Neuladen des Spielbretts.
      erneuerFeld(); 

	  // Kurzlegende mit Spielregeln.
      printf("\n");
	  printf("          Der blaue Spieler muss eine Bruecke von 1 - 17 bauen.");
	  printf("\n");
      printf("          Der Rote von A - Q\n\n");

      switch(iSpieler)  //Ausgabe, welcher Spieler am Zug ist.
         {
         case 1: 
			//Spieler 1 - Blau
            printf("          %s (Blau) ist am Zug\n", g_cSpieler1);
            break;
         case 2: 
			//Spieler 2 - Rot
            printf("          %s (Rot) ist am Zug\n", g_cSpieler2);
            break; 
         }
    

      
       //Benutzereingaben anfordern und abfangen
		printf("          Bitte waehlen Sie eine Breite aus! (A-Q) \n");
		printf("          X: ");
		fflush(stdin);
		scanf_s("%c", &cEingabe_Breite);
      
      
       
      //Mapping der Benutzereingabe(cEingabe_Breite) auf die tatsächliche Feldposition im Array.
      switch(cEingabe_Breite)
      {
         case 'a':
         case 'A': 
            iBreite = 3;
            break;
         case 'b':
         case 'B': 
            iBreite = 6;
            break;
         case 'c':
         case 'C': 
            iBreite = 9;
            break;
         case 'd':
         case 'D':
            iBreite = 12;
            break;
         case 'e':
         case 'E': 
            iBreite = 15;
            break;
         case 'f':
         case 'F': 
            iBreite = 18;
            break;
         case 'g':
         case 'G': 
            iBreite = 21;
            break;
         case 'h':
         case 'H': 
            iBreite = 24;
            break;
         case 'i':
         case 'I': 
            iBreite = 27;
            break;
         case 'j':
         case 'J': 
            iBreite = 30;
            break;
         case 'k':
         case 'K': 
            iBreite = 33;
            break;
         case 'l':
         case 'L': 
            iBreite = 36;
            break;
         case 'm':
         case 'M': 
            iBreite = 39;
            break;
         case 'n':
         case 'N': 
            iBreite = 42;
            break;
         case 'o':
         case 'O': 
            iBreite = 45;
            break;
         case 'p':
         case 'P': 
            iBreite = 48;
            break;
         case 'q':
         case 'Q': 
            iBreite = 51;
            break;
         case 's':
         case 'S':
            aufrufHilfeBridges();
            return 5;
            break;
         case 'w':
         case 'W': 
          /*  if(neustartSpiel() == 1)
            {
            return 4;
            }
            else
            {
               erneuerFeld();
               return 5;
            }
		*/
			 return 4;
         case 'x':
         case 'X': 
           /* if(spielabbruch() == 1)
            {
               return -1;
            }

            else
            {
               erneuerFeld();
               return 5;
            }
            break; */
			return -1;
         default:

            printf("\n          Bitte waehlen Sie einen gueltigen Wert.\n\n");
			system("PAUSE");
            return 5;
            break;
      }


	  // Eingabeaufforderung Höhe
      printf("          Bitte waehlen Sie eine Hoehe aus! (1-17) \n");
	  printf("          Y: ");
      fflush(stdin);
      scanf_s("%i", &iEingabeHoehe);

      

      // Mapping der iEingabeHoehe auf die tatsächliche Feldposition im Array.
      switch(iEingabeHoehe)
      {
         case 1: 
            iHoehe = 2;
            break;
         case 2: 
            iHoehe = 4;
            break;
         case 3: 
            iHoehe = 6;
            break;
         case 4: 
            iHoehe = 8;
            break;
         case 5: 
            iHoehe = 10;
            break;
         case 6: 
            iHoehe = 12;
            break;
         case 7: 
            iHoehe = 14;
            break;
         case 8: 
            iHoehe = 16;
            break;
         case 9: 
            iHoehe = 18;
            break;
         case 10: 
            iHoehe = 20;
            break;
         case 11: 
            iHoehe = 22;
            break;
         case 12: 
            iHoehe = 24;
            break;
         case 13: 
            iHoehe = 26;
            break;
         case 14: 
            iHoehe = 28;
            break;
         case 15: 
            iHoehe = 30;
            break;
         case 16: 
            iHoehe = 32;
            break;
         case 17: 
            iHoehe = 34;
            break;
		default:
            erneuerFeld();
            printf("\n          Bitte waehlen Sie einen gueltigen Wert.\n\n");
			system("PAUSE");
            return 5;
            break;
         }
      

	  //fehlzugBridges output: 1 bei "Feld ist weiß". 0 bei "Feld ist schon belegt"
      if (fehlzugBridges(iBreite,iHoehe)) 
      {   

         if (iSpieler == 1)
         {
            cSpieler = cBlau;
         }

         if (iSpieler == 2)
         {
            cSpieler = cRot;
         }

		 // Füllen des ausgewählten Feldes mit dem Farbcode.
		 // Feldgröße: 3x2
         cBrettBridges[iHoehe][iBreite] = cSpieler;
         cBrettBridges[iHoehe][iBreite + 1] = cSpieler;
         cBrettBridges[iHoehe][iBreite + 2] = cSpieler;
         cBrettBridges[iHoehe+1][iBreite] = cSpieler;
         cBrettBridges[iHoehe+1][iBreite + 1] = cSpieler;
         cBrettBridges[iHoehe+1][iBreite + 2] = cSpieler;


		 //Nullen des Prüfarrays vor der Prüfung
         for(i=0;i<40;i++) 
         {
            for (k=0;k<54;k++)
            {
               iPruefArray[i][k] = 0;
            }
         }

         

		 // Siegprüfung Spieler 1
		 if (iSpieler == 1)    
		 {
			 // Prüfe alle Pfade von allen Spalten ausgehend.
			for(k = 3; k<=54; k+=3)
			{
				if(pruefeBridges(cSpieler, k, 3, iPruefArray) == 1)
				{
					return 1; // Ausgabe 1 wenn Spieler 1 gewonnen hat.
				}
			}
         
		 }

		// Siegprüfung Spieler 2 
		if (iSpieler == 2)  
		{
			for(k = 3; k<=40; k+=2)
			{	// Prüfe alle Pfade von allen Zeilen ausgehend.
				if(pruefeBridges(cSpieler, 4, k, iPruefArray) == 1)
				{
					return 0; // Ausgabe 0 wenn Spieler 2 gewonnen hat.
				}
			}
		}
    

         }
      
      else
         {     
			// Auswahl eines bereits belegten Feldes.
            printf("          Bitte wählen Sie ein freies Feld \n\t");
			system("PAUSE");
            return 5;
         }
   
      return 3;
   }

      


/*
============================================================================
Funktion:			fehlzugBridges()
in:					iBreite, iHoehe
out:				1 bei "Feld ist weiß"
					0 bei "Feld ist schon belegt"
Beschreibung:		Die Funktion prüft das übergebene Feld. Ist es weiß, 
					wird 1 zurückgegeben und das Feld kann gefüllt werden. 
					Ansonsten ist derRückgabewert 0 und wird in der Spielzug() 
					abgefangen.
============================================================================
*/


int fehlzugBridges(int iBreite, int iHoehe)
   {

      if(cBrettBridges[iHoehe][iBreite] != '0')
         {
            return 0;  // Feld ist nicht weiß
         }


      else 
         {
            return 1;   // Feld ist  weiß
         }
   }





/*
============================================================================
Funktion:		pruefeBridges(char cSpieler, int iBreite, int iHoehe)
in:				cSpieler, iBreite, iHoehe,  iPruefArray[][54]
out:			1  -  Spieler hat gewonnen
				0  -  geprüftes Feld hat nicht die gesuchte Spielfarbe
Beschreibung:	Der Funktion werden die Feldwerte übergeben, von denen aus 
				sie	prüft, ob das Feld die entsprechende Spieler-Farbe hat. 
				Hat es sie, werden alle anliegenden Felder geprüft, bis der 
				Pfad endet oder der Spieler gewonnen hat. 
============================================================================
*/

int pruefeBridges(char cSpieler, int iBreite, int iHoehe, int iPruefArray[][54])
   {
	/* 
		======================================================================
		iPruefArray ist ein Prüfarray. Wurde das entsprechende Feld in diesem Spielzug 
	    schon geprüft, hat das Array-Feld den Wert 1 und wird nicht noch einmal 
		geprüft. Ansonsten wird es geprüft und der Wert auf 1 gesetzt.
		Dies verhindert, dass die Prüfung in Endlosschleifen gerät.
	    ======================================================================
	*/

	// Prüfen, ob Feld bereits gecheckt wurde.
   if (iPruefArray[iHoehe][iBreite] != 1) 
      {
		  // Feld wird mit 1 als geprüft deklariert.
         iPruefArray[iHoehe][iBreite] = 1;
      



		 // Wenn das Feld die zu prüfende Farbe hat, 
		 // werden alle anliegenden Felder ebenfalls geprüft.

         if(cBrettBridges[iHoehe][iBreite] == cSpieler)
         {
			// Funktion prüft, ob Spieler gewonnen hat und 
			//das Spiel damit beendet ist.
            if (!pruefeSiegBridges(cSpieler, iBreite, iHoehe))
            {   
				// Prüfung aller anliegenden Felder. rekursiver Aufruf
               if(pruefeBridges(cSpieler, iBreite + 3, iHoehe, iPruefArray))
                  return 1;
               if(pruefeBridges(cSpieler, iBreite, iHoehe + 2, iPruefArray))
                  return 1;
               if(pruefeBridges(cSpieler, iBreite - 3, iHoehe, iPruefArray))
                  return 1;
               if(pruefeBridges(cSpieler, iBreite, iHoehe - 2, iPruefArray))
                  return 1;
            }

            else
            {
				// Wenn Spieler das Spiel gewonnen hat, gibt die Funktion 1 zurück.
               return 1;
            }


         }
         
   
         }
   // Wenn das geprüfte Feld nicht die gesuchte Spielerfarbe hat, return 0
   return 0;
   }   

   
   
/*
============================================================================
Funktion:		pruefeSiegBridges()
in:				cSpieler, iBreite, iHoehe
out:			1 - Wenn Spieler Siegbedingung erfüllt ist.
				0 - Wenn Spieler Siegbedingung nicht erfüllt ist.
Beschreibung:   Prüfung, ob der Spieler die Brücke von einer Seite bis zur 
				anderen vollständig erstellt hat.
============================================================================
*/
int pruefeSiegBridges(char cSpieler, int iBreite, int iHoehe)
{
      if (cSpieler == '1')
      {
		// Spieler 1 muss im Feld oben nach unten gelangen. 
		//Wirkliche Spielfeldhöhe im Array: 37
         if (iHoehe >= 34)
         {
            return 1;
         }

      }
      else if (cSpieler == '2')
      {
		// Spieler 2 muss im Feld von links nach rechts gelangen. 
		//Wirkliche Spielfeldbreite im Array: 54
         if (iBreite >= 51)
         {      
            return 1;
         }
      }

      return 0;
}
/*
============================================================================
Funktion:		erneuerFeld()
in:				- 
out:			-
Beschreibung:	leert den Bildschirm und gibt das Spielfeld neu aus.
============================================================================
*/
void erneuerFeld(void)
{
	system("cls");
    ausgabeArrayBridges();
}
/*
============================================================================
Funktion:		aufrufHilfeBridges()
in:				- 
out:			-
Beschreibung:	ruft die Online-Hilfe auf
============================================================================
*/
void aufrufHilfeBridges(void)
{
	system("START bridges-hilfe.html");
}

/*
============================================================================
Funktion:		zeigerFarbe()
in:				iFarbwert
out:			-
Beschreibung:	zeigt die Farben auf der Konsole
============================================================================
*/
void zeigerFarbe(int iFarbwert)
{
	if(iFarbwert == 0)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	else if(iFarbwert == 1)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	else if (iFarbwert == 2)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
}
/*
================================================================================
Name: Beenden()
In: -
Out: -
Parameter: 
Comment:         
                             Package: 
================================================================================
*/
void beendenBridges(void)
{
	if(g_fReturnBridges == 0)
	{
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
		printf("\n\n");
		printf("Herzlichen Glueckwunsch.\n %s hat gewonnen!!\n\n", g_cSpieler2);
		printf("\n");
	}
	if(g_fReturnBridges == 1)
	{
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
		printf("\n\n");
		printf("Herzlichen Glueckwunsch.\n %s hat gewonnen!!\n\n", g_cSpieler1);
		printf("\n");
	}
	if(g_fReturnBridges == -1)
	{
		system("cls");
		printf("================================================================================");
		printf("              $$$$$$$  $$$$$$$  $$ $$$$$  $$$$$$  $$$$$$ $$$$$$                 ");
		printf("             $$    $$ $$    $$ $$ $$  $$ $$      $$     $$                      ");
		printf("            $$ $$$$  $$ $$$$$ $$ $$  $$ $$ $$$  $$$$$$ $$$$$$                   ");
		printf("           $$   $$  $$  $$   $$ $$  $$ $$   $$ $$         $$                    ");
		printf("          $$$$$$$  $$   $$  $$ $$$$$    $$$$  $$$$$$ $$$$$$                     ");
		printf("================================================================================");
		printf("\n\n");
		printf("\t Sie haben das Spiel beendet. ");
		printf("\n");
		printf("\t Es findet keine Wertung statt.");
	}
	printf("\n\n\t ");
    system("pause");
 }

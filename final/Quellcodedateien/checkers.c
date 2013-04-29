/*
==============================================================================
Author: Sebastian Weis
Firma: TARGO IT Consulting GmbH
PGM: checkers.c
Version: 1.0
Comment: Das Spiel "Checkers".
         <<<For internal use only>>>
==============================================================================
*/
/*
==============================================================================
Include Anweisungen
==============================================================================
*/

#include "checkers.h"

/*
==============================================================================
Name:         starteCheckers()
In:            -
Out:         float
Parameter:      Rückgabewert des gesamten Spiels:
   
            |   Wert   |   Bedeutung   | 
            |----------|---------------|
            |    -1    |    Abbruch    |    
            |     0    |  Sieg Sp. 2   |
            |   0,5    | Unentschieden |
            |     1    |  Sieg Sp. 1   |
            |----------|---------------|         
Beschreibung:   Durchläuft die gesamte Spiellogik. Gibt den entsprechenden #
            Return-Wert an das Hauptmenü zurück.

                             Package: OK
==============================================================================
*/
float starteCheckers(void)
{
   g_cBeenden = 'n';
   g_cNeustart = 'n';
   g_iAnzahlSteine = 0; 
   g_iPlayer = 1;
   g_iStep = 0;
   g_iSprung = 0;
   g_iBewegung = 0;
   g_iExitFlag = 0;

   do
    {
      switch(g_iStep)
        {
          //Setzen des Spielfeldes      
         case 0: setzeStartSpielfeld();            
         break;
         /*
         -> Prüfen ob Spielsteine vorhanden sind
         */
         case 1: pruefeSpielsteinVorhanden();
               /*
               Wenn ein Spieler keinen Spielstein mehr hat
               wird das Spiel beendet und der entsprechende
               Returncode gesetzt.
               */
               if(g_iAnzahlSpieler1 == 0 || g_iAnzahlSpieler2 == 0)
               {
                  if(g_iPlayer == 1)
                  {
                     g_fExitCode = 1;
                  }
                  else
                  {
                     g_fExitCode = 0;
                  }
                  g_iStep = 6;
               }
               else
               {
                  /*
                  Haben beide Spieler jeweils nur noch einen Spielstein,
                  ist es sehr unwahrscheinlich das dass Spiel noch 
                  gewonnen werden kann und es geht unentschieden aus.
                  */               
                  if(g_iAnzahlSpieler1 == 1 && g_iAnzahlSpieler2 == 1)
                  {
                     g_cBeenden = 'j';
                     g_fExitCode = 0,5;
                  }
               }
               /*
               Kann der aktuelle Spieler keinen gültigen Zug 
               ausführen, hat der andere Spieler gewonnen
               */
               if(g_iBewegung == 0)
               {
                  g_iStep = 6;
                  if(g_iPlayer == 1)
                  {
                     g_iPlayer = 2;
                     g_fExitCode = 0;
                  }
                  else
                  {
                     g_iPlayer = 1;
                     g_fExitCode = 1;
                  }
               }              
         break;
         case 2: /*
               Ist kein Sprung möglich kann der Spieler einen beliebigen
               Spielstein auswählen
               */
               if(g_iSprung == 0)
               {
                  waehleSpielstein();
               }
               /*
               Ansonsten muss er den bzw. einen der Sprungsteine wählen
               mit dem er einen gegnerischen Spielstein schlagen kann
               */
               else
               {
                  sprungSpielstein(g_cSpielfeld[g_iSteinX][g_iSteinY]);
               } 
         break;
         case 3: //Spieler muss eines der markierten Zielfelder wählen
               waehleZiel();
         break;
         case 4: //Überprüfung ob normale Spielsteine zur Dame werden
               wandleZuDame();
         break;
         case 5: //Spieler werden gewechselt
               wechselSpieler();  
         break;
         case 6: //Spiel wird beendet
               beenden();
         break;
         default: g_cBeenden = 'j';
      }                   
   }
   /*
   Solange das Spiel nicht beendet wurde soll die gesamte
   Spiellogik ausgeführt werden.
   */
   while(g_cBeenden != 'j');


   /*
   Zurücksetzen aller Variablen
   */
   g_iAnzahlSteine = 0;
   g_iPlayer = 1;
   g_iStep = 0;
   g_cBeenden = 'n';
   g_iSprung = 0;
   g_iBewegung = 0;
   g_cNeustart = 'n';
   g_iExitFlag = 0;
    
   //Rückgabe des entsprechenden Wertes
   return g_fExitCode;       
}
/*
==============================================================================
Name:         setzeStartSpielfeld()
In:            -
Out:         -
Parameter:      -
Beschreibung:   Füllt das Array mit Platzhaltern und den Spielsteinen.
            Spielsteine Spieler1: H
            Spielsteine Spieler1: C

                             Package: OK
==============================================================================
*/
void setzeStartSpielfeld(void)
{
   int i, h;
   /*
   Platzhalter werden generiert.
   */
   for(i = 0; i < 8; i++)
   {
      for(h = 0; h < 8; h++)
      {
         g_cSpielfeld[i][h] = '-' ;
      } 
   }
    
   /*
   Spielsteine des 1. Spielers werden gesetzt
   */
   for(i = 5; i < 8; i++)
   {
      if(i == 5)
      {
         //1. Reihe
         for(h = 0; h < 8; h = h+2)
         {
            g_cSpielfeld[i][h] = 'H';
         }
      }
      if(i == 6)
      {
         //2. Reihe
         for(h = 1; h < 8; h = h+2)
         {
            g_cSpielfeld[i][h] = 'H';
         }               
      }
      if(i == 7)
      {
         //3. Reihe
         for(h = 0; h < 8; h = h+2)
         {
            g_cSpielfeld[i][h] = 'H';
         }
      } 
   }    
   
   /*
   Spielsteine des 2. Spielers werden gesetzt
   */
   for(i = 0; i < 3; i++)
   {
      if(i == 0)
      {
         //1. Reihe
         for(h = 1; h < 8; h = h+2)
         {
            g_cSpielfeld[i][h] = 'C';
         }
      }
      if(i == 1)
      {
         //2. Reihe
         for(h = 0; h < 8; h = h+2)
         {
            g_cSpielfeld[i][h] = 'C';
         }               
      }
      if(i == 2)
      {
         //3. Reihe
         for(h = 1; h < 8; h = h+2)
         {
            g_cSpielfeld[i][h] = 'C';
         }
      } 
   }

   strcpy(g_cAktuellerSpieler, g_cSpieler1);

   g_iAnzahlSpieler1 = 12;
   g_iAnzahlSpieler2 = 12;
   
   g_iStep = 1;      
}
/*
==============================================================================
Name:         schreibe()
In:            -
Out:         -
Parameter:      -
Beschreibung:   Gibt das aktuelle Array auf der Konsole aus.

                             Package: OK
==============================================================================
*/
void schreibe(void)
{
   int i, h;
   char cZahl = 49;
   char cBuchstabe = 65;
   
   system("cls");
   
   //Horizontale Trennlinien
   for(h = 0; h <= 57; h++)
   {
      g_cAusgabe[1][h] = '\xC4';
   }
   g_cAusgabe[0][1] = '\xB3';
   g_cAusgabe[1][1] = '\xC5';
   
   //Vertikale Trennlinien
   for(i = 2; i <= 41; i++)
   {
      g_cAusgabe[i][1] = '\xB3';
   }
   
   //Reihen Bezeichnung (A-H)
   for(h = 5; h <= 57; h = h+7)
   {
      g_cAusgabe[0][h] = cBuchstabe;
      cBuchstabe++;
   }
   
   //Spalten Bezeichnung (1-8)
   for(i = 4; i <= 42; i = i+5)
   {
      g_cAusgabe[i][0] = cZahl ;
      cZahl++;
   }
   
   /* Setzen der Feldschattierungen
   durch Aufruf der Funktionen */
   fuelleReiheWeiss(2, 2); // 1. Reihe
   fuelleReiheSchwarz(7, 2); // 2. Reihe
   fuelleReiheWeiss(12, 2); // 3. Reihe
   fuelleReiheSchwarz(17, 2); // 4. Reihe
   fuelleReiheWeiss(22, 2); // 5. Reihe
   fuelleReiheSchwarz(27, 2); // 6. Reihe
   fuelleReiheWeiss(32, 2); // 7. Reihe
   fuelleReiheSchwarz(37, 2); // 8. Reihe
    
   //Setzen der Spielsteine
   for(i = 0; i <= 7; i++)
   {
      for(h = 0; h <= 7; h++)
      {
         if(g_cSpielfeld[i][h] != '-')
         {
            /* 
            Aufruf der Funktion schreibeStein
            mit den Paramatern (i,h) für die Position
            im Array (X- & Y-Koordinate) sowie dem char
            der in dem Array bei (i|h) gespeichert ist
            */
            schreibeStein(i, h, g_cSpielfeld[i][h]);
         }
      }
   }

   printf("===============================================================");
   printf("=================");
   printf("         $$$$$$$   $$  $$  $$$$$$ $$$$$$   $$ $$$  $$$$$$ $$$$$");
   printf("$$  $$$$$$       ");
   printf("        $$    $$  $$  $$  $$     $$   $$  $$ $$   $$     $$    ");
   printf("$$ $$            ");
   printf("       $$        $$$$$$  $$$$$  $$       $$$$$   $$$$   $$ $$$$");
   printf("  $$$$$$$        ");
   printf("      $$    $$  $$  $$  $$     $$   $$  $$ $$   $$     $$   $$ ");
   printf("      $$         ");
   printf("      $$$$$$$  $$  $$  $$$$$$$ $$$$$$  $$   $$ $$$$$$ $$    $$ ");
   printf("$$$$$$$          ");
   printf("===============================================================");
   printf("=================");
   
   //Ausgabe des Arrays auf der Konsole
   printf("\n");
   for(i = 0; i <= 41; i++)
   {
      printf("\t");         
      for(h = 0; h <= 57; h++)
      {
         if((g_cAusgabe[i][h] != 'H' && g_cAusgabe[i][h] != 'Q' 
          && g_cAusgabe[i][h] != 'C' && g_cAusgabe[i][h] != 'K') || i == 0)
         {
            /*
            Alle Felder und die Legenden sollen normal dargestellt werden.
            */
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
               FOREGROUND_BLUE | FOREGROUND_RED | 
               FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("%c", g_cAusgabe[i][h]);
         }
         else
         {
            if(g_cAusgabe[i][h] == 'H' && i != 0)
            {
               /*
               Alle normalen Spielsteine des ersten Spielers 
               sollen blau dargestellt werden
               */
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                  FOREGROUND_BLUE | FOREGROUND_INTENSITY);
               printf("%c", g_cAusgabe[i][h]);
               /*
               Ausgabe der Konsole wird zurück gesetzt
               */
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                  FOREGROUND_BLUE | FOREGROUND_RED | 
                  FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            if(g_cAusgabe[i][h] == 'Q' && i != 0)
            {
               /*
               Alle damen des ersten Spielers 
               sollen schwarz/blau dargestellt werden
               */
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                  BACKGROUND_BLUE | FOREGROUND_RED | 
                  FOREGROUND_GREEN | FOREGROUND_BLUE);
               printf("%c", g_cAusgabe[i][h]);
               /*
               Ausgabe der Konsole wird zurück gesetzt
               */
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                  FOREGROUND_BLUE | FOREGROUND_RED | 
                  FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            if(g_cAusgabe[i][h] == 'C' && i != 0)
            {
               /*
               Alle normalen Spielsteine des zweiten Spielers
               sollen rot dargestellt werden
               */
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                  FOREGROUND_RED | FOREGROUND_INTENSITY);
               printf("%c", g_cAusgabe[i][h]);
               /*
               Ausgabe der Konsole wird zurück gesetzt
               */
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                  FOREGROUND_BLUE | FOREGROUND_RED | 
                  FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            if(g_cAusgabe[i][h] == 'K' && i != 0)
            {
               /*
               Alle damen des zweiten Spielers 
               sollen schwarz/rot dargestellt werden
               */
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                  BACKGROUND_RED);
               printf("%c", g_cAusgabe[i][h]);
               /*
               Ausgabe der Konsole wird zurück gesetzt
               */
               SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                  FOREGROUND_BLUE | FOREGROUND_RED | 
                  FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }   
         }
      }
      printf("\n");
   }
   
   //schreibe Legende
   printf("\n");
   printf("          x:Hauptmenue          s:Hilfe          w:Neues Spiel");
   printf("\n");   
   
   printf("\n");
   if(g_iPlayer == 1)
   {
      printf("          %s (blau) ist an der Reihe!", g_cAktuellerSpieler);
   }
   else
   {
      printf("          %s (rot) ist an der Reihe!", g_cAktuellerSpieler);
   }
   printf("\n");           
}
/*
==============================================================================
Name: schreibeStein()
In:            iXmp, iYmp, cSpielstein
Out:         -
Parameter:      Position des Feldes sowie dessen Buchstabe/Zeichen
Beschreibung:   Schreibt den aktuellen Buchstaben in die Koordinaten des 
            Arrays,   ausgehend von:
            |         Formel            |   Form des Steins  |
            |-------------------------------|--------------------|
            |1.) 3+(5*iXmp) und 4+(7*iYmp)  |        ===         |
            |2.) 4+(5*iXmp) und 3+(7*iYmp)  |       =====        |
            |3.) 5+(5*iXmp) und 4+(7*iYmp)  |        ===         |
            |-------------------------------|--------------------|
                    
            Diese Formeln sind nötig, um die Position des Daten-Arrays
            cSpielfeld[8][8] in das Array cAusgabe[42][58] zu konvertieren.

                             Package: OK
==============================================================================
*/
void schreibeStein(int iXmp, int iYmp, char cSpielstein)
{
   int i = 3+(5*iXmp); 
   int h = 4+(7*iYmp);
   int iMaxY = h+2;

   /*
   Liegt auf dem Feld ein Spielstein so soll
   die Form des Spielsteins ausgegeben werden
   */
   if(cSpielstein == 'H' || cSpielstein == 'Q' 
   || cSpielstein == 'C' || cSpielstein == 'K')
   {
      /*
      Erste Spielstein Reihe
      */
      while(h <= iMaxY)
      {
         g_cAusgabe[i][h] = cSpielstein;
         h++;   
      }
   
      /*
      Zweite Spielstein Reihe
      */   
      i = 4+(5*iXmp); 
      h = 3+(7*iYmp);
      iMaxY = h+4;

      while(h <= iMaxY)
      {
         g_cAusgabe[i][h] = cSpielstein;
         h++;   
      }
   
      /*
      Dritte Spielstein Reihe
      */
      i = 5+(5*iXmp); 
      h = 4+(7*iYmp);
      iMaxY = h+2;
      
      while(h <= iMaxY)
      {
         g_cAusgabe[i][h] = cSpielstein;
         h++;   
      }
   }
   /*
   Ist das Feld ein "Zielfeld", also ein Feld auf den
   ein gewählter Stein springen kann, so soll dort
   ein Kreuz dargestellt werden.
            x x
   Form:       x
              x x
   */
   else
   {
      i = 3+(5*iXmp); 
      h = 4+(7*iYmp);
      g_cAusgabe[i][h] = cSpielstein;
      i++;
      h++;
      g_cAusgabe[i][h] = cSpielstein;
      i++;
      h++;
      g_cAusgabe[i][h] = cSpielstein;
      h = h-2;
      g_cAusgabe[i][h] = cSpielstein;
      i = i-2;
      h = h+2;
      g_cAusgabe[i][h] = cSpielstein;            
   }
}
/*
==============================================================================
Name:         fuelleReiheWeiss()
In:            iX, iY
Out:         -
Parameter:      Position des Feldes im Array
Beschreibung:   Schreibt die Feld-Schattierungen in das Array, beginnend mit 
            einem weißen 5*7 Viereck.

                             Package: OK
==============================================================================
*/
void fuelleReiheWeiss(int iX, int iY)
{
   int iStartX = iX;
   int iStartY = iY;
   
   //1. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+7)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB1';
         iStartY++;
      }
      iStartX++;
      iStartY = iY;
   }
   
   iStartX = iX;
   iStartY = iY+7;
   
   //2. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+14)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB0';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+7;
   }
   
   iStartX = iX;
   iStartY = iY+14;
   
   //3. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+21)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB1';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+14;
   }
   
   iStartX = iX;
   iStartY = iY+21;
   
   //4. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+28)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB0';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+21;
   }
   
   iStartX = iX;
   iStartY = iY+28;
   
   //5. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+35)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB1';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+28;
   }
   
   iStartX = iX;
   iStartY = iY+35;
   
   //6. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+42)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB0';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+35;
   }
   
   iStartX = iX;
   iStartY = iY+42;
   
   //7. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+49)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB1';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+42;
   }
   
   iStartX = iX;
   iStartY = iY+49;
   
   //8. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+55)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB0';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+49;
   }
}
/*
==============================================================================
Name:         fuelleReiheSchwarz()
In:            iX, iY
Out:         -
Parameter:      Position des Feldes im Array
Beschreibung:   Schreibt die Feld-Schattierungen in das Array, beginnend mit 
            einem schwarzen 5*7 Viereck.

                             Package: OK
==============================================================================
*/
void fuelleReiheSchwarz(int iX, int iY)
{
   int iStartX = iX;
   int iStartY = iY;
   
   //1. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+7)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB0';
         iStartY++;
      }
      iStartX++;
      iStartY = iY;
   }
   
   iStartX = iX;
   iStartY = iY+7;
   
   //2. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+14)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB1';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+7;
   }
   
   iStartX = iX;
   iStartY = iY+14;
   
   //3. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+21)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB0';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+14;
   }
   
   iStartX = iX;
   iStartY = iY+21;
   
   //4. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+28)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB1';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+21;
   }
   
   iStartX = iX;
   iStartY = iY+28;
   
   //5. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+35)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB0';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+28;
   }
   
   iStartX = iX;
   iStartY = iY+35;
   
   //6. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+42)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB1';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+35;
   }
   
   iStartX = iX;
   iStartY = iY+42;
   
   //7. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+49)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB0';
         iStartY++;
      }
      iStartX++;
      iStartY = iY+42;
   }
   
   iStartX = iX;
   iStartY = iY+49;
   
   //8. Viereck
   while(iStartX <= iX+4)
   {
      while(iStartY <= iY+55)
      {
         g_cAusgabe[iStartX][iStartY] = '\xB1';
         iStartY++;
      }   
      iStartX++;
      iStartY = iY+49;
   }
}
/*
==============================================================================
Name:         pruefeSpielsteinVorhanden()
In:            -
Out:         -
Parameter:      -
Beschreibung:   Zählt die Anzahl der vorhandenen Spielsteine des aktuellen
            Spielers.
         
                             Package: OK       
==============================================================================
*/
void pruefeSpielsteinVorhanden(void)
{
   int i; // Zählervariable
   int h; // Zählervariable
   
   switch(g_iPlayer)
   {
      /*
      Durchlaufen des Arrays mit der for-Schleife.
      Überprüfung jeder (i|h) Koordinate ob dort ein
      Spielstein des jew. Spielers liegt.
      */
      case 1: for(i = 0; i < 8; i++)
            {
               for(h = 0; h < 8; h++)
               {
                  /*
                  Liegt auf den Koordinaten (i|h) ein Stein des 
                  1. Spielers   dann wird die Anzahl der Spielsteine 
                  um 1 erhöht und   überprüft ob mit diesem Stein ein 
                  Sprung möglich ist
                  */ 
                  if(g_cSpielfeld[i][h] == 'H' 
                     || g_cSpielfeld[i][h] == 'Q')
                  {
                     g_iAnzahlSteine++;
                     /*
                     Übergabe der Koordinaten des gefundenen 
                     Spielsteins   an die Funktion 
                     "pruefeObSprungMoeglich()"
                     */
                     pruefeObSprungMoeglich(i, h, g_cSpielfeld[i][h]);
                     if(g_iSprung == 0)
                     {
                        pruefeObBewegungMoeglich(i, h, 
                           g_cSpielfeld[i][h]);
                     }
                  }
               }
            }
            break;
      case 2: for(i = 0; i < 8; i++)
            {
               for(h = 0; h < 8; h++)
               {
                  /*
                  Liegt auf den Koordinaten (i|h) ein Stein des 
                  2. Spielers   dann wird die Anzahl der Spielsteine um 
                  1 erhöht und überprüft ob mit diesem Stein ein 
                  Sprung möglich ist
                  */   
                  if(g_cSpielfeld[i][h] == 'C' 
                     || g_cSpielfeld[i][h] == 'K')
                  {
                     g_iAnzahlSteine++;
                     /*
                     Übergabe der Koordinaten des gefundenen 
                     Spielsteins   an die Funktion 
                     "pruefeObSprungMoeglich()"
                     */
                     pruefeObSprungMoeglich(i, h, g_cSpielfeld[i][h]);
                     if(g_iSprung == 0)
                     {
                        pruefeObBewegungMoeglich(i, h, 
                           g_cSpielfeld[i][h]);
                     }
                  }
               }
            }
            break;
   }
   /*
   Sind Steine vorhanden, soll der 
   nächste Schritt ausgeführt werden
   */
   if(g_iAnzahlSteine > 0)
   {
      g_iStep = 2;
   }
}
/*
==============================================================================
Name:         pruefeObSprungMoeglich()
In:            i, h, n
Out:         -
Parameter:      Die Koordinaten des aktuell gefundenen Steins werden hier 
            übergeben um dessen umliegende Felder zu überprüfen.
Beschreibung:   Überprüft ob der Spieler einen anderen Spielstein überspringen 
            kann. Ist dies der Fall, so muss der Spieler diesen Zug 
            ausführen.
         
                             Package: OK
==============================================================================
*/
void pruefeObSprungMoeglich(int i, int h, char n)
{
   int iXPos = i; //X-Position des akt. betrachteten Spielsteins
   int iYPos = h; //Y-Position des akt. betrachteten Spielsteins
   
   //Flag-Variablen für die Koordinaten:
   int iLO = 0; //Links-Oben
   int iRO = 0; //Rechts-Oben
   int iLU = 0; //Links-Unten
   int iRU = 0; //Rechts-Unten
   
   
   char cSteinArt = n; // Art des aktuellen Steins (H, Q, C oder K)
   
   if(g_iPlayer == 1)
   {
      /*
      Überprüfung ob der Spielstein eine dame ist
      oder ein normaler Spielstein
      */
      if(cSteinArt == 'H')
      {
         /*
         === Für normalen Spielstein ===
         Überprüfen der umliegenden Koordinaten auf gegnerische 
         Spielsteine:
         -> Links Oben
         */
         if((iXPos-1 >= 0 && iYPos-1 >= 0) 
            && (iXPos-2 >= 0 && iYPos-2 >= 0))
         {
            /*
            Liegt auf dem Feld Links-Oben vom aktuellen Feld aus 
            gesehen, ein normaler Stein bzw. eine dame des Gegners 
            und ist das Feld Links-Oben von diesem Feld frei, so 
            soll dieses mit einem "x" gekennzeichnet werden. 
            Die entsprechende Flag wird ebenfalls auf 1 gesetzt.
            */
            if((g_cSpielfeld[iXPos-1][iYPos-1] == 'C'
            || g_cSpielfeld[iXPos-1][iYPos-1] == 'K') 
            && g_cSpielfeld[iXPos-2][iYPos-2] == '-')
            {
               g_cSpielfeld[iXPos-2][iYPos-2] = 'x';
               iLO = 1;
               g_iSteinX = iXPos;
               g_iSteinY = iYPos;
            }
            else
            {
               iLO = 0;
            }
         }
         /*
         -> Rechts Oben
         */
         if((iXPos-1 >= 0 && iYPos+1 <= 7) 
            && (iXPos-2 >= 0 && iYPos+2 <= 7))
         {
            /*
            Liegt auf dem Feld Rechts-Oben vom aktuellen Feld aus 
            gesehen, ein normaler Stein bzw. eine dame des Gegners 
            und ist das Feld Rechts-Oben von diesem Feld frei, so 
            soll dieses mit einem "x" gekennzeichnet werden. 
            Die entsprechende Flag wird ebenfalls auf 1 gesetzt.
            */
            if((g_cSpielfeld[iXPos-1][iYPos+1] == 'C'
            || g_cSpielfeld[iXPos-1][iYPos+1] == 'K')
            && g_cSpielfeld[iXPos-2][iYPos+2] == '-')
            {
               g_cSpielfeld[iXPos-2][iYPos+2] = 'x';
               iRO = 1;
               g_iSteinX = iXPos;
               g_iSteinY = iYPos;               
            }
            else
            {
               iRO = 0;
            }
         }
         
         /*
         Ist eine Flag der oberen Felder auf 1 gesetzt, so ist definitiv 
         ein Sprung und damit eine Bewegung möglich und die Globale-Flag 
         iSprung wird auf 1 gesetzt.
         */
         if(iLO == 1)
         {
            g_iSprung = 1;
            g_iBewegung = 1;
         }
         if(iRO == 1)
         {
            g_iSprung = 1;
            g_iBewegung = 1;
         }         
      }
      if(cSteinArt == 'Q')
      {
         /*
         === Für dame als Spielstein ===
         Überprüfen der diagonalen Koordinaten auf gegnerische Spielsteine
         und Sprung Möglichkeiten:
         */
         pruefeObDamenSprung(iXPos, iYPos, 0);
      }          
   }
   else
   {
      /*
      Überprüfung ob der Spielstein eine dame ist
      oder ein normaler Spielstein
      */
      if(cSteinArt == 'C')
      {
         /*
         === Für normalen Spielstein ===
         Überprüfen der umliegenden Koordinaten auf gegnerische 
         Spielsteine:
         -> Links Unten
         */
         if((iXPos+1 <= 7 && iYPos-1 >= 0) 
            && (iXPos+2 <= 7 && iYPos-2 >= 0))
         {
            /*
            Liegt auf dem Feld Links-Unten vom aktuellen Feld aus 
            gesehen, ein normaler Stein bzw. eine dame des Gegners 
            und ist das Feld Links-Unten von diesem Feld frei, so 
            soll dieses mit einem "x" gekennzeichnet werden. 
            Die entsprechende Flag wird ebenfalls auf 1 gesetzt.
            */
            if((g_cSpielfeld[iXPos+1][iYPos-1] == 'H'
            || g_cSpielfeld[iXPos+1][iYPos-1] == 'Q')
            && g_cSpielfeld[iXPos+2][iYPos-2] == '-')
            {
               g_cSpielfeld[iXPos+2][iYPos-2] = 'x';
               iLU = 1;
               g_iSteinX = iXPos;
               g_iSteinY = iYPos;               
            }
            else
            {
               iLU = 0;
            }
         }
         /*
         -> Rechts Unten
         */
         if((iXPos+1 <= 7 && iYPos+1 <= 7) 
            && (iXPos+2 <= 7 && iYPos+2 <= 7))
         {
            /*
            Liegt auf dem Feld Rechts-Unten vom aktuellen Feld aus 
            gesehen, ein normaler Stein bzw. eine dame des Gegners 
            und ist das Feld Rechts-Unten von diesem Feld frei, so 
            soll dieses mit einem "x" gekennzeichnet werden. 
            Die entsprechende Flag wird ebenfalls auf 1 gesetzt.
            */
            if((g_cSpielfeld[iXPos+1][iYPos+1] == 'H'
            || g_cSpielfeld[iXPos+1][iYPos+1] == 'Q')
            && g_cSpielfeld[iXPos+2][iYPos+2] == '-')
            {
               g_cSpielfeld[iXPos+2][iYPos+2] = 'x';
               iRU = 1;
               g_iSteinX = iXPos;
               g_iSteinY = iYPos;               
            }
            else
            {
               iRU = 0;
            }
         }
         
         /*
         Ist eine Flag der unteren Felder auf 1 gesetzt, so ist definitiv 
         ein Sprung und damit eine Bewegung möglich und die Globale-Flag 
         iSprung wird auf 1 gesetzt.
         */
         if(iLU == 1)
         {
            g_iSprung = 1;
            g_iBewegung = 1;
         }
         if(iRU == 1)
         {
            g_iSprung = 1;
            g_iBewegung = 1;
         }        
      }
      if(cSteinArt == 'K')
      {   
         /*
         === Für dame als Spielstein ===
         Überprüfen der diagonalen Koordinaten auf gegnerische Spielsteine
         und Sprung Möglichkeiten:
         */
         pruefeObDamenSprung(iXPos, iYPos, 0);
      }          
   }    
}
/*
==============================================================================
Name:         pruefeObBewegungMoeglich();
In:            i, h, n
Out:         -
Parameter:      Position des Spielsteins sowie dessen Bezeichner
Beschreibung:   Hier wird für den Spielstein auf den übergebenen Koordinaten
            geprüft ob eine Bewegung möglich ist.

                        Package: OK
==============================================================================
*/
void pruefeObBewegungMoeglich(int i, int h, char n)
{
   int iXPos = i; //X-Position des akt. betrachteten Spielsteins
   int iYPos = h; //Y-Position des akt. betrachteten Spielsteins

   //Flag-Variablen für die Koordinaten:
   int iLO = 0; //Links-Oben
   int iRO = 0; //Rechts-Oben
   int iLU = 0; //Links-Unten
   int iRU = 0; //Rechts-Unten

   char cSteinArt = n; // Art des aktuellen Steins (H, Q, C oder K)

   switch(cSteinArt)
   {
      case 'H':
         if(iXPos-1 >= 0 && iYPos-1 >= 0 
            && g_cSpielfeld[iXPos-1][iYPos-1] == '-')
         {
            g_iBewegung = 1;          
         }
         if(iXPos-1 >= 0 && iYPos+1 <= 7 
            && g_cSpielfeld[iXPos-1][iYPos+1] == '-')
         {
            g_iBewegung = 1;
         }
      break;
      case 'C':
         if(iXPos+1 <= 7 && iYPos-1 >= 0 
            && g_cSpielfeld[iXPos+1][iYPos-1] == '-')
         {
            g_iBewegung = 1;
         }
         if(iXPos+1 <= 7 && iYPos+1 <= 7 
            && g_cSpielfeld[iXPos+1][iYPos+1] == '-')
         {
            g_iBewegung = 1;
         }
      break;
      case 'Q':
         if(iXPos-1 >= 0 && iYPos-1 >= 0 
            && g_cSpielfeld[iXPos-1][iYPos-1] == '-')
         {
            g_iBewegung = 1;          
         }
         if(iXPos-1 >= 0 && iYPos+1 <= 7 
            && g_cSpielfeld[iXPos-1][iYPos+1] == '-')
         {
            g_iBewegung = 1;
         }
         if(iXPos+1 <= 7 && iYPos-1 >= 0 
            && g_cSpielfeld[iXPos+1][iYPos-1] == '-')
         {
            g_iBewegung = 1;
         }
         if(iXPos+1 <= 7 && iYPos+1 <= 7 
            && g_cSpielfeld[iXPos+1][iYPos+1] == '-')
         {
            g_iBewegung = 1;
         }
      break;
      case 'K':
         if(iXPos-1 >= 0 && iYPos-1 >= 0 
            && g_cSpielfeld[iXPos-1][iYPos-1] == '-')
         {
            g_iBewegung = 1;          
         }
         if(iXPos-1 >= 0 && iYPos+1 <= 7 
            && g_cSpielfeld[iXPos-1][iYPos+1] == '-')
         {
            g_iBewegung = 1;
         }
         if(iXPos+1 <= 7 && iYPos-1 >= 0 
            && g_cSpielfeld[iXPos+1][iYPos-1] == '-')
         {
            g_iBewegung = 1;
         }
         if(iXPos+1 <= 7 && iYPos+1 <= 7 
            && g_cSpielfeld[iXPos+1][iYPos+1] == '-')
         {
            g_iBewegung = 1;
         }
      break;
   }
}
/*
==============================================================================
Name:         pruefeObDamenSprung()
In:            x, y, iSwitch
Out:         -
Parameter:      Koordinaten der Dame sowie die Rekursions-Stufe
Beschreibung:   Diese Funktion ist speziell für die Damen-Spielsteine.
            Hier wird per rekursiven Aufruf ermittelt, wie weit die Dame 
            ziehen kann und ob auf diesem Weg ein gegnerischer Spielstein 
            geschlagen werden kann.   

                             Package: Ok
==============================================================================
*/
void pruefeObDamenSprung(int x, int y, int iSwitch)
{
   int iXPos = x;
   int iYPos = y;
   char cGegenSpieler;
   char cGegnerdame;
      
   /*
   Zuordnung der jeweiligen Bezeichner des Gegners
   */
   if(g_iPlayer == 1)
   {
      cGegenSpieler = 'C';
      cGegnerdame = 'K';      
   }
   else
   {
      cGegenSpieler = 'H';
      cGegnerdame = 'Q';
   }
   
   switch(iSwitch)
   {
      /*
      Erster Aufruf der Funktion
      */
      case 0: if(iXPos-1 >= 0 && iYPos-1 >= 0)
            {
               if(g_cSpielfeld[iXPos-1][iYPos-1] == '-')
               {
                  /*
                  Ist das Feld Links-Oben vom aktuellen Feld frei, so 
                  findet ein rekursiver Aufruf mit den Koordinaten 
                  des Linken-Oberen Feldes statt. 
                  */
                  pruefeObDamenSprung(iXPos-1, iYPos-1, 1);
               }
               if(g_cSpielfeld[iXPos-1][iYPos-1] == cGegenSpieler
               || g_cSpielfeld[iXPos-1][iYPos-1] == cGegnerdame)
               {
                  /*
                  Liegt auf diesem Feld ein gegnerischer Stein, so 
                  wird überprüft ob das nächste Diagonale Feld frei ist.
                  */
                  if(iXPos-2 >= 0 && iYPos-2 >= 0)
                  {
                     if(g_cSpielfeld[iXPos-2][iYPos-2] == '-')
                     {
                        /*
                        Ist diese Feld frei, so soll es mit 
                        einem "x" gekennzeichnet werden.
                        */
                        g_cSpielfeld[iXPos-2][iYPos-2] = 'x';
                        g_iSprung = 1;
                        g_iBewegung = 1;
                     }
                  }
               }      
            }
            /*
            */
            if(iXPos-1 >= 0 && iYPos+1 <= 7)
            {
               if(g_cSpielfeld[iXPos-1][iYPos+1] == '-')
               {
                  /*
                  Ist das Feld Rechts-Oben vom aktuellen Feld frei, so 
                  findet ein rekursiver Aufruf mit den Koordinaten des 
                  Rechten-Oberen Feldes statt. 
                  */
                  pruefeObDamenSprung(iXPos-1, iYPos+1, 2);
               }
               if(g_cSpielfeld[iXPos-1][iYPos+1] == cGegenSpieler
               || g_cSpielfeld[iXPos-1][iYPos+1] == cGegnerdame)
               {
                  /*
                  Liegt auf diesem Feld ein gegnerischer Stein, so wird 
                  überprüft ob das nächste Diagonale Feld frei ist.
                  */
                  if(iXPos-2 >= 0 && iYPos+2 <= 7)
                  {
                     if(g_cSpielfeld[iXPos-2][iYPos+2] == '-')
                     {
                        /*
                        Ist diese Feld frei, so soll es mit einem 
                        "x" gekennzeichnet werden.
                        */
                        g_cSpielfeld[iXPos-2][iYPos+2] = 'x';
                        g_iSprung = 1;
                        g_iBewegung = 1;
                     }
                  }
               } 
            }
            /*
            */
            if(iXPos+1 <= 7 && iYPos-1 >= 0)
            {
               if(g_cSpielfeld[iXPos+1][iYPos-1] == '-')
               {
                  /*
                  Ist das Feld Links-Unten vom aktuellen Feld frei, so 
                  findet ein rekursiver Aufruf mit den Koordinaten 
                  des Linken-Unteren Feldes statt. 
                  */
                  pruefeObDamenSprung(iXPos+1, iYPos-1, 3);
               }
               if(g_cSpielfeld[iXPos+1][iYPos-1] == cGegenSpieler
               || g_cSpielfeld[iXPos+1][iYPos-1] == cGegnerdame)
               {
                  /*
                  Liegt auf diesem Feld ein gegnerischer Stein, so wird 
                  überprüft ob das nächste Diagonale Feld frei ist.
                  */
                  if(iXPos+2 <= 7 && iYPos-2 >= 0)
                  {
                     if(g_cSpielfeld[iXPos+2][iYPos-2] == '-')
                     {
                        /*
                        Ist diese Feld frei, so soll es mit einem "x" 
                        gekennzeichnet werden.
                        */
                        g_cSpielfeld[iXPos+2][iYPos-2] = 'x';
                        g_iSprung = 1;
                        g_iBewegung = 1;
                     }
                  }
               } 
            }
            /*
            */
            if(iXPos+1 <= 7 && iYPos+1 <= 7)
            {
               if(g_cSpielfeld[iXPos+1][iYPos+1] == '-')
               {
                  /*
                  Ist das Feld Rechts-Unten vom aktuellen Feld frei, so 
                  findet ein rekursiver Aufruf mit den Koordinaten des 
                  Rechten-Unteren Feldes statt. 
                  */
                  pruefeObDamenSprung(iXPos+1, iYPos+1, 4);
               }
               if(g_cSpielfeld[iXPos+1][iYPos+1] == cGegenSpieler
               || g_cSpielfeld[iXPos+1][iYPos+1] == cGegnerdame)
               {
                  /*
                  Liegt auf diesem Feld ein gegnerischer Stein, so wird 
                  überprüft ob das nächste Diagonale Feld frei ist.
                  */
                  if(iXPos+2 <= 7 && iYPos+2 <= 7)
                  {
                     if(g_cSpielfeld[iXPos+2][iYPos+2] == '-')
                     {
                        /*
                        Ist diese Feld frei, so soll es mit einem "x" 
                        gekennzeichnet werden.
                        */
                        g_cSpielfeld[iXPos+2][iYPos+2] = 'x';
                        g_iSprung = 1;   
                        g_iBewegung = 1;
                     }
                  }
               } 
            }
      break;
      case 1: if(iXPos-1 >= 0 && iYPos-1 >= 0)
            {   
               if(g_cSpielfeld[iXPos-1][iYPos-1] == '-')
               {
                  /*
                  Ist das Feld Links-Oben vom aktuellen Feld frei, so 
                  findet ein rekursiver Aufruf mit den Koordinaten 
                  des Linken-Oberen Feldes statt. 
                  */
                  pruefeObDamenSprung(iXPos-1, iYPos-1, 1);
               }
               if(g_cSpielfeld[iXPos-1][iYPos-1] == cGegenSpieler
               || g_cSpielfeld[iXPos-1][iYPos-1] == cGegnerdame)
               {
                  /*
                  Liegt auf diesem Feld ein gegnerischer Stein, so 
                  wird überprüft ob das nächste Diagonale Feld frei ist.
                  */
                  if(iXPos-2 >= 0 && iYPos-2 >= 0)
                  {
                     if(g_cSpielfeld[iXPos-2][iYPos-2] == '-')
                     {
                        /*
                        Ist diese Feld frei, so soll es mit 
                        einem "x" gekennzeichnet werden.
                        */
                        g_cSpielfeld[iXPos-2][iYPos-2] = 'x';
                        g_iSprung = 1; 
                        g_iBewegung = 1;
                     }
                  }
               }      
            }
      break;
      case 2: if(iXPos-1 >= 0 && iYPos+1 <= 7)
            {
               if(g_cSpielfeld[iXPos-1][iYPos+1] == '-')
               {
                  /*
                  Ist das Feld Rechts-Oben vom aktuellen Feld frei, 
                  so findet ein rekursiver Aufruf mit den Koordinaten
                  des Rechten-Oberen Feldes statt. 
                  */
                  pruefeObDamenSprung(iXPos-1, iYPos+1, 2);
               }
               if(g_cSpielfeld[iXPos-1][iYPos+1] == cGegenSpieler
               || g_cSpielfeld[iXPos-1][iYPos+1] == cGegnerdame)
               {
                  /*
                  Liegt auf diesem Feld ein gegnerischer Stein, so wird 
                  überprüft ob das nächste Diagonale Feld frei ist.
                  */
                  if(iXPos-2 >= 0 && iYPos+2 <= 7)
                  {
                     if(g_cSpielfeld[iXPos-2][iYPos+2] == '-')
                     {
                        /*
                        Ist diese Feld frei, so soll es mit einem "x" 
                        gekennzeichnet werden.
                        */
                        g_cSpielfeld[iXPos-2][iYPos+2] = 'x';
                        g_iSprung = 1;  
                        g_iBewegung = 1;
                     }
                  }
               } 
            }
      break;
      case 3: if(iXPos+1 <= 7 && iYPos-1 >= 0)
            {
               if(g_cSpielfeld[iXPos+1][iYPos-1] == '-')
               {
                  /*
                  Ist das Feld Links-Unten vom aktuellen Feld frei, so 
                  findet ein rekursiver Aufruf mit den Koordinaten des 
                  Linken-Unteren Feldes statt. 
                  */
                  pruefeObDamenSprung(iXPos+1, iYPos-1, 3);
               }
               if(g_cSpielfeld[iXPos+1][iYPos-1] == cGegenSpieler
               || g_cSpielfeld[iXPos+1][iYPos-1] == cGegnerdame)
               {
                  /*
                  Liegt auf diesem Feld ein gegnerischer Stein, so wird 
                  überprüft ob das nächste Diagonale Feld frei ist.
                  */
                  if(iXPos+2 <= 7 && iYPos-2 >= 0)
                  {
                     if(g_cSpielfeld[iXPos+2][iYPos-2] == '-')
                     {
                        /*
                        Ist diese Feld frei, so soll es mit einem "x" 
                        gekennzeichnet werden.
                        */
                        g_cSpielfeld[iXPos+2][iYPos-2] = 'x';
                        g_iSprung = 1;  
                        g_iBewegung = 1;
                     }
                  }
               }    
            }
      break;
      case 4: if(iXPos+1 <= 7 && iYPos+1 <= 7)
            {
               if(g_cSpielfeld[iXPos+1][iYPos+1] == '-')
               {
                  /*
                  Ist das Feld Rechts-Unten vom aktuellen Feld frei, so 
                  findet ein rekursiver Aufruf mit den Koordinaten 
                  des Rechten-Unteren Feldes statt. 
                  */
                  pruefeObDamenSprung(iXPos+1, iYPos+1, 4);
               }
               if(g_cSpielfeld[iXPos+1][iYPos+1] == cGegenSpieler
               || g_cSpielfeld[iXPos+1][iYPos+1] == cGegnerdame)
               {
                  /*
                  Liegt auf diesem Feld ein gegnerischer Stein, so wird 
                  überprüft ob das nächste Diagonale Feld frei ist.
                  */
                  if(iXPos+2 <= 7 && iYPos+2 <= 7)
                  {
                     if(g_cSpielfeld[iXPos+2][iYPos+2] == '-')
                     {
                        /*
                        Ist diese Feld frei, so soll es mit einem "x" 
                        gekennzeichnet werden.
                        */
                        g_cSpielfeld[iXPos+2][iYPos+2] = 'x';
                        g_iSprung = 1;   
                        g_iBewegung = 1;
                     }
                  }
               } 
            }
      break;
   }             
}
/*
==============================================================================
Name:         waehleSpielstein()
In:            -
Out:         -
Parameter:      -
Beschreibung:   Eingabe der Koordinaten des gewünschten Spielsteins werden 
            verlangt. Hierbei gilt für die Koordinaten:
            X: A-H
            Y: 1-8
         
                             Package: OK
==============================================================================
*/
void waehleSpielstein(void)
{
   char cTempX = 0; // Variable zur Speicherung der Eingabe
   char cTempY = 0; // Variable zur Speicherung der Eingabe
   char cX; //Speichern der X-Eingabe
   int iEingabeKorrekt;
   int iMoeglich = 0;   
   
   do
   {
      /*   
      Solange keine korrekte X-Position gewählt wird,
      soll die Eingabe abgefragt werden.
      */
                        
      do
      {
         system("cls");         
         schreibe();
         printf("          Waehle Stein:");
         printf("\n");
         printf("          X: ");
         while(cTempX == 0)
         {
            if(_kbhit())
            {
               cTempX = getchar();
            }       
            if(cTempX > 0)
            {
               fflush(stdin);
               /*
               Setzen des Wertes von "iAktXPos" in der 
               aufgerufenen Funktion
               */
               iEingabeKorrekt = pruefeXEingabe(cTempX);
            }     
         }
         cX = cTempX;
         cTempX = 0;
      }
      while(iEingabeKorrekt != 1 && g_cBeenden == 'n');
   
      if(g_iExitFlag == 0 && g_cNeustart == 'n')
      {      
         /*
         Solange keine korrekte Y-Position gewählt wird,
         soll die Eingabe abgefragt werden.
         */
         do
         {
            system("cls");         
            schreibe();
            printf("          Waehle Stein:");
            printf("\n");
            printf("          X: %c \n", cX);
            printf("          Y: ");         
            while(cTempY == 0)
            {
               if(_kbhit())
               {
                  cTempY = getchar();               
               }       
               if(cTempY > 0)
               {
                  fflush(stdin);
                  /*
                  Setzen des Wertes von "iAktXPos" in der 
                  aufgerufenen Funktion
                  */
                  iEingabeKorrekt = pruefeYEingabe(cTempY);
               }
            }
            cTempY = 0;
         }
         while(iEingabeKorrekt != 1 && g_cBeenden == 'n');
      }
      
      
      /*
      Liegt auf den eingegebenen Koordinaten ein Stein, soll 
      überprüft werden ob ein versetzen des Steins möglich ist 
      und wenn ja, ob es mehrere Möglichkeiten gibt.
      */     
      if(g_iPlayer == 1 && g_cBeenden == 'n' && g_cNeustart == 'n')
      {
         /*
         Liegt auf den Koordinaten ein eigener Spielstein sollen
         alle möglichen Züg ermittelt werden.
         */      
         if(g_cSpielfeld[g_iAktXPos][g_iAktYPos] == 'H')
         {
            /*
            Aufruf der Funktion "zeigeMoeglichkeiten()" mit den Parametern
            "iAktXPos" und "iAktYPos" die den Koordinaten des ausgewählten
            Steines entsprechen.
            */
            iMoeglich = zeigeMoeglichkeiten(g_iAktXPos, g_iAktYPos);                                                             
         }
         if(g_cSpielfeld[g_iAktXPos][g_iAktYPos] == 'Q')
         {
            iMoeglich = zeigeDamenMoeglichkeiten(g_iAktXPos, g_iAktYPos);
         }           
      }
      if(g_iPlayer == 2 && g_cBeenden == 'n' && g_cNeustart == 'n')
      {
         /*
         Liegt auf den Koordinaten ein eigener Spielstein sollen
         alle möglichen Züg ermittelt werden.
         */ 
         if(g_cSpielfeld[g_iAktXPos][g_iAktYPos] == 'C')
         {
            /*
            Aufruf der Funktion "zeigeMoeglichkeiten()" mit den Parametern
            "iAktXPos" und "iAktYPos" die den Koordinaten des ausgewählten
            Steines entsprechen.
            */
            iMoeglich = zeigeMoeglichkeiten(g_iAktXPos, g_iAktYPos);                                                             
         }
         if(g_cSpielfeld[g_iAktXPos][g_iAktYPos] == 'K')
         {
            iMoeglich = zeigeDamenMoeglichkeiten(g_iAktXPos, g_iAktYPos);
         }      
      }
   }
   /*
   Es muss solange ein Spielstein ausgewählt werden, bis es mindestens
   1 Möglichkeit gibt diesen zu versetzen.
   */
   while(iMoeglich == 0 && g_cBeenden == 'n' && g_cNeustart == 'n');
   
   
   g_iSteinX = g_iAktXPos;
   g_iSteinY = g_iAktYPos;
   
   //Der nächste Step soll ausgeführt werden
   if(g_cNeustart == 'n' && g_cBeenden == 'n')
   {
      g_iStep = 3;
   }
   if(g_cNeustart == 'j')
   {
      /*
      Reset aller nötigen Variablen
      */
      g_iAnzahlSteine = 0;
      g_iPlayer = 1;
      g_iStep = 0;
      g_cBeenden = 'n';
      g_iSprung=0;
      g_cNeustart = 'n';
   }
   if(g_cBeenden == 'j')
   {
      g_iStep = 6;
   }
}
/*
==============================================================================
Name:         sprungSpielstein()
In:            cSteinArt
Out:         -
Parameter:      -
Beschreibung:   Diese Funktion ist speziell für die Auswahl eines Spielsteines 
            der mindestens einen gegnerischen Spielstein überspringen kann.
         
                             Package: OK
==============================================================================
*/
void sprungSpielstein(char cSteinArt)
{
   char cTempX = 0; // Variable zur Speicherung der Eingabe
   char cTempY = 0; // Variable zur Speicherung der Eingabe
   char cX; //Speichern der X-Eingabe
   int iEingabeKorrekt;
   int iMoeglich = 0;
   char cSpieler; //Flag für den Spieler Buchstaben
   int x, y;
   
   do
   {
      do
      {
         system("cls");
         schreibe();
         printf("          Waehle Stein:");
         printf("\n");
         printf("          X: ");   
         while(cTempX == 0)
         {
            if(_kbhit())
            {
               cTempX = getchar();
            }       
            if(cTempX > 0)
            {
               fflush(stdin);
               /*
               Setzen des Wertes von "iAktXPos" in der 
               aufgerufenen Funktion
               */
               iEingabeKorrekt = pruefeXEingabe(cTempX);
            }
         }
         cX = cTempX;
         cTempX = 0;
      }
      while(iEingabeKorrekt != 1);
   
      if(g_iExitFlag == 0 && g_cNeustart == 'n')
      {
         /*
         Solange keine korrekte Y-Position gewählt wird,
         soll die Eingabe abgefragt werden.
         */      
         do
         {
            system("cls");         
            schreibe();
            printf("          Waehle Stein:");
            printf("\n");
            printf("          X: %c \n", cX);
            printf("          Y: ");             
            while(cTempY == 0)
            {
               if(_kbhit())
               {
                  cTempY = getchar();
               }       
               if(cTempY > 0)
               {
                  fflush(stdin);
                  /*
                  Setzen des Wertes von "iAktYPos" in der 
                  aufgerufenen Funktion
                  */
                  iEingabeKorrekt = pruefeYEingabe(cTempY);
               }
            }
            cTempY = 0;         
         }
         while(iEingabeKorrekt != 1);
      }
      
      /*
      Setzen der Spieler-Flag
      */
      if(g_iPlayer == 1)
      {
         cSpieler = 'H';                  
      }
      else
      {
         cSpieler = 'C';
      }
      
      /*
      Liegt auf den eingegebenen Koordinaten ein Spielstein des Spielers,
      soll überprüft werden ob in den Diagonalen ein gekennzeichnetes Feld
      vorhanden ist.
      */
      if(g_cSpielfeld[g_iAktXPos][g_iAktYPos] == 'H' 
      || g_cSpielfeld[g_iAktXPos][g_iAktYPos] == 'C')
      {
         /*
         Überprüfung ob die Koordinaten des zu überprüfenden Feldes 
         noch im Array liegen.
         */
         if(g_iAktXPos-2 >= 0 && g_iAktYPos-2 >= 0)
         {
            /*
            Ist ein gekennzeichnetes Feld vorhanden, soll die
            Flag iMoeglich auf 1 (true) gesetzt werden.
            */
            if(g_cSpielfeld[g_iAktXPos-2][g_iAktYPos-2] == 'x'
            && (g_cSpielfeld[g_iAktXPos-1][g_iAktYPos-1] == 'H'
            || g_cSpielfeld[g_iAktXPos-1][g_iAktYPos-1] == 'Q'
            || g_cSpielfeld[g_iAktXPos-1][g_iAktYPos-1] == 'C'
            || g_cSpielfeld[g_iAktXPos-1][g_iAktYPos-1] == 'K'))
            {
               iMoeglich = 1;
            }         
         }
         /*
         Überprüfung ob die Koordinaten des zu überprüfenden Feldes 
         noch im Array liegen.
         */
         if(g_iAktXPos-2 >= 0 && g_iAktYPos+2 >= 0)
         {
            /*
            Ist ein gekennzeichnetes Feld vorhanden, soll die
            Flag iMoeglich auf 1 (true) gesetzt werden.
            */
            if(g_cSpielfeld[g_iAktXPos-2][g_iAktYPos+2] == 'x'
            && (g_cSpielfeld[g_iAktXPos-1][g_iAktYPos+1] == 'H'
            || g_cSpielfeld[g_iAktXPos-1][g_iAktYPos+1] == 'Q'
            || g_cSpielfeld[g_iAktXPos-1][g_iAktYPos+1] == 'C'
            || g_cSpielfeld[g_iAktXPos-1][g_iAktYPos+1] == 'K'))
            {
               iMoeglich = 1;
            }                       
         }
         /*
         Überprüfung ob die Koordinaten des zu überprüfenden Feldes 
         noch im Array liegen.
         */
         if(g_iAktXPos+2 >= 0 && g_iAktYPos-2 >= 0)
         {
            /*
            Ist ein gekennzeichnetes Feld vorhanden, soll die
            Flag iMoeglich auf 1 (true) gesetzt werden.
            */
            if(g_cSpielfeld[g_iAktXPos+2][g_iAktYPos-2] == 'x'
            && (g_cSpielfeld[g_iAktXPos+1][g_iAktYPos-1] == 'H'
            || g_cSpielfeld[g_iAktXPos+1][g_iAktYPos-1] == 'Q'
            || g_cSpielfeld[g_iAktXPos+1][g_iAktYPos-1] == 'C'
            || g_cSpielfeld[g_iAktXPos+1][g_iAktYPos-1] == 'K'))
            {
               iMoeglich = 1;
            }         
         }
         /*
         Überprüfung ob die Koordinaten des zu überprüfenden Feldes 
         noch im Array liegen.
         */
         if(g_iAktXPos+2 >= 0 && g_iAktYPos+2 >= 0)
         {
            /*
            Ist ein gekennzeichnetes Feld vorhanden, soll die
            Flag iMoeglich auf 1 (true) gesetzt werden.
            */
            if(g_cSpielfeld[g_iAktXPos+2][g_iAktYPos+2] == 'x'
            && (g_cSpielfeld[g_iAktXPos+1][g_iAktYPos+1] == 'H'
            || g_cSpielfeld[g_iAktXPos+1][g_iAktYPos+1] == 'Q'
            || g_cSpielfeld[g_iAktXPos+1][g_iAktYPos+1] == 'C'
            || g_cSpielfeld[g_iAktXPos+1][g_iAktYPos+1] == 'K'))
            {
               iMoeglich = 1;
            }         
         }
      }
      if(g_cSpielfeld[g_iAktXPos][g_iAktYPos] == 'Q' 
      || g_cSpielfeld[g_iAktXPos][g_iAktYPos] == 'K')
      {
         /*
         Überprüfung ob in der Diagonalen nach Links-Oben
         ein gekennzeichnetes Feld vorhanden ist
         */
         x = g_iAktXPos;
         y = g_iAktYPos;
         while(x-1 >= 0 && y-1 >= 0)
         {
            if(g_cSpielfeld[x-1][y-1] == 'x')
            {
               iMoeglich = 1;
               break;
            }
            else
            {
               x--;
               y--;
            }
         }
         /*
         Überprüfung ob in der Diagonalen nach Rechts-Oben
         ein gekennzeichnetes Feld vorhanden ist
         */
         x = g_iAktXPos;
         y = g_iAktYPos;
         while(x-1 >= 0 && y+1 <= 7)
         {
            if(g_cSpielfeld[x-1][y+1] == 'x')
            {
               iMoeglich = 1;
               break;
            }
            else
            {
               x--;
               y++;
            }
         }
         /*
         Überprüfung ob in der Diagonalen nach Links-Unten
         ein gekennzeichnetes Feld vorhanden ist
         */
         x = g_iAktXPos;
         y = g_iAktYPos;
         while(x+1 <= 7 && y-1 >= 0)
         {
            if(g_cSpielfeld[x+1][y-1] == 'x')
            {
               iMoeglich = 1;
               break;
            }
            else
            {
               x++;
               y--;
            }
         }
         /*
         Überprüfung ob in der Diagonalen nach Rechts-Unten
         ein gekennzeichnetes Feld vorhanden ist
         */
         x = g_iAktXPos;
         y = g_iAktYPos;
         while(x+1 <= 7 && y+1 <= 7)
         {
            if(g_cSpielfeld[x+1][y+1] == 'x')
            {
               iMoeglich = 1;
               break;
            }
            else
            {
               x++;
               y++;
            }
         }
      }     
   }
   /*
   Die Eingabe soll solang erfolgen, bis ein Stein gewählt wurde der 
   auch wirklich einen gegnerischen Stein überspringen kann.
   */
   while(iMoeglich == 0);
   
   g_iSteinX = g_iAktXPos;
   g_iSteinY = g_iAktYPos;
   
   //Der nächste Step soll ausgeführt werden
   if(g_cNeustart == 'n' && g_cBeenden == 'n')
   {
      g_iStep = 3;
   }
   if(g_cNeustart == 'j')
   {
      /*
      Reset aller nötigen Variablen
      */
      g_iAnzahlSteine = 0;
      g_iPlayer = 1;
      g_iStep = 0;
      g_cBeenden = 'n';
      g_iSprung=0;
      g_cNeustart = 'n';
   }
   if(g_cBeenden == 'j')
   {
      g_iStep = 6;
   }
}
/*
==============================================================================
Name:         pruefeXEingabe()
In:            cTempX
Out:         1 - Eingabe richtig
            0 - Eingabe falsch
Parameter:      Eingabe des Users wird übergeben.
Beschreibung:   Überprüft die eingegebene X-Koordinate auf Korrektheit, und 
            wandelt den Buchstaben in die jeweilige Zahl um. Hier ist zu 
            beachten das "A = 0" ist, da das Array 0 indiziert wird.
            Dies vereinfacht später die Abfrage von Feldern im 
            zwei-dimensionalenArray.
         
                             Package: OK
==============================================================================
*/
int pruefeXEingabe(char cTempX)
{
   switch(cTempX)
   {
      case 0x41: g_iAktYPos = 0; //A
               return 1;
      break;
      case 0x42: g_iAktYPos = 1; //B
                return 1;
      break;
      case 0x43: g_iAktYPos = 2; //C
                return 1;
      break;
      case 0x44: g_iAktYPos = 3; //D
               return 1;
      break;
      case 0x45: g_iAktYPos = 4; //E
                return 1;
      break;
      case 0x46: g_iAktYPos = 5; //F
                   return 1;
      break;
      case 0x47: g_iAktYPos = 6; //G
                   return 1;
      break;
      case 0x48: g_iAktYPos = 7; //H
                   return 1;
      break;
      case 0x61: g_iAktYPos = 0; //a
                   return 1;
      break;
      case 0x62: g_iAktYPos = 1; //b
                return 1;
      break;
      case 0x63: g_iAktYPos = 2; //c
                   return 1;
      break;
      case 0x64: g_iAktYPos = 3; //d
                   return 1;
      break;
      case 0x65: g_iAktYPos = 4; //e
                   return 1;
      break;
      case 0x66: g_iAktYPos = 5; //f
                   return 1;
      break;
      case 0x67: g_iAktYPos = 6; //g
                   return 1;
      break;
      case 0x68: g_iAktYPos = 7; //h
                   return 1;
      break;
      case 0x78: g_fExitCode = -1; //x
                 g_iExitFlag = 1;
               g_cBeenden = 'j';
               beenden();
               return 1;
      break;
      case 0x73: system("start Checkers-Hilfe.html"); //s
                   return 0;
      break;
      case 0x77: g_cNeustart = 'j'; //w      
                   return 1;
      break;
      default: return 0;
    }
       
}
/*
==============================================================================
Name:         pruefeYEingabe()
In:            cTempY
Out:         1 - Eingabe richtig
            0 - Eingabe falsch
Parameter:      Eingabe des Users wird übergeben.
Beschreibung:   Überprüft die eingegebene y-Koordinate auf Korrektheit, und 
            wandelt den Buchstaben in die jeweilige Zahl um. Hier ist zu 
            beachten das "A = 0" ist, da das Array 0 indiziert wird.
            Dies vereinfacht später die Abfrage von Feldern im 
            zwei-dimensionalenArray.
         
                             Package: OK
==============================================================================
*/
int pruefeYEingabe(char cTempY)
{   
   switch(cTempY)
   {
      case 0x31: g_iAktXPos = 0; //1
                   return 1;              
      break;
      case 0x32: g_iAktXPos = 1; //2
                return 1;              
      break;
      case 0x33: g_iAktXPos = 2; //3
               return 1;              
      break;
      case 0x34: g_iAktXPos = 3; //4
                   return 1;
      break;
      case 0x35: g_iAktXPos = 4; //5
                   return 1;
      break;
      case 0x36: g_iAktXPos = 5; //6
                   return 1;
      break;
      case 0x37: g_iAktXPos = 6; //7
                   return 1;
      break;
      case 0x38: g_iAktXPos = 7; //8
                   return 1;
      case 0x78: g_fExitCode = -1; //x
               g_iExitFlag = 1;
               g_cBeenden = 'j';
               beenden();
               return 1;
      break;
      case 0x73: system("start Checkers-Hilfe.html"); //s                 
                   return 0;
      break;
      case 0x77: g_cNeustart = 'j'; //w
                   return 1;
      break;
      default: return 0;
   }
}
/*
==============================================================================
Name:         zeigeMoeglichkeiten()
In:            iXPos, iYPos
Out:         1 - es gibt einen oder mehrere mögliche Züge
            0 - es gibt keinen möglichen Zug
Parameter:      -
Beschreibung:   Hier werden alle möglichen Züge für den Spielstein auf den 
            übergebenen Koordinaten (iXPos, iYPos) errechnet.
   
                             Package: OK
==============================================================================
*/
int zeigeMoeglichkeiten(int iXPos, int iYPos)
{
   int iMoeglich = 0;
   if(g_iPlayer == 1)
   {
      /*
      Überprüfung ob kein OutOfIndex vorliegt wenn die 
      umliegenden Koordinaten   geprüft werden sollen
      */
      if(iXPos-1 >= 0 && iYPos-1 >= 0)
      {
         /*
         Liegt auf dem Feld kein gegnerischer oder eigener Stein, so soll
         dies als möglicher Zug gekennzeichnet werden
         */
         if(g_cSpielfeld[iXPos-1][iYPos-1] == '-')
         {
            g_cSpielfeld[iXPos-1][iYPos-1] = 'x';
            iMoeglich = 1;          
         }         
      }
      /*
      Überprüfung ob kein OutOfIndex vorliegt wenn die umliegenden 
      Koordinaten   geprüft werden sollen
      */
      if(iXPos-1 >=0 && iYPos+1 <= 7)
      {
         /*
         Liegt auf dem Feld kein gegnerischer oder eigener Stein, so soll
         dies als möglicher Zug gekennzeichnet werden
         */
         if(g_cSpielfeld[iXPos-1][iYPos+1] == '-')
         {
            g_cSpielfeld[iXPos-1][iYPos+1] = 'x';
            iMoeglich = 1;
         }
      }
   }
   else
   {
      /*
      Überprüfung ob kein OutOfIndex vorliegt wenn die umliegenden 
      Koordinaten   geprüft werden sollen
      */
      if(iXPos+1 <= 7 && iYPos-1 >= 0)
      {
         /*
         Liegt auf dem Feld kein gegnerischer oder eigener Stein, so 
         soll dies als möglicher Zug gekennzeichnet werden
         */
         if(g_cSpielfeld[iXPos+1][iYPos-1] == '-')
         {
            g_cSpielfeld[iXPos+1][iYPos-1] = 'x'; 
            iMoeglich = 1;         
         }         
      }
      /*
      Überprüfung ob kein OutOfIndex vorliegt wenn die umliegenden 
      Koordinaten   geprüft werden sollen
      */
      if(iXPos+1 <=7 && iYPos+1 <= 7)
      {
         /*
         Liegt auf dem Feld kein gegnerischer oder eigener Stein, so 
         soll dies als möglicher Zug gekennzeichnet werden
         */
         if(g_cSpielfeld[iXPos+1][iYPos+1] == '-')
         {
            g_cSpielfeld[iXPos+1][iYPos+1] = 'x';
            iMoeglich = 1;
         }
      }     
   }
   /*
   Anzahl der möglichen Züge wird zurückgegeben
   */
   return iMoeglich;   
}
/*
==============================================================================
Name:         zeigeDamenMoeglichkeiten()
In:            iXPos, iYPos
Out:         iMoeglich
Parameter:      Koordinaten der Dame sowie die Rückgabe ob diese einen Zug 
            machen kann oder nicht.
Beschreibung:   Durch den Aufruf der Unterfunktionen wird überprüft ob mit der 
            Dame ein Zug gemacht werden kann oder nicht.

                             Package: OK
==============================================================================
*/
int zeigeDamenMoeglichkeiten(int iXPos, int iYPos)
{
   int iSchritt = 1;
   int iMoeglich = 0;
   /*
   Variablen für alle vier diagonalen der Dame:
   LO = Links-Oben
   RO = Rechts-Oben
   LU = Links-Unten
   RU = Rechts-Unten
   */
   int iLO, iRO, iLU, iRU;
   
   iLO = dameLinksOben(iXPos, iYPos);
   iRO = dameRechtsOben(iXPos, iYPos);
   iLU = dameLinksUnten(iXPos, iYPos);
   iRU = dameRechtsUnten(iXPos, iYPos);
   
   iMoeglich = iLO + iRO + iLU + iRU;   
      
   return iMoeglich;
}
/*
==============================================================================
Name:         dameLinksOben()
In:            iXPos, iYPos
Out:         1  -  Dame befindet sich links oben
            0  -  Dame befindet sich ncht links oben
Parameter:      Position der Dame sowie rückgabe ob in dieser Diagonalen ein 
            Zug möglich ist.
Beschreibung:   Überprüfung ob in der Diagonalen Links-Oben ein Zug möglich 
            ist (rekursiv)
                             Package: OK
==============================================================================
*/
int dameLinksOben(int iXPos, int iYPos)
{
   if(iXPos-1 >= 0 && iYPos-1 >= 0)
   {
      if(g_cSpielfeld[iXPos-1][iYPos-1] == '-')
      {
         dameLinksOben(iXPos-1, iYPos-1);
         g_cSpielfeld[iXPos-1][iYPos-1] = 'x';
         return 1;         
      }
      else
      {
         return 0;
      }
   }
   else
   {
      return 0;
   }
}
/*
==============================================================================
Name:         dameRechtsOben()
In:            iXPos, iYPos
Out:         1  -  Dame befindet sich rechts oben
            0  -  Dame befindet sich ncht rechts oben
Parameter:      Position der Dame sowie rückgabe ob in dieser Diagonalen ein 
            Zug möglich ist.
Beschreibung:   Überprüfung ob in der Diagonalen Rechts-Oben ein Zug möglich 
            ist (rekursiv)

                             Package: OK
==============================================================================
*/
int dameRechtsOben(int iXPos, int iYPos)
{
   if(iXPos-1 >= 0 && iYPos+1 <= 7)
   {
      if(g_cSpielfeld[iXPos-1][iYPos+1] == '-')
      {
         dameRechtsOben(iXPos-1, iYPos+1);
         g_cSpielfeld[iXPos-1][iYPos+1] = 'x';
         return 1;
      }     
   }   
   return 0;
}
/*
==============================================================================
Name:         dameLinksUnten()
In:            iXPos, iYPos
Out:         1  -  Dame befindet sich links unten
            0  -  Dame befindet sich ncht links unten
Parameter:      Position der Dame sowie rückgabe ob in dieser Diagonalen ein 
            Zug möglich ist.
Beschreibung:   Überprüfung ob in der Diagonalen Links-Unten ein Zug möglich 
            ist (rekursiv)
                             Package: OK
==============================================================================
*/
int dameLinksUnten(int iXPos, int iYPos)
{
   if(iXPos+1 <= 7 && iYPos-1 >= 0)
   {
      if(g_cSpielfeld[iXPos+1][iYPos-1] == '-')
      {
         dameLinksUnten(iXPos+1, iYPos-1);
         g_cSpielfeld[iXPos+1][iYPos-1] = 'x';
         return 1;
      }
   }
   return 0;
}
/*
==============================================================================
Name:         dameRechtsUnten()
In:            iXPos, iYPos
Out:         1  -  Dame befindet sich rechts unten
            0  -  Dame befindet sich ncht rechts unten
Parameter:      Position der Dame sowie rückgabe ob in dieser Diagonalen ein 
            Zug möglich ist.
Beschreibung:   Überprüfung ob in der Diagonalen Rechts-Unten ein Zug möglich 
            ist (rekursiv)

                             Package: OK 
==============================================================================
*/
int dameRechtsUnten(int iXPos, int iYPos)
{
   if(iXPos+1 <= 7 && iYPos+1 <= 7)
   {
      if(g_cSpielfeld[iXPos+1][iYPos+1] == '-')
      {
         dameRechtsUnten(iXPos+1, iYPos+1);
         g_cSpielfeld[iXPos+1][iYPos+1] = 'x';
         return 1;
      }
   }
   return 0;
}
/*
==============================================================================
Name:         waehleZiel()
In:            -
Out:         -
Parameter:      - 
Beschreibung:   Der Spieler soll seine Zielkoordinaten eingeben.
            Diese werden überprüft. Sin die Koordinaten korrekt, wird 
            der Stein neu gesetzt.

                             Package: OK
==============================================================================
*/
void waehleZiel(void)
{
   char cTempX = 0;
   char cTempY = 0;
   char cX; //Speichern der X-Eingabe
   int iEingabeKorrekt;
   int iZielOk = 0;
   int iSteinGesetzt;
   
   do
   {
      do
      {
         /*
         Eingabe der X-Koordinate wird erfordert
         */
         system("cls");
         schreibe();
         printf("          Waehle Ziel:");
         printf("\n");   
         printf("          X: ");         
         while(cTempX == 0)
         {
            if(_kbhit())
            {
               cTempX = getchar();
            }       
            if(cTempX > 0)
            {
               fflush(stdin);
               /*
               Setzen des Wertes von "iAktYPos" in der 
               aufgerufenen Funktion
               */
               iEingabeKorrekt = pruefeXEingabe(cTempX);
            }
         }
         cX = cTempX;
         cTempX = 0;
      }
      while(iEingabeKorrekt != 1 && g_cBeenden == 'n');
   
      if(g_iExitFlag == 0 && g_cNeustart == 'n')
      {
         do
         {
            /*
            Eingabe der Y-Koordinate wird erfordert
            */
            system("cls");         
            schreibe();
            printf("          Waehle Stein:");
            printf("\n");
            printf("          X: %c \n", cX);
            printf("          Y: ");             
            while(cTempY == 0)
            {
               if(_kbhit())
               {
                  cTempY = getchar();
               }       
               if(cTempY > 0)
               {
                  fflush(stdin);
                  /*
                  Setzen des Wertes von "iAktYPos" in der 
                  aufgerufenen Funktion
                  */
                  iEingabeKorrekt = pruefeYEingabe(cTempY);
               }
            }
            cTempY = 0;         
         }
         while(iEingabeKorrekt != 1 && g_cBeenden == 'n');
      
         iZielOk = pruefeZiel(g_iAktXPos, g_iAktYPos);
      }    
   }
   while(iZielOk != 1 && g_cBeenden == 'n' && g_cNeustart == 'n');
   
   /*
   Ist der Stein eine Dame soll die Funktion:
   setzeDame() ausgeführt werden
   */
   if(g_cSpielfeld[g_iSteinX][g_iSteinY] == 'Q' 
   || g_cSpielfeld[g_iSteinX][g_iSteinY] == 'K')
   {
      iSteinGesetzt = setzeDame(g_iAktXPos, g_iAktYPos);
   }
   /*
   Ist der Stein ein normaler Stein soll die Funktion:
   setzeStein() ausgeführt werden
   */
   else
   {
      iSteinGesetzt = setzeStein(g_iAktXPos, g_iAktYPos);
   }  
      
   /*
   Wenn der Stein gesetzt werden konnte, wird der nächste Schritt
   in der Spiellogik ausgeführt
   */
   if(iSteinGesetzt == 1)
   {
      g_iStep = 4;
   }
   if(g_cNeustart == 'j')
   {  
      g_iAnzahlSteine = 0;
      g_iPlayer = 1;
      g_iStep = 0;
      g_cBeenden = 'n';
      g_iSprung=0;
      g_cNeustart = 'n';
   }
   if(g_cBeenden == 'j')
   {
      g_iStep = 6;
   }
}
/*
==============================================================================
Name:         pruefeZiel()
In:            iXPos, iYPos
Out:         1 - Ziel ist OK
            0 - Ziel ist nicht OK
Parameter:      Koordinaten des Ziels sowie rückgabe ob das Ziel korrekt ist
Beschreibung:   Nutzt die übergebenen Koordinaten um im Array das entsprechende 
            Feld zu überprüfen. Ist das Feld ein möglicher Ablegeplatz für 
            einen Spielstein (also mit 'x' gekennzeichnet) sendet die 
            Funktion ein return 1 für "Ziel ist Ok".
                  
                             Package: OK
==============================================================================
*/
int pruefeZiel(int iXPos, int iYPos)
{
   int iZielOk = 0;
   if(g_cSpielfeld[iXPos][iYPos] == 'x')
   {
      iZielOk = 1;
   }
   return iZielOk;
}
/*
==============================================================================
Name:         setzeStein()
In:            iNeueXPos, iNeueYPos
Out:         1  -  Stein konnte gesetzt werden
            0  -  Stein konnte nicht gesetzt werden
Parameter:      Koordinaten des Ziels sowie rückgabe ob der Stein gesetzt
            werden konnte.
Beschreibung:   Erst wird überprüft ob das gewünschte Ziel auch ein Ziel des
            gewählten Spielsteins ist, dann wird dieser dorthin gesetzt und
            alle markierten Ziele entfernt.

                             Package: OK
==============================================================================
*/
int setzeStein(int iNeueXPos, int iNeueYPos)
{
   char cSpieler;
   
   if(g_iPlayer == 1)
   {
      cSpieler = 'H';      
   }
   else
   {
      cSpieler = 'C';
   }
   
   /*
   Unterscheidet sich die neue Y-Koordinate von der Stein Y-Koordinate
   kann der Stein neu gesetzt werden.
   */
   if(iNeueYPos != g_iSteinY && iNeueXPos != g_iSteinX)
   {
      /*
      Einfaches setzen des Steines auf ein freies diagonales Feld.
      -> Links oben
      */
      if(g_iSteinX-1 == iNeueXPos && g_iSteinY-1 == iNeueYPos)
      {
         g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
         g_cSpielfeld[iNeueXPos][iNeueYPos]= cSpieler;
      }
      /*
      -> Rechts oben
      */
      if(g_iSteinX-1 == iNeueXPos && g_iSteinY+1 == iNeueYPos)
      {
         g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
         g_cSpielfeld[iNeueXPos][iNeueYPos]= cSpieler;
      }
      /*
      -> Links unten
      */
      if(g_iSteinX+1 == iNeueXPos && g_iSteinY-1 == iNeueYPos)
      {
         g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
         g_cSpielfeld[iNeueXPos][iNeueYPos]= cSpieler;
      }
      /*
      -> Rechts unten
      */
      if(g_iSteinX+1 == iNeueXPos && g_iSteinY+1 == iNeueYPos)
      {
         g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
         g_cSpielfeld[iNeueXPos][iNeueYPos]= cSpieler;
      }    
   
      /*
      Setzen des Steins wenn ein gegnerischer Stein übersprungen wird.
      -> Links oben
      */
      if(g_iSteinX-2 == iNeueXPos && g_iSteinY-2 == iNeueYPos)
      {
         g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
         g_cSpielfeld[g_iSteinX-1][g_iSteinY-1] = '-';
         g_cSpielfeld[iNeueXPos][iNeueYPos]= cSpieler;
         /*
         Anzahl der gegnerischen Steine wird um 1 reduziert
         */
         if(g_iPlayer == 1)
         {
            g_iAnzahlSpieler2--;
         }
         else
         {
            g_iAnzahlSpieler1--;
         }
      }
      /*
      -> Rechts oben
      */
      if(g_iSteinX-2 == iNeueXPos && g_iSteinY+2 == iNeueYPos)
      {
         g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
         g_cSpielfeld[g_iSteinX-1][g_iSteinY+1] = '-';
         g_cSpielfeld[iNeueXPos][iNeueYPos]= cSpieler;
         /*
         Anzahl der gegnerischen Steine wird um 1 reduziert
         */
         if(g_iPlayer == 1)
         {
            g_iAnzahlSpieler2--;
         }
         else
         {
            g_iAnzahlSpieler1--;
         }
      }
      /*
      -> Links unten
      */
      if(g_iSteinX+2 == iNeueXPos && g_iSteinY-2 == iNeueYPos)
      {
         g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
         g_cSpielfeld[g_iSteinX+1][g_iSteinY-1] = '-';
         g_cSpielfeld[iNeueXPos][iNeueYPos]= cSpieler;
         /*
         Anzahl der gegnerischen Steine wird um 1 reduziert
         */
         if(g_iPlayer == 1)
         {
            g_iAnzahlSpieler2--;
         }
         else
         {
            g_iAnzahlSpieler1--;
         }
      }
      /*
      -> Rechts unten
      */
      if(g_iSteinX+2 == iNeueXPos && g_iSteinY+2 == iNeueYPos)
      {
         g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
         g_cSpielfeld[g_iSteinX+1][g_iSteinY+1] = '-';
         g_cSpielfeld[iNeueXPos][iNeueYPos]= cSpieler;
         /*
         Anzahl der gegnerischen Steine wird um 1 reduziert
         */
         if(g_iPlayer == 1)
         {
            g_iAnzahlSpieler2--;
         }
         else
         {
            g_iAnzahlSpieler1--;
         }
      }
      
      g_iSteinX = iNeueXPos;
      g_iSteinY = iNeueYPos;
      
      /*
      Stein konnte gesetzt werden.
      */
      return 1;
   }
   /*
   Entspricht die neue Y-Koordinate der Stein Y-Koordinate wurde
   zwar ein markiertes Feld ausgewählt, jedoch eines für den Sprung
   eines anderen Spielsteines(Spielstein links oder rechts daneben) 
   */
   else
   {
      /*
      Stein konnte nicht gesetzt werden.
      */      
      return 0;
   }         
}
/*
==============================================================================
Name:         setzeDame()
In:            iNeueXPos, iNeueYPos
Out:         1  -  Dame konnte gesetzt werden
            0  -  Dame konnte nicht gesetzt werden
Parameter:      Koordinaten des Ziels sowie rückgabe ob die Dame gesetzt
            werden konnte.
Beschreibung:   Erst wird überprüft ob das gewünschte Ziel auch ein Ziel der
            Dame ist, dann wird diese dorthin gesetzt und alle markierten 
            Ziele entfernt.        
                             Package: OK
==============================================================================
*/
int setzeDame(int iNeueXPos, int iNeueYPos)
{
   int x, y;
   int iArrayZaehler = 0;
   char cSpielerFigur;
   
   /*
   Setzen des jeweiligen Bezeichners
   */
   if(g_iPlayer == 1)
   {
      cSpielerFigur = 'Q';
   }
   else
   {
      cSpielerFigur = 'K';
   }
    
   /*
   Überprüfung ob das Ziel ein markiertes Feld ist und 
   diese Felds in der diagonalen der Dame liegt
   */
   if(g_cSpielfeld[iNeueXPos][iNeueYPos] == 'x'
   && iNeueXPos != g_iSteinX && iNeueYPos != g_iSteinY)
   {
      /*
      Diagonale Links-Oben
      */
      x = iNeueXPos;
      y = iNeueYPos;
      while(x < g_iSteinX && y < g_iSteinY)
      {
         if(g_cSpielfeld[x][y] == 'H' || g_cSpielfeld[x][y] == 'Q' ||
            g_cSpielfeld[x][y] == 'C' || g_cSpielfeld[x][y] == 'K')
         {
            g_cSpielfeld[x][y] = '-';   
         }
         /*
         */
         if(x+1 == g_iSteinX && y+1 == g_iSteinY)
         {
            g_cSpielfeld[iNeueXPos][iNeueYPos] = cSpielerFigur;
            g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
            
            g_iSteinX = iNeueXPos;
            g_iSteinY = iNeueYPos;
            return 1;
         }
         else
         {
            x++;
            y++;
         }
      }
      /*
      Diagonale Rechts-Oben
      */
      x = iNeueXPos;
      y = iNeueYPos;
      iArrayZaehler = 0;
      while(x < g_iSteinX && y > g_iSteinY)
      {
         if(g_cSpielfeld[x][y] == 'H' || g_cSpielfeld[x][y] == 'Q' ||
            g_cSpielfeld[x][y] == 'C' || g_cSpielfeld[x][y] == 'K')
         {
            g_cSpielfeld[x][y] = '-';   
         }
         if(x+1 == g_iSteinX && y-1 == g_iSteinY)
         {
            g_cSpielfeld[iNeueXPos][iNeueYPos] = cSpielerFigur;
            g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
            
            g_iSteinX = iNeueXPos;
            g_iSteinY = iNeueYPos;
            return 1;
         }
         else
         {
            x++;
            y--;
         }
      }
      /*
      Diagonale Links-Unten
      */
      x = iNeueXPos;
      y = iNeueYPos;
      iArrayZaehler = 0;
      while(x > g_iSteinX && y < g_iSteinY)
      {
         if(g_cSpielfeld[x][y] == 'H' || g_cSpielfeld[x][y] == 'Q' ||
               g_cSpielfeld[x][y] == 'C' || g_cSpielfeld[x][y] == 'K')
         {
            g_cSpielfeld[x][y] = '-';   
         }
         if(x-1 == g_iSteinX && y+1 == g_iSteinY)
         {
            g_cSpielfeld[iNeueXPos][iNeueYPos] = cSpielerFigur;
            g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
            
            g_iSteinX = iNeueXPos;
            g_iSteinY = iNeueYPos;
            return 1;
         }
         else
         {
            x--;
            y++;
         }
      }
      /*
      Diagonale Rechts-Unten
      */
      x = iNeueXPos;
      y = iNeueYPos;
      iArrayZaehler = 0;
      while(x > g_iSteinX && y > g_iSteinY)
      {
         if(g_cSpielfeld[x][y] == 'H' || g_cSpielfeld[x][y] == 'Q' ||
               g_cSpielfeld[x][y] == 'C' || g_cSpielfeld[x][y] == 'K')
         {
            g_cSpielfeld[x][y] = '-';   
         }
         if(x-1 == g_iSteinX && y-1 == g_iSteinY)
         {
            g_cSpielfeld[iNeueXPos][iNeueYPos] = cSpielerFigur;
            g_cSpielfeld[g_iSteinX][g_iSteinY] = '-';
            
            g_iSteinX = iNeueXPos;
            g_iSteinY = iNeueYPos;
            return 1;
         }
         else
         {
            x--;
            y--;
         }
      }    
   }
   return 0;      
} 
/*
==============================================================================
Name:         wandleZuDame()
In:            -
Out:         -
Parameter:      -
Beschreibung:   Hat der Spieler mit einem seiner Steine die gegenüberliegende 
            Seite des Feldes erreicht, wird dieser in eine Dame verwandelt.        
                             Package: OK
==============================================================================
*/
void wandleZuDame(void)
{
   int h;
   for(h = 0; h <= 7; h++)
   {
      /*
      Gehört der Spielstein dem ersten Spieler wird das "H" zu
      einem "Q"
      */
      if(g_cSpielfeld[0][h] == 'H')
      {
         g_cSpielfeld[0][h] = 'Q';
      }
      /*
      Gehört der Spielstein dem zweiten Spieler wird das "C" zu
      einem "K"
      */
      if(g_cSpielfeld[7][h] == 'C')
      {
         g_cSpielfeld[7][h] = 'K';
      }
   }
   
   //Der nächste Step soll ausgeführt werden
   g_iStep = 5;
}
/*
==============================================================================
Name:         wechselSpieler()
In:            -
Out:         -
Parameter:      -
Beschreibung:   Diese Funktion vollzieht den Spieler wechsel, nachdem der 
            Spieler einen gültigen Zug gemacht hat und dieser keine 
            Möglichkeit mehr hat, mit einem Spielstein der bereits einen 
            Stein geschlagen hat noch einen Stein zu schlagen.        
                             Package: OK
==============================================================================
*/
void wechselSpieler(void)
{
   int i, h;
   
   /*
   Alle gekennzeichneten Felder werden wieder auf "-"
   gesetzt.   
   */   
   for(i = 0; i < 8; i++)
   {
      for(h = 0; h < 8; h++)
      {
         if(g_cSpielfeld[i][h] == 'x')
         {
            g_cSpielfeld[i][h] = '-';
         }
      }
   }
   
   /*
   War bereits das Schlagen eines gegnerischen Steines möglich, soll
   überprüft werden ob mit dem selben eigenen Stein noch ein gegnerischer
   Stein geschlagen werden kann.
   */
   if(g_iSprung == 1)
   {
      g_iSprung = 0;
      pruefeObSprungMoeglich(g_iSteinX, g_iSteinY, g_cSpielfeld[g_iSteinX][g_iSteinY]);
   }
   /*
   Ist es nicht möglich mit dem gleichen Stein noch einen Stein zu schlagen,
   wird der Spieler gewechselt und der Programmablauf fängt von vorne an.
   */
   if(g_iSprung == 0)
   {
      if(g_iPlayer == 1)
      {
         //Wechsel zu Spieler 2
         strcpy(g_cAktuellerSpieler, g_cSpieler2);
         g_iPlayer = 2;
      }
      else
      {
         //Wechsel zu Spieler 1
         strcpy(g_cAktuellerSpieler, g_cSpieler1);
         g_iPlayer = 1;
      }
      g_iStep = 1;
      g_iAnzahlSteine = 0;
      g_iBewegung = 0;
   }
   else
   {
      g_iStep = 2; //
   }   
   
   //Konsole wird geleert
   system("cls");
   
   //Puffer-Speicher wird geleert
   fflush(stdin);
}
/*
==============================================================================
Name:         beenden()
In:            -
Out:         -
Parameter:      -
Beschreibung:   Der jeweils angebrachte Screen am Ende des Spiels wird 
            ausgegeben. Die Wahl des Screens am Ende ist bedingt durch den 
            Abschluss des Spiels: Gewonnen, Verloren, Unentschieden oder 
            Abbruch.

                             Package: OK
==============================================================================
*/
void beenden(void)
{
   if(g_fExitCode == 0)
   {
      system("cls");
      printf("===========================================================");
      printf("=====================");
      printf("    $$     $$ $$ $$$  $$||    $$     $$ $$ $$$  $$||    $$ ");
      printf("    $$ $$ $$$  $$    ");
      printf("   $$     $$ $$ $$$$ $$ ||   $$     $$ $$ $$$$ $$ ||   $$  ");
      printf("   $$ $$ $$$$ $$     ");      
      printf("  $$  $  $$ $$ $$ $$$$  ||  $$  $  $$ $$ $$ $$$$  ||  $$  $");
      printf("  $$ $$ $$ $$$$      ");
      printf(" $$ $$$ $$ $$ $$  $$$   || $$ $$$ $$ $$ $$  $$$   || $$ $$$");
      printf(" $$ $$ $$  $$$       ");
      printf("$$$$$$$$$ $$ $$   $$    ||$$$$$$$$$ $$ $$   $$    ||$$$$$$$");
      printf("$$ $$ $$   $$        ");
      printf("===========================================================");
      printf("=====================");
      printf("\n\nHerzlichen Glueckwunsch.\n %s hat gewonnen!!\n\n", 
         g_cSpieler2);
      printf("\n");
   }
   if(g_fExitCode == 1)
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
      printf("Herzlichen Glueckwunsch.\n %s hat gewonnen!!\n\n", 
         g_cSpieler1);
      printf("\n");
   }
   if(g_fExitCode == -1)
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
      printf("\t Sie haben das Spiel beendet. ");
      printf("\n");
      printf("\t Es findet keine Wertung statt.");
   }
   if(g_fExitCode == 0.5)
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
      printf("\t Das Spiel endete: Unentschieden");
   }
   printf("\n\n\t ");
    system("pause");
   g_cBeenden = 'j';
}
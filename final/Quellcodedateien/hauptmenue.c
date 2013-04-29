/*
===============================================================================
   Autor :  Monika Klein
   Klasse : FA3
   Dateiname : hauptmenue.c
   Datum : 30.05.2011
   Beschreibung: 
   Version : 1.0
===============================================================================
*/

/* 
===============================================================================
   Include-Dateien
===============================================================================
*/

#include "hauptmenue.h"

/*
===============================================================================
   Funktion:      hauptmenue()
   in:            -
   out:           -
   Beschreibung:  Nach dem Login beider Spieler oder der Wahl eines 
                  Computergegners gelangen sie ins Hauptmenue, um forzufahren.
                  Das entsprechende Spiel wird gestartet oder die Statistik 
                  angezeigt.
                  Die Spieler haben auch die Möglichkeit sich wieder 
                  auszuloggen, um das Spiel ggf. zu beenden.
===============================================================================
*/
void hauptmenue(void)
{
   char cAuswahl;
   int iRun = 1;

   do
   {
      system("cls");

      //Ausgabe
      printf("===================================================");
	  printf("=============================");
      printf("               $$$  $$$     $$$$$$ $$$  $$  $$   $$");
	  printf("  $$    $$$$    $$           ");
      printf("              $$$$ $$$$    $$     $$$$ $$  $$   $$ ");
	  printf("  $$  $$$$$$$$  $$           ");
      printf("             $$ $$$$ $$   $$$$   $$ $$$$  $$   $$  ");
	  printf("    $$$ $$$$ $$$             ");
      printf("            $$  $$$  $$  $$     $$  $$$  $$   $$   ");
	  printf("      $$$$$$$$               ");
      printf("           $$   $$   $$ $$$$$$ $$   $$    $$$$     ");
	  printf("$$   $$   $$             ");
      printf("===================================================");
	  printf("=============================");
      printf("\n\n");
      printf("\ta: Checkers");
      if (!strcmp(g_cSpieler2, "COMPUTER"))
         printf("(Im Computer-Modus nicht verfuegbar)");
      printf("\n");
      printf("\tb: Reversi\n");
      printf("\tc: 4-Gewinnt\n");
      printf("\td: Bridges");
      if (!strcmp(g_cSpieler2, "COMPUTER"))
         printf("(Im Computer-Modus nicht verfuegbar)");
      printf("\n");
      printf("\ts: Statistiken anzeigen\n");
      printf("\n");
      printf("\tl: Logout\n");
      printf("\n");
   
      //Eingabe
      printf("\tIhre Eingabe: ");
      scanf("%c", &cAuswahl);
      fflush(stdin);
      printf("\n\n");

      switch(cAuswahl){
         case 'a':
            // Checkers 
            if (strcmp(g_cSpieler2, "COMPUTER"))
               zeigeSpielmenu("Checkers");
            break;
   
         case 'b':
            // Reversi 
            zeigeSpielmenu("Reversi");
            break;

         case 'c':
            // 4-Gewinnt 
            zeigeSpielmenu("4Gewinnt");
            break;

         case 'd':
            // Bridges
            if (strcmp(g_cSpieler2, "COMPUTER"))
               zeigeSpielmenu("Bridges");
            break;

         case 's':
            zeigeGesamtStatistik();
            break;

         case 'l':
            iRun = 0;
            break;
      }
   }
   while(iRun);
}

/*
===============================================================================
   Funktion:      zeigeGesamtStatistik()
   in:            -
   out:           -
   Beschreibung:  Zeigt ein Untermenü für die Statistik an. Man kann sich          
                  verschiedene Statistiktabellen anzeigen lassen. 
===============================================================================
*/
void zeigeGesamtStatistik(void)
{
   char cEingabe;

   system("cls");
   printf("======================================================");
   printf("==========================");
   printf("         $$$$$$$ $$$$$$$$ $$$$$$$ $$$$$$$$$ $$ $$$$$$ ");
   printf("$$$$$$$$ $$ $$   $$       ");
   printf("        $$         $$    $$   $$    $$     $$ $$      ");
   printf("  $$    $$ $$  $$$        ");
   printf("       $$$$$$$$   $$    $$$$$$$    $$     $$ $$$$$$$  ");
   printf(" $$    $$ $$$$$$          ");
   printf("            $$   $$    $$   $$    $$     $$      $$   ");
   printf("$$    $$ $$  $$           ");
   printf("      $$$$$$$   $$    $$   $$    $$     $$ $$$$$$$   $");
   printf("$    $$ $$   $$           ");
   printf("======================================================");
   printf("==========================");
   printf("\n\n");
   printf("\ta: Eigene Punktbewertung (Spieler 1 und Spieler 2) "); 
   printf("\n\t   aller Spiele anzeigen\n");
   printf("\tb: Punktbewertung aller Sieler aller Spiele anzeigen \n");
   printf("\tc: Anzahl der eigenen (Spieler 1 und Spieler 2) Siege, \n");
   printf("\t   Niederlagen und Remis anzeigen\n");
   printf("\n");

   //Eingabe
   printf("\tIhre Eingabe: ");
   scanf("%c", &cEingabe);
   fflush(stdin);
   printf("\n\n");

   switch(cEingabe){
         case 'a':
            eigeneBewertungAllerSpiele();
            break;
   
         case 'b':
            bewertungKomplett();
            break;

         case 'c':
            anzahlSpieleAlle();
            break;
         default:
            printf("falsche Eingabe. Bitte wiederholen");
   }
}

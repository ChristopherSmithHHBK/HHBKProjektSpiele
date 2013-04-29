/*
===============================================================================
   Autor         : Monika Klein
   Klasse        : FA3
   Dateiname     : Login.h
   Datum         : 01.06.2011
   Version       : 1.0
   Beschreibung  : Startpunkt des Programmes.
                   Loggt die Spieler ein und lässt den ersten Spieler seinen 
                   Gegner wählen
===============================================================================
*/

/*
==============================================================================
   Include Anweisungen
==============================================================================
*/

#include "Login.h"

/*
===============================================================================
   Hauptfunktion main()
===============================================================================
*/
int main(void)
{   
   int iRun = 1;
   initi();

   while (iRun)
   {
      if (login(1))
	  {
         iRun = 0;
	  }
      else if (gegnerWaehlen())
	  {
         if(login(2))
		 {
            iRun = 0;
		 }
	  }
      if (iRun)
	  {
         hauptmenue();
	  }
   }

   if (g_iVerbunden)
   {
      schliesseDB();
   }

   return 0;
}
/*
===============================================================================
   Funktion:      gegnerWaehlen()
   in:            -
   out:           1  - Computer
                  0  - 2. Spieler
   Beschreibung:  Zeigt die Auswahl, ob man einen zweiten Spieler einloggen
                  oder gegen den Computer spielen möchte.
===============================================================================
*/
int gegnerWaehlen(void)
{
      char cGegner;
     int iLogout = 0;

     do
     {
         system("cls");
         printf("============================================================");
         printf("====================");
         printf("               $$     $$$$$   $$$$$$     $$ $$$$   $$       ");
         printf("       $$           ");
         printf("              $$     $$  $$  $$         $$ $$$$$  $$    $$$$");
         printf("$$$$$$$$$$$         ");
         printf("             $$     $$  $$  $$ $$$     $$ $$  $$ $$      $$$");
         printf("$$$$$$$$$$$$$       ");
         printf("            $$     $$  $$  $$   $$    $$ $$   $$$$      $$$$");
         printf("$$$$$$$$$$$         ");
         printf("           $$$$$$$ $$$$    $$$$$     $$ $$    $$$           ");
         printf("       $$           ");
         printf("============================================================");
         printf("====================");
         printf("\n\n");
         printf("\tWaehlen Sie Ihren Gegner:\n\n");
         printf("\ta: Computer(Nur fuer Reversi und 4Gewinnt ");
         printf("verfuegbar)\n"); 
         printf("\tb: 2. Spieler\n\n"); 
        
         printf("\tEingabe: ");
         
         scanf("%c", &cGegner);
         fflush(stdin);
      
         switch(cGegner)
         {
            case 'a':
               strcpy(g_cSpieler2, "COMPUTER"); 
               g_iKI = 1;
               return 0;
               break;
            case 'b':
               // 2. Spieler einloggen
               g_iKI = 0;
               return 1;
               break;
            default:
               printf("\n\tungueltige Eingabe\n\n");
               printf("\tDruecken Sie eine beliebige Taste, um die ");
               printf("Eingabe zu wiederholen.\n");
               getchar();
               break;
         }
      }   
      while(cGegner != 'a' && cGegner != 'b');  

      g_iKI = 1;
      return 0;
}

/*
===============================================================================
   Funktion:      ausgabenText()
   in:            iLogout, iSpielerNr, iLoginNeu, iUngueltigesZeichen, 
                  iUngueltigesZeichen, iBereitsEingeloggt
   out:           -
   Beschreibung:  Gibt den Ausgabetext zum Einloggen der Spieler und 
                  evtl weitere Meldungen und Hinweise aus.
===============================================================================
*/
void ausgebenText(int iLogout, int iSpielerNr, int iLoginNeu, 
   int iUngueltigesZeichen, int iUngueltigerName, int iBereitsEingeloggt)
{

   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
      FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
   system("cls");
   // Schreibe Meldung, wenn Spieler ausgeloggt wurden
   if (iLogout)
   {
      printf("\n");
      printf("\tMeldung:\n");
      printf("\tSie wurden erfolgreich ausgeloggt\n");
      printf("\n");
   } 
   else
   {

      // Schreibe überschrift
      printf("============================================================");
      printf("====================");
      printf("               $$     $$$$$   $$$$$$     $$ $$$$   $$       ");
      printf("       $$           ");
      printf("              $$     $$  $$  $$         $$ $$$$$  $$    $$$$");
      printf("$$$$$$$$$$$         ");
      printf("             $$     $$  $$  $$ $$$     $$ $$  $$ $$      $$$");
      printf("$$$$$$$$$$$$$       ");
      printf("            $$     $$  $$  $$   $$    $$ $$   $$$$      $$$$");
      printf("$$$$$$$$$$$         ");
      printf("           $$$$$$$ $$$$    $$$$$     $$ $$    $$$           ");
      printf("       $$           ");
      printf("============================================================");
      printf("====================");
      printf("\n");
      printf("\tSpieler %i\n\n", iSpielerNr);

      // Schreibe Meldung, wenn Spieler 3 mal falsches Passwort eingegeben hat
      if (iLoginNeu)
      {
         printf("\n");
         printf("\tMeldung:\n");
         printf("\tSie haben Ihr Passwort 3 mal falsch eingegeben.\n");
         printf("\tWenn Sie Ihr Passwort nicht mehr wissen, koennen ");
         printf("Sie sich mit\n");
         printf("\teinem neuen Nicknamen registrieren. Ihre alten Werte ");
         printf("und\n");
         printf("\tPunkte gehen dabei verloren.\n");
         printf("\n\n");
      }

      if (iUngueltigesZeichen)
      {
         printf("\tSonderzeichen sind nicht erlaubt. ");
         printf("Bitte geben Sie nur\n");
         printf("\tBuchstaben von A-Z und Ziffern von 0-9 ein.\n");
         printf("\tBitte waehlen Sie einen anderen.\n\n");
      }

      if (iBereitsEingeloggt)
      {
         printf("\tSie duerfen sich nicht mit dem gleichen Nicknamen,\n");
         printf("wie den von Spieler 1 einloggen.\n");
         printf("\tBitte waehlen Sie einen anderen.\n");
      }

      if (iUngueltigerName)
      {
         printf("\tDer Name darf nicht leer sein oder den Namen ");
         printf("\"COMPUTER\" haben.\n");
         printf("\tBitte waehlen Sie einen anderen.\n");
      }
      // Schreibe Informationen zum Login
      printf("\tWenn Sie schon registriert sind, dann geben Sie Ihren\n");
      printf("\tNicknamen ein.\n\n");
      printf("\tWenn Sie sich registrieren wollen, dann geben Sie\n");
      printf("\tIhren Wunschnicknamen ein\n\n");
      printf("\tx: Spiel beenden\n");
      printf("\n");
   }
}
/*
===============================================================================
   Funktion:      registriereBenutzer()
   in:            cSpielerNeu[]
   out:           1  -  Registrierung erfolgreich
                  0  -  Registrierung fehlgeschlagen    
   Beschreibung:  Benutzer in die Datenbank einfügen (Registrierung)
===============================================================================
*/

int registriereBenutzer(char cSpielerNeu[])
{
   char cPasswortNeu[SPIELERLAENGE] = "";
   char cStatement[200];
   int iGueltig = 1;
   int i;
   do
   {
      if (iGueltig == 0)
      {
         printf("\tDas Passwort entspricht nicht den kriterien.\n");
         printf("\tDas Passwort muss mindestens ein Buchstabe von A-Z, a-z");
         printf("\n\toder eine Ziffern enthalten.\n");
      }
      else
      {
         printf("\tSie sind noch nicht registriert. ");
         printf("Bitte geben Sie Ihr Passwort ein.\n");
      }

      iGueltig = 1;
      printf("\tPasswort: ");
      scanf("%24s", cPasswortNeu);
      fflush(stdin);

      for (i = 0; i < strlen(cPasswortNeu); i++)
      {
         if (!isalpha((unsigned char) cPasswortNeu[i]))
         {
            if (!isalnum((unsigned char) cPasswortNeu[i]))
			{
               iGueltig = 0;
			}
         }
      }
   }
   while(!iGueltig);

   holeSQLNeuerBenutzerStatement(cStatement, cSpielerNeu, cPasswortNeu);

   //Einfügen
   if(mysql_query(conn,cStatement))
   {
      ausgebenFehlermeldung("Fehler1 beim Einfuegen des Benutzers in DB");
      return 0;
   }

   //Benutzer in den Tabellen der 4 Spiele anlegen
   if(!benutzerInSpieleEinfuegen(cSpielerNeu))
   {
      return 0;
   }

   printf("\n\n");
   printf("\tSie wurden erfolgreich registriert\n\t");
   system("pause");

   return 1;
}

/*
===============================================================================
   Funktion:      benutzerInSpieleEinfuegen()
   in:            cName[]
   out:           1  -  Benutzer nicht gefunden
                  0  -  Benutzer gefunden   
   Beschreibung:  Wenn ein Spieler sich registriert hat, dann muss auch ein 
                  Benutzer in den 4 Tabellen der Spiele für die Statistik
                  erstellt werden.
===============================================================================
*/
int benutzerInSpieleEinfuegen(char cName[])
{
   int iBenutzerInDbGefunden = 0;
   char cNeuerBenutzerIn4GewinntEinfuegen[100] = 
      "insert into 4gewinnt (ben_id) values (\"";
   char cNeuerBenutzerInCheckersEinfuegen[100] = 
      "insert into checkers (ben_id) values (\"";
   char cNeuerBenutzerInReversiEinfuegen[100] = 
      "insert into reversi (ben_id) values (\"";
   char cNeuerBenutzerInBridgesEinfuegen[100] = 
      "insert into bridges (ben_id) values (\"";

   //Die Benutzer-ID holen
   if(!sucheSpielerInDb(cName))
      return 0;

   //SQL-Befehl zusammensetzten
   strcat(cNeuerBenutzerIn4GewinntEinfuegen, g_cBenutzerID);
   strcat(cNeuerBenutzerIn4GewinntEinfuegen, "\")");

   strcat(cNeuerBenutzerInCheckersEinfuegen, g_cBenutzerID);
   strcat(cNeuerBenutzerInCheckersEinfuegen, "\")");

   strcat(cNeuerBenutzerInReversiEinfuegen, g_cBenutzerID);
   strcat(cNeuerBenutzerInReversiEinfuegen, "\")");

   strcat(cNeuerBenutzerInBridgesEinfuegen, g_cBenutzerID);
   strcat(cNeuerBenutzerInBridgesEinfuegen, "\")");

   //Einfügen
   if(mysql_query(conn,cNeuerBenutzerIn4GewinntEinfuegen))
   {
      ausgebenFehlermeldung("Fehler2 beim Einfuegen in 4Gewinnt");
      return 0;
   }

   if(mysql_query(conn,cNeuerBenutzerInCheckersEinfuegen))
   {
      ausgebenFehlermeldung("Fehler3 beim Einfuegen in Checkers");
      return 0;
   }

   if(mysql_query(conn,cNeuerBenutzerInReversiEinfuegen))
   {
      ausgebenFehlermeldung("Fehler4 beim Einfuegen in Reversi");
      return 0;
   }

   if(mysql_query(conn,cNeuerBenutzerInBridgesEinfuegen))
   {
      ausgebenFehlermeldung("Fehler5 beim Einfuegen in Bridges");
      return 0;
   }

   return 1;
}

/*
===============================================================================
   Funktion:      pruefePasswort()
   in:            cName[]
   out:           1  -  Passwort ist richtig
                  0  -  Passowort wurde 3 mal falsch eingegeben    
   Beschreibung:  Prueft, ob das eingegebene Passwort zu dem eingegebenen
                  Namen gehört.
                  Gibt der Benutzer sein Passwort 3 mal falsch ein, so
                  gelangt er zurück zum Login, um ggf. einen neuen Nicknamen
                  einzugeben.
===============================================================================
*/
int pruefePasswort(char cName[SPIELERLAENGE])
{
   char cPasswort[SPIELERLAENGE];
   char cStatement[200];
   int iLoginVersuche = 1;

   // 3x falsches Passwort --> Zurück zum Login
   for (iLoginVersuche = 1; iLoginVersuche <= 3; iLoginVersuche++)
   {
      printf("\tPasswort: ");
      scanf("%24s", cPasswort);
      fflush(stdin);

      holeSQLPruefePasswortStatement(cStatement, cName, cPasswort);

      //Überprüfung, ob Spieler mit Passowrt vorhanden--> Select Befehl 
      if(mysql_query(conn,cStatement))
      {
         ausgebenFehlermeldung("Fehler6 bei derSuche mit Passwort ");
      }

      // Ergebnisse in MYSQL_RES ablegen
      if((result= mysql_store_result(conn)) == NULL)
      {
         //printf("Test: result ist null (Passwort)");
         if(mysql_errno(conn))
            ausgebenFehlermeldung
            ("Ergebnis Struktur konnte nicht angelegt werden.");
         else
            ausgebenFehlermeldung("Anfrage lieferte keine Ergebnisse.");
      }

      // Pruefe, ob ein Benutzer mit dem Passowrot gefunden wurde
      if((row= mysql_fetch_row(result)))
      {
         return 1;
      }
   }

   return 0;
}

/*
===============================================================================
   Funktion:      pruefeSpielerName()
   in:            cSpielerName[]
   out:           1 = Name in Ordnung
                  0 = Name falsch (enthält ungültige zeichen)
   Beschreibung:  Prüft, ob der eingegebene Spielername nicht „COMPUTER“, 
                  beim 2. Spieler nicht gleich dem ersten Spieler und nicht
                  leer ist.
===============================================================================
*/

int pruefeSpielerName(char cSpielerName1[25], char cSpielerName2[25])
{
   int i;
   for (i = 0; i  < strlen(cSpielerName1); i++)
   {
      if (!isalpha((unsigned char)cSpielerName1[i]))
         if (!isalnum((unsigned char) cSpielerName1[i]))
		 {
            return -1;
		 }
   }

   if (!strcmp(cSpielerName1, "COMPUTER") ||
      !strcmp(cSpielerName1, ""))
   {
      return -2;
   }

   if (!strcmp(cSpielerName1, cSpielerName2))
   {
      return -3;
   }

   return 0;
}

/*
===============================================================================
   Funktion:      initi()
   in:            -
   out:           -
   Beschreibung:  Initialisiert die Größe des Konsolenfensters
===============================================================================
*/
void initi(void)
{
   // Konsolenfenstergröße einstellen
   HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   BOOL Result;

   if (ConsoleHandle != INVALID_HANDLE_VALUE)
   {
      SMALL_RECT ConsoleRectangle;
      // Größe und Position der Konsole in Zeilen und Spalten
      ConsoleRectangle.Top = 0;
      ConsoleRectangle.Bottom = 60;
      ConsoleRectangle.Left = 0;
      ConsoleRectangle.Right = 75;
      Result = SetConsoleWindowInfo(ConsoleHandle, TRUE, &ConsoleRectangle);
   }
}

/*
===============================================================================
   Funktion:      login()
   in:            iSpieler
   out:           1  -  Verbindung zur Datenbank konnte hergestellt werden
                  0  -  Verbindung zur Datenbank konnte nicht hergestellt             
                        werden
   Beschreibung:  Stellt eine Verbindung zur Datenbank her und loggt den 
                  ersten und optional den zweiten Spieler ein.
===============================================================================
*/
int login(int iSpieler)
{
   if (verbindeDB())
   {
      int iEingeloggt = 0;
      int iBeendet = 0;
      int iUngueltigesZeichen = 0;
      int iUngueltigerName = 0;
      int iBereitsEingeloggt = 0;
      int iLoginNeu = 0;
      int iLogout = 0;
      char cSpielerName[SPIELERLAENGE];

      if (iSpieler == 1)
	  {
         strcpy(cSpielerName, g_cSpieler1);
	  }
      else
	  {
         strcpy(cSpielerName, g_cSpieler2);
	  }

      do
      {
         ausgebenText(iLogout, iSpieler, iLoginNeu, iUngueltigesZeichen, 
            iUngueltigerName, iBereitsEingeloggt);
         iUngueltigesZeichen = 0;
         iUngueltigerName = 0;
         iBereitsEingeloggt = 0;
         switch(eingebenNickname(cSpielerName, iSpieler))
         {
            // Nickname vorhanden
            case 0:
               
               if (pruefePasswort(cSpielerName))
               {
                  iEingeloggt = 1;
                  if (iSpieler == 1)
				  {
                     strcpy(g_cSpieler1, cSpielerName);
				  }
                  else
				  {
                     strcpy(g_cSpieler2, cSpielerName);
				  }
               }
               else
			   {
                  iLoginNeu = 1;
			   }
               break;
            
            // Nickname noch nicht vorhanden
            case 1:
               if (registriereBenutzer(cSpielerName))
               {
                  iEingeloggt = 1;
                  if (iSpieler == 1)
				  {
                     strcpy(g_cSpieler1, cSpielerName);
				  }
                  else
				  {
                     strcpy(g_cSpieler2, cSpielerName);
				  }
               }
               else
			   {
				   iLoginNeu = 1;
			   }
               break;
            // Ungültiges Zeichen
            case -1:
               iUngueltigesZeichen = 1;
               break;
            // Name darf nicht leer oder "COMPUTER" sein
            case -2:
               iUngueltigerName = 1;
               break;
            // Nickname schon eingeloggt
            case -3:
               iBereitsEingeloggt = 1;
               break;
            // Spiel beenden
            case 2:
               iBeendet = 1;
               break;
         }
      }
      while(!iEingeloggt && !iBeendet);

      if (iBeendet)
	  {
         return 1;
	  }
   }
   else
   {
      printf("\tEs konnte keine Verbindung zur Datenbank hergestellt ");
      printf("werden.\n");
      printf("\tBitte beachten Sie, dass Ihre Bewertungen nicht ");
      printf("gespeichert werden können.\n");
      strcpy(g_cSpieler1, "Spieler 1");
      strcpy(g_cSpieler2, "Spieler 2");
      g_iVerbunden = 0;
   }
   
   g_iVerbunden = 1;
   return 0;
}

/*
===============================================================================
   Funktion:      eingebenNickname()
   in:            cSpielerName[], iSpieler
   out:           0  -  Name wurde in der Datenbank gefunden
                  1   -  Name wurde nicht gefunden
                  2   -  Spiel beenden
                  -1 bis -3   -  Fehler
   Beschreibung:  Fordert den Benutzer auf, seinen Nicknamen einzugeben und          
                  prüft, ob der Benutzer das Spiel beendet hat.
===============================================================================
*/
int eingebenNickname(char cSpielerName[SPIELERLAENGE], int iSpieler)
{
   char cTempName[SPIELERLAENGE];
   printf("\tNickname: ");
   
   scanf("%24s", cSpielerName);
   fflush(stdin);

   if (iSpieler == 1)
      strcpy(cTempName, "");
   else
      strcpy(cTempName, g_cSpieler1);
   if (pruefeSpielerName(cSpielerName, cTempName))
      return pruefeSpielerName(cSpielerName, cTempName);

   if ((cSpielerName[0] == 'x' && cSpielerName[1] == '\0') || 
       (cSpielerName[0] == 'x' && cSpielerName[1] == '\0'))
   {
      printf("\n\tDas Spiel wird beendet\n\n\t");
      system("pause");
      return 2;
   }

   if (sucheSpielerInDb(cSpielerName))
      return 0;

   return 1;
}
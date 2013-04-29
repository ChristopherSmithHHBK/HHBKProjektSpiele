#include "bridges.h"

int feld[17][17];



int	playBrides(int player_1_ID, int player_2_ID)
{
init();
spiel();
zeichneSpielfeld();
printf("\n\n\n\t\t Sieg !!!\n\n");
system("Pause");

}

void init(){

	int i=0;
	int j=0;

	for( i=0 ; i<17 ; i++)
	{
		for( j=0 ; j<17 ; j++)
		{
		  feld[j][i]= 0 ;
		}
	}

	for( i=1 ; i<17 ; i=i+2)
	{
		for( j=0 ; j<17 ; j=j+2)
		{
		  feld[j][i]= 1 ;
		}
	}

		for( i=0 ; i<17 ; i=i+2)
	{
		for( j=1 ; j<17 ; j=j+2)
		{
		  feld[j][i]= 2 ;
		}
	}
}

void zeichneSpielfeld(){
	
	int i=0;
	int j=0;
	system("cls");

	
	printf("\n\t\t\t      Bridges\n\n ") ;
	 printf("\n\t\t       2   4   6   8   10  12  14  16  ") ;
	 printf("\n\t\t     1   3   5   7   9   11  13  15  17") ;
	 printf("\n\t\t    -----------------------------------") ;

	for( i=0 ; i<17 ; i++)
	{
		printf("\n\t\t%3i%c ",i+1, 124) ;
		for( j=0 ; j<17 ; j++)
		{
		  if(feld[j][i]== 1)
		  {
			  printf("XX") ;
		 }
		   if(feld[j][i]== 2)
		  {
			  printf("00") ;
		 }
		      if(feld[j][i]== 0)
		  {
			  printf("  ") ;
		 }
		}
	}
}

int spiel(){
	int iSpieler=2;
	int iSpielerNeu=0;
	while (Sieg(iSpieler)==0){	
	if(iSpieler==1){
	iSpielerNeu = 2;
	}
	if(iSpieler==2){
	iSpielerNeu = 1;
	}
	iSpieler = iSpielerNeu;
	
	
	zug(iSpieler);
	}
	return 0;
}

	void zug(int iSpieler){
		int iXKordinate=0;
		int iYKordinate=0;
		while(!(zulaessigerZug(iXKordinate, iYKordinate ))){
		zeichneSpielfeld();
		printf("\n\n\t\t Spieler %i mache deinen Zug \n\t\t(erste X  dann Y Kordinate)\n\n",iSpieler) ;
		fflush(stdin);
		scanf("%i",&iXKordinate);
		fflush(stdin);
		scanf("%i",&iYKordinate);
		}		
		feld[iXKordinate-1][iYKordinate-1]=iSpieler;	
	}

	int zulaessigerZug(int iX , int iY ){
		if(iX<1||iY<1||iX>17||iY>17){
		/*printf("\n Nicht auf dem Feld\n");
		system("Pause");*/
		return 0;
		}
		if(feld[iX-1][iY-1]!=0){
	/*	printf("\n Nicht leer\n");
		system("Pause");*/
		return 0;
		}
		return 1;
	}


	int Sieg(int iSpieler){
		int iBruecken [17][17];
		int Aendernungen=1;
	    int i=0;	
		int j=0;

	
			for( i=0 ; i<17 ; i++)
	
			{
				for( j=0 ; j<17 ; j++)
				{
					iBruecken[j][i]= 0 ;
				}
			}

		if(iSpieler==1){
		iBruecken [0][1]=1;
		iBruecken [0][3]=1;
		iBruecken [0][5]=1;
		iBruecken [0][7]=1;
		iBruecken [0][9]=1;
		iBruecken [0][11]=1;
		iBruecken [0][13]=1;
		iBruecken [0][15]=1;

		}

		if(iSpieler==2){
		iBruecken [1][0]=1;
		iBruecken [3][0]=1;
		iBruecken [5][0]=1;
		iBruecken [7][0]=1;
		iBruecken [9][0]=1;
		iBruecken [11][0]=1;
		iBruecken [13][0]=1;
		iBruecken [15][0]=1;
		
		}

		
		while(Aendernungen!=0)
		{
			Aendernungen=0;	
		for( i=0 ; i<17 ; i++)
	
			{
				for( j=0 ; j<17 ; j++)
				{

					if(j+1<17 && iBruecken[j][i]== 1 && feld[j+1][i]== iSpieler && iBruecken [j+1][i]!=1){
					 iBruecken [j+1][i]=1;
					 Aendernungen++;
					}
					if(i+1<17 && iBruecken[j][i]== 1 && feld[j][i+1]== iSpieler && iBruecken [j][i+1]!=1){
					 iBruecken [j][i+1]=1;
					 Aendernungen++;
					}
					if(j-1>-1  && iBruecken[j][i]== 1 && feld[j-1][i]== iSpieler && iBruecken [j-1][i]!=1){
					 iBruecken [j-1][i]=1;
					 Aendernungen++;
					}
					if(i-1>-1 && iBruecken[j][i]== 1 && feld[j][i-1]== iSpieler && iBruecken [j][i-1]!=1){
					 iBruecken [j][i-1]=1;
					 Aendernungen++;
					}
				}
			}
		}

			//////////////////////////////////////////////////////////////////////////////////////////////////// 
	/*	for( i=0 ; i<17 ; i++)
	{
		printf("\n\t\t%3i ",i+1) ;
		for( j=0 ; j<17 ; j++)
		{
		  if(iBruecken[j][i]== 1)
		  {
			  printf("XX") ;
		 }
		   if(iBruecken[j][i]== 2)
		  {
			  printf("00") ;
		 }
		      if(iBruecken[j][i]== 0)
		  {
			  printf("--") ;
		 }
		}
	}
		system("Pause");*/
		 //////////////////////////////////////////////////////////////////////////////////////////////////////

		for( i=0 ; i<17 ; i++)
			{
				for( j=0 ; j<17 ; j++)
				{
					if(  iSpieler==2  && i==16 && iBruecken [j][i]== 1 ){
					return 1;
					}
					if(  iSpieler==1  && j==16 && iBruecken [j][i]== 1 ){
					return 1;
					}
				}
			}
		return 0;
	}

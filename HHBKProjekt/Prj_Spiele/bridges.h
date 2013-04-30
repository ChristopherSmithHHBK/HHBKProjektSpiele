#if !defined (BRIDGES)

#define BRIDGES

#include <stdio.h>

void init();
int	playBrides(int,  int );
void zeichneSpielfeld();
int spiel();
void zug(int);
int zulaessigerZug(int , int);
int Sieg(int iSpieler);
void zugKI(int iSpieler);

#endif
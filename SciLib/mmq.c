/******************************************************************************/
/* Programador : Fabio Andreozzi Godoy                     Data : 31/08/2002  */
/*     Arquivo : mmq.c                       Ultima atualizacao : 31/08/2002  */
/*      Funcao : Metodo dos minimos quadrados                                 */
/******************************************************************************/

#include <stdio.h>
#include <conio.h>

void main() {
  FILE *fdat;
  float X, SY = 0, SX = 0, SXX = 0;
  float Y, SXY = 0;
  int i = 0;
  float a, b;
  fdat = fopen("\\data.dat","r");
  while (!feof(fdat)) {
    fscanf(fdat,"%f", &X);
    fscanf(fdat,"%f", &Y);
    i++;
    SY  = SY + Y;
    SX  = SX + X;
    SXX = SXX + (X * X);
    SXY = SXY + (X * Y);
  }
  a = ((SY * SXX) - (SX * SXY)) / ((i * SXX) - (SX * SX));
  b = ((i * SXY) - (SX * SY)) / ((i * SXX) - (SX * SX));
  printf("%f",a);
  printf(" -  %f\n",b);
  getchar();
}
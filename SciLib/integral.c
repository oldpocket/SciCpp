/******************************************************************************/
/* Programador : Fabio Andreozzi Godoy                     Data : 01/10/2001  */
/*     Arquivo : trapesio.c                  Ultima atualizacao : 01/10/2002  */
/*      Funcao : Calcular integrais com regra do trapesio e simpson           */
/******************************************************************************/
#include <stdio.h>

int main() {
 int k;
 int i;
 float m, a, b, xk, soma = 0;
 printf("\nEntre com k :"); scanf("%i",&k);
 printf("\nEntre com a :"); scanf("%f",&a);
 printf("\nEntre com b :"); scanf("%f",&b);
/* Regra do Trapesio **********************************************************/
 xk = a;
 for (i = 0; i <= k; i++) {
   if (i == k) xk = b;
   if ((xk == a) || (xk == b)) m = 1.0;
     else m = 2.0;
   soma += (m * (1/xk));
   xk += ((b-a)/k);
 }
 printf("\nValor trapesio: %f", ((b-a)/(2*k))*soma);
/* Regra de Simpson ***********************************************************/
 soma = 0;
 xk = a;
 for (i = 0; i <= k; i++) {
   if ((i == 0) || (i == k)) m = 1;
     else if ((m == 1) || (m == 2)) m = 4;
       else if (m == 4) m = 2;
   soma += (m * (1/xk));
   xk += ((b-a)/k);
 }
 printf("\nValor simpson : %f", ((b-a)/(3*k))*soma);
 return 0;
}

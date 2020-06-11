#include <stdio.h>
#include <string.h>
#include "pilha.h"
#include "pilha.c"

void trans() {
  int r, n, d;
  struct stack s;
  inicPilha(&s);
  printf("Entre com a base que deseja : ");
  scanf("%i",&d);
  printf("Entre com o n. decimal      : ");
  scanf("%i",&n);
  do {
    r = (int)(n%d);
    n = (int)(n/d); // numerador = quociente
    push(&s,r);
  } while (n > 0);
  printf("\nNumero na base %i           : ",d);
  while (!pilhaVazia(&s)) {
    printf("%i", pop(&s));
  }
  printf("\n");
};

void destrans(){
  int b, i, tmp = 0;
  int j, exp, iinv;
  char n[15];
  printf("Entre com a base do numero : "); 
  scanf("%i",&b);
  printf("Entre com o numero que deseja passar para decimal : ");
  scanf("%s",n);
  for (i = 0; i < strlen(n); i++) {
   exp = b;
   iinv = (strlen(n) - (i + 1));
   if (iinv == 0) exp = 1;
     else if (iinv == 1) exp = b;
       else for (j = 0; j < iinv; j += 2) exp = exp * b;
   if (n[i] == '0') tmp = tmp + 0;
     else if (n[i] == '1') tmp = tmp + exp;
       else if (n[i] == '2') tmp = tmp + (2 * exp);
         else if (n[i] == '3') tmp = tmp + (3 * exp);
           else if (n[i] == '4') tmp = tmp + (4 * exp);
             else if (n[i] == '5') tmp = tmp + (5 * exp);
               else if (n[i] == '6') tmp = tmp + (6 * exp);
  }
  printf("Numero decimal : %i",tmp);
}

int main(){
  int op;
  do {
    printf("1 - Transformacao decimal -> base\n");
    printf("2 - Transformacao base -> decimal\n");
    printf("3 - Encerrar...\n");
    printf("Entre com a opcao : "); scanf("%i",&op);  
    if (op == 1) trans();
    if (op == 2) destrans();
    printf("\n\n");
  } while (op != 3);
}

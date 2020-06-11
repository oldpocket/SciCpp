/******************************************************************************/
/*      Funcao : Transformar expressoes na forma infixa em pos-fixa (polonesa)*/
/* Programador : Fabio Andreozzi Godoy - Arquivo : inf_pos.c                  */
/*        Data : 09/07/2002 - Ultima atualizacao : 09/07/2002                 */
/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXPILHA 100

struct stack {
  int topo;
  int item[MAXPILHA];
};
typedef struct stack *STACKPTR;

void inicPilha(STACKPTR ps) {
  ps->topo = -1;
}

int pilhaVazia(STACKPTR ps) {
  if (ps->topo == -1)
    return (1);
    /* verdadeiro */
    else  return (0); /* falso */
}

int pilhaCheia(STACKPTR ps) {
  if (ps->topo == MAXPILHA - 1)
    return (1);
     else return (0);
}

int push (STACKPTR ps, int x) {
  if (pilhaCheia(ps) == 1) {
   printf("Ocorreu overflow na pilha!\n");
   return -1;
  } else {
    return (ps->item[++(ps->topo)] = x);
  }
}

int pop (STACKPTR ps) {
  if (pilhaVazia(ps) == 1) {
    printf("Ocorreu underflow na pilha!\n");
    return -1;
    } else {
      return (ps->item[ps->topo--]);
    }
}

int elemTopo (STACKPTR ps) {
  if (pilhaVazia(ps) == 1) {
    printf("Ocorreu underflow na pilha!\n");
    return -1;
   } else {
      return (ps->item[ps->topo]);
  }
}

/* Parte de converssao das expressoes */

int prioridade (char op) {
  switch (op) {
    case '(' : return(1);
    case '+' :
    case '-' : return(2);
    case '*' :
    case '/' : return(3);
    case '^' : return(4);
    default  : return(0);
  }
};

int valida(char exp) {
  int  i;
  char numc[10] = {'0','1','2','3','4','5','6','7','8','9'};
  char oper[5] = {'*','/','+','-','^'};

  for (i = 0; i <= strlen(numc); i++)
    if (exp == numc[i]) {
      return (1);
      break;
    }
  for (i = 0; i <= strlen(oper); i++) 
    if (exp == oper[i]) { 
      return (2);
      break;
    }
    return -1;
};

int inf_pos(char infixa[], int valores[], char npos[]) {
  int  pos = -1;           /* Indice da pos-fixa */  
  int  i, j, pr;
  int  mem, indCol = -1;
  char x, y[1], aux[100];
  struct stack s;          /* Pilha utilizada durante a converssao inf-posfixa */    
  int   num[10] = {0,1,2,3,4,5,6,7,8,9};
  char numc[10] = {'0','1','2','3','4','5','6','7','8','9'};
  
  strcpy(y, "");
  inicPilha(&s);  

  for (i = 0; i <= strlen(infixa); i++) {
    switch (infixa [i]) {
      case '1' : case '4' : case '5' : case '6' : case '7' :
      case '2' : case '8' : case '9' : case '0' :
      case '3' : pos++;
                 indCol++;
                 for (j = 0; j <= strlen(aux); j++)
                   aux[j] = y[0];
                 for (j = 0; j <= 9; j++)
                   if (num[j] == indCol) npos[pos] = numc[j];
                 j = -1;
                 do {
                   j++;
                   aux[j] = infixa[i];
                   if (valida(infixa[i+1]) == 1) { 
                     mem = 1; 
                     i++;
                   } else mem = 0;
                 } while (mem);
                 valores[indCol] = atoi(aux);
                 break;
      case '+' :
      case '-' :
      case '*' :
      case '/' :
      case '^' : pr = prioridade(infixa[i]);
                 while ((!pilhaVazia(&s)) && (prioridade(elemTopo(&s)) >= pr)) {
                   pos++;
                   npos[pos] = pop(&s);
                 }
                 push(&s, infixa[i]);
                 break;
      case '(' : push(&s, infixa[i]);
                 break;
      case ')' : x = pop(&s);
                 while (x != '(') {
                   pos++;
                   npos[pos] = x;
                   x = pop(&s);
                 }
                 break;
    }
  }
  while (!pilhaVazia(&s)) {
    pos++;
    npos[pos] = pop(&s);
  }
  printf("\nExpressao pos-fixa:    ");
  for (i = 0; i <= pos; i++) 
    printf("%c", npos[i]);
  return pos;
};

int main() {
  /* Declaracao de variaveis e inicializoes */
  char npos[100];          /* Expressao pos-fixa */
  char infixa[100];        /* Expressao infixa   */
  int  vx, vy, i, j, pos;
  int  valores[100];
  struct stack sv;
  int   num[10] = {0,1,2,3,4,5,6,7,8,9};
  char numc[10] = {'0','1','2','3','4','5','6','7','8','9'};

  printf("\nEntre com a expressao: "); scanf("%s",infixa);

  pos = inf_pos(infixa, valores, npos);

  printf("\n\n");
  /* Inicio do procedimento de calculo final */  
  inicPilha(&sv);
  for (i = 0; i <= pos; i++)
    if (valida(npos[i]) == 1)
      for (j = 0; j <= 9; j++) {
        if (numc[j] == npos[i])  push(&sv, valores[num[j]]);
      }
      else {
        vx = pop(&sv);
        vy = pop(&sv);
        switch (npos[i]) {
          case '+' : push(&sv, vx+vy); break;
          case '-' : push(&sv, vx-vy); break;
          case '*' : push(&sv, vx*vy); break;
          case '/' : if (vy) push(&sv, vx/vy);
                       else printf("Divisao por zero");
                     break;
        }
      }

  printf("\nResultado    : %i\n", pop(&sv));

  return 0;
}

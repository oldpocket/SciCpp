#include "pilha.h"

/*************************************/
/*Definicoes das funcoes sobre pilhas*/
/*************************************/
void inicPilha(struct stack *ps) {
  ps->topo = -1;
}

int pilhaVazia(struct stack *ps) {
  if (ps->topo == -1)
    return (1);
    /* verdadeiro */
    else  return (0); /* falso */
}

int pilhaCheia(struct stack *ps) {
  if (ps->topo == MAXPILHA - 1)
    return (1);
     else return (0);
}

int push (struct stack *ps, int x) {
  if (pilhaCheia(ps) == 1) {
   printf("&s","Ocorreu overflow na pilha!\n");
  } else {
    return (ps->item[++(ps->topo)] = x);
  }
}

int pop (struct stack *ps) {
  if (pilhaVazia(ps) == 1) {
    printf("&s","Ocorreu underflow na pilha!\n");
    } else {
      return (ps->item[ps->topo--]);
    }
}

int elemTopo (struct stack *ps) {
  if (pilhaVazia(ps) == 1) {
    printf("&s","Ocorreu underflow na pilha!\n");
   } else {
      return (ps->item[ps->topo]);
  }
}
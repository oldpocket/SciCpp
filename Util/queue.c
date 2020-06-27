/******************************************************************************/
/*   Function : Pilha                                     */
/*  Developer : Fabio Andreozzi Godoy                                         */
/*       Date : 2002-feb */
/******************************************************************************/

/******************************************************************************/
/* Funcoes para o funcionamento de uma FILA                                   */
/* Definicoes das operacoes                                                   */
/******************************************************************************/

#include "queue.h"

/* Inicializa a estrutura da fila */
void inicFila(struct queue *pq) {
  pq->inic = MAXFILA-1;
  pq->fim  = MAXFILA-1;
}

/* Insere o elemento x na fila */
void insFila(struct queue *pq, int x) {
  if (pq->fim == MAXFILA-1)
    pq->fim = 0;
    else
      (pq->fim)++;

  if (pq->fim == pq->inic) {
    printf("Ocorreu overflow na fila!\n");
    exit(1);
  }

  pq->item[pq->fim] = x;
}

/* Remove um elemento da fila */
int remFila(struct queue *pq) {
  if (filaVazia(pq) == 1) {
    printf("Ocorreu underflow na fila!\n");
    exit(1);
  }
  if (pq->inic == MAXFILA-1)
    pq->inic = 0;
    else
      (pq->inic)++;

  return (pq->item[pq->inic]);
}

/* Verifica se a fila esta vazia */
int filaVazia(struct queue *pq) {
  if (pq->inic == pq-> fim)
    return (1); /* verdadeiro */
    else
      return (0); /* falso */
}

/* Verifica se a fila esta cheia */
int filaCheia(struct queue *pq) {
  if (pq->fim == MAXFILA-1)
    return (pq->inic == 0);
    else
      return (pq->inic == ((pq->fim) + 1));
}

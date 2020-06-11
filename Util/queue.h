/******************************************************************************/
/* Funcoes para o funcionamento de uma FILA                                   */
/* Prototipos das funcoes que atuam sobre filas                               */
/******************************************************************************/
/* Estrutura da fila */
#define MAXFILA 8
struct queue {
  int item[MAXFILA];
  int inic, fim;
};

/* Inicializa a estrutura da fila */
void inicFila(struct queue *pq);

/* Insere o elemnto x na fila */
void insFila(struct queue *pq, int x);

/* Remove um elemento da fila */
int remFila(struct queue *pq);

/* Verifica se a fila esta vazia */
int filaVazia(struct queue *pq);

/* Verifica se a fila esta cheia */
int filaCheia(struct queue *pq);

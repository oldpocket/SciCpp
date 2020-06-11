/****************************************/
/*Prototipos das funcoes sobre pilhas   */
/****************************************/

#define MAXPILHA 100

struct stack {
  int topo;
  int item[MAXPILHA];
}

/*Inicializa a pilha*/
void inicPilha(struct stack *ps);

/*Verifica se a pilha esta vazia*/
int pilhaVazia(struct stack *ps);

/*Verifica se a pilha esta cheia*/
int pilhaCheia(struct stack *ps);

/*Adiciona um item a pilha*/
int push(struct stack *ps, int x);

/*Remove um item da pilha e retorna-o*/
int pop(struct stack *ps);

/*Consulta o elemento do topo da pilha*/
int elemTopo(struct stack *ps);

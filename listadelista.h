typedef struct nodo_num{
    int numero;
    struct nodo_num *prox_num;
} nodo_num_t;

typedef struct nodo_letra{
    char letra;
    int tam;
    nodo_num_t *prim_num;
    struct nodo_letra *prox_letra;
} nodo_letra_t;

typedef struct lista{
    nodo_letra_t *Primeiro;
} lista_t;

/*imprime mensagem em caso de erro*/
void error(char *msg);

/*cria lista vazia*/
lista_t *cria_lista();

/*destroi a lista e retorna null*/
lista_t *destroi_lista(lista_t *lista);

/*cria uma letra e adiciona no inicio da lista letra,
*retorna 1 se deu, 0 senao*/
int adiciona_letra_ordem(lista_t *lista, char letra);

int adiciona_letra(lista_t *lista, char letra);

/*verifica a existencia da letra se existir retorna 1, senao retorna 0*/
int verifica_letra(lista_t *lista, char letra);

/*encontra letra e adiciona numero de forma ordenada*/
int adiciona_num(lista_t *lista,  char letra, int num);

/*encontra letra e retorna num aleatorio para codificar, sem remover*/
int retorna_num(lista_t *lista, char letra);

/*retorna 1 se o numero existir, 0 senao*/
int verifica_numero(lista_t *lista, int num);

/*gera aleatorio*/
int gera_aleat(int numero);

/*verifica se a lista esta vazia
* retorna 1 se sim, 0 senao*/
int vazia_lista(lista_t *lista);

/*encontra num e retorna letra para decodificar, sem remover*/
char retorna_letra(lista_t *lista, int num);

/*imprime estrutura*/
int imprime_lista(lista_t *lista, FILE* arquivo);


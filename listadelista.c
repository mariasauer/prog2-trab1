#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "listadelista.h"

/*mensagem de erro*/
void error(char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

/*cria lista vazia return NULL se nao foi possível*/
lista_t *cria_lista(){
    lista_t *lista;

    lista = malloc(sizeof(lista_t));
    if(lista == NULL){
        return NULL;
    }

    lista->Primeiro = NULL;
    return lista;
}


/*destroi lista e returna NULL*/
lista_t *destroi_lista(lista_t *lista){
    nodo_letra_t *letra_aux;
    nodo_num_t *num_aux;

    /*destroi lista de numeros e lista de caracteres*/
    while(lista->Primeiro != NULL){
        while(lista->Primeiro->prim_num != NULL){
        num_aux = lista->Primeiro->prim_num;
        lista->Primeiro->prim_num = lista->Primeiro->prim_num->prox_num;
        free(num_aux);
        }
    letra_aux = lista->Primeiro;
    lista->Primeiro = lista->Primeiro->prox_letra;
    free(letra_aux);
    }

    free(lista);
    return NULL;
}


/*adiciona ordenado na lista letra
*retorna 1 se foi possivel, 0 caso contrario*/
int adiciona_letra_ordem(lista_t *lista, char letra){
    nodo_letra_t *nova_letra, *aux;

    /*verifica se a letra ja existe na lista*/
    if(verifica_letra(lista, letra)){
        return 0;
    }

    nova_letra = malloc(sizeof(nodo_letra_t));
    if(nova_letra == NULL){
        error("Erro ao alocar memoria");
    }
    nova_letra->letra = letra;
    nova_letra->prim_num = NULL;
    nova_letra->tam = 0;

    /*se for a primeira letra a ser adicionada, so adiciona*/
   if(lista->Primeiro == NULL){
        lista->Primeiro = nova_letra;
        nova_letra->prox_letra = NULL;
        return 1;
   }

   aux = lista->Primeiro;
   /*verifica se a primeira posição já é a correta*/
   if(letra < aux->letra){
        nova_letra->prox_letra = lista->Primeiro;
        lista->Primeiro = nova_letra;
        return 1;
   }

    /*procura a posição correta*/
   while((aux->prox_letra != NULL) && ((nova_letra->letra) > (aux->prox_letra->letra))){
        aux = aux->prox_letra;
   }

   /*adiciona*/
   nova_letra->prox_letra = aux->prox_letra;
   aux->prox_letra = nova_letra;
   return 1;
}


/*adiciona sem ordem*/
int adiciona_letra(lista_t *lista, char letra){
     nodo_letra_t *nova_letra, *aux;

    /*verifica se a letra ja existe na lista*/
    if(verifica_letra(lista, letra)){
        return 0;
    }

    nova_letra = malloc(sizeof(nodo_letra_t));
    if(nova_letra == NULL){
        perror("Erro ao alocar memoria");
        exit(1);
    }
    nova_letra->letra = letra;
    nova_letra->prim_num = NULL;
    nova_letra->tam = 0;

   if(lista->Primeiro == NULL){
        lista->Primeiro = nova_letra;
        nova_letra->prox_letra = NULL;
        return 1;
   }


   aux = lista->Primeiro;
    /*vai ate a ultima posição*/
    while(aux->prox_letra != NULL){
        aux = aux->prox_letra;
    }

  
   nova_letra->prox_letra = aux->prox_letra;
   aux->prox_letra = nova_letra;
   return 1;
}



/*verifica se o numero buscado se encontra na estrutura,
*retorna 1 se sim, 0 caso contrario*/
int verifica_numero(lista_t *lista, int numero) {
    nodo_letra_t *aux = lista->Primeiro;
    nodo_num_t *num_aux;

    /*Verifica se a lista está vazia*/
    if (aux == NULL) {
        return 0;
    }

    /*Percorre a lista de letras e números até encontrar o número desejado*/
    while (aux != NULL) {
        num_aux = aux->prim_num;
        while ((num_aux != NULL) && (num_aux->numero != numero) && (num_aux->numero > numero)) {
            num_aux = num_aux->prox_num;
        }

        if ((num_aux != NULL) && (num_aux->numero == numero)) {
            return 1;
        }
        
        aux = aux->prox_letra;
    }

    /*Verifica se o número está na primeira letra*/
    if ((lista->Primeiro->prim_num != NULL) && (lista->Primeiro->prim_num->numero == numero)) {
        return 1;
    }

    return 0;
}




/*verifica a existencia da letra
*se existir retorna 1, senao retorna 0*/
int verifica_letra(lista_t *lista, char letra){
    nodo_letra_t *aux = lista->Primeiro;

    /*verifica se lista esta vazia*/
    if(lista->Primeiro == NULL){
        return 0;
    }

    while((aux->prox_letra != NULL) && (aux->letra != letra)){
        aux = aux->prox_letra;
    }

    /*verifica se parou pelo null ou pq achou a letra*/
    if(aux->letra == letra){
        return 1;
    }

    return 0;
}



/*encontra letra e adiciona numero no inicio da lista numero
*se a letra nao existir retorna 0, se der retorna 1
*/
int adiciona_num(lista_t *lista,  char letra, int num){
    nodo_letra_t *aux = lista->Primeiro;
    nodo_num_t *novo, *num_aux;

    /*verifica se a letra existe*/
    if(!verifica_letra(lista, letra)){
        return 0;
    }

    novo = malloc(sizeof(nodo_num_t));
    if(novo == NULL){
        error("Erro ao alocar memoria");
    }
    novo->numero = num;
    novo->prox_num = NULL;

    /*encontra a letra*/
    while(aux->letra != letra){
        aux = aux->prox_letra;
    }

    /*caso nao exista numero na letra, adiciona*/
    if(aux->prim_num == NULL){
        aux->prim_num = novo;
        aux->tam ++;
        return 1;
    }

    /*caso já exista numero na letra, procura posicao correta e adiciona*/
    /*verifica primeiro valor*/
    if(aux->prim_num->numero < num){
        novo->prox_num = aux->prim_num;
        aux->prim_num = novo;
        aux->tam ++;
        return 1;
    }

    /*procura posição*/
    num_aux = aux->prim_num;
    while((num_aux->prox_num != NULL) && (num_aux->prox_num->numero > num) ){
        num_aux = num_aux->prox_num;
    }

    novo->prox_num = num_aux->prox_num;
    num_aux->prox_num = novo;

    aux->tam ++;
    return 1;
}



/*gera aleatorio*/
int gera_aleat(int numero){
    return 1+(rand()%numero);
}



/*encontra letra e retorna num aleatorio para codificar, sem remover,
* a estrutura de dados nao pode estar vazia e a letra precisa, necessariamente, existir*/
int retorna_num(lista_t *lista, char letra){
    nodo_letra_t *aux;
    nodo_num_t *num_aux;
    int tam, local, i;

    /*encontra letra*/
    aux = lista->Primeiro; 
    while(aux->letra != letra){
        aux = aux->prox_letra;
    }
    /*descobre quantidade de numeros na letra*/
    tam = aux->tam;

    /*caso exista apenas um numero*/
    if(tam == 1){
        return aux->prim_num->numero;
    }

    /*aleatorio entre os valores existentes, retorna a posicao*/
    local = gera_aleat(tam);

    /*busca o valor a ser retornado*/
    num_aux = aux->prim_num;
    if(local == 1){
        return num_aux->numero;
    }

    for(i=1; i<local; i++){
        num_aux = num_aux->prox_num;
    }

    return num_aux->numero;
}



/*retorna 1 se a lista estiver vazia, 0 senao*/
int vazia_lista(lista_t *lista){
    if(lista->Primeiro == NULL)
        return 1;
    return 0;
}



/*encontra num e retorna letra para decodificar, sem remover
*nao verifica se o caracter existe*/
char retorna_letra(lista_t *lista, int num) {
    nodo_letra_t *aux_letra = lista->Primeiro;

    while (aux_letra != NULL) {
        nodo_num_t *aux_num = aux_letra->prim_num;
        while ((aux_num != NULL) && (aux_num->numero != num)) {
            aux_num = aux_num->prox_num;
        }
        if ((aux_num != NULL) && (aux_num->numero == num)) {
            return aux_letra->letra;
        }
        aux_letra = aux_letra->prox_letra;
    }

}


/*imprime estrutura*/
int imprime_lista(lista_t *lista, FILE* arquivo){
    nodo_letra_t *aux_letra;
    nodo_num_t *aux_num;
    int i=1;

    if(vazia_lista(lista)){
        fprintf(arquivo, "lista vazia\n");
        return 0;
    }

    aux_letra = lista->Primeiro;
    aux_num = aux_letra->prim_num;
    /*percorre primeira lista*/
    fprintf(arquivo, "%c :", aux_letra->letra);
    while((i <= aux_letra->tam)){
        fprintf(arquivo, " %d", aux_num->numero);
        aux_num = aux_num->prox_num;
        i++;
    }
    fprintf(arquivo, "\n");

    while(aux_letra->prox_letra != NULL){
        aux_letra = aux_letra->prox_letra;
        aux_num = aux_letra->prim_num;
        i=1;
        fprintf(arquivo,"%c :", aux_letra->letra);
        while((i <= aux_letra->tam)){
            fprintf(arquivo, " %d", aux_num->numero);
            aux_num = aux_num->prox_num;
            i++;
        }
        fprintf(arquivo, "\n");
    }

    return 1;        
}


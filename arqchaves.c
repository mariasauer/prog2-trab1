#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listadelista.h"
#include "arqchaves.h"

/*encontra o maior codigo da lista */
int maior_chave(lista_t *chaves){
    int maior = 0;
    nodo_letra_t *aux = chaves->Primeiro;

    if(chaves->Primeiro == NULL){
        error("Lista vazia");
    }

    while(aux->prox_letra != NULL){
        if(aux->prim_num->numero > maior)
            maior = aux->prim_num->numero;
        aux = aux->prox_letra;
    }

    if(aux->prim_num->numero > maior)
        maior = aux->prim_num->numero;
    
    return maior;
}

/*adiciona caracteres nao presentes no livro cifra,
*adiciona abaixo dos que existem no livro cifra,
*sua chave corresponde a maior_chave++*/
void completa_chaves(lista_t *chaves, int maior){
    nodo_letra_t *novo;
    char controle = 33;
    /*controle estabelece o caracter, valor corresponde a tabela ascii*/
    
    if(chaves->Primeiro == NULL){
        error("Lista vazia");
    }

    maior++;
    while(controle <= 126){
        /*pula caracteres maiusculos*/
        if(controle == 65)
            controle = 91;
        if(!verifica_letra(chaves, controle)){
            if(!caracter_valido(controle)){
                adiciona_letra(chaves, controle);
                adiciona_num(chaves, controle, maior);
            }
        }
        controle++; 
        maior++;       
    }
}



/*gera arquivo com chaves, se flag == 1 gera arq*/
void gera_arquivo(lista_t *chaves, char* arquivo_chave, int flag){
    if(flag == 0)
        return;
    FILE* arquivo;

    arquivo = fopen(arquivo_chave, "w+");
    if(!arquivo){
        error("Erro ao criar arquivo de chaves");
    }

    imprime_lista(chaves, arquivo);
    fclose(arquivo);
}

/*verifica se o caracter é valido*/
int caracter_valido(char letra){
    if((letra >= 'a' && letra <= 'z') || (letra >= '0' && letra <= '9'))
        return 1;
    return 0;
}



/*gera chaves apartir do livro cifra*/
void *cria_chaves(FILE* livro_cifra, char* arquivo_chave, lista_t *chaves, int flag){
    char letra;
    int maior, i = 0;

    /*le primeiro caracter*/
    while(fread(&letra, sizeof(char), 1, livro_cifra) == 1){
           letra = tolower(letra);
        if((letra >= 'a' && letra <= 'z')  || (letra >= '0' && letra <= '9')){
            if(!verifica_letra(chaves, letra)){
                adiciona_letra_ordem(chaves, letra);
            }
            adiciona_num(chaves, letra, i);
            i++;
        }

        /*le o proximo, enquanto nao for nova palavra le
        *a proxima paralavra é a primeira letra apos um ' ' ou \n*/  
        while((letra != ' ' ) && (letra != '\n') && (!feof(livro_cifra)) ){
            fread(&letra, sizeof(char), 1, livro_cifra);
        }    
    }

    /*coloca todos os outros caracteres na lista apartir da maior chave*/
    /*pega a maior chave*/
    maior = maior_chave(chaves);
    completa_chaves(chaves, maior);

    /*identifica se gera ou nao arquivo chave*/
    gera_arquivo(chaves, arquivo_chave, flag);
}


/*gera lista de chaves apartir de um arquivo*/
void le_chaves(lista_t *chaves, FILE* arq_chaves){
    char letra, letra_num;
    int num = 0, maior;
    int trocou= 0;
    /*controla*/
  

    /*começa procurando primeiro char*/
    while(fread(&letra, sizeof(char), 1, arq_chaves) == 1 ){
        while((letra == '\n') || (letra == ' ')){
                fread(&letra, sizeof(char), 1, arq_chaves);
            }
            /*adiciona letra*/
            adiciona_letra_ordem(chaves, letra);
            letra_num = letra;
        while ((fread(&letra, sizeof(char), 1, arq_chaves) == 1)  && (letra != '\n')){
            /*pula espaços*/
            if((letra != ' ') && (letra != ':')){
                num = (letra-'0')  + (num * 10);
                trocou= 1;
            /*trocou para int, adiciona int*/
            } else if(trocou){
                adiciona_num(chaves, letra_num, num);
                num = 0;
                trocou=0;
            }

        }
        if (trocou){
            adiciona_num(chaves, letra_num, num);
            num = 0;
            trocou=0;
        }
    
    }
    /*completa tabela ascii*/
    maior = maior_chave(chaves);
    completa_chaves(chaves, maior);

}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "listadelista.h"
#include "arqchaves.h"
#include "codifica.h"

/*função responsavel por codificar o texto*/
void codifica_mensagem(lista_t *chave, FILE *txt_mensagem, FILE *txt_codificada) {
    char caracter;
    int anterior = 0, valor;

    srand(time(NULL));

    if(txt_mensagem == NULL){
        error("Arquivo vazio");
    }

    fread(&caracter, sizeof(char), 1, txt_mensagem);
    while(!feof(txt_mensagem)){
        caracter = tolower(caracter);
       if(caracter_ascii(caracter) && verifica_letra(chave, caracter)){
        valor = retorna_num(chave, caracter);
       } else if (caracter == ' '){
        valor = -1;
       } else if (caracter == '\n'){
        valor = -2;
       } else {
        valor = -3;
       }

        /*evita que imprima duas vezes o -3 em caracteres com acentuacao*/
        if(anterior != valor || valor != -3){
            fprintf(txt_codificada, " %d", valor);
        }
        anterior = valor;
        fread(&caracter, sizeof(char), 1, txt_mensagem);
    }

}


/*verifica se o caracter pertence a tabela ascii*/
int caracter_ascii(char caracter){
    if(caracter >='!' && caracter <='}'){
        return 1;
    }
    return 0;
}

/*funcao principal da biblioteca*/
void codifica(char *cifra_arq, char *chave_arq, char *mensagem_arq, char *codificada_arq ){
    FILE* livro_cifra, *txt_mensagem, *txt_codificada;
    lista_t *chave;

    /*abre/cria arquivos*/
    livro_cifra = fopen(cifra_arq, "r");
    txt_mensagem = fopen(mensagem_arq, "r");
    txt_codificada = fopen(codificada_arq, "w+");
        if(!livro_cifra || !txt_mensagem || !txt_codificada){
            error("Erro ao abrir arquivo");
        }

    /*cria lista de lista*/
    chave = cria_lista();
    
    /*gera chaves, e gera o arquivo de chaves*/
    cria_chaves(livro_cifra, chave_arq, chave, 1);
    if(vazia_lista(chave)){
        error("Erro ao criar lista de lista");
    }

    /*codifica mensagem*/
    codifica_mensagem(chave, txt_mensagem, txt_codificada);
    
    /*destroi lista de lista*/
    chave = destroi_lista(chave);

    /*fecha arquivos*/
    fclose(livro_cifra);
    fclose(txt_mensagem);
    fclose(txt_codificada);
}

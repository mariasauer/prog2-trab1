#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listadelista.h"
#include "arqchaves.h"
#include "decodifica.h"

/*funcao responsavel por decodificar*/
void decodifica_texto(lista_t *chave, FILE *txt_codificada, FILE *txt_mensagem) {
    char caracter;
    int codigo;

    while (fscanf(txt_codificada, "%d", &codigo) == 1) {
        if (codigo == -1) {
            fprintf(txt_mensagem, " ");
        } else if (codigo == -2) {
            fprintf(txt_mensagem, "\n");
        } else if (codigo == -3) {
            fprintf(txt_mensagem, "[]");
        } else if (verifica_numero(chave, codigo)) {
            caracter = retorna_letra(chave, codigo);
            fprintf(txt_mensagem, "%c", caracter);
        }
        /*le o espaço em branco*/
        fgetc(txt_codificada);
    }
}


/*decodifica apartir do livro cifra*/
void decodifica_usando_livro(char *cifra_arq, char *mensagem_arq, char *codificada_arq){
    FILE* txt_mensagem, *txt_codificada, *txt_cifra;
    lista_t *chave;

    /*abre/cria arquivos*/
    txt_mensagem = fopen(mensagem_arq, "w+");
    txt_codificada = fopen(codificada_arq, "r");
    txt_cifra = fopen(cifra_arq, "r");
        if(!txt_cifra || !txt_codificada || !txt_mensagem){
            error("Erro ao abrir arquivo");
        }


    /*cria lista de lista*/
    chave = cria_lista();
    cria_chaves(txt_cifra, "chave", chave, 0 );
    if(vazia_lista(chave)){
        error("Erro ao criar lista de lista");
    }

    /*decodifica*/
    decodifica_texto(chave, txt_codificada, txt_mensagem);
    

    /*destroi lista de lista*/
    chave = destroi_lista(chave);

    /*fecha arquivos*/
    fclose(txt_mensagem);
    fclose(txt_codificada);
    fclose(txt_cifra);
}


/*decodifica usando arquivo de chaves*/
void decodifica_usando_codigo(char *arq_chaves, char *mensagem_arq, char *codificada_arq){
    FILE* txt_mensagem, *txt_codificada, *txt_chaves;
    lista_t *chave;

    /*abre/cria arquivos*/
    txt_mensagem = fopen(mensagem_arq, "w+");
    txt_codificada = fopen(codificada_arq, "r");
    txt_chaves = fopen(arq_chaves, "r");
        if(!txt_chaves || !txt_codificada || !txt_mensagem){
            error("Erro ao abrir arquivo");
        }


    /*cria lista de lista*/
    chave = cria_lista();
    le_chaves(chave, txt_chaves);
    if(vazia_lista(chave)){
        error("Erro ao criar lista de lista");
    }
    
    /*decodifica*/
    decodifica_texto(chave, txt_codificada, txt_mensagem);

    /*destroi lista de lista*/
    chave = destroi_lista(chave);

    /*fecha arquivos*/
    fclose(txt_mensagem);
    fclose(txt_codificada);
    fclose(txt_chaves);
}


/*funcao principal do decodifica*/
void decodifica(char *livro_cifra, char *arq_chaves, char *arq_mensagem, char *arq_codificada, int flag){
    switch (flag){
    case 1:
        /* usando arquivo*/
        decodifica_usando_codigo(arq_chaves, arq_mensagem, arq_codificada);
        break;
    case 0:
        /* usando livro */
        decodifica_usando_livro(livro_cifra, arq_mensagem, arq_codificada);
        break;
    }

}

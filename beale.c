#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include "listadelista.h"
#include "arqchaves.h"
#include "decodifica.h"
#include "codifica.h"


int main(int argc, char **argv){
    int opcao, flag_g = 0;
    char *livroCifra = NULL, *menCodificada = NULL, *menOriginal = NULL, *mensagemO = NULL, *arqChaves = NULL;

    opterr = 0;


    /*verifica se existe a quantidade de entradas necessarias*/
    if(argc != 10 && argc != 8){
        printf("Entrada inválida \n");
        exit(1);
    }

    /*le e separa entradas*/
    while ((opcao = getopt(argc, argv, "edb:i:m:o:c:")) != -1){
        switch (opcao){
        case 'e':
            break;
        
        case 'd':
            break;
            
        case 'b':
            livroCifra = optarg;
            break;

        case 'i':
            menCodificada = optarg;
            break;

        case 'm':
            menOriginal = optarg;
            break;

        case 'o':
            mensagemO = optarg;
            break;

        case 'c':
            arqChaves = optarg;
            break;

        default:
            printf("Entrada inválida.\n");
            exit(1);
            break;
        }
    }


    /*seleciona caso*/
    if ((strcmp(argv[1], "-e") == 0) && (argc == 10)){
        /*funcao codifica*/
        codifica(livroCifra, arqChaves, menOriginal, mensagemO);
        exit(0);

    } else if ((strcmp(argv[1], "-d") == 0) && (strcmp(argv[4], "-c" ) == 0)){
        /*funcao decofica com arquivo de chaves*/
        decodifica(livroCifra, arqChaves, mensagemO, menCodificada, 1);
        exit(0);

    } else if ((strcmp(argv[1], "-d") == 0) && (strcmp(argv[4], "-b" ) == 0)){
        /*funcao decofica com livro, nao gera arquivo de chaves*/
        decodifica(livroCifra, arqChaves, mensagemO, menCodificada, 0);
        exit(0);
    } else {
        exit(1);
    }
}

/*verifica se é letra ou numero*/
int caracter_valido(char letra);

/*gera arquivo com chaves quando flag == 1*/
void gera_arquivo(lista_t *chaves, char* arquivo_chave, int flag);

/*"main" gera chaves*/
void *cria_chaves(FILE* livro_cifra, char* arquivo_chave, lista_t *chave, int flag);

/*le as chaves do arquivo de chaves*/
void le_chaves(lista_t *chaves, FILE* arq_chaves);

/*completa a lista com todos os caracteres ascii*/
void completa_chaves(lista_t *chaves, int maior);

/*encontra a maior chave*/
int maior_chave(lista_t *chaves);
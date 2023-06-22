/*usando codigo flag == 1, usando livro flag == 0*/
void decodifica(char *cifra_arq, char *arq_chaves, char *mensagem_arq, char *codificada_arq, int flag);

/*decodifica apartir de arquivo chave*/
void decodifica_usando_codigo(char *arq_chaves, char *mensagem_arq, char *codificada_arq);

/*decodifica apartir do livro cifra*/
void decodifica_usando_livro(char *cifra_arq, char *mensagem_arq, char *codificada_arq);

/*decodifica texto*/
void decodifica_texto(lista_t *chave, FILE *txt_codificada, FILE *txt_mensagem);

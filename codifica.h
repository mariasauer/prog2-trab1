/*funcao principal do codifica*/
void codifica(char *cifra_arq, char *chave_arq, char *mensagem_arq, char *codificada_arq );

/*verifica se o caracter pertence a tabela ascii, se pertence retorna 1, caso contrario 0*/
int caracter_ascii(char caracter);

/*funcao que codifica a mensagem*/
void codifica_mensagem(lista_t *chave, FILE *txt_mensagem, FILE *txt_codificada);
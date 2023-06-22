Nome: Maria Carolina Sauer (login dinf: mcs22)
GRR: 20221249

Cifras de Beale:
Trabalho feito com o objetivo de implementar a criptografia de Beale.
Na implementação do trabalho foi priorizada a alocação dinâmica de memória.

Arquivos criados:
    beale.c, listadelista.c, listadelista.h, codifica.c, codifica.h, decodifica.c, decodifica.h, arqchaves.c e arqchaves.h.

Função e estrutra de cada arquivo:
    * beale.c:
        -Arquivo principal do trabalho, nele está contida a condicional que verifica e trata as informações passadas pelo usuário pela entrada padrão;
        -Além disso, constam também as chamadas de funções para tratar o caso exigido pelo usuário.
        -Nesse arquivo não são executadas nenhuma alocação de memória ou abertura/criação de arquivo;
    
    *listadelista.c e listadelista.h:
        -Arquivos que manipulam a principal estrutura de dados empregada nesse trabalho: listas de lista;
        -Criação e destruição da estrutura;
        -Inserção e retorno de elementos;
        -Impressão da estrutra na saida exigida pelo usuário.
        -Essa estrutura conta com um nodo(struct) inicial que indica o inicio da lista de letras;
        -Cada nodo(struct) de letra indica o inicio da lista de números, a quantidade de nodos de números e a próxima letra;
        -Em seguida os nodos(struct) dos números armazenam um int e um endereço(próximo número);
        -Nessa estrutura a manipulação dos dados(tanto char, quanto int) levam em consideração que as listas de int estão organizadas de forma ordenada, logo a inserção/busca de elementos nessas levam essa organização em consideração;
        -Apesar dos elementos estarem ordenados, as buscas dentro dessa estrutura são feitas com um algoritmo de busca sequencial;

    *codifica.c e codifica.h:
        -Biblioteca responsável pela codificação da mensagem;
        -Como explicado no enunciado do trabalho, o algoritmo leva em conta apenas caracteres contidos na tabela ASCII, qualquer caracter diferente desses são ignorados;
        -Os arquivos de texto são abertos nas funções dessa biblioteca;
        -Para codificação o arquivo de mensagem original é aberto, e dentro de um while, um caracter da mensagem original é lido, codificado e impresso no arquivo que armazena a mensagem codificada, dessa forma não foi necessária efetuar nenhuma alocação de memória nessa etapa;
        -Todos os caracteres do texto são codificados, execeto palavras acentuadas;
        -O espaço entre palavras é codificado com -1, o '/n' é codificado como -2 e qualquer caracter que não consta na lista de chaves é codificado como -3 (como é o caso dos caracteres acentuados);

    *decodifica.c e decodifica.h
        -Biblioteca responsável pela decodificação da mensagem;
        -Os arquivos de texto são abertos nas funções dessa biblioteca;
        -Dentro dessa biblioteca, existem duas principais funções, a responsável por decodificar apartir de um livro cifra e a decodificação apartir de um arquivo de chaves, nos dois casos a decodificação segue o mesmo padrão;
        -Os arquivos a serem decodificados são abertos, e por meio de um while, cada int, do arquivo codificado, é lido, decodificado por meio da lista de chaves e o char encontrado é impresso no arquivo de mensagem decodificada;
        -Da mesma forma que a codificação nenhum tipo de alocação de memória foi necessária, no momento de decodificação;
        -Como no caso da codificação, se o caracter não constar na lista é inserido o valor -3, na decodificação o -3 é trocado pelo '[]';

    *arqchaves.c e arqchaves.h:
        -Arquivo responsável pela manipulação das chaves/códigos, ou seja, nesse arquivo os códigos que são usados para codificar/decodificar são gerados apartir do livro cifra ou apartir da leitura de um arquivo que contenha os códigos.
        -Para que todos os caracteres da tabela ASCII sejam contemplados por esse algoritmo, após a obtenção das chaves apartir do livro cifra/arquivo de chaves, todos os elementos da tabela ASCII são percorridos, caso algum caracter não conste na estrutura lista, esse é inserido com o maior código gerado, até o momento, mais um (maior_codigo++). Essa ação evita que livros cifras muito pequenos não contemplem de forma correta a codificação/decodificação de mensagens. Além disso, a inserção do código como "maior + 1" evita que entre livros cifra diferentes exista um padrão na codificação de caracteres especiais(como sinais de pontuação) que não são contemplados pela geração de códigos da Cifra de Beale;
        -Os caracteres obtidos através do livro cifra/arquivo de chaves são inseridos na estrutura de forma ordenada (do menor para o maior); os caracteres que não estão presentes no livro cifra, mas fazem parte da tabela ASCII, são adicionados abaixo desses;
        -Caracteres maiúsculos e minúsculos são tratados como caracteres de mesmo valor, ou seja, 'A' é considerado como 'a';

    *makefile:
        Makefile para compilar o programa.

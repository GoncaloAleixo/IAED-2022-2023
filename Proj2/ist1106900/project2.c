/* 
 * Ist1106900
 * Gonçalo Aleixo
 * Segundo projeto
 * 
 * Este ficheiro contém todas as 
 * variáveis e funções do projeto
 */


/* Bibliotecas usadas */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes */

#define MAX_NOME_C      21
#define MAX_NOME_P      51
#define MAX_DOUBLE      20

#define MAX_CARREIRAS   200
#define MAX_PARAGEM     10000
#define MAX_LIGACAO     30000

#define INVERSO         "inverso"

/* Tipos de Erros */

#define ERR1            "incorrect sort option.\n"
#define ERR2            "%s: stop already exists.\n"
#define ERR3            "%s: no such stop.\n"
#define ERR4            "%s: no such line.\n"
#define ERR5            "link cannot be associated with bus line.\n"
#define ERR6            "negative cost or duration.\n"

#define CREATE          1
#define EXPAND          2
#define REMOVE          3

#define ALLOC_SIZE      10
#define REALLOC_SIZE    5

/* Tipos de Dados */

typedef struct {
    double latitude, longitude;
} Localizacao;

typedef struct {
    char nome[MAX_NOME_P];
    Localizacao localizacao;
    int numCarreiras, removido;
} Paragem;

typedef struct {
    Paragem *paragem;
    int num, max;
} Paragens;

typedef struct {
    char nome[MAX_NOME_C];
    Paragem origem, destino;
    double custoTotal, duarcaoTotal;
    int numParagens;
    int loop;
} Carreira;

typedef struct {
    Carreira *carreira;
    int num, max;
} Carreiras;

typedef struct {
    char carreira[MAX_NOME_C];
    char pOrigem[MAX_NOME_P], pDestino[MAX_NOME_P];
    double custo, duracao;
} Ligacao;

typedef struct {
    Ligacao *ligacao;
    int num, max;
} Ligacoes;

/* Declaração de funções */

/*função de sort*/
void insertion_sort_carreiras(Carreiras);

/*verifica se existe uma carreira*/
int existeCarreira(Carreiras, char*);
/*verifica se existe uma paragem*/
int existeParagem(Paragens, char*);
/*verifica se uma paragem é origem ou destino*/
int origemOuDestino(Carreiras, int, char*, char*);
/*imprime os erros de ouver (acabar)*/
int errLigacoes(Carreiras, Paragens, char*, char*, char*, double, double, int, int*);
/*verifica os erros no loop*/
int errLoop(Carreiras, int, char*, char*);

/*lê uma linha*/
void lerLinha(char*);
/*lê a próxima palavra inserida*/
int lerProxPalavra(char*, char*);
/*lê a palavra inverso*/
int lerInverso(char*, char*);
/*lê um double*/
double lerDouble(char*);
/*todas as funções de leitura necessárias para as ligações*/
void lerLigacoes(char*, char*, char*, double*, double*, char*);

/*imprime uma carreira*/
void mostraCarreira(Carreiras);
/*imprime as paragens de uma carreira*/
void mostraParagensNaCarreira(Carreiras, Paragens, Ligacoes, int);
/*procura a ligação*/
void procura(Carreiras, Paragens, Ligacoes, int);
/*semelhante à anterior, mas de trás para a frente*/
void mostraParagensNaCarreiraInv(Carreiras, Paragens, Ligacoes, int);
/*procura a ligação (inv)*/
void procuraInv(Carreiras, Paragens, Ligacoes, int);
/*imprime uma paragem*/
void mostraParagens(Paragens);
/*imprime a latitude e longitude de uma paragem*/
void mostraLatLon(Paragens, int);
/*imprime as carreiras de uma paragem*/
void mostraIntercecoes(Paragens, Carreiras, int, int[]);

/*guarda uma nova carreira*/
void guardaCarreiras(Carreiras*, char*);
/*faz update das variáveis da carreira*/
void updateCarreira(Carreiras*, int, char*, char*, double, double);
/*faz update da ligação (loop ou só carreira)(não altera as ligações em si)*/
void updateLigacao(Carreiras*, int, char*, char*, float, float);
/*guarda uma nova paragem*/
void guardaParagem(Paragens*, char*, char*);
/*faz update das variáveis da paragem*/
int* updateParagem(Carreiras, Paragens*, Ligacoes, int);
/*guarda uma ligação*/
void guardarLigacoes(Ligacoes*, Carreiras, char*, char*, char*, float, float, int, int);
/*remove o custo da paragem se for a origem*/
void removerCustoOrigem(Carreiras*, Ligacoes*, char*);
/*remove o custo da paragem se for o destino*/
void removerCustoDestino(Carreiras*, Ligacoes*, char*);
/*adiciona uma ligação ordenada no início da carreira*/
void addLigacaoInicio(Ligacoes*, Carreiras, int, char*, char*, char*, float, float);
/*adiciona uma ligação ordenada no fim da carreira*/
void addLigacaoFim(Ligacoes*, Carreiras, int, char*, char*, char*, float, float);

/*função do comando 'c'*/
void adicionaOuListaCarreiras(Carreiras*, Paragens, Ligacoes, char*);
/*função do comando 'p'*/
void adicionaOuListaParagens(Paragens*, char*);
/*função do comando 'l'*/
void adicionaLiagacoes(Carreiras*, Paragens*, Ligacoes*, char*);
/*função do comando 'i'*/
void intercecoes(Paragens*, Carreiras, Ligacoes);
/*função do comando 'r'*/
void removeCarreira(Carreiras*, Ligacoes*, char*);
/*função do comando 'e'*/
void removeParagem(Paragens*, Carreiras*, Ligacoes*, char*);
/*função do comando 'a'*/
void apagaTudo(Carreiras*, Paragens*, Ligacoes*);

/*função que controla o espaço de memória das carreiras*/
void memory_controller_carreiras(const int, Carreiras*);
/*função que controla o espaço de memória das paragens*/
void memory_controller_paragens(const int, Paragens*);
/*função que controla o espaço de memória das ligações*/
void memory_controller_ligacoes(const int, Ligacoes*);

int main() {
    Carreiras c;
    Paragens p;
    Ligacoes l;

    int comando;
    char linha[BUFSIZ];

    c.num = 0;
    c.max = 0;
    p.num = 0;
    p.max = 0;
    l.num = 0;
    l.max = 0;


    while ((comando = getchar()) != EOF) {
        lerLinha(linha);
        switch (comando) {
            case 'q': if (c.max != 0) memory_controller_carreiras(REMOVE, &c);
                if (p.max != 0) memory_controller_paragens(REMOVE, &p);
                if (l.max != 0) memory_controller_ligacoes(REMOVE, &l);
                return (EXIT_SUCCESS);
            case 'c': adicionaOuListaCarreiras(&c, p, l, linha);
                break;
            case 'p': adicionaOuListaParagens(&p, linha);
                break;
            case 'l': adicionaLiagacoes(&c, &p, &l, linha);
                break;
            case 'i': intercecoes(&p, c, l);
                break;
            case 'r': removeCarreira(&c, &l, linha);
                break;
            case 'e': removeParagem(&p, &c, &l, linha);
                break;
            case 'a': apagaTudo(&c, &p, &l);
                break;
        }
    }
    return (EXIT_SUCCESS);
}

void adicionaOuListaCarreiras(Carreiras *c, Paragens p, Ligacoes l, char linha[]) {
    char palavra[MAX_NOME_C];
    int controlo = lerProxPalavra(palavra, linha), posicao = existeCarreira(*c, palavra);
    if (palavra[0] != '\0') {
        if (posicao >= 0) {
            switch (controlo) {
                case 1:
                    if (lerInverso(palavra, linha)) {
                        mostraParagensNaCarreiraInv(*c, p, l, posicao);
                    } else {
                        printf(ERR1);
                    }
                    break;
                case 0: mostraParagensNaCarreira(*c, p, l, posicao);
                    break;
            }
            return;
        } else if (!controlo) {
            guardaCarreiras(c, palavra);
        }
        return;
    }
    mostraCarreira(*c);
}

void adicionaOuListaParagens(Paragens *p, char linha[]) {
    char palavra[MAX_NOME_P];
    int controlo = lerProxPalavra(palavra, linha), posicao = existeParagem(*p, palavra);
    if (palavra[0] != '\0') {
        if (controlo) {
            guardaParagem(p, palavra, linha);
            return;
        } else if (posicao >= 0) {
            mostraLatLon(*p, posicao);
            return;
        } else {
            printf(ERR3, palavra);
            return;
        }
    }
    mostraParagens(*p);
    return;
}

void adicionaLiagacoes(Carreiras *c, Paragens *p, Ligacoes *l, char linha[]) {
    int i, index = 0, iof = 0;
    char carNome[MAX_NOME_C], p1[MAX_NOME_P], p2[MAX_NOME_P];
    double duracao, custo;
    lerLigacoes(carNome, p1, p2, &duracao, &custo, linha);
    for (i = 0; i < c->num; i++) if (!strcmp(c->carreira[i].nome, carNome)) {
            index = i;
            break;
        }
    if (errLigacoes(*c, *p, carNome, p1, p2, duracao, custo, index, &iof)) return;
    updateLigacao(c, index, p1, p2, duracao, custo);
    guardarLigacoes(l, *c, carNome, p1, p2, duracao, custo, iof, index);
    for (i = 0; i < p->num; i++) {
        if (!strcmp(p1, p->paragem[i].nome)) updateParagem(*c, p, *l, i);
        if (!strcmp(p2, p->paragem[i].nome)) updateParagem(*c, p, *l, i);
    }
}

void intercecoes(Paragens *p, Carreiras c, Ligacoes l) {
    int i, *posicoes;
    insertion_sort_carreiras(c); /*mudar p bubbleSort*/
    for (i = 0; i < p->num; i++) {
        posicoes = updateParagem(c, p, l, i);
        mostraIntercecoes(*p, c, i, posicoes);
    }
}

void removeCarreira(Carreiras *c, Ligacoes *l, char linha[]) {
    char palavra[MAX_NOME_C];
    int posicao, i, j;
    lerProxPalavra(palavra, linha);
    posicao = existeCarreira(*c, palavra);
    if (posicao >= 0) {
        for (i = posicao; i < c->num - 1; i++) c->carreira[i] = c->carreira[i + 1];
        c->num--;
        for (i = 0; i < l->num; i++) {
            if (!strcmp(l->ligacao[i].carreira, palavra)) {
                for (j = i; j < l->num - 1; j++) l->ligacao[j] = l->ligacao[j + 1];
                c->num--;
            }
        }
    } else printf(ERR4, palavra);
}

void removeParagem(Paragens *p, Carreiras *c, Ligacoes *l, char linha[]) {
    char palavra[MAX_NOME_P];
    int posicao, i, j;
    lerProxPalavra(palavra, linha);
    posicao = existeParagem(*p, palavra);
    p->paragem[posicao].removido = 1;
    removerCustoOrigem(c, l, palavra);
    removerCustoDestino(c, l, palavra);
    for (i = 0; i < c->num; i++) {
        for (j = 0; j < l->num; j++) {
            if (!strcmp(l->ligacao[j].carreira, c->carreira[i].nome) && !strcmp(l->ligacao[j].pDestino, palavra))
                c->carreira[i].numParagens--;
        }
    }
}

void apagaTudo(Carreiras *c, Paragens *p, Ligacoes *l) {
    if (c->max != 0) memory_controller_carreiras(REMOVE, c);
    if (p->max != 0) memory_controller_paragens(REMOVE, p);

    if (l->max != 0) memory_controller_ligacoes(REMOVE, l);
    c->max = 0;
    c->num = 0;
    p->max = 0;
    p->num = 0;
    l->max = 0;
    l->num = 0;
}

/* Funções de Existência */

int existeCarreira(Carreiras c, char nome[]) {
    int i;
    for (i = 0; i < c.num; i++) {
        if (!strcmp(nome, c.carreira[i].nome)) {

            return i;
        }
    }
    return -1;
}

int existeParagem(Paragens p, char nome[]) {
    int i;
    for (i = 0; i < p.num; i++) {
        if (!strcmp(nome, p.paragem[i].nome)) {

            return i;
        }
    }
    return -1;
}

int errLigacoes(Carreiras c, Paragens p, char nome[], char p1[], char p2[], double duracao, double custo, int index, int *iof) {
    if (existeCarreira(c, nome) < 0) {
        printf(ERR4, nome);
        return 1;
    }
    if (existeParagem(p, p1) < 0) {
        printf(ERR3, p1);
        return 1;
    }
    if (existeParagem(p, p2) < 0) {
        printf(ERR3, p2);
        return 1;
    }
    if (duracao < 0.0 || custo < 0.0) {
        printf(ERR6);
        return 1;
    }
    if ((!(*iof = origemOuDestino(c, index, p1, p2))) > c.carreira[index].loop) {
        printf(ERR5);

        return 1;
    }
    return 0;
}

int origemOuDestino(Carreiras c, int index, char p1[], char p2[]) {
    int controlo = 0, posicao = 0;
    if (strcmp(c.carreira[index].origem.nome, p1) && !strcmp(c.carreira[index].destino.nome, p1)) {
        controlo++;
        posicao = 2;
    }
    if (strcmp(c.carreira[index].destino.nome, p2) && !strcmp(c.carreira[index].origem.nome, p2)) {
        controlo++;
        posicao = 1;
    }
    if (controlo == 2) {
        c.carreira[index].loop = 1;
        return 2;
    }
    if (controlo == 1) return posicao;
    if (c.carreira[index].origem.nome[0] == '\0' && c.carreira[index].destino.nome[0] == '\0') return 3;

    return 0;
}

int errLoop(Carreiras c, int index, char p1[], char p2[]) {
    if (!strcmp(c.carreira[index].destino.nome, p1)
            && strcmp(c.carreira[index].origem.nome, p2)) {
        strcpy(c.carreira[index].destino.nome, p2);
        return 0;
    }
    if (!strcmp(c.carreira[index].origem.nome, p2)
            && strcmp(c.carreira[index].destino.nome, p1)) {
        strcpy(c.carreira[index].destino.nome, p2);
        return 0;
    }
    printf(ERR5);

    return 1;
}

/* Funções de Mostrar */

void mostraCarreira(Carreiras c) {
    int i;
    for (i = 0; i < c.num; i++) {
        printf("%s", c.carreira[i].nome);
        if (c.carreira[i].origem.nome[0] != '\0') printf(" %s", c.carreira[i].origem.nome);

        if (c.carreira[i].destino.nome[0] != '\0') printf(" %s", c.carreira[i].destino.nome);
        printf(" %d %.2f %.2f\n", c.carreira[i].numParagens,
                c.carreira[i].duarcaoTotal, c.carreira[i].custoTotal);
    }
}

void mostraParagensNaCarreira(Carreiras c, Paragens p, Ligacoes l, int posicao) {

    if (c.carreira[posicao].numParagens == 0) return;
    printf("%s", c.carreira[posicao].origem.nome);
    procura(c, p, l, posicao);
    printf("\n");
}

void mostraParagensNaCarreiraInv(Carreiras c, Paragens p, Ligacoes l, int posicao) {

    if (c.carreira[posicao].numParagens == 0) return;
    printf("%s", c.carreira[posicao].destino.nome);
    procuraInv(c, p, l, posicao);
    printf("\n");
}

void procura(Carreiras c, Paragens p, Ligacoes l, int index) {
    int i, j = 0, k, pos = 0, breaker;
    char atual[MAX_NOME_C];
    strcpy(atual, c.carreira[index].origem.nome);
    while (j < c.carreira[index].numParagens - 1) {
        breaker = 0;
        for (i = pos; i < l.num; i++) {
            if (!strcmp(l.ligacao[i].carreira, c.carreira[index].nome) &&
                    !strcmp(atual, l.ligacao[i].pOrigem)) {
                for (k = 0; k < p.num; k++)
                    if (!strcmp(p.paragem[k].nome, l.ligacao[i].pDestino) && p.paragem[k].removido == 0)
                        printf(", %s", l.ligacao[i].pDestino);
                strcpy(atual, l.ligacao[i].pDestino);
                pos = i;
                breaker++;
                j++;
            }
        }
        for (i = 0; i < pos && !breaker; i++) {
            if (!strcmp(l.ligacao[i].carreira, c.carreira[index].nome) &&
                    !strcmp(atual, l.ligacao[i].pOrigem)) {
                for (k = 0; k < p.num; k++)

                    if (!strcmp(p.paragem[k].nome, l.ligacao[i].pDestino) && p.paragem[k].removido == 0)
                        printf(", %s", l.ligacao[i].pDestino);
                strcpy(atual, l.ligacao[i].pDestino);
                pos = i;
                j++;
            }
        }
    }
}

void procuraInv(Carreiras c, Paragens p, Ligacoes l, int index) {
    int i, j = 0, k, pos = 0, breaker;
    char atual[MAX_NOME_C];
    strcpy(atual, c.carreira[index].origem.nome);
    while (j < c.carreira[index].numParagens - 1) {
        breaker = 0;
        for (i = pos; i < l.num; i++) {
            if (!strcmp(l.ligacao[i].carreira, c.carreira[index].nome) &&
                    !strcmp(atual, l.ligacao[i].pDestino)) {
                for (k = 0; k < p.num; k++)
                    if (!strcmp(p.paragem[k].nome, l.ligacao[i].pOrigem) && p.paragem[k].removido == 0)
                        printf(", %s", l.ligacao[i].pOrigem);
                strcpy(atual, l.ligacao[i].pOrigem);
                pos = i;
                breaker++;
                j++;
            }
        }
        for (i = 0; i < pos && !breaker; i++) {
            if (!strcmp(l.ligacao[i].carreira, c.carreira[index].nome) &&
                    !strcmp(atual, l.ligacao[i].pDestino)) {
                for (k = 0; k < p.num; k++)

                    if (!strcmp(p.paragem[k].nome, l.ligacao[i].pOrigem) && p.paragem[k].removido == 0)
                        printf(", %s", l.ligacao[i].pOrigem);
                strcpy(atual, l.ligacao[i].pOrigem);
                pos = i;
                j++;
            }
        }
    }
}

void mostraParagens(Paragens p) {
    int i;
    for (i = 0; i < p.num; i++) {
        if (p.paragem[i].removido == 0)
            printf("%s: %16.12f %16.12f %d\n", p.paragem[i].nome,
                p.paragem[i].localizacao.latitude,
                p.paragem[i].localizacao.longitude,
                p.paragem[i].numCarreiras);
    }
}

void mostraLatLon(Paragens p, int posicao) {
    if (p.paragem[posicao].removido == 0) {
        printf("%16.12f %16.12f\n", p.paragem[posicao].localizacao.latitude,
                p.paragem[posicao].localizacao.longitude);
    }
}

void mostraIntercecoes(Paragens p, Carreiras c, int num, int posicoes[]) {
    int i;
    if (p.paragem[num].numCarreiras > 1 && p.paragem[num].removido == 0) {
        printf("%s %d:", p.paragem[num].nome, p.paragem[num].numCarreiras);
        for (i = 0; i < p.paragem[num].numCarreiras; i++) {
            printf(" %s", c.carreira[posicoes[i]].nome);
        }
        printf("\n");
    }
}

/* Funções de Guardar */

void memory_controller_carreiras(const int OPERATION, Carreiras *c) {
    switch (OPERATION) {
        case EXPAND:
        {
            Carreira *temp;
            temp = (Carreira*) realloc(c->carreira, (c->max + REALLOC_SIZE) * sizeof (Carreira));
            c->carreira = temp;
            temp = NULL;
            c->max += REALLOC_SIZE;
            break;
        }
        case REMOVE:
            free(c->carreira);
            break;
        case CREATE:
            c->carreira = (Carreira*) malloc(ALLOC_SIZE * sizeof (Carreira));
            c->max = ALLOC_SIZE;

            break;
    }
}

void memory_controller_paragens(const int OPERATION, Paragens *p) {
    switch (OPERATION) {
        case EXPAND:
        {
            Paragem *temp;
            temp = (Paragem*) realloc(p->paragem, (p->max + REALLOC_SIZE) * sizeof (Paragem));
            p->paragem = temp;
            temp = NULL;
            p->max += REALLOC_SIZE;
            break;
        }
        case REMOVE:
            free(p->paragem);
            break;
        case CREATE:
            p->paragem = (Paragem*) malloc(ALLOC_SIZE * sizeof (Paragem));
            p->max = ALLOC_SIZE;

            break;
    }
}

void memory_controller_ligacoes(const int OPERATION, Ligacoes *l) {
    switch (OPERATION) {
        case EXPAND:
        {
            Ligacao *temp;
            temp = (Ligacao*) realloc(l->ligacao, (l->max + REALLOC_SIZE) * sizeof (Ligacao));
            l->ligacao = temp;
            temp = NULL;
            l->max += REALLOC_SIZE;
            break;
        }
        case REMOVE:
            free(l->ligacao);
            break;
        case CREATE:
            l->ligacao = (Ligacao*) malloc(ALLOC_SIZE * sizeof (Ligacao));
            l->max = ALLOC_SIZE;

            break;
    }
}

void guardaCarreiras(Carreiras *c, char nome[]) {
    if (c->max == 0) memory_controller_carreiras(CREATE, c);

    if (c->num == c->max) memory_controller_carreiras(EXPAND, c);
    c->carreira[c->num].duarcaoTotal = 0;
    c->carreira[c->num].custoTotal = 0;
    c->carreira[c->num].numParagens = 0;
    c->carreira[c->num].loop = 0;
    strcpy(c->carreira[c->num].nome, nome);
    c->num++;
}

void guardaParagem(Paragens *p, char nome[], char linha[]) {
    if (existeParagem(*p, nome) >= 0) {
        printf(ERR2, nome);
        return;
    }
    if (p->max == 0) memory_controller_paragens(CREATE, p);

    if (p->num == p->max) memory_controller_paragens(EXPAND, p);
    strcpy(p->paragem[p->num].nome, nome);
    p->paragem[p->num].localizacao.latitude = lerDouble(linha);
    p->paragem[p->num].localizacao.longitude = lerDouble(linha);
    p->paragem[p->num].numCarreiras = 0;
    p->paragem[p->num].removido = 0;
    p->num++;
}

void updateCarreira(Carreiras *c, int index, char p1[], char p2[], double duracao, double custo) {
    if (c->carreira[index].origem.nome[0] == '\0' && c->carreira[index].destino.nome[0] == '\0') {
        strcpy(c->carreira[index].origem.nome, p1);
        strcpy(c->carreira[index].destino.nome, p2);
        c->carreira[index].numParagens++;
    }
    if (!strcmp(c->carreira[index].origem.nome, p2)) strcpy(c->carreira[index].origem.nome, p1);

    if (!strcmp(c->carreira[index].destino.nome, p1)) strcpy(c->carreira[index].destino.nome, p2);
    c->carreira[index].custoTotal += custo;
    c->carreira[index].duarcaoTotal += duracao;
    c->carreira[index].numParagens++;
}

void updateLigacao(Carreiras *c, int index, char p1[], char p2[], float duracao, float custo) {
    if (c->carreira[index].loop == 0) {
        updateCarreira(c, index, p1, p2, duracao, custo);
    } else if (c->carreira[index].loop == 1) {
        strcpy(c->carreira[index].destino.nome, p2);
        c->carreira[index].custoTotal += custo;
        c->carreira[index].duarcaoTotal += duracao;
        c->carreira[index].numParagens++;
        c->carreira[index].loop++;
    } else if (c->carreira[index].loop == 2) {

        if (errLoop(*c, index, p1, p2)) return;
        c->carreira[index].custoTotal += custo;
        c->carreira[index].duarcaoTotal += duracao;
        c->carreira[index].numParagens++;
        c->carreira[index].loop = 0;
    }
}

int* updateParagem(Carreiras c, Paragens *p, Ligacoes l, int num) {
    int i, j, k = 0;
    static int posicoes[MAX_CARREIRAS];
    p->paragem[num].numCarreiras = 0;
    for (i = 0; i < c.num; i++) {
        for (j = 0; j < l.num; j++) {
            if (!strcmp(l.ligacao[j].carreira, c.carreira[i].nome) &&
                    (!strcmp(l.ligacao[j].pOrigem, p->paragem[num].nome) ||
                    !strcmp(l.ligacao[j].pDestino, p->paragem[num].nome))) {
                p->paragem[num].numCarreiras++;
                posicoes[k++] = i;

                break;
            }
        }
    }
    return posicoes;
}

void guardarLigacoes(Ligacoes *l, Carreiras c, char nome[], char p1[], char p2[], float duracao, float custo, int iof, int index) {
    if (l->max == 0) memory_controller_ligacoes(CREATE, l);
    if (l->num == l->max) memory_controller_ligacoes(EXPAND, l);
    switch (iof) {
        case 1: addLigacaoInicio(l, c, index, nome, p1, p2, duracao, custo);
            break;
        case 2: addLigacaoFim(l, c, index, nome, p1, p2, duracao, custo);
            break;
        case 3:
            strcpy(l->ligacao[l->num].carreira, nome);
            strcpy(l->ligacao[l->num].pOrigem, p1);
            strcpy(l->ligacao[l->num].pDestino, p2);
            l->ligacao[l->num].duracao = duracao;
            l->ligacao[l->num].custo = custo;
            l->num++;

            break;
    }
}

void addLigacaoInicio(Ligacoes *l, Carreiras c, int index, char nome[], char p1[], char p2[], float duracao, float custo) {
    int posicao, i;
    for (posicao = 0; posicao < l->num; posicao++) if (!strcmp(l->ligacao[posicao].carreira, c.carreira[index].nome)) break;

    for (i = l->num; i > posicao; i--) l->ligacao[i] = l->ligacao[i - 1];
    strcpy(l->ligacao[posicao].carreira, nome);
    strcpy(l->ligacao[posicao].pOrigem, p1);
    strcpy(l->ligacao[posicao].pDestino, p2);
    l->ligacao[posicao].duracao = duracao;
    l->ligacao[posicao].custo = custo;
    l->num++;
}

void addLigacaoFim(Ligacoes *l, Carreiras c, int index, char nome[], char p1[], char p2[], float duracao, float custo) {
    int posicao, i;
    for (posicao = l->num - 1; posicao >= 0; posicao--) if (!strcmp(l->ligacao[posicao].carreira, c.carreira[index].nome)) break;
    for (i = l->num; i > posicao + 1; i--) l->ligacao[i] = l->ligacao[i - 1];
    strcpy(l->ligacao[++posicao].carreira, nome);
    strcpy(l->ligacao[posicao].pOrigem, p1);
    strcpy(l->ligacao[posicao].pDestino, p2);
    l->ligacao[posicao].duracao = duracao;
    l->ligacao[posicao].custo = custo;
    l->num++;
}

void removerCustoOrigem(Carreiras *c, Ligacoes *l, char palavra[]) {
    int i, j, k;
    for (i = 0; i < c->num; i++) {
        if (!strcmp(c->carreira[i].origem.nome, palavra)) {
            for (j = 0; j < l->num; j++) {
                if (!strcmp(c->carreira[i].nome, l->ligacao[j].carreira)) {
                    c->carreira[i].custoTotal -= l->ligacao[j].custo;
                    c->carreira[i].duarcaoTotal -= l->ligacao[j].duracao;
                    c->carreira[i].numParagens--;
                    strcpy(c->carreira[i].origem.nome, l->ligacao[j].pDestino);
                    for (k = j; k < l->num - 1; k++) l->ligacao[k] = l->ligacao[k + 1];
                    l->num--;
                    break;
                }
            }
        }
    }
}

void removerCustoDestino(Carreiras *c, Ligacoes *l, char palavra[]) {
    int i, j, k;
    for (i = 0; i < c->num; i++) {
        if (!strcmp(c->carreira[i].destino.nome, palavra)) {
            for (j = l->num; j >= 0; j--) {
                if (!strcmp(c->carreira[i].nome, l->ligacao[j].carreira)) {
                    c->carreira[i].custoTotal -= l->ligacao[j].custo;
                    c->carreira[i].duarcaoTotal -= l->ligacao[j].duracao;
                    c->carreira[i].numParagens--;
                    strcpy(c->carreira[i].destino.nome, l->ligacao[j].pOrigem);
                    for (k = j; k < l->num - 1; k++) l->ligacao[k] = l->ligacao[k + 1];
                    l->num--;

                    break;
                }
            }
        }
    }
}

/* Funções de Input */

void lerLinha(char str[]) {
    char p = getchar();
    int i = 0;
    while (p == ' ' || p == '\t') p = getchar();
    while (p != '\n') {

        str[i++] = p;
        p = getchar();
    }
    str[i] = '\n';
}

int lerProxPalavra(char str[], char linha[]) {
    int i = 0, j = 0, k = 0;
    while (linha[i] == ' ' || linha[i] == '\t') i++;
    if (linha[i] == '"') {
        i++;
        while (linha[i] != '"') str[j++] = linha[i++];
    } else {
        while (linha[i] != ' ' && linha[i] != '\t' && linha[i] != '\n') {
            str[j++] = linha[i++];
        }
    }
    str[j] = '\0';
    do {
        linha[k] = linha[i + k];
    } while (linha[k++] != '\n');

    return (linha[0] == '\n') ? 0 : 1;
}

int lerInverso(char str[], char linha[]) {
    size_t i;
    lerProxPalavra(str, linha);
    if (strlen(str) < strlen(INVERSO) - 4 || strlen(str) > strlen(INVERSO)) {
        return 0;
    } else {
        for (i = 0; i < strlen(str); i++) {
            if (str[i] != INVERSO[i]) {

                return 0;
            }
        }
    }
    return 1;
}

double lerDouble(char linha[]) {
    char str[MAX_DOUBLE];
    int i = 0, j = 0, k = 0;
    while (linha[i] == ' ' || linha[i] == '\t') i++;
    while (linha[i] != ' ' && linha[i] != '\t' && linha[i] != '\n') str[j++] = linha[i++];
    str[j] = '\0';
    do {
        linha[k] = linha[i + k];
    } while (linha[k++] != '\n');

    return (atof(str));
}

void lerLigacoes(char c[], char p1[], char p2[], double *duracao, double *custo, char linha[]) {

    lerProxPalavra(c, linha);
    lerProxPalavra(p1, linha);
    lerProxPalavra(p2, linha);
    *duracao = lerDouble(linha);
    *custo = lerDouble(linha);
}

/* Funções Sort */

void insertion_sort_carreiras(Carreiras c) {
    int i, j, k;
    for (i = 0; i < c.num - 1; i++) {
        for (j = 0; j < c.num - i - 1; j++) {
            k = 0;
            while (c.carreira[j].nome[k] != '\0' && c.carreira[j + 1].nome[k] != '\0') {
                if (c.carreira[j].nome[k] > c.carreira[j + 1].nome[k]) {
                    Carreira temp = c.carreira[j];
                    c.carreira[j] = c.carreira[j + 1];
                    c.carreira[j + 1] = temp;
                    break;
                } else if (c.carreira[j].nome[k] < c.carreira[j + 1].nome[k]) {
                    break;
                }
                k++;
            }
        }
    }
}
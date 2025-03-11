/* 
 * Primeiro projeto de IAED
 * Autor: Gonçalo Fernandes Aleixo
 * IST1: 106900
 * 
 * Este ficheiro contém todas as 
 * variáveis e funções do projeto
 */


/* Bibliotecas usadas */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes */

#define MAX_NOME_C      21              /* maximo de bytes para um nome de uma carreira  */
#define MAX_NOME_P      51              /* maximo de bytes para um nome de uma paragem*/
#define MAX_DOUBLE      20              /* maximo de bytes para um float */

#define MAX_CARREIRAS   200             /* numero máximo de carreiras */
#define MAX_PARAGEM     10000           /* numero máximo de paragens */
#define MAX_LIGACAO     30000           /* numero máximo de ligações */

#define INVERSO         "inverso"       /* inverso */ 


/* Tipos de Erros */

#define ERR1            "incorrect sort option.\n"          /* Erro do inverso */           
#define ERR2            "%s: stop already exists.\n"        /* Erro da paragem já existir */ 
#define ERR3            "%s: no such stop.\n"               /* Erro não existir paragem */ 
#define ERR4            "%s: no such line.\n"               /* Erro de não existir ligação*/
#define ERR5            "link cannot be associated with bus line.\n"  /* Erro de não dar para associar ligação com paragem */
#define ERR6            "negative cost or duration.\n"      /* Erro de custo ou duração negativa*/

/* Tipos de Dados */

typedef struct {
    double latitude, longitude;
} Localizacao;

typedef struct {
    char nome[MAX_NOME_P];
    Localizacao localizacao;
    int numCarreiras;
} Paragem;

typedef struct {
    char nome[MAX_NOME_C];
    Paragem origem, destino;
    double custoTotal, duarcaoTotal;
    int numParagens;
    int loop;
} Carreira;

typedef struct {
    char carreira[MAX_NOME_C];
    char pOrigem[MAX_NOME_P], pDestino[MAX_NOME_P];
    double custo, duracao;
} Ligacao;

/* Variáveis Globais */

int _numCarreiras = 0;
Carreira _carreiras[MAX_CARREIRAS];

int _numParagens = 0;
Paragem _paragens[MAX_PARAGEM];

int _numLigacoes = 0;
Ligacao _ligacoes[MAX_LIGACAO];

/* Declaração de funções */

/*função de sort*/
void insertion_sort_carreiras();

/*verifica se existe uma carreira*/
int existeCarreira(char*);
/*verifica se existe uma paragem*/
int existeParagem(char*);
/*verifica se uma paragem é origem ou destino*/
int origemOuDestino(int, char*, char*);
/*imprime os erros de ouver (acabar)*/
int errLigacoes(char*, char*, char*, double, double, int);
/*verifica os erros no loop*/
int errLoop(int, char*, char*);

/*lê a próxima palavra inserida*/
int lerProxPalavra(char*);
/*lê a palavra inverso*/
int lerInverso(char*);
/*lê um double*/
double lerDouble();
/*todas as funções de leitura necessárias para as ligações*/
void lerLigacoes(char*, char*, char*, double *, double *);

/*imprime uma carreira*/
void mostraCarreira();
/*imprime as paragens de uma carreira*/
void mostraParagensNaCarreira(char*);
/*semelhante à anterior, mas de trás para a frente*/
void mostraParagensNaCarreiraInv(char*);
/*imprime uma paragem*/
void mostraParagens();
/*imprime a latitude e longitude de uma paragem*/
void mostraLatLon(char*);
/*imprime as carreiras de uma paragem*/
void mostraIntercecoes(int, int[]);

/*faz update das variáveis da carreira*/
void updateCarreira(int, char*, char*, double, double);
/*faz update da ligação (loop ou só carreira)(não altera as ligações em si)*/
void updateLigacao(int, char*, char*, float, float);
/*guarda uma nova paragem*/
void guardaParagem(char*);
/*faz update das variáveis da paragem*/
int* updateParagem(int);
/*guarda uma ligação*/
void guardarLigacoes(char*, char*, char*, float, float);

/*função do comando 'c'*/
void adicionaOuListaCarreiras();
/*função do comando 'p'*/
void adicionaOuListaParagens();
/*função do comando 'l'*/
void adicionaLigacoes();
/*função do comando 'i'*/
void intercecoes();

/*
 * Função Principal, nesta encontram-se as principais funções de cada comando
 * implementadas num ciclo que vai lendo cada comando e executando a respetiva função
 */
int main() {
    int c;

    while ((c = getchar()) != EOF) {
        switch (c) {
            case 'q': return (EXIT_SUCCESS);
            case 'c': adicionaOuListaCarreiras();
                break;
            case 'p': adicionaOuListaParagens();
                break;
            case 'l': adicionaLigacoes();
                break;
            case 'i': intercecoes();
                break;
        }
    }
    return (EXIT_SUCCESS);
}

void adicionaOuListaCarreiras() {
    char c[MAX_NOME_C];
    int controlo = lerProxPalavra(c);
    if (c[0] != '\0') {
        if (existeCarreira(c)) {
            switch (controlo) {
                case 1:
                    if (lerInverso(c)) mostraParagensNaCarreiraInv(c); else {
                        printf(ERR1); } 
                    break;
                case 0: mostraParagensNaCarreira(c); 
                break;
                } 
                return;
        } else if (!controlo) {
            _carreiras[_numCarreiras].duarcaoTotal = 0;
            _carreiras[_numCarreiras].custoTotal = 0;
            _carreiras[_numCarreiras].numParagens = 0;
            _carreiras[_numCarreiras].loop = 0;
            strcpy(_carreiras[_numCarreiras++].nome, c);
        } else if (!lerInverso(c)){
            printf(ERR1);
        } return; }
    mostraCarreira();
}

void adicionaOuListaParagens() {
    char p[MAX_NOME_P];
    int controlo = lerProxPalavra(p);
    if (p[0] != '\0') {
        if (controlo) {
            guardaParagem(p);
            return;
        } else if (existeParagem(p)) {
            mostraLatLon(p);
            return;
        } else {
            printf(ERR3, p);
            return;
        }
    }
    mostraParagens();
    return;
}

void adicionaLigacoes() {
    int i, index = 0;
    char c[MAX_NOME_C], p1[MAX_NOME_P], p2[MAX_NOME_P];
    double duracao, custo;
    lerLigacoes(c, p1, p2, &duracao, &custo);
    for (i = 0; i < _numCarreiras; i++) if (!strcmp(_carreiras[i].nome, c)) {
            index = i;
            break;
        }
    if (errLigacoes(c, p1, p2, duracao, custo, index)) return;
    updateLigacao(index, p1, p2, duracao, custo);
    guardarLigacoes(c, p1, p2, duracao, custo);
    for (i = 0; i < _numParagens; i++) {
        if (!strcmp(p1, _paragens[i].nome)) updateParagem(i);
        if (!strcmp(p2, _paragens[i].nome)) updateParagem(i);
    }
}

void intercecoes() {
    int i, *posicoes;
    insertion_sort_carreiras();
    for (i = 0; i < _numParagens; i++) {
        posicoes = updateParagem(i);
        mostraIntercecoes(i, posicoes);
    }
}

/* Funções de Existência */

int existeCarreira(char nome[]) {
    int i;
    for (i = 0; i < _numCarreiras; i++) {
        if (!strcmp(nome, _carreiras[i].nome)) {
            return 1;
        }
    }
    return 0;
}

int existeParagem(char nome[]) {
    int i;
    for (i = 0; i < _numParagens; i++) {
        if (!strcmp(nome, _paragens[i].nome)) {
            return 1;
        }
    }
    return 0;
}

int errLigacoes(char c[], char p1[], char p2[], double duracao, double custo, int index) {
    if (!existeCarreira(c)) {
        printf(ERR4, c);
        return 1;
    }
    if (!existeParagem(p1)) {
        printf(ERR3, p1);
        return 1;
    }
    if (!existeParagem(p2)) {
        printf(ERR3, p2);
        return 1;
    }
    if (duracao < 0.0 || custo < 0.0) {
        printf(ERR6);
        return 1;
    }
    if ((!origemOuDestino(index, p1, p2)) > _carreiras[index].loop) {
        printf(ERR5);
        return 1;
    }
    return 0;
}

int origemOuDestino(int index, char p1[], char p2[]) {
    int controlo = 0;
    if (strcmp(_carreiras[index].origem.nome, p1) && !strcmp(_carreiras[index].destino.nome, p1)) controlo++;
    if (strcmp(_carreiras[index].destino.nome, p2) && !strcmp(_carreiras[index].origem.nome, p2)) controlo++;
    if (controlo == 2) {
        _carreiras[index].loop = 1;
        return 1;
    }
    if (controlo == 1) return 1;
    if (_carreiras[index].origem.nome[0] == '\0' && _carreiras[index].destino.nome[0] == '\0') return 1;
    return 0;
}

int errLoop(int index, char p1[], char p2[]) {
    if (!strcmp(_carreiras[index].destino.nome, p1)
            && strcmp(_carreiras[index].origem.nome, p2)) {
        strcpy(_carreiras[index].destino.nome, p2);
        return 0;
    }
    if (!strcmp(_carreiras[index].origem.nome, p2)
            && strcmp(_carreiras[index].destino.nome, p1)) {
        strcpy(_carreiras[index].destino.nome, p2);
        return 0;
    }
    printf(ERR5);
    return 1;
}

/* Funções de Mostrar/Output */

void mostraCarreira() {
    int i;
    for (i = 0; i < _numCarreiras; i++) {
        printf("%s", _carreiras[i].nome);
        if (_carreiras[i].origem.nome[0] != '\0') printf(" %s", _carreiras[i].origem.nome);

        if (_carreiras[i].destino.nome[0] != '\0') printf(" %s", _carreiras[i].destino.nome);
        printf(" %d %.2f %.2f\n", _carreiras[i].numParagens,
                _carreiras[i].custoTotal, _carreiras[i].duarcaoTotal);
    }
}

void mostraParagensNaCarreira(char nome[]) {
    int i, j = 0, index = 0;
    char atual[MAX_NOME_C];
    for (i = 0; i < _numCarreiras; i++) {
        if (!strcmp(nome, _carreiras[i].nome)) {
            index = i;
            break;
        }
    }
    if (_carreiras[index].numParagens == 0) return;
    printf("%s", _carreiras[index].origem.nome);
    strcpy(atual, _carreiras[index].origem.nome);
    while (j < _carreiras[index].numParagens - 1) {
        for (i = 0; i < _numLigacoes; i++) {
            if (!strcmp(_ligacoes[i].carreira, _carreiras[index].nome) &&
                    !strcmp(atual, _ligacoes[i].pOrigem)) {
                printf(", %s", _ligacoes[i].pDestino);
                strcpy(atual, _ligacoes[i].pDestino);
                break;
            }
        }
        j++;
    }
    printf("\n");
}

void mostraParagensNaCarreiraInv(char nome[]) {
    int i, j = 0, index = 0;
    char atual[MAX_NOME_C];
    for (i = 0; i < _numCarreiras; i++) {
        if (!strcmp(nome, _carreiras[i].nome)) {
            index = i;
            break;
        }
    }
    if (_carreiras[index].numParagens == 0) return;
    printf("%s", _carreiras[index].destino.nome);
    strcpy(atual, _carreiras[index].destino.nome);
    while (j < _carreiras[index].numParagens - 1) {
        for (i = 0; i < _numLigacoes; i++) {
            if (!strcmp(_ligacoes[i].carreira, _carreiras[index].nome) &&
                    !strcmp(atual, _ligacoes[i].pDestino)) {
                printf(", %s", _ligacoes[i].pOrigem);
                strcpy(atual, _ligacoes[i].pOrigem);
                break;
            }
        }
        j++;
    }
    printf("\n");
}

void mostraParagens() {
    int i;
    for (i = 0; i < _numParagens; i++) {

        printf("%s: %16.12f %16.12f %d\n", _paragens[i].nome,
                _paragens[i].localizacao.latitude,
                _paragens[i].localizacao.longitude,
                _paragens[i].numCarreiras);
    }
}

void mostraLatLon(char p[]) {
    int i;
    for (i = 0; i < _numParagens; i++) {
        if (!strcmp(p, _paragens[i].nome)) {
            printf("%16.12f %16.12f\n", _paragens[i].localizacao.latitude,
                    _paragens[i].localizacao.longitude);

            break;
        }
    }
}

void mostraIntercecoes(int num, int posicoes[]) {
    int i;
    if (_paragens[num].numCarreiras > 1) {
        printf("%s %d:", _paragens[num].nome, _paragens[num].numCarreiras);
        for (i = 0; i < _paragens[num].numCarreiras; i++) {
            printf(" %s", _carreiras[posicoes[i]].nome);
        }
        printf("\n");
    }
}

/* Funções de Guardar */

void guardaParagem(char p[]) {
    if (existeParagem(p)) {
        printf(ERR2, p);

        return;
    }
    strcpy(_paragens[_numParagens].nome, p);
    _paragens[_numParagens].localizacao.latitude = lerDouble();
    _paragens[_numParagens].localizacao.longitude = lerDouble();
    _paragens[_numParagens++].numCarreiras = 0;
}

void updateCarreira(int index, char p1[], char p2[], double duracao, double custo) {
    if (_carreiras[index].origem.nome[0] == '\0' && _carreiras[index].destino.nome[0] == '\0') {
        strcpy(_carreiras[index].origem.nome, p1);
        strcpy(_carreiras[index].destino.nome, p2);
        _carreiras[index].numParagens++;
    }
    if (!strcmp(_carreiras[index].origem.nome, p2)) strcpy(_carreiras[index].origem.nome, p1);
    if (!strcmp(_carreiras[index].destino.nome, p1)) strcpy(_carreiras[index].destino.nome, p2);
    _carreiras[index].custoTotal += duracao;
    _carreiras[index].duarcaoTotal += custo;
    _carreiras[index].numParagens++;
}

void updateLigacao(int index, char p1[], char p2[], float duracao, float custo) {
    if (_carreiras[index].loop == 0) {
        updateCarreira(index, p1, p2, duracao, custo);
    } else if (_carreiras[index].loop == 1) {
        strcpy(_carreiras[index].destino.nome, p2);
        _carreiras[index].custoTotal += duracao;
        _carreiras[index].duarcaoTotal += custo;
        _carreiras[index].numParagens++;
        _carreiras[index].loop++;
    } else if (_carreiras[index].loop == 2) {
        if (errLoop(index, p1, p2)) return;
        _carreiras[index].custoTotal += duracao;
        _carreiras[index].duarcaoTotal += custo;
        _carreiras[index].numParagens++;
        _carreiras[index].loop = 0;
    }
}

int* updateParagem(int num) {
    int i, j, k = 0;
    static int posicoes[MAX_CARREIRAS];
    _paragens[num].numCarreiras = 0;
    for (i = 0; i < _numCarreiras; i++) {
        for (j = 0; j < _numLigacoes; j++) {
            if (!strcmp(_ligacoes[j].carreira, _carreiras[i].nome) &&
                    (!strcmp(_ligacoes[j].pOrigem, _paragens[num].nome) ||
                    !strcmp(_ligacoes[j].pDestino, _paragens[num].nome))) {
                _paragens[num].numCarreiras++;
                posicoes[k++] = i;

                break;
            }
        }
    }
    return posicoes;
}

void guardarLigacoes(char c[], char p1[], char p2[], float duracao, float custo) {
    strcpy(_ligacoes[_numLigacoes].carreira, c);
    strcpy(_ligacoes[_numLigacoes].pOrigem, p1);
    strcpy(_ligacoes[_numLigacoes].pDestino, p2);
    _ligacoes[_numLigacoes].duracao = duracao;
    _ligacoes[_numLigacoes++].custo = custo;
}

/* Funções de Input */

int lerProxPalavra(char str[]) {
    char p = getchar();
    int i = 0;
    while (p == ' ' || p == '\t') p = getchar();
    if (p == '"') {
        p = getchar();
        while (p != '"') {
            str[i++] = p;
            p = getchar();
        }
    } else {
        while (p != ' ' && p != '\t' && p != '\n') {
            str[i++] = p;
            p = getchar();
        }
    }
    str[i] = '\0';

    return (p == '\n') ? 0 : 1;
}

int lerInverso(char str[]) {
    size_t i;
    lerProxPalavra(str);
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

double lerDouble() {
    char c = getchar();
    char str[MAX_DOUBLE];
    int i = 0;
    while (c == ' ' || c == '\t') c = getchar();
    while (c != ' ' && c != '\t' && c != '\n') {
        str[i++] = c;
        c = getchar();
    }
    str[i] = '\0';

    return (atof(str));
}

void lerLigacoes(char c[], char p1[], char p2[], double *duracao, double *custo) {

    lerProxPalavra(c);
    lerProxPalavra(p1);
    lerProxPalavra(p2);
    *duracao = lerDouble();
    *custo = lerDouble();
}

/* Funções Sort */

/* Insertion_sort para ordenar as carreiras por ordem alfabética 
   quando se lista as carreiras de uma certa paragem*/
void insertion_sort_carreiras() {
    int i, j, k;
    for (i = 0; i < _numCarreiras - 1; i++) {
        for (j = 0; j < _numCarreiras - i - 1; j++) {
            k = 0;
            while (_carreiras[j].nome[k] != '\0' && _carreiras[j + 1].nome[k] != '\0') {
                if (_carreiras[j].nome[k] > _carreiras[j + 1].nome[k]) {
                    Carreira temp = _carreiras[j];
                    _carreiras[j] = _carreiras[j + 1];
                    _carreiras[j + 1] = temp;
                    break;
                } else if (_carreiras[j].nome[k] < _carreiras[j + 1].nome[k]) {
                    break;
                }
                k++;
            }
        }
    }
}
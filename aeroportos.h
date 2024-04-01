#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PI 3.14159265358979323846
#define R 6381
#define Ro 10
#define DEGREE 0
#define MINUTE 1
#define SECOND 2
typedef struct AEROPORTO
{
    char icao[5];
    char iata[4];
    double x;
    double y;
    double z;
    int latitude[3];
    int longitude[3];
    char lat;
    char lon;
    char city[32];
    int time;
    struct AEROPORTO *next;
} AEROPORTOS;
/**
 * Função para converter coordenadas geográficas em coordenadas cartesianas.
 * 
 * @param lat Ponteiro para a latitude em graus.
 * @param lon Ponteiro para a longitude em graus.
 * @param x Ponteiro para a coordenada x em metros.
 * @param y Ponteiro para a coordenada y em metros.
 * @param z Ponteiro para a coordenada z em metros.
 */
void coordConv(int *lat, int *lon, double *x, double *y, double *z);

/**
 * Função para libertar a memória alocada para a estrutura de dados AEROPORTOS.
 * 
 * @param top Ponteiro para o topo da pilha de aeroportos.
 */
void freeAero(AEROPORTOS *top);

/**
 * Função para escrever os dados da estrutura de dados AEROPORTOS.
 * 
 * @param top Ponteiro para o topo da pilha de aeroportos.
 */
void writeAero(AEROPORTOS *top);

/**
 * Função para ler os dados da estrutura de dados AEROPORTOS de um arquivo.
 * 
 * @param aeros Ponteiro para a estrutura de dados AEROPORTOS existente.
 * @return Ponteiro para a estrutura de dados AEROPORTOS atualizada.
 */
AEROPORTOS *readAero(AEROPORTOS *aeros);

/**
 * Função para inicializar a pilha de aeroportos.
 * 
 * @return Ponteiro para o topo da pilha de aeroportos.
 */
AEROPORTOS *startStackAero(void);

/**
 * Função para criar um novo elemento da estrutura de dados AEROPORTOS.
 * 
 * @return Ponteiro para o novo elemento criado.
 */
AEROPORTOS *newElementAero(void);

/**
 * Função para calcular a distância entre dois aeroportos.
 * 
 * @param aero1 Ponteiro para o primeiro aeroporto.
 * @param aero2 Ponteiro para o segundo aeroporto.
 * @return A distância entre os dois aeroportos em metros.
 */
double distanceCalc(AEROPORTOS *aero1, AEROPORTOS *aero2);

/**
 * Função para encontrar um aeroporto na pilha de aeroportos pelo código IATA.
 * 
 * @param top Ponteiro para o topo da pilha de aeroportos.
 * @param IATA Código IATA do aeroporto a ser encontrado.
 * @return Ponteiro para o aeroporto encontrado ou NULL se não for encontrado.
 */
AEROPORTOS *findAero(AEROPORTOS *top, char *IATA);

#define HOUR 0
#define MINUTE 1
#include "aeroportos.h"
typedef struct VOO 
{
    char flightCode[6];
    char departure[4];
    int departTime [2];
    char arrival[4];
    int arrivalTime [2];
    struct VOO *next;
}VOOS;
typedef struct itinerario
{
    VOOS *flightOne;
    VOOS *flightTwo;
    VOOS *flightThree;
    float distance;
    struct itinerario *next;
}ITINERARY;
/**
 * Função para libertar a memória alocada para a lista de voos.
 * 
 * @param top O ponteiro para o topo da lista de voos.
 */
void freeFlight(VOOS *top);

/**
 * Função para imprimir os voos da lista.
 * 
 * @param top O ponteiro para o topo da lista de voos.
 */
void writeFlight(VOOS *top);

/**
 * Função para ler os voos de um arquivo e criar a lista de voos.
 * 
 * @param top O ponteiro para o topo da lista de voos.
 * @return O ponteiro para o topo da lista de voos atualizada.
 */
VOOS *readFlight(VOOS *top);

/**
 * Função para inicializar a lista de voos vazia.
 * 
 * @return O ponteiro para o topo da lista de voos vazia.
 */
VOOS *startStackFlight(void);

/**
 * Função para criar um novo elemento da lista de voos.
 * 
 * @return O ponteiro para o novo elemento da lista de voos.
 */
VOOS *newElementFlight(void);

/**
 * Função para encontrar um voo na lista de voos com base no aeroporto de partida e chegada.
 * 
 * @param top O ponteiro para o topo da lista de voos.
 * @param departure O aeroporto de partida.
 * @param arrival O aeroporto de chegada.
 * @return O ponteiro para o voo encontrado ou NULL se não for encontrado.
 */
VOOS *findFlight(VOOS *top, char *departure, char *arrival);

/**
 * Função para imprimir as informações de um voo.
 * 
 * @param aux O ponteiro para o voo a ser impresso.
 */
void printFlight(VOOS *aux);

/**
 * Função para comparar o horário de dois voos.
 * 
 * @param top O ponteiro para o topo da lista de voos.
 * @param curr O ponteiro para o voo atual.
 * @param choice A escolha de ordenação (-TD ou -TC).
 * @return O ponteiro para o topo da lista de voos atualizada.
 */
VOOS* timeCompare(VOOS *top, VOOS *curr, char *choice);

/**
 * Função para copiar um voo para a lista de voos.
 * 
 * @param top O ponteiro para o topo da lista de voos.
 * @param curr O ponteiro para o voo atual.
 * @return O ponteiro para o topo da lista de voos atualizada.
 */
VOOS *copyFlight(VOOS *top, VOOS *curr);

/**
 * Função para inicializar a lista de itinerários vazia.
 * 
 * @return O ponteiro para o topo da lista de itinerários vazia.
 */
ITINERARY *startStackItinerary(void);

/**
 * Função para construir um itinerário com base em três voos e calcular a distância total.
 * 
 * @param route O ponteiro para o topo da lista de itinerários.
 * @param one O ponteiro para o primeiro voo.
 * @param two O ponteiro para o segundo voo.
 * @param three O ponteiro para o terceiro voo.
 * @param top O ponteiro para o topo da lista de aeroportos.
 * @return O ponteiro para o novo itinerário criado.
 */
ITINERARY *buildItinerary(ITINERARY *route, VOOS *one, VOOS *two, VOOS *three, AEROPORTOS *top);

/**
 * Função para criar um novo elemento da lista de itinerários.
 * 
 * @return O ponteiro para o novo elemento da lista de itinerários.
 */
ITINERARY *newElementItinerary(void);

/**
 * Função para imprimir os itinerários da lista.
 * 
 * @param top O ponteiro para o topo da lista de itinerários.
 */
void writeItinerary(ITINERARY *top);

/**
 * Função para libertar a memória alocada para a lista de itinerários.
 * 
 * @param top O ponteiro para o topo da lista de itinerários.
 */
void freeItinerary(ITINERARY *top);

/**
 * Função para verificar se um horário é anterior a outro.
 * 
 * @param time1 O ponteiro para o primeiro horário.
 * @param time2 O ponteiro para o segundo horário.
 * @return 1 se o primeiro horário for anterior ao segundo, 0 caso contrário.
 */
int isEarlier(int *time1, int *time2);

/**
 * Função para retornar o(s) itinerário(s) com a menor distância total.
 * 
 * @param top O ponteiro para o topo da lista de itinerários.
 * @return O ponteiro para o(s) itinerário(s) com a menor distância total.
 */
ITINERARY *returnSmallest(ITINERARY *top);

/**
 * Função para calcular a distância entre dois aeroportos com base em suas coordenadas geográficas.
 * 
 * @param voo O ponteiro para o voo.
 * @param aeroTop O ponteiro para o topo da lista de aeroportos.
 * @return A distância entre os dois aeroportos.
 */
double flightDistance(VOOS *voo, AEROPORTOS *aeroTop);

/**
 * Função para imprimir as informações de um itinerário.
 * 
 * @param itinerary O ponteiro para o itinerário a ser impresso.
 */
void printItinerary(ITINERARY *itinerary);

/**
 * Função para reordenar a lista de itinerários com base no horário de partida do primeiro voo.
 * 
 * @param route O ponteiro para o topo da lista de itinerários.
 * @param order A ordem de ordenação (-TC ou -TD).
 * @return O ponteiro para a lista de itinerários reordenada.
 */
ITINERARY *reOrder(ITINERARY *route, char *order);
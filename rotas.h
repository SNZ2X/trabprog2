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
void writeFlight(VOOS *top);
void freeFlight(VOOS *top);
VOOS *readFlight(VOOS *top);
VOOS *startStackFlight(void);
VOOS *newElementFlight(void);
VOOS *findFlight(VOOS *TOP, char *departure, char *arrival);
void printFlight(VOOS *aux);
VOOS *copyFlight(VOOS *top, VOOS *curr);
VOOS *timeCompare(VOOS *top, VOOS *curr, char *choice);
ITINERARY *startStackItinerary(void);
ITINERARY *buildItinerary(ITINERARY *route, VOOS *one, VOOS *two, VOOS *three, AEROPORTOS *topAero);
ITINERARY *newElementItinerary(void);
void writeItinerary(ITINERARY *top, char *dist);
void freeItinerary(ITINERARY *top);
ITINERARY *pushItinerary(ITINERARY *top, ITINERARY *curr);
int isEarlier(int *time1, int *time2);
ITINERARY *returnSmallest(ITINERARY *top);
double flightDistance(VOOS *voo, AEROPORTOS *aeroTop);
void printItinerary(ITINERARY *itinerary);
ITINERARY *reOrder(ITINERARY *route,char *order);
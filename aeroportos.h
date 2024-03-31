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
void coordConv(int *lat, int *lon, double *x, double *y, double *z);
void freeAero(AEROPORTOS *top);
void writeAero(AEROPORTOS *top);
AEROPORTOS *readAero(AEROPORTOS *aeros);
AEROPORTOS *startStackAero(void);
AEROPORTOS *newElementAero(void);
double distanceCalc(AEROPORTOS *aero1, AEROPORTOS *aero2);
AEROPORTOS *findAero(AEROPORTOS *top, char *IATA);

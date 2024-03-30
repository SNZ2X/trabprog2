#include "aeroportos.h"

AEROPORTOS *startStackAero(void)
{
 return ((AEROPORTOS *) NULL);
}
AEROPORTOS *readAero(AEROPORTOS *top)
{
    AEROPORTOS *add;
    FILE *faero;
    int ret;
    faero = fopen("aeroportos.txt","r");
    while((add = newElementAero()) != NULL && (ret = fscanf(faero, "%s %s %d %d %d %c %d %d %d %c %s %d", add->icao, add->iata, &add->latitude[DEGREE], &add->latitude[MINUTE], &add->latitude[SECOND],
&add->lat, &add->longitude[DEGREE], &add->longitude[MINUTE], &add->longitude[SECOND], &add->lon, add->city, &add->time)) != EOF)
    {
        if (ret == 12)
        {
            coordConv(add->latitude, add->longitude, &add->x, &add->y, &add->z);
            if(add->lat == 'S'){add->z = -add->z;}
            if(add->lon == 'W'){add->x = -add->x;}
            add->next = top;
            top = add;
        }
        else{free(add);}
    }
    fclose(faero);
    free(add);
    return top;
}
void coordConv(int *lat, int *lon, double *x, double *y, double *z)
{
    double lataux = lat[DEGREE] + (lat[MINUTE]/60.0) + (lat[SECOND]/3600.0);
    double lonaux = lon[DEGREE] + (lon[MINUTE]/60.0) + (lon[SECOND]/3600.0);
    lataux = (lataux * PI) / 180.0;
    lonaux = (lonaux * PI) / 180.0;
    *x = R * (cos(lataux) * cos(lonaux));
    *y = R * (cos(lataux) * sin(lonaux));
    *z = R * sin(lataux);
}
AEROPORTOS* newElementAero(void)
{
    return malloc(sizeof(AEROPORTOS));
}
void writeAero(AEROPORTOS *top)
{
    AEROPORTOS *aux = top;
    for(; aux!=NULL;aux=aux->next)
    {
    printf("%s %s %d %d %d %c %d %d %d %c %s %d\n", aux->icao, aux->iata, aux->latitude[DEGREE], aux->latitude[MINUTE], aux->latitude[SECOND], aux->lat, aux->longitude[DEGREE], aux->longitude[MINUTE], aux->longitude[SECOND], aux->lon, aux->city, aux->time);
    }
}
void freeAero(AEROPORTOS *top)
{
    AEROPORTOS *aux;
    for(;top != NULL; top = aux)
    {
        aux = top->next;
        free(top);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rotas.h"

void freeFlight(VOOS *top)
{
    VOOS* aux = top;
    for(;top!=NULL;top = aux)
    {
        aux = top->next;
        free(top);
    }
}
void writeFlight(VOOS *top)
{
    VOOS *aux = top;
    for(;aux != NULL;aux = aux->next)
    {
        printFlight(aux);
    }
}
VOOS *readFlight(VOOS *top)
{
    VOOS *aux;
    FILE *fp = fopen("rotas.txt", "r");
    int ret;
    while((aux = newElementFlight()) != NULL && (ret = fscanf(fp, "%s %s %d:%d %s %d:%d", aux->flightCode, aux->departure, &aux->departTime[HOUR], &aux->departTime[MINUTE], aux->arrival, &aux->arrivalTime[HOUR], &aux->arrivalTime[MINUTE])) != EOF)
    {
        if (ret == 7)
        {
            aux->next = top;
            top = aux;
        }
        else{free(aux);}
    }
    fclose(fp);
    free(aux);
    return top;
}
VOOS *startStackFlight(void)
{
    return ((VOOS*) NULL);
}
VOOS *newElementFlight(void)
{
    return malloc(sizeof(VOOS));
}
VOOS *findFlight(VOOS *top, char *departure, char *arrival)
{
    VOOS *aux = top;
    for(;aux!=NULL; aux = aux->next)
    {
        if(strcmp(aux->departure, departure) == 0 && strcmp(aux->arrival, arrival) == 0)
        {
            return aux;
        }
        if(strcmp(aux->departure, departure) == 0 && strcmp(arrival, "\0") == 0)
        {
            return aux;
        }
        if(strcmp(departure, "\0") == 0 && strcmp(aux->arrival, arrival) == 0)
        {
            return aux;
        }
    }
    return NULL;
}
void printFlight(VOOS *aux)
{
    if(aux!=NULL)
    {
    printf("%s %s %02d:%02d %s %02d:%02d\n", aux->flightCode, aux->departure, aux->departTime[HOUR], aux->departTime[MINUTE], aux->arrival, aux->arrivalTime[HOUR], aux->arrivalTime[MINUTE]);}
}
VOOS* timeCompare(VOOS *top, VOOS *curr, char *choice)
{
    VOOS *newNode = copyFlight(NULL, curr);
    if (top == NULL)
    {
        newNode->next = top;
        top = newNode;
    }
    else if (isEarlier(top->departTime, curr->departTime) == 0 && strcmp(choice, "-TC")== 0)
    {
        newNode->next = top;
        top = newNode;
    }
    else
    {
        VOOS* aux = top;
        while (aux->next != NULL && isEarlier(curr->departTime, aux->next->departTime) == 1)
        {
            aux = aux->next;
        }
        newNode->next = aux->next;
        aux->next = newNode;
    }
    return top;
}

VOOS *copyFlight(VOOS *top, VOOS *curr)
{
    if(top!=NULL)
    {
        VOOS *element = newElementFlight();
        *element = *curr;
        element->next = top;
        top = element;
        return top;
    }
    else
    {
        VOOS *element = newElementFlight();
        *element = *curr;
        element->next = NULL;
        return element; 
    }
}
ITINERARY *startStackItinerary(void)
{
    return (ITINERARY*)NULL;
}
ITINERARY *buildItinerary(ITINERARY *route,VOOS *one, VOOS *two, VOOS *three, VOOS *four)
{
    ITINERARY *curr = newElementItinerary();
    curr->flightOne = one;
    curr->flightTwo = two;
    curr->flightThree = three;
    curr->flightFour = four;
    curr->next = route;
    return curr;
}
ITINERARY *newElementItinerary(void)
{
    return malloc(sizeof(ITINERARY));
}
void writeItinerary(ITINERARY *top)
{
    ITINERARY *aux = top;
    int n=1;
    for(;aux != NULL;aux = aux->next)
    {
        printf("ITINERÁRIO %d\n", n);
        printFlight(aux->flightOne);
        printFlight(aux->flightTwo);
        printFlight(aux->flightThree);
        printFlight(aux->flightFour);
        n++;
    }
}
void freeItinerary(ITINERARY *top)
{
    ITINERARY* aux = top;
    for(;top!=NULL;top = aux)
    {
        aux = top->next;
        free(top);
    }
}
ITINERARY *pushItinerary(ITINERARY *top, ITINERARY *curr)
{
    curr->next = top;
    top = curr;
    return top;
}
int isEarlier(int *time1, int *time2)
{
    if (time1[HOUR] < time2[HOUR] || 
        (time1[HOUR] == time2[HOUR] && time1[MINUTE] < time2[MINUTE]))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

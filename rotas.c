#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rotas.h"

void freeFlight(VOOS *top)
{
    VOOS* aux = top;
    while(top != NULL)
    {
        aux = top;
        top = top->next;
        free(aux);
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
    else if (isEarlier(top->departTime, curr->departTime) == 0 && strcmp(choice, "-TD")== 0)
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
ITINERARY *buildItinerary(ITINERARY *route, VOOS *one, VOOS *two, VOOS *three, AEROPORTOS *top)
{
    ITINERARY *curr = newElementItinerary();
    curr->flightOne = one;
    curr->flightTwo = two;
    curr->flightThree = three;
    curr->next = route;
    if (two == NULL){curr->distance = flightDistance(one, top);}
    else if (three == NULL){curr->distance = flightDistance(one, top) + flightDistance(two, top);}
    else {curr->distance = flightDistance(one, top) + flightDistance(two, top) + flightDistance(three, top);}
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
            printItinerary(aux);
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
ITINERARY *returnSmallest(ITINERARY *top)
{
    ITINERARY *aux;
    ITINERARY *newNode;
    ITINERARY *topDist = startStackItinerary();
    float distance;
    if(top == NULL){return NULL;}
    aux = top;
    distance = top->distance;
    for(;aux!=NULL; aux = aux->next)
    {
        if(aux->distance < distance){distance=aux->distance;}
    }
    aux=top;
    for (; aux!=NULL; aux = aux->next)
    {
        if (aux->distance == distance)
        {
            if (topDist == NULL)
            {
                newNode = newElementItinerary();
                *newNode = *aux;
                newNode->next = NULL;
                topDist = newNode;
            }
            else
            {
                newNode = newElementItinerary();
                *newNode = *aux;
                newNode->next = topDist;
                topDist = newNode;
            }
        }
    }
    return topDist;
}
double flightDistance(VOOS *voo, AEROPORTOS *aeroTop)
{
    return (distanceCalc(findAero(aeroTop, voo->departure), findAero(aeroTop, voo->arrival)));
}
void printItinerary(ITINERARY *itinerary)
{
    printFlight(itinerary->flightOne);
    printFlight(itinerary->flightTwo);
    printFlight(itinerary->flightThree);
}
ITINERARY *reOrder(ITINERARY *route, char *order) {
    ITINERARY *current;
    ITINERARY *prev;
    int swapped;
    if (route == NULL || route->next == NULL) {
        return route;
    }

    do {
        swapped = 0;
        current = route;
        prev = NULL;

        while (current->next != NULL) {
            int shouldSwap = 0;
            if (strcmp(order, "-TC") == 0 && isEarlier(current->next->flightOne->departTime, current->flightOne->departTime)) {
                shouldSwap = 1;
            } else if (strcmp(order, "-TD") == 0 && isEarlier(current->flightOne->departTime, current->next->flightOne->departTime)) {
                shouldSwap = 1;
            }

            if (shouldSwap) {
                ITINERARY *temp = current->next;
                current->next = temp->next;

                if (prev == NULL) {
                    route = temp;
                } else {
                    prev->next = temp;
                }
                temp->next = current;
                prev = temp;
                swapped = 1;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);

    return route;
}

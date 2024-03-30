#include "aeroportos.h"
#include "rotas.h"
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (strcmp(argv[1],"-aeroportos") == 0)
        {
            AEROPORTOS *topAero = startStackAero();
            topAero = readAero(topAero);
            writeAero(topAero);
            freeAero(topAero);
        }
        if (strcmp(argv[1],"-voos") == 0)
        {
            VOOS *topVoo = startStackFlight();
            topVoo = readFlight(topVoo);
            writeFlight(topVoo);
            freeFlight(topVoo);
        }
    }
    if (argc == 5)
    {
        if(strcmp(argv[3],"-L") == 0)
        {
            if(strcmp(argv[4],"0") == 0)
            {
                VOOS *topVoo = startStackFlight();
                VOOS *matchedFlights = startStackFlight();
                VOOS *aux;
                topVoo = readFlight(topVoo);
                aux = topVoo;
                while(aux!=NULL)
                {
                    aux = findFlight(aux, argv[1], argv[2]);
                    if (aux == NULL) 
                    {
                        break;
                    }
                    matchedFlights = copyFlight(matchedFlights,aux);
                    aux = aux->next;
                }

                writeFlight(matchedFlights);
                freeFlight(topVoo);
                freeFlight(matchedFlights);   
            }
            if(strcmp(argv[4],"1") == 0)
            {
                ITINERARY *route = startStackItinerary();
                VOOS *topVoo = startStackFlight();
                VOOS *auxFirstFlight;
                VOOS *topFirstFlight = startStackFlight();
                VOOS *topSecondFlight = startStackFlight();
                VOOS *auxSecondFlight;
                topVoo = readFlight(topVoo);
                auxFirstFlight=topVoo;
                auxSecondFlight=topVoo;
                while(auxFirstFlight!=NULL)
                {
                    auxFirstFlight = findFlight(auxFirstFlight,argv[1],"\0");
                    if(auxFirstFlight==NULL){break;}
                    topFirstFlight = copyFlight(topFirstFlight, auxFirstFlight);
                    auxFirstFlight = auxFirstFlight->next;
                }
                while(auxSecondFlight!=NULL)
                {
                    auxSecondFlight = findFlight(auxSecondFlight,"\0",argv[2]);
                    if(auxSecondFlight==NULL){break;}
                    topSecondFlight = copyFlight(topSecondFlight, auxSecondFlight);
                    auxSecondFlight = auxSecondFlight->next;
                }
                auxFirstFlight = topFirstFlight;
                auxSecondFlight = topSecondFlight;
                while (auxFirstFlight != NULL)
                {
                    while (auxSecondFlight != NULL)
                    {
                        if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0)
                        {
                            route = buildItinerary(route, auxFirstFlight, auxSecondFlight, NULL, NULL);
                        }
                        auxSecondFlight = auxSecondFlight->next;
                    }
                    auxSecondFlight = topSecondFlight;
                    auxFirstFlight = auxFirstFlight->next;   
                }   
                writeItinerary(route);
                freeFlight(topVoo);
                freeFlight(topFirstFlight);
                freeFlight(topSecondFlight);
                freeItinerary(route);
            }
        }
    }
    if (argc == 6)
    {
        if(strcmp(argv[3],"-L") == 0 && strcmp(argv[4],"0") == 0)
        {
            if (strcmp(argv[5],"-TC") == 0 || strcmp(argv[5],"-TD") == 0)
            {
                    VOOS *topVoo = startStackFlight();
                    VOOS *aux;
                    VOOS *conditionFlightTop = startStackFlight();
                    topVoo = readFlight(topVoo);
                    aux = topVoo;
                    
                    while(aux!=NULL)
                    {
                        aux = findFlight(aux, argv[1], argv[2]);
                        if (aux == NULL) 
                        {
                            break;
                        }
                        conditionFlightTop = timeCompare(conditionFlightTop, aux, argv[5]);
                        aux = aux->next;
                    }
                        writeFlight(conditionFlightTop);
                        freeFlight(topVoo);
                        freeFlight(conditionFlightTop);                   
            }
            else{printf("Inválido.");}
        }
        if(strcmp(argv[3],"-L") == 0 && strcmp(argv[4],"1") == 0)
        {
            if (strcmp(argv[5],"-TC") == 0)
            {
                ITINERARY *route = startStackItinerary();
                VOOS *topVoo = startStackFlight();
                VOOS *auxFirstFlight;
                VOOS *topFirstFlight = startStackFlight();
                VOOS *topSecondFlight = startStackFlight();
                VOOS *auxSecondFlight;
                topVoo = readFlight(topVoo);
                auxFirstFlight=topVoo;
                auxSecondFlight=topVoo;
                while(auxFirstFlight!=NULL)
                {
                    auxFirstFlight = findFlight(auxFirstFlight,argv[1],"\0");
                    if(auxFirstFlight==NULL){break;}
                    topFirstFlight = copyFlight(topFirstFlight, auxFirstFlight);
                    auxFirstFlight = auxFirstFlight->next;
                }
                while(auxSecondFlight!=NULL)
                {
                    auxSecondFlight = findFlight(auxSecondFlight,"\0",argv[2]);
                    if(auxSecondFlight==NULL){break;}
                    topSecondFlight = copyFlight(topSecondFlight, auxSecondFlight);
                    auxSecondFlight = auxSecondFlight->next;
                }
                auxFirstFlight = topFirstFlight;
                auxSecondFlight = topSecondFlight;
                while (auxFirstFlight != NULL)
                {
                    while (auxSecondFlight != NULL)
                    {
                        if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0 && isEarlier(auxFirstFlight->departTime, auxSecondFlight->departTime))
                        {
                            route = buildItinerary(route, auxFirstFlight, auxSecondFlight, NULL, NULL);
                        }
                        auxSecondFlight = auxSecondFlight->next;
                    }
                    auxSecondFlight = topSecondFlight;
                    auxFirstFlight = auxFirstFlight->next;   
                }   
                writeItinerary(route);
                freeFlight(topVoo);
                freeFlight(topFirstFlight);
                freeFlight(topSecondFlight);
                freeItinerary(route);  
            }
        }
    }

return 0;    
}

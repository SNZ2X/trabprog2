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
                    auxFirstFlight = findFlight(auxFirstFlight, argv[1], "\0");
                    if (auxFirstFlight == NULL) 
                    {
                        break;
                    }
                    while(auxSecondFlight!=NULL)
                    {
                        auxSecondFlight = findFlight(auxSecondFlight, auxFirstFlight->arrival, argv[2]);
                        if (auxSecondFlight == NULL) 
                        {
                            break;
                        }
                        route = pushItinerary(route,buildItinerary(auxFirstFlight,auxSecondFlight,NULL,NULL));
                        auxSecondFlight = auxSecondFlight->next;
                    }
                    auxFirstFlight = auxFirstFlight->next;
                }
                writeItinerary(route);
                freeItinerary(route);
                freeFlight(topFirstFlight);
                freeFlight(topSecondFlight);
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
    }

return 0;    
}

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
        else if (strcmp(argv[1],"-voos") == 0)
        {
            VOOS *topVoo = startStackFlight();
            topVoo = readFlight(topVoo);
            writeFlight(topVoo);
            freeFlight(topVoo);
        }
    }
    else if (argc == 5)
    {
        if(strcmp(argv[3],"-L") == 0)
        {
            if(strcmp(argv[4],"0") == 0)
            {
                VOOS *topVoo = startStackFlight();
                VOOS *matchedFlights = startStackFlight();
                VOOS *aux;
                ITINERARY *route = startStackItinerary();
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
            else if(strcmp(argv[4],"1") == 0)
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
                writeItinerary(route, "j");
                freeFlight(topVoo);
                freeFlight(topFirstFlight);
                freeFlight(topSecondFlight);
                freeItinerary(route);
            }
            if(strcmp(argv[4],"2") == 0)
            {
                ITINERARY *route = startStackItinerary();
                VOOS *topVoo = startStackFlight();
                VOOS *auxFirstFlight, *auxSecondFlight, *auxThirdFlight;
                VOOS *topFirstFlight = startStackFlight();
                VOOS *topSecondFlight = startStackFlight();
                VOOS *topThirdFlight = startStackFlight();
                topVoo = readFlight(topVoo);
                auxFirstFlight = auxSecondFlight = auxThirdFlight = topVoo;

                while(auxFirstFlight!=NULL)
                {
                    auxFirstFlight = findFlight(auxFirstFlight,argv[1],"\0");
                    if(auxFirstFlight==NULL){break;}
                    topFirstFlight = copyFlight(topFirstFlight, auxFirstFlight);
                    auxFirstFlight = auxFirstFlight->next;
                }
                while(auxSecondFlight!=NULL)
                {
                    if(auxSecondFlight==NULL){break;}
                    topSecondFlight = copyFlight(topSecondFlight, auxSecondFlight);
                    auxSecondFlight = auxSecondFlight->next;
                }
                while(auxThirdFlight!=NULL)
                {
                    auxThirdFlight = findFlight(auxThirdFlight,"\0",argv[2]);
                    if(auxThirdFlight==NULL){break;}
                    topThirdFlight = copyFlight(topThirdFlight, auxThirdFlight);
                    auxThirdFlight = auxThirdFlight->next;
                }
                auxFirstFlight = topFirstFlight;
                auxSecondFlight = topSecondFlight;
                auxThirdFlight = topThirdFlight;
                while (auxFirstFlight != NULL)
                {
                    while (auxSecondFlight != NULL)
                    {
                        if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0)
                        {
                            while (auxThirdFlight != NULL)
                            {
                                if(strcmp(auxSecondFlight->arrival, auxThirdFlight->departure) == 0 && strcmp(auxFirstFlight->departure,auxSecondFlight->arrival) && strcmp(argv[2],auxFirstFlight->arrival))
                                {
                                    route = buildItinerary(route, auxFirstFlight, auxSecondFlight, auxThirdFlight, NULL);
                                }
                                auxThirdFlight = auxThirdFlight->next;
                            }
                            auxThirdFlight = topThirdFlight;
                        }
                        auxSecondFlight = auxSecondFlight->next;
                    }
                    auxSecondFlight = topSecondFlight;
                    auxFirstFlight = auxFirstFlight->next;   
                }   
                writeItinerary(route, "j");
                freeFlight(topVoo);
                freeFlight(topFirstFlight);
                freeFlight(topSecondFlight);
                freeFlight(topThirdFlight);
                freeItinerary(route);
            }
        }
    }
    else if (argc == 6)
    {
        if(strcmp(argv[3],"-L") == 0 && strcmp(argv[4],"0") == 0)
        {
            if (strcmp(argv[5],"-TC") == 0 || strcmp(argv[5],"-TD") == 0)
            {
                    VOOS *topVoo = startStackFlight();
                    ITINERARY *route = startStackItinerary();
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
                    aux = conditionFlightTop;
                    for(;aux!=NULL;aux = aux->next)
                    {route = buildItinerary(route,aux,NULL,NULL,NULL);}
                    writeItinerary(route, "j");
                    freeFlight(topVoo);
                    freeFlight(conditionFlightTop);
                    freeItinerary(route);                   
            }
            else{printf("Inválido.");}
        }
        else if(strcmp(argv[3],"-L") == 0 && strcmp(argv[4],"1") == 0)
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
                        if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0 && isEarlier(auxFirstFlight->arrivalTime, auxSecondFlight->departTime))
                        {
                            route = buildItinerary(route, auxFirstFlight, auxSecondFlight, NULL, NULL);
                        }
                        auxSecondFlight = auxSecondFlight->next;
                    }
                    auxSecondFlight = topSecondFlight;
                    auxFirstFlight = auxFirstFlight->next;   
                }   
                writeItinerary(route, "j");
                freeFlight(topVoo);
                freeFlight(topFirstFlight);
                freeFlight(topSecondFlight);
                freeItinerary(route);  
            }
        }
        else if (strcmp(argv[3], "-L") == 0 && strcmp(argv[4],"2") == 0)
        {
            if (strcmp(argv[5],"-TC") == 0)
            {
                ITINERARY *route = startStackItinerary();
                VOOS *topVoo = startStackFlight();
                VOOS *auxFirstFlight, *auxSecondFlight, *auxThirdFlight;
                VOOS *topFirstFlight = startStackFlight();
                VOOS *topSecondFlight = startStackFlight();
                VOOS *topThirdFlight = startStackFlight();
                topVoo = readFlight(topVoo);
                auxFirstFlight = auxSecondFlight = auxThirdFlight = topVoo;

                while(auxFirstFlight!=NULL)
                {
                    auxFirstFlight = findFlight(auxFirstFlight,argv[1],"\0");
                    if(auxFirstFlight==NULL){break;}
                    topFirstFlight = copyFlight(topFirstFlight, auxFirstFlight);
                    auxFirstFlight = auxFirstFlight->next;
                }
                while(auxSecondFlight!=NULL)
                {
                    if(auxSecondFlight==NULL){break;}
                    topSecondFlight = copyFlight(topSecondFlight, auxSecondFlight);
                    auxSecondFlight = auxSecondFlight->next;
                }
                while(auxThirdFlight!=NULL)
                {
                    auxThirdFlight = findFlight(auxThirdFlight,"\0",argv[2]);
                    if(auxThirdFlight==NULL){break;}
                    topThirdFlight = copyFlight(topThirdFlight, auxThirdFlight);
                    auxThirdFlight = auxThirdFlight->next;
                }
                auxFirstFlight = topFirstFlight;
                auxSecondFlight = topSecondFlight;
                auxThirdFlight = topThirdFlight;
                while (auxFirstFlight != NULL)
                {
                    while (auxSecondFlight != NULL)
                    {
                        if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0)
                        {
                            while (auxThirdFlight != NULL)
                            {
                                if(strcmp(auxSecondFlight->arrival, auxThirdFlight->departure) == 0 && strcmp(auxFirstFlight->departure,auxSecondFlight->arrival) && strcmp(argv[2],auxFirstFlight->arrival) && isEarlier(auxFirstFlight->arrivalTime,auxSecondFlight->departTime) && isEarlier(auxSecondFlight->arrivalTime,auxThirdFlight->departTime))
                                {
                                    route = buildItinerary(route, auxFirstFlight, auxSecondFlight, auxThirdFlight, NULL);
                                }
                                auxThirdFlight = auxThirdFlight->next;
                            }
                            auxThirdFlight = topThirdFlight;
                        }
                        auxSecondFlight = auxSecondFlight->next;
                    }
                    auxSecondFlight = topSecondFlight;
                    auxFirstFlight = auxFirstFlight->next;   
                }   
                writeItinerary(route, "j");
                freeFlight(topVoo);
                freeFlight(topFirstFlight);
                freeFlight(topSecondFlight);
                freeFlight(topThirdFlight);
                freeItinerary(route);
            }  
        }
    }
    else if (argc == 7)
    {
        if(strcmp(argv[3],"-L") == 0)
        {
            if (strcmp(argv[5],"-TC") == 0)
            {
                if (strcmp(argv[6],"-D") == 0)
                {
                    if(strcmp(argv[4],"0") == 0)
                    {
                    VOOS *topVoo = startStackFlight();
                    ITINERARY *route = startStackItinerary();
                    ITINERARY *smallest = startStackItinerary();
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
                    aux = conditionFlightTop;
                    for(;aux!=NULL;aux = aux->next)
                    {route = buildItinerary(route,aux,NULL,NULL,NULL);}
                    smallest = returnSmallest(route);
                    printItinerary(smallest);
                    freeFlight(topVoo);
                    freeFlight(conditionFlightTop);
                    freeItinerary(route); 
                    }
                    else if (strcmp(argv[4], "1") ==0)
                    {
                        ITINERARY *route = startStackItinerary();
                        ITINERARY *smallest = startStackItinerary();
                        AEROPORTOS *topAero = startStackAero();
                        VOOS *topVoo = startStackFlight();
                        VOOS *auxFirstFlight;
                        VOOS *topFirstFlight = startStackFlight();
                        VOOS *topSecondFlight = startStackFlight();
                        VOOS *auxSecondFlight;
                        topAero = readAero(topAero);
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
                                if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0 && isEarlier(auxFirstFlight->arrivalTime, auxSecondFlight->departTime))
                                {
                                    route = buildItinerary(route, auxFirstFlight, auxSecondFlight, NULL, topAero);
                                }
                                auxSecondFlight = auxSecondFlight->next;
                            }
                            auxSecondFlight = topSecondFlight;
                            auxFirstFlight = auxFirstFlight->next;   
                        }
                        smallest = returnSmallest(route);
                        if(smallest!=NULL)
                        {
                            printf("ITINERÁRIO 1");
                            printItinerary(smallest);
                        }
                        freeFlight(topVoo);
                        freeAero(topAero);
                        freeFlight(topFirstFlight);
                        freeFlight(topSecondFlight);
                        freeItinerary(route);
                    }
                    else if(strcmp(argv[4],"2") == 0)
                    {
                    ITINERARY *route = startStackItinerary();
                    ITINERARY *smallest = startStackItinerary();
                    AEROPORTOS *topAero = startStackAero();
                    VOOS *topVoo = startStackFlight();
                    VOOS *auxFirstFlight, *auxSecondFlight, *auxThirdFlight;
                    VOOS *topFirstFlight = startStackFlight();
                    VOOS *topSecondFlight = startStackFlight();
                    VOOS *topThirdFlight = startStackFlight();
                    topAero = readAero(topAero);
                    topVoo = readFlight(topVoo);
                    auxFirstFlight = auxSecondFlight = auxThirdFlight = topVoo;
                    while(auxFirstFlight!=NULL)
                    {
                        auxFirstFlight = findFlight(auxFirstFlight,argv[1],"\0");
                        if(auxFirstFlight==NULL){break;}
                        topFirstFlight = copyFlight(topFirstFlight, auxFirstFlight);
                        auxFirstFlight = auxFirstFlight->next;
                    }
                    while(auxSecondFlight!=NULL)
                    {
                        if(auxSecondFlight==NULL){break;}
                        topSecondFlight = copyFlight(topSecondFlight, auxSecondFlight);
                        auxSecondFlight = auxSecondFlight->next;
                    }
                    while(auxThirdFlight!=NULL)
                    {
                        auxThirdFlight = findFlight(auxThirdFlight,"\0",argv[2]);
                        if(auxThirdFlight==NULL){break;}
                        topThirdFlight = copyFlight(topThirdFlight, auxThirdFlight);
                        auxThirdFlight = auxThirdFlight->next;
                    }
                    auxFirstFlight = topFirstFlight;
                    auxSecondFlight = topSecondFlight;
                    auxThirdFlight = topThirdFlight;
                    while (auxFirstFlight != NULL)
                    {
                        while (auxSecondFlight != NULL)
                        {
                            if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0)
                            {
                                while (auxThirdFlight != NULL)
                                {
                                    if(strcmp(auxSecondFlight->arrival, auxThirdFlight->departure) == 0 && strcmp(auxFirstFlight->departure,auxSecondFlight->arrival) && strcmp(argv[2],auxFirstFlight->arrival) && isEarlier(auxFirstFlight->arrivalTime,auxSecondFlight->departTime) && isEarlier(auxSecondFlight->arrivalTime,auxThirdFlight->departTime))
                                    {
                                        route = buildItinerary(route, auxFirstFlight, auxSecondFlight, auxThirdFlight, topAero);
                                    }
                                    auxThirdFlight = auxThirdFlight->next;
                                }
                                auxThirdFlight = topThirdFlight;
                            }
                            auxSecondFlight = auxSecondFlight->next;
                        }
                        auxSecondFlight = topSecondFlight;
                        auxFirstFlight = auxFirstFlight->next;   
                    }   
                    smallest = returnSmallest(route);
                    
                    if(smallest!=NULL)
                    {
                        printf("ITINERÁRIO 1\n");
                        printItinerary(smallest);
                    }
                    freeFlight(topVoo);
                    freeAero(topAero);
                    freeFlight(topFirstFlight);
                    freeFlight(topSecondFlight);
                    freeFlight(topThirdFlight);
                    freeItinerary(route);   
                    }
                }                   
            }
            else{printf("Inválido.");}
        }
    }
return 0;    
}

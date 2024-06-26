#include "rotas.h"
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        /*-aeroportos*/
        if (strcmp(argv[1],"-aeroportos") == 0)
        {
            AEROPORTOS *topAero = startStackAero();
            topAero = readAero(topAero);
            writeAero(topAero);
            freeAero(topAero);
        }
        /*-rotas*/
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
                /*-L 0*/
                /*INICIALIZACAO DAS VARIAVEIS*/
                VOOS *topVoo = startStackFlight();
                VOOS *matchedFlights = startStackFlight();
                VOOS *aux;
                topVoo = readFlight(topVoo);
                aux = topVoo;
                /*PROCURA DOS VOOS*/
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
                /*ESCRITA E SUBSEQUENTE LIBERTACAO DA MEMORIA*/
                writeFlight(matchedFlights);
                freeFlight(topVoo);
                freeFlight(matchedFlights);   
            }
            else if(strcmp(argv[4],"1") == 0)
            {
                /*-L 1*/
                /*INICIALIZACAO DAS VARIAVEIS*/
                ITINERARY *route = startStackItinerary();
                VOOS *topVoo = startStackFlight();
                VOOS *auxFirstFlight;
                VOOS *topFirstFlight = startStackFlight();
                VOOS *topSecondFlight = startStackFlight();
                VOOS *auxSecondFlight;
                /*LEITURA DO FICHEIRO DAS ROTAS*/
                topVoo = readFlight(topVoo);
                auxFirstFlight=topVoo;
                auxSecondFlight=topVoo;
                /*INICIALIZACAO DAS STACKS AUXILIARES*/
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
                /*PROCURA DOS VOOS QUE VERIFIQUEM OS PARAMETROS*/
                while (auxFirstFlight != NULL)
                {
                    while (auxSecondFlight != NULL)
                    {
                        if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0)
                        {
                            /*CONSTRUCAO DO ITINERARIO*/
                            route = buildItinerary(route, auxFirstFlight, auxSecondFlight, NULL, NULL);
                        }
                        auxSecondFlight = auxSecondFlight->next;
                    }
                    auxSecondFlight = topSecondFlight;
                    auxFirstFlight = auxFirstFlight->next;   
                }   
                /*ESCRITA DO ITINERARIO E SUBSEQUENTE LIBERTACAO DE MEMORIA*/
                writeItinerary(route);
                freeFlight(topVoo);
                freeFlight(topFirstFlight);
                freeFlight(topSecondFlight);
                freeItinerary(route);
            }
            if(strcmp(argv[4],"2") == 0)
            {
                /*-L 2*/
                /*INICIALIZACAO DAS VARIAVEIS*/
                ITINERARY *route = startStackItinerary();
                VOOS *topVoo = startStackFlight();
                VOOS *auxFirstFlight, *auxSecondFlight, *auxThirdFlight;
                VOOS *topFirstFlight = startStackFlight();
                VOOS *topSecondFlight = startStackFlight();
                VOOS *topThirdFlight = startStackFlight();
                /*LEITURA DAS ROTAS*/
                topVoo = readFlight(topVoo);
                auxFirstFlight = auxSecondFlight = auxThirdFlight = topVoo;
                /*INICIALIZACAO DAS STACKS AUXILIARES*/
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
                /*PROCURA DOS VOOS QUE VERIFIQUEM OS PARAMETROS*/
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
                                    /*CONSTRUCAO DA ROTA*/
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
                /*ESCRITA DO ITINERARIO E LIBERTACAO DE MEMORIA*/
                writeItinerary(route);
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
                    /*-L 0 -TC/-TD*/
                    /*INICIALIZACAO DAS VARIAVEIS*/
                    VOOS *topVoo = startStackFlight();
                    ITINERARY *route = startStackItinerary();
                    VOOS *aux;
                    VOOS *conditionFlightTop = startStackFlight();
                    topVoo = readFlight(topVoo);
                    aux = topVoo;
                    /*PROCURA DO VOO QUE SATISFACA OS PARAMETROS*/
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
                    /*CONSTRUCAO DO ITINERARIO*/
                    aux = conditionFlightTop;
                    for(;aux!=NULL;aux = aux->next)
                    {route = buildItinerary(route,aux,NULL,NULL,NULL);}
                    route = reOrder(route, argv[5]);
                    /*ESCRITA DO ITINERARIO E LIBERTACAO DE MEMORIA*/
                    writeItinerary(route);
                    freeFlight(topVoo);
                    freeFlight(conditionFlightTop);
                    freeItinerary(route);                   
            }
        }
        else if(strcmp(argv[3],"-L") == 0 && strcmp(argv[4],"1") == 0)
        {
            if (strcmp(argv[5],"-TC") == 0||strcmp(argv[5],"-TD")==0)
            {
                /*-L 1 -TC/-TD*/
                /*INICIALIZACAO DAS VARIAVEIS*/
                ITINERARY *route = startStackItinerary();
                VOOS *topVoo = startStackFlight();
                VOOS *auxFirstFlight;
                VOOS *topFirstFlight = startStackFlight();
                VOOS *topSecondFlight = startStackFlight();
                VOOS *auxSecondFlight;
                /*LEITURA DO FICHEIRO DAS ROTAS*/
                topVoo = readFlight(topVoo);
                auxFirstFlight=topVoo;
                auxSecondFlight=topVoo;
                /*INICIALIZACAO DAS STACKS AUXILIARES*/
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
                /*PROCURA DOS VOOS QUE VERIFIQUEM OS PARAMETROS*/
                while (auxFirstFlight != NULL)
                {
                    while (auxSecondFlight != NULL)
                    {
                        if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0 && isEarlier(auxFirstFlight->arrivalTime, auxSecondFlight->departTime))
                        {
                            /*CONSTRUCAO DO ITINERARIO*/
                            route = buildItinerary(route, auxFirstFlight, auxSecondFlight, NULL, NULL);
                        }
                        auxSecondFlight = auxSecondFlight->next;
                    }
                    auxSecondFlight = topSecondFlight;
                    auxFirstFlight = auxFirstFlight->next;   
                }
                /*REORDENACAO POR TEMPO DE PARTIDA CRESCENTE*/
                route = reOrder(route,argv[5]);
                /*ESCRITA E SUBSEQUENTE LIBERTACAO DE MEMORIA*/   
                writeItinerary(route);
                freeFlight(topVoo);
                freeFlight(topFirstFlight);
                freeFlight(topSecondFlight);
                freeItinerary(route);  
            }
        }
        else if (strcmp(argv[3], "-L") == 0 && strcmp(argv[4],"2") == 0)
        {
            if (strcmp(argv[5],"-TC") == 0||strcmp(argv[5],"-TD")==0)
            {
                /*-L 2 -TC/-TD*/
                /*INICIALIZACAO DAS VARIAVEIS*/
                ITINERARY *route = startStackItinerary();
                VOOS *topVoo = startStackFlight();
                VOOS *auxFirstFlight, *auxSecondFlight, *auxThirdFlight;
                VOOS *topFirstFlight = startStackFlight();
                VOOS *topSecondFlight = startStackFlight();
                VOOS *topThirdFlight = startStackFlight();
                topVoo = readFlight(topVoo);
                auxFirstFlight = auxSecondFlight = auxThirdFlight = topVoo;
                /*INICIALIZACAO DAS STACKS AUXILIARES*/
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
                /*PROCURA DOS VOOS QUE VERIFIQUEM AS CONDICÕES*/
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
                                    /*CONSTRUCAO DO ITINERARIO*/
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
                /*REORDENACAO DA ROTA POR TEMPO DE PARTIDA CRESCENTE*/
                route = reOrder(route,argv[5]); 
                /*ESCRITA DO ITINERARIO DA ROTA E SUBSEQUENTE LIBERTACAO DE MEMORIA*/  
                writeItinerary(route);
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
            if (strcmp(argv[5],"-TC") == 0 || strcmp(argv[5],"-TD") == 0)
            {
                if (strcmp(argv[6],"-D") == 0)
                {
                    if(strcmp(argv[4],"0") == 0)
                    {
                        /*./rotas2024 partida chegada -L 0 -TC/-TD -D*/
                        /*InicializaCAo das variAveis*/
                        VOOS *topVoo = startStackFlight();
                        ITINERARY *route = startStackItinerary();
                        ITINERARY *smallest = startStackItinerary();
                        VOOS *aux;
                        VOOS *conditionFlightTop = startStackFlight();
                        topVoo = readFlight(topVoo);
                        aux = topVoo;
                        /*INICIALIZACAO DA STACK DO PRIMEIRO VOO*/
                        while(aux!=NULL)
                        {
                            /*PROCURA DE VOO NA STACK QUE VERIFIQUE OS PARAMETROS*/
                            aux = findFlight(aux, argv[1], argv[2]);
                            if (aux == NULL) 
                            {
                                break;
                            }
                            /*VERIFICACAO DA LIGACAO HORÁRIA*/
                            conditionFlightTop = timeCompare(conditionFlightTop, aux, argv[5]);
                            aux = aux->next;
                        }
                        /*CONSTRUCAO DO ITINERARIO*/
                        aux = conditionFlightTop;
                        for(;aux!=NULL;aux = aux->next)
                        {route = buildItinerary(route,aux,NULL,NULL,NULL);}
                        /*PROCURA DAS VIAGENS COM MENOR DISTANCIA E REORDENACAO POR ORDEM DE PARTIDA*/
                        smallest = returnSmallest(route);
                        smallest = reOrder(smallest, argv[5]);
                        /*IMPRESSAO E LIMPEZA DA MEMORIA*/
                        writeItinerary(smallest);
                        freeFlight(topVoo);
                        freeFlight(conditionFlightTop);
                        freeItinerary(route); 
                        freeItinerary(smallest);
                    }
                    else if (strcmp(argv[4], "1") ==0)
                    {
                        /*./rotas2024 partida chegada -L 1 -TC/-TD -D*/
                        /*INICIALIZACAO DAS VARIAVEIS*/
                        ITINERARY *route = startStackItinerary();
                        ITINERARY *smallest = startStackItinerary();
                        AEROPORTOS *topAero = startStackAero();
                        VOOS *topVoo = startStackFlight();
                        VOOS *auxFirstFlight;
                        VOOS *topFirstFlight = startStackFlight();
                        VOOS *topSecondFlight = startStackFlight();
                        VOOS *auxSecondFlight;
                        /*LEITURA DOS FICHEIROS DAS ROTAS E AEROPORTOS*/
                        topAero = readAero(topAero);
                        topVoo = readFlight(topVoo);
                        auxFirstFlight=topVoo;
                        auxSecondFlight=topVoo;
                        /*INICIALIZACAO DAS STACKS AUXILIARES DOS VOOS*/
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
                        /*PROCURA DOS VOOS QUE VERIFIQUEM OS PARAMETROS*/
                        while (auxFirstFlight != NULL)
                        {
                            while (auxSecondFlight != NULL)
                            {
                                if(strcmp(auxFirstFlight->arrival, auxSecondFlight->departure) == 0 && isEarlier(auxFirstFlight->arrivalTime, auxSecondFlight->departTime))
                                {
                                    /*CONSTRUCAO DAS ROTAS QUE VERIFIQUEM OS PARAMETROS*/
                                    route = buildItinerary(route, auxFirstFlight, auxSecondFlight, NULL, topAero);
                                }
                                auxSecondFlight = auxSecondFlight->next;
                            }
                            auxSecondFlight = topSecondFlight;
                            auxFirstFlight = auxFirstFlight->next;   
                        }
                        /*RETORNO DOS ITINERARIOS COM MENOR DISTANCIA E REORDENACAO POR ORDEM DE PARTIDA*/
                        smallest = returnSmallest(route);
                        smallest = reOrder(smallest,argv[5]);
                        /*IMPRESSAO E LIMPEZA DA MEMORIA*/
                        writeItinerary(smallest);
                        freeFlight(topVoo);
                        freeAero(topAero);
                        freeFlight(topFirstFlight);
                        freeFlight(topSecondFlight);
                        freeItinerary(route);
                        freeItinerary(smallest);
                    }
                    else if(strcmp(argv[4],"2") == 0)
                    {
                    /*./rotas2024 partida chegada -L 2 -TC/-TD -D*/
                    /*INICIALIZACAO DAS VARIAVEIS*/
                    ITINERARY *route = startStackItinerary();
                    ITINERARY *smallest = startStackItinerary();
                    AEROPORTOS *topAero = startStackAero();
                    VOOS *topVoo = startStackFlight();
                    VOOS *auxFirstFlight, *auxSecondFlight, *auxThirdFlight;
                    VOOS *topFirstFlight = startStackFlight();
                    VOOS *topSecondFlight = startStackFlight();
                    VOOS *topThirdFlight = startStackFlight();
                    /*LEITURA DOS FICHEIROS*/
                    topAero = readAero(topAero);
                    topVoo = readFlight(topVoo);
                    auxFirstFlight = auxSecondFlight = auxThirdFlight = topVoo;
                    /*INICIALIZACAO DAS STACKS AUXILIARES*/
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
                    /*PROCURA DOS VOOS QUE VERIFIQUEM OS PARAMETROS*/
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
                                        /*CONSTRUCAO DA ROTA*/
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
                    /*PROCURA DOS ITINERARIOS COM A MENOR DISTANCIA REORDENACAO DOS VOOS POR ORDEM DE PARTIDA*/
                    smallest = returnSmallest(route);
                    smallest = reOrder(smallest,argv[5]);
                    /*ESCRITA DO ITINERARIO*/
                    writeItinerary(smallest);
                    /*LIBERTACAO DA MEMORIA*/
                    freeFlight(topVoo);
                    freeAero(topAero);
                    freeFlight(topFirstFlight);
                    freeFlight(topSecondFlight);
                    freeFlight(topThirdFlight);
                    freeItinerary(route);
                    freeItinerary(smallest);   
                    }
                }                   
            }
        }
    }
    else{printf("Inválido");}
return 0;    
}

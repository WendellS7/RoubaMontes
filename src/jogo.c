#include "roubamonte.h"

/*--------------------------------FUNÇÕES DO JOGO--------------------------------*/


MontePlayer *criaMontePlayer(){
    MontePlayer *monte;
    monte = (MontePlayer *)malloc(sizeof(MontePlayer));
    monte->topo = NULL;
    monte->quant = 0;
    return monte;
}

void deletaMontePlayer(ListaPlayer *lp){
    while(lp->inicio != NULL){
        CartaMontePlayer *carta_delete;
        while(lp->inicio->monte->topo != NULL){
            carta_delete = lp->inicio->monte->topo;
            lp->inicio->monte->topo = lp->inicio->monte->topo->anterior;
            free(carta_delete);
        }
        lp->inicio = lp->inicio->prox;
    }
    free(lp);
}

void deletaMonte(MontePlayer *monte) {
    if(monte == NULL){
        return;
    }
    CartaMontePlayer *atual = monte->topo;
    CartaMontePlayer *proximo;
    while(atual != NULL){
        proximo = atual->anterior;
        free(atual);
        atual = proximo;
    }
    monte->topo = NULL;
}

int empilhaCarta(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada){

    printf("A Carta comprada carta e: %d de %d\n", carta_comprada->valor, carta_comprada->naipe);
    vez = vez+1;

    Jogador *atual;
    atual = lista_jogador->inicio;

    if(lista_jogador->inicio == NULL){
        return 0;
    }
    if(atual->monte->topo == NULL){
        return 0;
    }
    int cont =1;
    CartaMontePlayer *carta_nova;
    carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

    while(atual->num_jogador != vez && atual != NULL){
        atual = atual->prox;
    }
    
    if(atual->num_jogador == vez && atual->monte->topo != NULL){

        printf("A carta do topo do monte do jogador %d e: %d de %d\n", atual->num_jogador , atual->monte->topo->carta->valor, atual->monte->topo->carta->naipe);

        if(atual->monte->topo->carta->valor == carta_comprada->valor){

            carta_nova->carta = carta_comprada;
            carta_nova->anterior = atual->monte->topo;

            atual->monte->topo = carta_nova;
            atual->monte->quant ++;

            printf("A carta esta em seu monte agora.\n");

            printf("A quantidade de cartas no monte do jogador %d e: %d",atual->num_jogador ,atual->monte->quant);

            return 1;
        }
    }else{
        return 0;
    }
    return 0;
}

int empilhaDescarte(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada, Carta *carta_descarte) {

    vez = vez+1;

    printf("A Carta comprada e: %d de %d\n", carta_comprada->valor, carta_comprada->naipe);
    if(carta_descarte != NULL){
        printf("A Carta do descarte e: %d de %d\n", carta_descarte->valor, carta_descarte->naipe);
    }

    if(carta_descarte != NULL){
        Jogador *atual;
        atual = lista_jogador->inicio;

        if(atual->monte->topo == NULL){
            CartaMontePlayer *carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
            carta_nova->carta = carta_descarte;
            carta_nova->anterior = atual->monte->topo;
            atual->monte->topo = carta_nova;
            atual->monte->quant++;

            // Criação e empilhamento da carta comprada
            CartaMontePlayer *carta_nova2 = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
            carta_nova2->carta = carta_comprada;
            carta_nova2->anterior = carta_nova; // Agora a segunda carta é empilhada sobre a primeira
            atual->monte->topo = carta_nova2;
            atual->monte->quant++;

            printf("Ambas agora estao em meu monte.\n");
            printf("A quantidade de cartas no meu monte e: %d\n", atual->monte->quant);

            return 1;
        }

        while (atual->num_jogador != vez && atual->prox != NULL) {
            atual = atual->prox;
        }

        if (atual->num_jogador == vez) {
            // Criação e empilhamento da carta do descarte
            CartaMontePlayer *carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
            carta_nova->carta = carta_descarte;
            carta_nova->anterior = atual->monte->topo;
            atual->monte->topo = carta_nova;
            atual->monte->quant++;

            // Criação e empilhamento da carta comprada
            CartaMontePlayer *carta_nova2 = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
            carta_nova2->carta = carta_comprada;
            carta_nova2->anterior = carta_nova; // Agora a segunda carta é empilhada sobre a primeira
            atual->monte->topo = carta_nova2;
            atual->monte->quant++;

            printf("Ambas agora estão em meu monte.\n");
            printf("A quantidade de cartas no seu monte é: %d\n", atual->monte->quant);

            return 1;
        }
    }

    return 0;
}


int verificaCartaTopo(Jogador *atual,Carta *carta_comprada){

    if(atual->monte->topo == NULL){
        return 0;
    }
    if(atual->monte->topo->carta->valor == carta_comprada->valor){
        return 1;
    }else{
        return 0;
    }

    return 0;
}


int verificaTopoMonte(ListaPlayer *lista_jogador,Carta *carta_comprada,int vez){

    Jogador *atual;
    atual = lista_jogador->inicio;
    int cont = 0, ver = 0;
    vez = vez+1;

    printf("A carta comprada e: %d de %d\n",  carta_comprada->valor, carta_comprada->naipe);

    if(lista_jogador->inicio == NULL){
        return 0;
    }

    while(atual->num_jogador != vez && atual->prox != NULL){
        atual = atual->prox;
    }

    //chama a função de verificar topo
    //se retornou 1 , rouba o monte
    MontePlayer *monte_da_vez;
    monte_da_vez = (MontePlayer *)malloc(sizeof(MontePlayer));
    MontePlayer *monte_saida;
    monte_saida = (MontePlayer *)malloc(sizeof(MontePlayer));

    if(atual->num_jogador == vez){
        monte_da_vez = atual->monte;
    }

    Jogador *aux2 = lista_jogador->inicio;

    while(aux2 != NULL){

        if(aux2->num_jogador != vez){

            ver = verificaCartaTopo(aux2, carta_comprada);

            if(ver == 1){
                monte_saida = aux2->monte;

                ver = roubaMonte(monte_da_vez, monte_saida, carta_comprada);

                if(ver == 1){
                    return 1;
                }else{
                    return 0;
                }
            }
        }
        aux2 = aux2->prox;
    }

    return 0;
}

int roubaMonte(MontePlayer *monte_destino, MontePlayer *monte_saida, Carta *carta_comprada){

    // DESEMPILHA PRA UMA PILHA AUX

    int saida = monte_saida->quant;

    MontePlayer *monte_aux;
    monte_aux = criaMontePlayer();

    while(monte_saida->topo != NULL){

        CartaMontePlayer *aux;
        CartaMontePlayer *novo;
        novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

        novo->carta = monte_saida->topo->carta;

        if(monte_aux->topo == NULL){
            novo->anterior = NULL;
        }else{
            novo->anterior = monte_aux->topo;
            monte_aux->topo = novo;
        }

        aux = monte_saida->topo;

        monte_saida->topo = monte_saida->topo->anterior;

        monte_saida->quant --;

        free(aux);
    };

    while(monte_aux->topo != NULL){

        CartaMontePlayer *aux;
        CartaMontePlayer *novo;
        novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

        novo->carta = monte_aux->topo->carta;

        if(monte_destino->topo == NULL){
            novo->anterior = NULL;
        }else{
            novo->anterior = monte_destino->topo;
            monte_destino->topo = novo;
        }
        aux = monte_aux->topo;
        monte_aux->topo = monte_aux->topo->anterior;
        monte_destino->quant++;
        
        monte_aux->quant --;

        free(aux);
    };

    // COLOCA A CARTA COMPRADA NO TOPO

    CartaMontePlayer *novo;
    novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

    novo->carta = carta_comprada;
    novo->anterior = monte_destino->topo;
    monte_destino->topo = novo;
    printf("\nA quantidade de cartas no monte ANTES e: %d , saida = %d, + 1 comprada\n",monte_destino->quant, saida);
    monte_destino->quant ++;
    monte_destino->quant = monte_destino->quant + saida;
    printf("\nA quantidade de cartas no monte DEPOIS e: %d\n",monte_destino->quant);

    return 1;
}


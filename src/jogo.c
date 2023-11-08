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

int empilhaCarta(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada){

    printf("A Carta comprada e: %d de %d\n", carta_comprada->valor, carta_comprada->naipe);

    Jogador *atual;
    atual = lista_jogador->inicio;

    if(lista_jogador->inicio == NULL){
        return 0;
    }
    if(atual->monte->topo == NULL){
        return 0;
    }

    CartaMontePlayer *carta_nova;
    carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

    while(atual->quant_jogador != vez && atual->prox != NULL){
        printf("A carta do topo do monte do jogador %d e: %d de %d\n", atual->quant_jogador+1 , atual->monte->topo->carta->valor, atual->monte->topo->carta->naipe);
        atual = atual->prox;
    } 
    if(atual->quant_jogador == vez){

        if(atual->monte->topo->carta->valor == carta_comprada->valor){

            carta_nova->carta = carta_comprada;
            carta_nova->anterior = atual->monte->topo;

            atual->monte->topo = carta_nova;
            atual->monte->quant ++;

            printf("A carta esta em seu monte agora.\n");

            return 1;
        }
    }else{
        return 0;
    }
    return 0;
}

int empilhaDescarte(ListaPlayer *lista_jogador, int vez, Carta *carta_comprada, Carta *carta_descarte){

    printf("A Carta comprada e: %d de %d\n", carta_comprada->valor, carta_comprada->naipe);
    printf("A Carta do descarte e: %d de %d\n", carta_descarte->valor, carta_descarte->naipe);

    Jogador *atual;
    atual = lista_jogador->inicio;

    if(lista_jogador->inicio == NULL){
        return 0;
    }
    if(atual->monte->topo == NULL){
        return 0;
    }
    
    CartaMontePlayer *carta_nova;
    carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

    while(atual->quant_jogador != vez && atual->prox != NULL){
        atual = atual->prox;
    }
    if(atual->quant_jogador == vez){

        for(int i=0; i<2; i++){

            if(i==0){
                carta_nova->carta = carta_descarte;
            }else{
                carta_nova->carta = carta_comprada;
            }
            carta_nova->anterior = atual->monte->topo;
            atual->monte->topo = carta_nova;
            atual->monte->quant++;
        }
        printf("Ambas agora estao em meu monte.");
        return 1;
    }
    return 0;
}

int verificaTopoMonte(ListaPlayer *lista_jogador,Carta *carta_comprada,int vez){

    Jogador *atual;
    atual = lista_jogador->inicio;

    printf("entrou topo dos montes pra roubar\n");
    printf("A carta comprada e: %d de %d\n",  carta_comprada->valor, carta_comprada->naipe);

    if(lista_jogador->inicio == NULL){
        return 0;
    }
    if(atual->monte->topo == NULL){
        return 0;
    }

    while(atual->quant_jogador != vez && atual->prox != NULL){
        atual = atual->prox;
    }
    if(atual->quant_jogador == vez){

        MontePlayer *monte_da_vez = atual->monte;
        Jogador *jog_atual;
        MontePlayer *monte_saida;
        jog_atual = lista_jogador->inicio;

        while(jog_atual->prox != NULL){

            if(jog_atual->monte->topo->carta->valor == monte_da_vez->topo->carta->valor){

                monte_saida = jog_atual->monte;

                roubaMonte(monte_da_vez, monte_saida, carta_comprada);

                printf("Roubou\n");

                return 1;
            }
            
            jog_atual = jog_atual->prox;
        }
    }
    return 0;
}

int roubaMonte(MontePlayer *monte_destino, MontePlayer *monte_saida, Carta *carta_comprada){

    // DESEMPILHA PRA UMA PILHA AUX

    CartaMontePlayer *aux;

    while(monte_saida->topo != NULL){
        CartaMontePlayer *novo;
        novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

        novo->carta = monte_saida->topo->carta;
        novo->anterior = aux;
        aux = novo;

        free(monte_saida->topo);

        monte_saida->topo = monte_saida->topo->anterior;

        monte_saida->quant --;
    };

    // DESMPILHA AUX PARA A PILHA DO JOGADOR QUE ROUBOU

    while(aux != NULL){
        CartaMontePlayer *novo;
        novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

        novo->carta = aux->carta;
        novo->anterior = monte_destino->topo;
        monte_destino->topo = novo;

        CartaMontePlayer *temp = aux;

        aux = aux->anterior;
        free(temp);
        monte_destino->quant ++;
    };

    // COLOCA A CARTA COMPRADA NO TOPO

    CartaMontePlayer *novo;
    novo = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

    novo->carta = carta_comprada;
    novo->anterior = monte_destino->topo;
    monte_destino->topo = novo;
    monte_destino->quant ++;

    return 1;
}
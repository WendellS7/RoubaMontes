#include "roubamonte.h"

/*--------------------------------FUNÇÕES DO MONTE DE COMPRAS--------------------------------*/
//INICIO

MonteBaralho *criaMonteCompra(int quant_jog){

    MonteBaralho *monte_baralho;
    monte_baralho = (MonteBaralho *)malloc(sizeof(MonteBaralho));
    monte_baralho->topo = NULL;

    int repeat = 0;

    while(quant_jog >= 2 && repeat < 2){
        for(int j=0;j<4;j++){
            for(int k=0;k<13;k++){
                CartaMonteBaralho *carta_baralho;
                carta_baralho = (CartaMonteBaralho *)malloc(sizeof(CartaMonteBaralho));

                carta_baralho->carta = (Carta *)malloc(sizeof(Carta)); 

                carta_baralho->carta->valor = k+1;
                carta_baralho->carta->naipe = j+1;
                carta_baralho->anterior = monte_baralho->topo;

                monte_baralho->topo = carta_baralho;
            }
        }
        repeat++;
    };
    return monte_baralho;
}

void embaralha(MonteBaralho *monte_compra){

    srand(time(NULL));

    int tamanho = 0;
    CartaMonteBaralho *carta_atual = monte_compra->topo;

    while (carta_atual != NULL) {
        tamanho++;
        carta_atual = carta_atual->anterior;
    }

    // Embaralha as cartas usando o algoritmo de Fisher-Yates
    carta_atual = monte_compra->topo;

    for (int i = tamanho - 1; i > 0; i--) {

        int j = rand() % (i + 1);

        Carta *temp = carta_atual->carta;
        CartaMonteBaralho *carta_j = monte_compra->topo;
        for (int k = 0; k < j; k++) {
            carta_j = carta_j->anterior;
        }
        carta_atual->carta = carta_j->carta;
        carta_j->carta = temp;

        carta_atual = carta_atual->anterior;
    }
}

Carta *compra(MonteBaralho *monte_compra){

    Carta *carta;
    carta = (Carta *)malloc(sizeof(Carta));
    CartaMonteBaralho *aux;
    aux = monte_compra->topo;

    carta = monte_compra->topo->carta;
    monte_compra ->topo = monte_compra->topo->anterior;
    free(aux);

    return carta;
}

void deletaMonteBaralho(MonteBaralho *monte_compra){
    free(monte_compra);
}

//FIM
/*--------------------------------FUNÇÕES DO MONTE DO JOGADOR 1--------------------------------*/
//INICIO

MontePlayer *criaMontePlayer(){
    MontePlayer *monte;
    monte = (MontePlayer *)malloc(sizeof(MontePlayer));
    monte->topo = NULL;
    monte->quant = 0;
    return monte;
}

void deletaMontePlayerConteudo(MontePlayer *monte){
    if(monte != NULL){
        CartaMontePlayer *carta_delete;
        while(monte->topo != NULL){
            carta_delete = monte->topo;
            monte->topo = monte->topo->anterior;
            free(carta_delete);
        }
    }
}

void deletaMontePlayerStruct(MontePlayer *monte){
    free(monte);
}

int empilhaCarta(MontePlayer *monte, Carta *carta){

    printf("A Carta comprada e: %d de %d\n", carta->valor, carta->naipe);
    printf("A carta do topo do seu monte e: %d de %d\n", monte->topo->carta->valor, monte->topo->carta->naipe);

    if(monte->topo->carta == carta){
        CartaMontePlayer *carta_nova;
        carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));

        carta_nova->carta = carta;
        carta_nova->anterior = monte->topo;

        monte->topo = carta_nova;
        monte->quant ++;

        printf("A carta esta em seu monte agora.\n");

        return 1;
    }else{
        return 0;
    }
}

int empilhaDescarte(MontePlayer *monte, Carta *carta_comprada, Carta *carta_descarte){

    printf("A Carta comprada e: %d de %d\n", carta_comprada->valor, carta_comprada->naipe);
    printf("A Carta do descarte e: %d de %d\n", carta_descarte->valor, carta_descarte->naipe);

    for(int i=0; i<2; i++){
        CartaMontePlayer *carta_nova;
        carta_nova = (CartaMontePlayer *)malloc(sizeof(CartaMontePlayer));
        if(i==0){
            carta_nova->carta = carta_descarte;
        }else{
            carta_nova->carta = carta_comprada;
        }
        carta_nova->anterior = monte->topo;
        monte->topo = carta_nova;
        monte->quant++;
    }
    printf("Ambas agora estao em meu monte.");
    return 1;
}

int verificaTopoMonte(MontePlayer *monte_p1, MontePlayer *monte_p2, MontePlayer *monte_p3, MontePlayer *monte_p4, Carta *carta_comprada, int vez, int quant_jog){

    int ver = 0;
    printf("entrou topo dos montes pra roubar\n");
    printf("A carta comprada e: %d de %d\n",  carta_comprada->valor, carta_comprada->naipe);

    if((carta_comprada->valor == monte_p1->topo->carta->valor) && (vez != 1)){

        printf("entrou rouba monte do 1\n");

        printf("O topo do monte do jogador 1 e:  %d de %d\n", monte_p1->topo->carta->valor, monte_p1->topo->carta->naipe);

        if(vez == 2){
            ver = roubaMonte(monte_p2, monte_p1, carta_comprada);
            printf("Monte do jogador 1 roubado. O topo do seu monte agora e %d de %d\n", monte_p2->topo->carta->valor, monte_p2->topo->carta->naipe);
        }else if(vez == 3){
            ver = roubaMonte(monte_p3, monte_p1, carta_comprada);
            printf("Monte do jogador 1 roubado. O topo do seu monte agora e %d de %d\n", monte_p3->topo->carta->valor, monte_p3->topo->carta->naipe);
        }else if(vez == 4){
            ver = roubaMonte(monte_p4, monte_p1, carta_comprada);
            printf("Monte do jogador 1 roubado. O topo do seu monte agora e %d de %d\n", monte_p4->topo->carta->valor, monte_p4->topo->carta->naipe);
        }
    }else if((carta_comprada->valor == monte_p2->topo->carta->valor) && (vez != 2)){

        printf("entrou rouba monte do 2\n");

        printf("O topo do monte do jogador 2 e:  %d de %d\n", monte_p2->topo->carta->valor, monte_p2->topo->carta->naipe);

        if(vez == 1){
            ver = roubaMonte(monte_p1, monte_p2, carta_comprada);
            printf("Monte do jogador 2 roubado. O topo do seu monte agora e %d de %d\n", monte_p1->topo->carta->valor, monte_p1->topo->carta->naipe);
        }else if(vez == 3){
            ver = roubaMonte(monte_p3, monte_p2, carta_comprada);
            printf("Monte do jogador 2 roubado. O topo do seu monte agora e %d de %d\n", monte_p3->topo->carta->valor, monte_p3->topo->carta->naipe);
        }else if(vez == 4){
            ver = roubaMonte(monte_p4, monte_p2, carta_comprada);
            printf("Monte do jogador 2 roubado. O topo do seu monte agora e %d de %d\n", monte_p4->topo->carta->valor, monte_p4->topo->carta->naipe);
        }
    }else if((quant_jog >= 3) && (carta_comprada->valor == monte_p3->topo->carta->valor) && (vez != 3)){

        printf("entrou rouba monte do 3\n");

        printf("O topo do monte do jogador 3 e:  %d de %d\n", monte_p3->topo->carta->valor, monte_p3->topo->carta->naipe);
        
        if(vez == 1){
            ver = roubaMonte(monte_p1, monte_p3, carta_comprada);
            printf("Monte do jogador 3 roubado. O topo do seu monte agora e %d de %d\n", monte_p1->topo->carta->valor, monte_p1->topo->carta->naipe);
        }else if(vez == 2){
            ver = roubaMonte(monte_p2, monte_p3, carta_comprada);
            printf("Monte do jogador 3 roubado. O topo do seu monte agora e %d de %d\n", monte_p2->topo->carta->valor, monte_p2->topo->carta->naipe);
        }else if(vez == 4){
            ver = roubaMonte(monte_p4, monte_p3, carta_comprada);
            printf("Monte do jogador 3 roubado. O topo do seu monte agora e %d de %d\n", monte_p4->topo->carta->valor, monte_p4->topo->carta->naipe);
        }
    }else if((quant_jog == 4) && (carta_comprada->valor == monte_p4->topo->carta->valor && vez != 4)){

        printf("entrou rouba monte do 4\n");

        printf("O topo do monte do jogador 4 e:  %d de %d\n", monte_p4->topo->carta->valor, monte_p4->topo->carta->naipe);

        if(vez == 1){
            ver = roubaMonte(monte_p1, monte_p4, carta_comprada);
            printf("Monte do jogador 4 roubado. O topo do seu monte agora e %d de %d\n", monte_p1->topo->carta->valor, monte_p1->topo->carta->naipe);
        }else if(vez == 2){
            ver = roubaMonte(monte_p2, monte_p4, carta_comprada);
            printf("Monte do jogador 4 roubado. O topo do seu monte agora e %d de %d\n", monte_p2->topo->carta->valor, monte_p2->topo->carta->naipe);
        }else if(vez == 3){
            ver = roubaMonte(monte_p3, monte_p4, carta_comprada);
            printf("Monte do jogador 4 roubado. O topo do seu monte agora e %d de %d\n", monte_p3->topo->carta->valor, monte_p3->topo->carta->naipe);
        }
    }else{
        printf("nao entrou em nenhum\n");
    }
    
    if(ver == 1){
        printf("\nroubado\n");
        return 1;
    }else{
        printf("\nsem estar roubado\n");
        return 0;
    }
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

/*--------------------------------FUNÇÕES DO DESCARTE--------------------------------*/


Descarte *criaDescarte(){
    Descarte *descarte;
    descarte = (Descarte *)malloc(sizeof(Descarte));
    if(descarte != NULL){
        descarte->inicio = NULL;
    }
    return descarte;
}

void deletaDescarte(Descarte *descarte){
    while(descarte->inicio != NULL){
        CartaDescarte *aux;
        aux = descarte->inicio;
        descarte->inicio = descarte->inicio->prox;
        free(aux);
    }
    free(descarte);
}

void descartaCarta(Descarte *descarte, Carta *carta){ // INSERÇÃO NO INICIO O(1)
    CartaDescarte *carta_descarte;
    carta_descarte = (CartaDescarte *)malloc(sizeof(CartaDescarte));

    carta_descarte->carta = carta;
    carta_descarte->prox = descarte->inicio;
    descarte->inicio = carta_descarte;
}

Carta *RetiraCarta(Descarte *descarte, Carta *carta_comprada){

    printf("entrou retiracartas\n");
    CartaDescarte *atual, *anterior, *retorno = NULL;
    atual = descarte->inicio;

    while(atual->carta->valor != carta_comprada->valor){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual != NULL && atual->carta->valor == carta_comprada->valor){
        if(atual == descarte->inicio){
            descarte->inicio = atual->prox;
        }else{
            anterior->prox = atual->prox;
        }
        retorno = atual;
        free(atual);
    }

    printf("saiu\n");
    return (retorno != NULL) ? retorno->carta : NULL;
}


/*--------------------------------FUNÇÕES DA VITORIA--------------------------------*/

ListaPlayer *criaListaJogadores(){
    ListaPlayer *lp;
    lp = (ListaPlayer *)malloc(sizeof(ListaPlayer));
    if(lp != NULL){
        lp->inicio = NULL;
    }
    return lp;
}

ListaPlayer *verificaVencedor(ListaPlayer *player, MontePlayer *monte_p1, MontePlayer *monte_p2, MontePlayer *monte_p3, MontePlayer *monte_p4){

    ListaPlayer *vencedores;
    vencedores = (ListaPlayer *)malloc(sizeof(ListaPlayer));

    vencedores->inicio = NULL;

    Jogador *atual;
    atual = player->inicio;
    Jogador *mai = atual;

    while(atual != NULL){

        if(atual->quant_jogador == 1){
            atual->quant_carta = monte_p1->quant;
        }
        if(atual->quant_jogador == 2){
            atual->quant_carta = monte_p2->quant;
        }
        if(atual->quant_jogador == 3){
            atual->quant_carta = monte_p3->quant;
        }
        if(atual->quant_jogador == 4){
            atual->quant_carta = monte_p4->quant;
        }

        atual = atual->prox;
    }

    atual = player->inicio;

    while(atual != NULL){
        if(atual->quant_carta == mai->quant_carta){
            
            Jogador* novo_vencedor = (Jogador*)malloc(sizeof(Jogador));// Adicione o jogador a lista de vencedores
            novo_vencedor->quant_jogador = atual->quant_jogador;
            novo_vencedor->quant_carta = atual->quant_carta;
            novo_vencedor->prox = vencedores->inicio;
            vencedores->inicio = novo_vencedor;
        }
        atual = atual->prox;
    }

    return vencedores;
}

ListaVencedor *criaListaVencedor(){
    ListaVencedor *lv;
    lv = (ListaVencedor *)malloc(sizeof(ListaVencedor));
    if(lv != NULL){
        lv->inicio = NULL;
        return lv;
    }
    return lv;    
}

void copiaCartasVencedor(ListaVencedor *lista_vencedor, MontePlayer *monte_vencedor){

    // PASSAR TODA A PILHA DO MONTE VENCEDOR PARA A LISTA = LISTAVENCEDOR;
    // PASSANDO PRO INICIO DA LISTA O(1)

    while(monte_vencedor->topo != NULL){
        CartaListaVencedor *novo_vencedor;
        novo_vencedor = (CartaListaVencedor *)malloc(sizeof(CartaListaVencedor));

        novo_vencedor->carta = monte_vencedor->topo->carta;
        monte_vencedor->topo = monte_vencedor->topo->anterior;

        if(lista_vencedor->inicio == NULL){
            lista_vencedor->inicio = novo_vencedor;
        }else{
            novo_vencedor->prox = lista_vencedor->inicio;
            lista_vencedor->inicio = novo_vencedor;
        }
    }
}

// ALGORITMO BUBBLE SORT - ORDENAÇÃO DE CARTA

void trocarCarta(Carta *a, Carta *b){
    Carta temp = *a;
    *a = *b;
    *b = temp;
}

void ordenaCartas(ListaVencedor *lista_vencedor){

    int trocado;
    CartaListaVencedor *ptr1;
    CartaListaVencedor *lptr = NULL;

    // Verifica se a lista está vazia
    if (lista_vencedor->inicio == NULL){
        return;
    }

    do{
        trocado = 0;
        ptr1 = lista_vencedor->inicio;

        while (ptr1->prox != lptr) {
            // Compara os valores das cartas
            if(ptr1->carta->valor > ptr1->prox->carta->valor){
                trocarCarta(ptr1->carta, ptr1->prox->carta);
                trocado = 1;
            }
            // Se os valores são iguais, compara os naipes
            else if (ptr1->carta->valor == ptr1->prox->carta->valor && ptr1->carta->naipe > ptr1->prox->carta->naipe){
                trocarCarta(ptr1->carta, ptr1->prox->carta);
                trocado = 1;
            }

            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    }while(trocado);
}

// IMPRIMINDO A LISTA DE CARTAS

void imprimirLista(ListaVencedor *lista){
    CartaListaVencedor *atual = lista->inicio;
    while(atual != NULL){
        printf("Valor: %d, Naipe: %d\n", atual->carta->valor, atual->carta->naipe);
        atual = atual->prox;
    }
}

// ALGORITMO BUBBLE SORT - ORDENAÇÃO DE JOGADOR

void trocarJogador(Jogador *a, Jogador *b){
    Jogador temp = *a;
    *a = *b;
    *b = temp;
}

void ordenarListaJogadores(ListaPlayer *lista){
    int trocado;
    Jogador *ptr1;
    Jogador *lptr = NULL;

    if (lista->inicio == NULL)
        return;
    do{
        trocado = 0;
        ptr1 = lista->inicio;

        while (ptr1->prox != lptr) {
            // Compara as quantidades de cartas dos jogadores
            if (ptr1->quant_carta > ptr1->prox->quant_carta) {
                trocarJogador(ptr1, ptr1->prox);
                trocado = 1;
            }
            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    }while(trocado);
}

// IMPRIMINDO O RANKING DE JOGADORES

void imprimirRanking(ListaPlayer *lista){
    Jogador *atual = lista->inicio;
    while (atual != NULL) {
        printf("Nome: %s, Quantidade de Cartas: %d\n", atual->nome, atual->quant_carta);
        atual = atual->prox;
    }
}

// FIM DAS FUNÇOES
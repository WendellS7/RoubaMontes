#include "roubamonte.h"

int main(){

    int quant_jog, ver_tm, ver_ec, cont_rodadas = 0, ver_dc;

    printf("BEM VINDO AO JOGO ROUBA-MONTES\n\n");

    printf("Insira quantos jogadores irao jogar: ");
    scanf("%d",&quant_jog);
    if(quant_jog < 2 || quant_jog > 4){
        printf("A quantidade de jogadores deve ser 2, 3 ou 4");
    }
    
    ListaPlayer *lista_jogador;
    lista_jogador = criaListaJogadores();

    listaJogadores(lista_jogador, quant_jog);

    MonteBaralho *monte_baralho;
    monte_baralho = criaMonteCompra(quant_jog);

    embaralha(monte_baralho);

    Carta *carta_comprada;
    carta_comprada = (Carta *)malloc(sizeof(Carta));

    Descarte *descarte;
    descarte = criaDescarte();

    for(int vez = 0; vez < quant_jog; vez++){

        carta_comprada = NULL;
        cont_rodadas++;
        
        printf("\n---------------------------------------\n");
        printf("\nRodada %d - ", cont_rodadas);

        printf("Vez do jogador %d\n",vez+1);

        carta_comprada = compra(monte_baralho); // compra uma carta

        if(carta_comprada != NULL){ // se a carta comprada for valida
            ver_tm = verificaTopoMonte(lista_jogador,carta_comprada,vez); // verifica o topo dos outros montes
            if(ver_tm == 1){ // se tem igual , rouba
                printf("\n\nMonte Roubado\n\n");
                vez--; // repete a vez
            }else{
                printf("\n\nNao achou uma carta igual a comprada, nos outros montes\n");

                ver_dc = RetiraCarta(lista_jogador, vez, descarte, carta_comprada); // retira uma carta do descarte, caso for igual

                if(ver_dc == 1){ // tinha no descarte igual
                    printf("Carta do descarte e comprada, no seu monte\n");
                    vez--;
                }else{ // nao tinha no descarte uma carta igual a comprada
                    printf("Nenhuma carta no descarte com o mesmo valor\n\n");
                    ver_ec = empilhaCarta(lista_jogador, vez, carta_comprada); // empilha a carta no meu monte se o topo for igual
                    if(ver_ec == 1){ // a carta e igual a do topo do meu monte
                        printf("\n\nCarta comprada no seu monte\n\n");
                        vez--;
                    }else{
                        descartaCarta(descarte, carta_comprada); // descarta a carta 
                        printf("Carta descartada\n\n");
                    }
                }
            }
        }else{

            Jogador *venceu;
            venceu = verificaVencedor(lista_jogador);

            printf("Ganhador: %d\nQuantidade de cartas %d\n",venceu->num_jogador, venceu->quant_carta);

            deletaMonteBaralho(monte_baralho);
            deletaDescarte(descarte);
            deletaMontePlayer(lista_jogador);

            printf("\nFIM DE JOGO - TESTE\n\n");
            break;
        }
        if(vez == quant_jog-1){
            vez = -1;
        }
    }    

    return 0;
}
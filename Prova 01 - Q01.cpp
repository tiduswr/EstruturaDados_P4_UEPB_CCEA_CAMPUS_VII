#include <iostream>

using namespace std;

struct Jogador {
    string nome;
    Jogador *prox;
};


struct Time {
    string nome;
    Jogador *elenco;
    Time *prox;
};

Time* init(){
    return NULL;
}

void newTime(Time*& list, string nome){
    if(list == NULL){
        list = new Time;
        list->nome = nome;
        list->elenco = NULL;
        list->prox = NULL;
    }else{
        Time* aux = list;

        while(aux->prox != NULL){
            aux = aux->prox;
        }
        Time* aux2 = new Time;
        aux2->nome = nome;
        aux2->elenco = NULL;
        aux2->prox = NULL;
        aux->prox = aux2;

    }
}

bool newJogador(Time*& list, string nomeJogador){
    if(list->elenco == NULL){
        Jogador* aux = new Jogador;

        aux->nome = nomeJogador;
        aux->prox = NULL;
        list->elenco = aux;

    }else{
        Jogador* aux = list->elenco;

        while(aux->prox != NULL){
            aux = aux->prox;
        }
        Jogador* aux2 = new Jogador;
        aux2->nome = nomeJogador;
        aux2->prox = NULL;
        aux->prox = aux2;
    }
}

Time* getTime(Time* list, string nome){
    while(list != NULL && nome.compare(list->nome) != 0){
        list = list->prox;
    }
    return list;
}

int contarJogadores(Time* list){
    Jogador* aux = list->elenco;
    int i{};

    while(aux != NULL){
        i++;
        aux = aux->prox;
    }

    return i;

}

string maiorNumeroJogadores(Time* list){
    Time* maior = list;
    
    while(list != NULL){
        if(contarJogadores(list) > contarJogadores(maior)) maior = list;
        list = list->prox;
    }

    if(maior != NULL){
        return maior->nome;
    }else{
        return "";
    }

}

int main(){

    Time* l = init();
    newTime(l, "Barcelona");
    newTime(l, "Flamengo");

    Time* barcelona = getTime(l, "Barcelona");
    Time* flamengo = getTime(l, "Flamengo");

    newJogador(barcelona, "Messi");
    newJogador(barcelona, "Neymar");
    newJogador(barcelona, "CR7");

    newJogador(flamengo, "Gabi Gol");
    newJogador(flamengo, "Ribamar");
    newJogador(flamengo, "Adriano Imperador");
    newJogador(flamengo, "Outro Jogador Qualquer");

    cout << "Time com maior quantidade de Jogadores: " << endl << endl << maiorNumeroJogadores(l) << "-> " << contarJogadores(flamengo);
    cout << endl << endl;
    return 0;
}
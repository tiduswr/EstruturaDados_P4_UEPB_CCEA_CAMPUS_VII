/*  Proprietario: Harllem Nascimento
    Data: 15/08/2021
    Curso: Ciências da Computação - UEPB Campus CCEA VII - Periodo 04
    Disciplina: Estruturas de Dados - Ricardo
*/
#include <iostream>

using namespace std;
int const LIST_INIT_INDEX = 1;

struct  node{
    int dado;
    node* prox;
};

node* init(){
    return NULL;
}

void insertFirst(node*&list, int info){
    node* novo = new node;
    novo->dado = info;
    novo->prox = list;

    list = novo;
}

void insertLast(node*&list, int info){
    node* novo = new node;
    novo->dado = info;
    novo->prox = NULL;

    if(list == NULL){
        list = novo;
    }else{
        node* i = list;
        while(i->prox != NULL){
            i = i->prox;
        }
        i->prox = novo;
    }
}

void printList(node* list){
    if(list != NULL) cout << "{";
    while(list != NULL){

        cout << list->dado;

        list = list->prox;
        if(list == NULL){
            cout << "}" << endl;
        }else{
            cout << ", ";
        }
    }
}

int listLenght(node* list){
    int l{};

    while(list != NULL){
        l++;
        list = list->prox;
    }

    return l;
}

bool insertIn(node*&list, int info, int pos){
    int const LIST_LENGHT = listLenght(list);

    if(pos > LIST_LENGHT + 1){
        return false;
    }else{
        if(pos == LIST_INIT_INDEX){
            insertFirst(list, info);
        }else if(pos == LIST_LENGHT + 1){
            insertLast(list, info);
        }else{
            int i = LIST_INIT_INDEX;
            node* aux = list;

            node* novo = new node;
            novo->dado = info;

            while(i < pos - 1){
                aux = aux->prox;
                i++;
            }
            novo->prox = aux->prox;
            aux->prox = novo;
        }
        return true;
    }
}

bool removeNode(node*& list, int pos){
    int const LIST_LENGHT = listLenght(list);

    if(pos > LIST_LENGHT){
        return false;
    }else{
        if(pos == LIST_INIT_INDEX){
            //Inicio da Lista

           node* aux = list;
           list = list->prox;
           aux->prox = NULL;
           delete aux; 
        }else if(pos == LIST_LENGHT){
            //Fim da lista

            node* before = list;
            node* aux = list;

            while(aux->prox != NULL){
                before = aux;
                aux = aux->prox;
            }

            before->prox = NULL;
            delete aux;
        }else{
            //Meio da Lista

            int i = LIST_INIT_INDEX;
            node* before;
            node* aux = list;

            while(i < pos){
                before = aux;
                aux = aux->prox;
                i++;
            }

            before->prox = aux->prox;
            delete aux;
        }
        return true;
    }
}
bool concatList(node*& list1, node*& list2){
    if(list1 != NULL){
        if(list2 == NULL){
            return false;
        }
        node* aux = list1;
        
        while(aux->prox != NULL){
            aux = aux->prox;
        }

        aux->prox = list2;
        list2 = NULL;
        return true;
    }
    return false;
}

int elementPosition(node* list, int info){
    int l{};

    while(list != NULL){
        l++;
        if(list->dado == info) return l;
        list = list->prox;
    }

    return -1;
}

void removeAllMatchValues(node*& list, int info){
    int itemPosition = elementPosition(list, info);

    while(itemPosition != -1){
        removeNode(list, itemPosition);

        itemPosition = elementPosition(list, info);
    }

}

/*Ativiade 01
Faça uma função que receba duas listas encadeadas. Essa função deve verificar se as listas 
possuem o mesmo tamanho e, em caso positivo, intercalar os seus elementos, fazendo com que 
a primeira lista possua todos os elementos ao fim do processo, enquanto a segunda lista 
termine vazia. Por intercalar entende-se fazer com que os elementos integrem uma única lista, 
alternando elementos da primeira com a segunda lista.

Gravar um vídeo de no máximo 3 minutos explicando o desenvolvimento da solução. Vídeos que 
estourem o limite de tempo não serão aceitos. Entregas com atraso terão 50% da nota descontada, 
mais 10% por dia excedente de atraso.
*/

int interligarLista(node*& list1, node*& list2){

    /*  Sucesso = 1
        Listas com tamanho incompativel = -1
        Listas Vazias = 0
    */
    const int TAM_LIST[2] = {listLenght(list1), listLenght(list2)};
    node* aux = list1;
    node* aux2 = list2;
    node* proxAux;

    if(TAM_LIST[0] == 0 && TAM_LIST[1] == 0) return 0;
    else if(TAM_LIST[0] == TAM_LIST[1]){
        while(aux2 != NULL){
            proxAux = aux->prox;
            
            aux->prox = aux2;
            aux2 = aux2->prox;
            aux->prox->prox = proxAux;
            aux = proxAux;
        }
        list2 = NULL;
        return 1;
    }
    return -1;
}

int main(){

    node* list1 = init();
    node* list2 = init();

    //Preenchendo primeira lista
    insertFirst(list1, 1);
    insertLast(list1, 2);
    insertLast(list1, 3);
    //Preenchendo segunda lista
    insertLast(list2, 4);
    insertLast(list2, 5);
    insertLast(list2, 6);

    cout << "Lista 01: ";
    printList(list1);

    cout << "Lista 02: ";
    printList(list2);

    cout << endl << "Interligando listas..." << endl << endl;
    int status = interligarLista(list1, list2);
    if(list2 == NULL) cout << "Lista 2: Nula" << endl;
    if(status == 1){
        cout << endl << "As listas foram interligadas!" << endl << "Lista Resultante: ";
        printList(list1);
    }else if(status == -1){
        cout << "As listas possuem tamanhos incompativeis";
    }else{
        cout << "As listas estão vazias!";
    }

    cout << endl;
    return 0;
}

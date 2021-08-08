/*  Proprietario: Harllem Nascimento
    Data: 07/08/2021
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
    cout << "{";
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

// ------------- Exercicio Listas Encadeadas ---------------------------

//Questão 01
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

void questaoUm(){
    node* list1 = init();
    node* list2 = init();

    //Preenchendo primeira lista
    insertFirst(list1, 1);
    insertLast(list1, 2);
    //Preenchendo segunda lista
    insertFirst(list2, 5);
    insertLast(list2, 6);

    cout << "Lista 01: ";
    printList(list1);

    cout << "Lista 02: ";
    printList(list2);

    cout << endl << "Concatenando listas..." << endl << endl;
    bool status = concatList(list1, list2);
    if(list2 == NULL){
        cout << "Lista 2: Nula";
        if(status) cout << endl << "As listas foram concatenadas!" << endl << "Lista Resultante: ";
    }
    printList(list1);
}

//Questão 02
int elementPosition(node* list, int info){
    int l{};

    while(list != NULL){
        l++;
        if(list->dado == info) return l;
        list = list->prox;
    }

    return -1;
}
void questaoDois(){
    node* list1 = init();
    int itemPosition{}, itemBusca{};

    insertFirst(list1, 123);
    insertLast(list1, 421);
    insertLast(list1, 564);
    insertLast(list1, 32);
    insertLast(list1, 44);
    insertLast(list1, 67);
    cout << "Lista Exemplo: ";
    printList(list1);

    cout << "Qual o numero que você quer buscar?" << endl;
    cin >> itemBusca;
    itemPosition = elementPosition(list1, itemBusca);

    if(itemPosition != -1){
        cout << "Posição do item: " << itemPosition;
    }else{
        cout << "Item não encontrado!";
    }
}

//Questao 3
int removeAllMatchValues(node*& list, int info){
    int itemPosition = elementPosition(list, info);

    while(itemPosition != -1){
        removeNode(list, itemPosition);

        itemPosition = elementPosition(list, info);
    }

}
void questaoTres(){
    node* list1 = init();
    int itemBusca{};
    
    insertFirst(list1, 12);
    insertLast(list1, 44);
    insertLast(list1, 11);
    insertLast(list1, 32);
    insertLast(list1, 44);
    insertLast(list1, 12);
    cout << "Lista Inicial: ";
    printList(list1);

    cout << endl << "Qual o numero que você quer deletar?" << endl;
    cin >> itemBusca;

    removeAllMatchValues(list1, itemBusca);

    cout << endl << "Lista Resultante: ";
    printList(list1);
}
//Fim da Lista

int main(){

    int questao{};

    cout << "Qual questão você quer testar?" << endl;
    cin >> questao;
    cout << endl;

    switch(questao){
        case 1: questaoUm(); break;
        case 2: questaoDois(); break;
        case 3: questaoTres(); break;
        default: cout << endl << "Só existem 3 questões numeradas de 1 a 3!"; break;
    }

    cout << endl;
    return 0;
}
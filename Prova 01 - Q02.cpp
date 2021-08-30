# include <iostream>

using namespace std;
int const INIT_LIST_INDEX = 1;

//Structs principais

struct data{
    int inteiro;
};
struct headerInfo{
    string name;
};

struct node{
    data info;
    node* next;
    node* previous;
};
struct headerList{
    node* first;
    node* last;
    headerList* next;
    int tamanho;
    headerInfo properties;
};

//Procedimentos

headerList* init(){
    return NULL;
}

void newList(headerList*& list, headerInfo value){

    if(list == NULL){
        list = new headerList;
        list->first = NULL;
        list->last = NULL;
        list->next = NULL;
        list->tamanho = 0;
        list->properties = value;
    }else{
        headerList* aux = list;

        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = new headerList;
        aux->next->first = NULL;
        aux->next->last = NULL;
        aux->next->next = NULL;
        aux->next->tamanho = 0;
        aux->next->properties = value;
    }
}

int listLenght(headerList* l){
    if(l != NULL) return l->tamanho;
}

//Mude a chave de pesquisa da lista se necessário no método getList
headerList* getList(headerList* list, string name){
    headerList* aux = list;

    while(aux != NULL){
        if(aux->properties.name.compare(name) == 0) break;
        aux = aux->next;
    }
    return aux;
}

bool insertFirst(headerList* l, data value){
    
    if(l == NULL) return false;

    if(l->first == NULL){
        l->first = new node;

        l->first->info = value;
        l->first->next = NULL;
        l->first->previous = NULL;

        l->last = l->first;
        l->tamanho = INIT_LIST_INDEX;
    }else{
        node* aux = new node;

        l->first->previous = aux;
        aux->next = l->first;
        aux->previous = NULL;
        aux->info = value;
        l->first = aux;
        l->tamanho++;
    }
    return true;
}

bool insertLast(headerList* l, data value){
    
    if(l == NULL) return false;

    if(l->first == NULL){
        l->first = new node;

        l->first->info = value;
        l->first->next = NULL;
        l->first->previous = NULL;

        l->last = l->first;
        l->tamanho = INIT_LIST_INDEX;
    }else{
        node* aux = new node;

        l->last->next = aux;
        aux->previous = l->last;
        aux->next = NULL;
        aux->info = value;
        l->last = aux;
        l->tamanho++;
    }
    return true;
}

bool inserInPosition(headerList* list, data value, int position){

    if(list != NULL){
        if(position >= INIT_LIST_INDEX && position <= list->tamanho){
            
            if(position == INIT_LIST_INDEX){
                insertFirst(list, value);
                list->tamanho++;
            }else if(position == list->tamanho){
                insertLast(list, value);
                list->tamanho++;
            }else{
                node* auxL = list->first;
                node* aux = new node;
                int index = INIT_LIST_INDEX;
                aux->info = value;

                while(auxL != NULL && index < position){
                    auxL = auxL->next;
                    index++;
                }

                aux->previous = auxL->previous;
                aux->next = auxL->next;
                auxL->previous->next = aux;
                auxL->previous = aux;
                list->tamanho++;
            }
            return true;
        }
        return false;
    }
    return false;
}

//Altere abaixo as chaves do método getElement() e removeElement() caso a struct data seja alterada
node* getElement(headerList* list, int key){
    node* aux = list->first;

    while(aux != NULL){
        if(aux->info.inteiro == key) break;
        aux = aux->next;
    }
    return aux;
}

bool removeElement(headerList* list, int key){
    node* elm = getElement(list, key);

    if(elm != NULL){
        if(elm->previous == NULL && elm->next == NULL){
            list->first = NULL;
            list->last = NULL;
            delete elm;
        }else if(elm->previous == NULL){
            list->first = elm->next;
            elm->next->previous = NULL;
            delete elm;
        }else if(elm->next == NULL){
            list->last = elm->previous;
            elm->previous->next = NULL;
            delete elm;
        }else{
            elm->previous->next = elm->next;
            elm->next->previous = elm->previous;
            delete elm;
        }
        return true;
    }
    return false;
}

/*Assim como os métodos get, altere tambem os métodos prints caso seja
adicionado mais dados na struct data ou headerInfo
*/

void printList(headerList* list){
    
    if(list != NULL){
        node* aux = list->first;

        if(aux != NULL){
            cout << list->properties.name << ": {";

            while(aux != NULL){

                cout << aux->info.inteiro;

                aux = aux->next;
                if(aux == NULL){
                    cout << "}" << endl;
                }else{
                    cout << ", ";
                }
            }

        }else{
            cout << list->properties.name << ": {NULL}" << endl;
        }

    }
}

void printAllLists(headerList* list){
    while(list != NULL){
        printList(list);
        list = list->next;
    }
}

void printListsInfo(headerList* list){

    while(list != NULL){
        cout << list->properties.name << ": " << endl;
        cout << "    Quantidade de Items:" << list->tamanho << endl;
        list = list->next;
    }
    cout << endl;
}

void clearMemory(headerList*& l){
    while(l != NULL){
        node* aux = l->first;
        while(aux != NULL){
            if(aux->next != NULL){
                aux = aux->next;
                delete aux->previous;
            }else{
                delete aux;
                aux = NULL;
            }
        }
        l = l->next;
    }
}

//!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!

//------------------------------------------------------------------------------------------------------
//Foi utilizado uma estrutura utilizada na atividade em sala como base para uso, a função esta descrita
//abaixo:
//-------------------------------------------------------------------------------------------------------
bool isSorted(headerList* l){
    node* value = l->first;

    while(value->next != NULL){
        if(value->info.inteiro > value->next->info.inteiro){
            return false;
        }
        value = value->next;
    }
    return true;
}

int main(){

    headerList* l = init();
    newList(l, headerInfo{"Lista 01"});

    insertLast(l, data{1});
    insertLast(l, data{2});
    insertLast(l, data{3});
    insertLast(l, data{4});
    insertLast(l, data{5});

    printList(l);
    if(isSorted(l)){
        cout << "-> A Lista esta ordenada!";
    }else{
        cout << "-> A Lista não esta ordenada!";
    }

    clearMemory(l);
    return 0;
}
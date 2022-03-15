# include <iostream>

using namespace std;
int const INIT_LIST_INDEX = 1;
int const INIT_LISTOFLIST_INDEX = 1;

/*
    SOBRE OS TIPOS DE DADOS GENERICOS:

    T = DADOS PARA O NODE DA LISTA
    I = DADOS PARA O CABEÇALHO DA LISTA
    K = CHAVE DE PESQUISA PARA OS NODES DA LISTA
    X = CHAVE DE PESQUISA PARA O CABEÇALHO DA LISTA
*/

//Structs principais
template<typename T, typename K>
struct node{
    T info;
    K searchKey;
    node<T,K>* next;
    node<T,K>* previous;
};
template<typename T, typename I, typename K, typename X>
struct headerList{
    X searchKey;
    node<T,K>* first;
    node<T,K>* last;
    headerList<T,I,K,X>* next;
    headerList<T,I,K,X>* previous;
    int tamanho;
    I properties;
};

//Procedimentos
template<typename T, typename I, typename K, typename X>
void init(headerList<T,I,K,X>*& listHeader){
    listHeader = NULL;
}
template<typename T, typename I, typename K, typename X>
void insertListFirst(headerList<T,I,K,X>*& list, I value, X key){

    if(list == NULL){
        list = new headerList<T,I,K,X>;
        list->first = NULL;
        list->last = NULL;
        list->next = NULL;
        list->previous = NULL;
        list->tamanho = INIT_LISTOFLIST_INDEX;
        list->properties = value;
        list->searchKey = key;
    }else{
        headerList<T,I,K,X>* aux = new headerList<T,I,K,X>;
        aux->first = NULL;
        aux->last = NULL;
        aux->next = list;
        aux->previous = NULL;
        aux->properties = value;
        aux->searchKey = key;
        aux->tamanho = 0;
        list = aux;
    }
}
template<typename T, typename I, typename K, typename X>
void insertListLast(headerList<T,I,K,X>*& list, I value, X key){

    if(list == NULL){
        insertListFirst(list, value, key);
    }else{
        headerList<T,I,K,X>* aux = list;

        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = new headerList<T,I,K,X>;
        aux->next->first = NULL;
        aux->next->last = NULL;
        aux->next->next = NULL;
        aux->next->previous = aux;
        aux->next->tamanho = 0;
        aux->next->properties = value;
        aux->next->searchKey = key;
    }
}
template<typename T, typename I, typename K, typename X>
int listCount(headerList<T,I,K,X>* list){
    headerList<T,I,K,X>* aux = list;
    int i{};

    while(aux != NULL){
        i++;
        aux = aux->next;
    }

    return i;
}
template<typename T, typename I, typename K, typename X>
int listLenght(headerList<T,I,K,X>* l){
    if(l != NULL) return l->tamanho;
    return 0;
}

template<typename T, typename I, typename K, typename X>
headerList<T,I,K,X>* getList(headerList<T,I,K,X>* listsHeader, X key){
    headerList<T,I,K,X>* aux = listsHeader;
    
    while(aux != NULL){
        if(key == aux->searchKey) return aux;
        aux = aux->next;
    }
    return NULL;
}

template<typename T, typename I, typename K, typename X>
bool insertFirst(headerList<T,I,K,X>* l, T value, K key){

    if(l == NULL) return false;

    if(l->first == NULL){
        l->first = new node<T,K>;

        l->first->info = value;
        l->first->searchKey = key;
        l->first->next = NULL;
        l->first->previous = NULL;

        l->last = l->first;
        if(INIT_LIST_INDEX == 0) l->tamanho = 1;
        else l->tamanho = INIT_LIST_INDEX;
    }else{
        node<T,K>* aux = new node<T,K>;

        l->first->previous = aux;
        aux->next = l->first;
        aux->previous = NULL;
        aux->info = value;
        aux->searchKey = key;
        l->first = aux;
        l->tamanho++;
    }
    return true;
}
template<typename T, typename I, typename K, typename X>
bool insertLast(headerList<T,I,K,X>* l, T value, K key){

    if(l == NULL) return false;

    if(l->first == NULL){
        l->first = new node<T,K>;

        l->first->info = value;
        l->first->searchKey = key;
        l->first->next = NULL;
        l->first->previous = NULL;

        l->last = l->first;
        if(INIT_LIST_INDEX == 0) l->tamanho = 1;
        else l->tamanho = INIT_LIST_INDEX;
    }else{
        node<T,K>* aux = new node<T,K>;

        l->last->next = aux;
        aux->previous = l->last;
        aux->next = NULL;
        aux->info = value;
        aux->searchKey = key;
        l->last = aux;
        l->tamanho++;
    }
    return true;
}
template<typename T, typename I, typename K, typename X>
bool insertInPosition(headerList<T,I,K,X>* list, T value, K key, int position){

    if(list != NULL){
        if(position >= INIT_LIST_INDEX && position <= list->tamanho){

            if(position == INIT_LIST_INDEX){
                insertFirst(list, value, key);
                list->tamanho++;
            }else if(position == list->tamanho){
                insertLast(list, value, key);
                list->tamanho++;
            }else{
                node<T,K>* auxL = list->first;
                node<T,K>* aux = new node<T,K>;
                int index = INIT_LIST_INDEX;
                aux->info = value;
                aux->searchKey = key;

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

template<typename T, typename I, typename K, typename X>
node<T,K>* getElement(headerList<T,I,K,X>* list, K key){
    node<T,K>* aux = list->first;

    while(aux != NULL){
        if(key == aux->searchKey) return aux;
        aux = aux->next;
    }
    return NULL;
}

template<typename T, typename I, typename K, typename X>
bool removeElement(headerList<T,I,K,X>* list, K key){
    node<T,K>* elm = getElement(list, key);
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

template<typename T, typename I, typename K, typename X>
void clearListsMemory(headerList<T,I,K,X>*& l){
    while(l != NULL){
        node<T,K>* aux = l->first;
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

int main (){
    //Teste de Uso da Lista Encadeada
    headerList<string, int, string, int>* list;
    init(list);

    insertListFirst(list, 0, 0);
    insertFirst(list, (string) "oi", (string) "oi");
    insertLast(list, (string) "ola", (string) "ola");

    cout << getElement(getList(list, 0), (string) "oi")->info;

    clearListsMemory(list);
    cout << endl << endl << "-- Fim do programa." << endl;
    return 0;
}

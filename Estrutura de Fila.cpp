#include <iostream>

using namespace std;

//Fila
template<typename T>
struct queue{
    T info;
    queue * prox;
};
template<typename T>
void createList(queue<T> *& list){
    list = NULL;
}
template<typename T>
void push(queue<T> *& list, T dado){
    queue<T> * aux = new queue<T>;
    aux->info = dado;
    aux->prox = NULL;
    
    if(list == NULL){
        list = aux;
    }else{
        queue<T> * p = list;
        while(p->prox != NULL){
            p = p->prox;
        }
        p->prox = aux;
    }
}
template<typename T>
T pop(queue<T> *& list){
    if(list != NULL){
        queue<T> * aux = list;
        T value = aux->info;

        list = list->prox;
        delete aux;
        return value;
    }else return NULL;
}

int main(){

    return 0;
}
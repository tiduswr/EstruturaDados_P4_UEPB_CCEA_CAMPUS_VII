/*
    Proprietario: Harllem Nascimento
    Data: 20/08/2021
    Curso: Ciências da Computação - UEPB Campus CCEA VII - Periodo 04
    Disciplina: Estruturas de Dados - Ricardo

Descrição da atividade:

Faça um programa que leia dados informados pelo usuário e os armazene, um por um, 
no final de uma lista duplamente encadeada com descritor. O usuário para de informar 
valores quando digitar zero (que não deve ser inserido na lista). Considere que o 
tipo de dados da lista contém apenas um inteiro como informação.

Faça um procedimento para dividir a lista ao meio, gerando duas novas listas. Caso haja 
um número ímpar de elementos, a primeira metade deve ficar com um elemento a mais.
Imprima as listas resultantes.

Gravar um vídeo de no máximo 3 minutos explicando o desenvolvimento da solução. Vídeos 
que estourem o limite de tempo não serão aceitos. Entregas com atraso terão 50% da nota 
descontada, mais 10% por dia excedente de atraso.
*/

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

headerList* cutInHalf(headerList*& list){
    if(list != NULL){
        if(list->first != NULL && list->tamanho > 1){
            if((list->tamanho % 2) == 0){
                const int MEIO = list->tamanho / 2;
                int i = INIT_LIST_INDEX;
                node* aux = list->first;

                while(aux != NULL && i < MEIO){
                    aux = aux->next;
                    i++;
                }

                headerList* newL = new headerList;
                newL->first = list->first;
                newL->last = aux;
                newL->next = NULL;
                newL->tamanho = MEIO;
                newL->properties.name = list->properties.name + " 01";

                newList(newL, list->properties);
                newL->next->first = aux->next;
                newL->next->last = list->last;
                newL->next->next = NULL;
                newL->next->tamanho = MEIO;
                newL->next->properties.name = list->properties.name + " 02";

                aux->next->previous = NULL;
                aux->next = NULL;

                if(list->next != NULL){
                    headerList* temp = list;
                    list = list->next;
                    delete temp;
                }else{
                    list->first = NULL;
                    list->last = NULL;
                    list->tamanho = 0;
                }

                return newL;

            }else{

                const int MEIO = (int) list->tamanho / 2;
                int i = INIT_LIST_INDEX;
                node* aux = list->first;

                while(aux != NULL && i < MEIO){
                    aux = aux->next;
                    i++;
                }

                headerList* newL = new headerList;
                newL->first = list->first;
                newL->last = aux;
                newL->next = NULL;
                newL->tamanho = MEIO;
                newL->properties.name = list->properties.name + " 01";

                newList(newL, list->properties);
                newL->next->first = aux->next;
                newL->next->last = list->last;
                newL->next->next = NULL;
                newL->next->tamanho = MEIO + 1;
                newL->next->properties.name = list->properties.name + " 02";

                aux->next->previous = NULL;
                aux->next = NULL;
                insertLast(newL, data{0});

                if(list->next != NULL){
                    headerList* temp = list;
                    list = list->next;
                    delete temp;
                }else{
                    list->first = NULL;
                    list->last = NULL;
                    list->tamanho = 0;
                }

                return newL;

            }
        }
        return NULL;
    }
    return NULL;
}

void solicita_dados(headerList*& l){
    cout << endl << "Por favor, insira continuamente dados nas listas(Pressione 0 para parar): " << endl << endl;
    int aux{}, i = 1;
    
    cout << "Valor[" << i << "]: ";
    cin >> aux;

    while(aux != 0){
        insertLast(l, data{aux});
        i++;
        cout << endl << "Valor[" << i << "]: ";
        cin >> aux;
    }

}

int main(){

    headerList* l = NULL;
    newList(l, headerInfo{"Lista"});

    solicita_dados(l);
    
    if(l != NULL && l->tamanho > 1){
        cout << "Lista original: " << endl << endl;
        printList(l);    

        cout << endl << "Listas cortadas:" << endl << endl;

        headerList* aux = cutInHalf(l);
        printList(aux);
        printList(aux->next);
    }else{
        cout << "A lista precisa conter mais de um Elemento!" << endl;
    }
    return 0;
}
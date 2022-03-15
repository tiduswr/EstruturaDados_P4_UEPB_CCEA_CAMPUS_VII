#include <iostream>

using namespace std;

//Tipo de dados de Funcionário
struct funcionario{
    int mat;
    string nome;
    double salario;
    string funcao;
};

//Lista encadeada
struct node{
    funcionario info;
    node * prox;
};

node * createList(){
    return NULL;
}

bool insertNode(node *& list, funcionario dado){
    node * aux = new node;
    aux->info = dado;
    aux->prox = NULL;
    
    if(list == NULL){
        list = aux;
    }else{
        node * p = list;
        while(p->prox != NULL){
            p = p->prox;
        }
        p->prox = aux;
    }
    return true;
}

bool removeNode(node *& list, int matricula){
    if(list != NULL){
        node * del, * ant;
        if(list->info.mat != matricula){
            del = list->prox;
            ant = list;
            while(del != NULL){
                if(del->info.mat == matricula){
                    ant->prox = del->prox;
                    delete del;
                    break;
                }
                del = del->prox;
                ant = ant->prox;
            }
        }else{
            del = list;
            list = list->prox;
            delete del;
        }
        return true;
    }
}

node * buscarNode(node * list, int matricula){
    while(list != NULL){
        if(list->info.mat == matricula) return list;
        list = list->prox;
    }
}

node * printNodes(node * list){
    if(list != NULL) cout << endl << "Imprimindo Lista(Matricula: Nome)" << endl << endl;
    while(list != NULL){
        cout << list->info.mat << ": " << list->info.nome << endl;
        list = list->prox;
    }
}

//Tabela Hash
const int M = 25;

struct hashIndex{
    node * list;
};

hashIndex * createHash(){
    hashIndex * aux = new hashIndex[M];
    for(int i = 0; i < M; i++){
        aux[i].list = createList();
    }
    return aux;
}

bool insertHash(hashIndex *& hash, funcionario dado){
    int position = ((int) dado.mat) % ((int) M);
    return insertNode(hash[position].list, dado);
}

hashIndex * getHashElements(hashIndex * hash, int key){
    return key <= M ? &hash[key] : NULL;
}

void printHash(hashIndex * hash){
    for(int i = 0; i < M; i++){
        node * aux = hash[i].list;
        if(aux != NULL) cout << "Index[" << i+1 << "]" << ":" << endl;
        while(aux != NULL){
            cout << "   Matricula=" << aux->info.mat << "; Nome=" << aux->info.nome << "; Função=" << aux->info.funcao << "; Salario=" << aux->info.salario << endl;
            aux = aux->prox;
        }
        if(aux != NULL) cout << endl;
    }
}

//Functions auxiliares
funcionario solicitaDados(){
    funcionario aux{};
    
    cout << endl;
    cout << "Matricula: ";
    cin >> aux.mat;
    if(aux.mat == 0) return aux;

    cout << "Nome:";
    cin.ignore();
    getline(cin, aux.nome);
    cout << "Função:";
    getline(cin, aux.funcao);
    cout << "Salario: ";
    cin >> aux.salario;

    return aux;
}
void pressKey2Cont(){
    cout << endl << "Pressione qualquer tecla para continuar..." << endl;
    cin.ignore();
    cin.get();
}
void limpar_tela(){
    system("cls||clear");
}

int main(){
    
    hashIndex * hash = createHash();
    bool continuar = true;

    cout << "-------- TABELAS HASH" << endl << endl;
    cout << "[!] Insira continuamente os dados de funcionarios para popular a tabela Hash!" << endl;
    cout << "[!] Digite 0 na matricula para para o preenchimento!" << endl << endl;
    pressKey2Cont();

    while(continuar){
        limpar_tela();
        cout << "Digite os dados para incluir um Funcionário:" << endl;

        funcionario aux = solicitaDados();
        cout << endl;

        if(aux.mat != 0){
            insertHash(hash, aux);
            cout << "Funcionário incluido!" << endl;
            pressKey2Cont();
        }else continuar = false;
    }

    limpar_tela();
    cout << "Imprimindo tabela hash:" << endl << endl;
    printHash(hash);
    
    cout << endl;
    pressKey2Cont();

    return 0;
}
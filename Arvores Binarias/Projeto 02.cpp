#include <iostream>
#include <string>

using namespace std;

//LinkedList-------------------------------------------------------------------------------------

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
void initList(headerList<T,I,K,X>*& listHeader){
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

//ARVORE -----------------------------------------------------------------------------------

/*
    Foram feitas alterações para referenciar espaços de memórias ja criados, e não criar novos nesta arvore.
    Mais especificamente foi inserido a opção de atribuir NULL ao campo info antes da exclusão de uma folha
    da arvore. Dessa forma, é quebrado somente a referencia da Informação.

    O Código original exclui o nó por completo.
*/

//Structs
template<typename T, typename I>
struct treeNode{
    T info;
    I key;
    treeNode<T, I> *left, *right;
    int bal;
    bool isAVL; // BSTree e AVL
};

//Funções Principais
template<typename T, typename I>
void printTreeNode(treeNode<T, I> *node){
    if(node != NULL) cout << node->key << " ";
}
template<typename I>
int checkKey(I valueOne, I valueTwo){
    /* 0 é igual
    *  1 é maior
    *  -1 é menor*/

    if(valueOne > valueTwo)return 1;
    else if(valueOne < valueTwo) return -1;
    else if(valueOne == valueTwo) return 0;
}
template<typename T, typename I>
void initTree(treeNode<T, I> *&binaryTree){
    binaryTree = NULL;
}
template<typename T, typename I>
void printPre(treeNode<T, I> *root){
    if(root != NULL){
        printTreeNode(root);
        printPre(root->left);
        printPre(root->right);
    }
}
template<typename T, typename I>
void printCenter(treeNode<T, I> *root){
    if(root != NULL){
        printCenter(root->left);
        printTreeNode(root);
        printCenter(root->right);
    }
}
template<typename T, typename I>
void printPos(treeNode<T, I> *root){
    if(root != NULL){
        printPos(root->left);
        printPos(root->right);
        printTreeNode(root);
    }
}
template<typename T, typename I>
bool insertBSTree(treeNode<T, I> *&root, T value, I key){
    //A função retorna falso caso o valor ja exista na árvore

    if(root == NULL){
        root = new treeNode<T, I>;
        root->info = value;
        root->key = key;
        root->left = root->right = NULL;
        root->isAVL = false;
        return true;
    }
    else if(checkKey(root->key, key) == 1) return insertBSTree(root->left, value, key);
    else if(checkKey(root->key, key) == -1) return insertBSTree(root->right, value, key);
    else if(checkKey(root->key, key) == 0) return false;
}
template<typename T, typename I>
treeNode<T, I> * findNode(treeNode<T, I> *root, I key){
    if(root == NULL || checkKey(root->key, key) == 0) return root;
    else if(checkKey(root->key, key) == 1) return findNode(root->left, key);
    else return findNode(root->right, key);
}
template<typename T, typename I>
int treeLenght(treeNode<T, I> *root){
    if(root == NULL){
        return 0;
    }else{
        return treeLenght(root->left) + treeLenght(root->right) + 1;
    }
}
template<typename T, typename I>
int treeHeight(treeNode<T, I> *root){
    if(root == NULL){
        return -1;
    }else{
        int heightLeft = treeHeight(root->left);
        int heightRight = treeHeight(root->right);
        if(heightLeft > heightRight){
            return heightLeft + 1;
        }else{
            return heightRight + 1;
        }
    }
}
template<typename T, typename I>
treeNode<T, I>* treeMaxKeyValue(treeNode<T, I> *root){
    if(root == NULL || root->right == NULL) return root;
    else return treeMaxKeyValue(root->right);
}
template<typename T, typename I>
treeNode<T, I>* treeMinKeyValue(treeNode<T, I> *root){
    if(root == NULL || root->left == NULL) return root;
    else return treeMinKeyValue(root->left);
}
template<typename T, typename I>
treeNode<T, I>* removeTreeNode(treeNode<T, I> *root, I key){
    //Procura o nó com o valor passado na função
    if(root == NULL) return NULL;
    else if(checkKey(root->key, key) == 1) root->left = removeTreeNode(root->left, key);
    else if(checkKey(root->key, key) == -1) root->right = removeTreeNode(root->right, key);
    else{
        //Verifica qual o caso de exclusão
        if(root->left == NULL && root->right == NULL){
            root->info = NULL;
            delete root;
            root = NULL;
        }else if(root->left == NULL){
            root->info = NULL;
            treeNode<T, I> * aux = root;
            root = root->right;
            delete aux;
        }else if(root->right == NULL){
            root->info = NULL;
            treeNode<T, I> *aux = root;
            root = root->left;
            delete aux;
        }else{
            //No caso em que possui duas folhas, é pegado primeiro a ramificação da esquerda
            treeNode<T, I> *aux = root->left;
            while(aux->right != NULL){
                //Na ramificação da esquerda é feita um busca para achar o maior valor
                aux = aux->right;
            }
            //Esse maior valor é copiado para a raiz atual, pois ele sera a nova raiz
            root->info = aux->info;

            //E então deletamos o valor desejado
            aux->info = NULL;
            delete aux;
        }
    }
    return root;
}
template<typename T, typename I>
bool isBalancedTree(treeNode<T, I> *root){
    if(root == NULL) return true;
    else{
        if(abs(treeHeight(root->left) - treeHeight(root->right)) > 1) return false;
        else{
            return isBalancedTree(root->left) && isBalancedTree(root->right);
        }
    }
}
template<typename T, typename I>
void generateVector(treeNode<T, I> *root, T *arrayData, I *arrayKeys, int &i){
    if(root != NULL){
        generateVector(root->left, arrayData, arrayKeys, i);
        arrayData[i] = root->info;
        arrayKeys[i] = root->key;
        i++;
        generateVector(root->right, arrayData, arrayKeys, i);
    }
}
template<typename T, typename I>
void killTree(treeNode<T, I> *&root){
    if(root != NULL){
        killTree(root->left);
        killTree(root->right);
        root->info = NULL;
        delete root;
        root = NULL;
    }
}
template<typename T, typename I>
void makeBalancedTree(treeNode<T, I> *&root, T* arrayData, I* arrayKeys, int startArray, int endArray){
    if(endArray < startArray){
        root = NULL;
    }else{
        int MEIO = (startArray + endArray) / 2;
        root = new treeNode<T, I>;
        root->info = arrayData[MEIO];
        root->key = arrayKeys[MEIO];
        makeBalancedTree(root->left, arrayData, arrayKeys, startArray, MEIO-1);
        makeBalancedTree(root->right, arrayData, arrayKeys, MEIO+1, endArray);
    }
}
template<typename T, typename I>
bool staticBalanceTree(treeNode<T, I> *&root){
    if(!isBalancedTree(root)){
        int lengthTree = treeLenght(root);
        T* arrayData = new T[lengthTree];
        I* arrayKeys = new I[lengthTree];
        int i = 0;
        generateVector(root, arrayData, arrayKeys, i);
        killTree(root);
        makeBalancedTree(root, arrayData, arrayKeys, 0, lengthTree - 1);
        delete [] arrayData;
        delete [] arrayKeys;
        return true;
    }else{
        return false;
    }
}

// Functions Auxiliares ---------------------------------------------------------------
void pressKey2Cont(){
    cout << endl << "Pressione qualquer tecla para continuar..." << endl;
    cin.ignore();
    cin.get();
}
void limpar_tela(){
    system("cls||clear");
}

//Struct de Funcionários
struct funcionario{
    string nome;
    long matricula;
};

//Functions do Main --------------------------------------------------------------------
int menuHeader(){
    int opt{};
    limpar_tela();
    cout << "MENU PRINCIPAL:" << endl << endl;
    cout << "[1] Inserir elemento no fim da lista;" << endl;
    cout << "[2] Buscar elemento na lista por matrícula ou nome;" << endl;
    cout << "[3] Imprimir todos os elementos por ordem de matrícula ou nome;" << endl;
    cout << "[4] Balancear árvores;" << endl;
    cout << "[0] Sair." << endl;
    cout << endl << "Digite a Opção desejada: ";
    cin >> opt;
    limpar_tela();
    return opt;
}
funcionario * cria_novo_funcionario(){
    funcionario * novo = new funcionario;

    cout << "Preencha os dados do Novo Funcionário:" << endl << endl; 
    cout << "Mátricula: ";
    cin >> novo->matricula;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, novo->nome);
    return novo;
}
void print_funcionario(funcionario * func){
    if(func != NULL){
        cout << "Nome: " << func->nome << ", Mátricula: " << func->matricula << endl;
    }
}
void novoFuncionario_Main(headerList<funcionario *, int, long, int> *& list,
    treeNode<funcionario *, long> *& treeMatricula,
    treeNode<funcionario *, string> *& treeNome){

    string const TITLE = "-=-=-= CADASTRO DE FUNCIONARIO -=-=-=";
    
    cout << TITLE << endl;
    funcionario * aux = cria_novo_funcionario();

    limpar_tela();
    cout << TITLE << endl;

    insertLast(list, aux, aux->matricula);
    insertBSTree(treeMatricula, aux, aux->matricula);
    insertBSTree(treeNome, aux, aux->nome);
    
    limpar_tela();
    cout << TITLE << endl;
    cout << "Novo funcionario inserido, voltando ao menu principal!" << endl;
    pressKey2Cont();
}
void buscarFuncionario_Main(treeNode<funcionario *, long> * treeMatricula,
    treeNode<funcionario *, string> * treeNome){
    string const TITLE = "-=-=-= BUSCA DE FUNCIONARIO -=-=-=";

    limpar_tela();
    cout << TITLE << endl << endl;
    int opt;
    cout << "Selecione um Formato de Busca: " << endl << endl;
    cout << "[1] Matricula;" << endl;
    cout << "[2] Nome;" << endl;
    cout << "Digite a Opção: ";
    cin >> opt;

    long matricula{}; string nome{};
    switch(opt){
        case 1:
            treeNode<funcionario *, long> * buscaMat;

            limpar_tela();
            cout << TITLE << endl << endl;
            cout << "Digite a Matricula do Funcionário: ";
            cin >> matricula;

            buscaMat = findNode(treeMatricula, matricula);
            if(buscaMat != NULL){
                limpar_tela();
                cout << TITLE << endl << endl;
                cout << "Dados do Funcionário: " << endl;
                print_funcionario(buscaMat->info);
                pressKey2Cont();
            }else{
                limpar_tela();
                cout << TITLE << endl << endl;
                cout << "Funcionário não encontrado!" << endl;
                pressKey2Cont();
            }
            break;
        case 2:
            treeNode<funcionario *, string> * buscaNome;

            limpar_tela();
            cout << TITLE << endl << endl;
            cout << "Digite o nome do Funcionário: ";
            cin.ignore();
            getline(cin, nome);

            buscaNome = findNode(treeNome, nome);
            if(buscaNome != NULL){
                limpar_tela();
                cout << TITLE << endl << endl;
                cout << "Dados do Funcionário: " << endl;
                print_funcionario(buscaNome->info);
                pressKey2Cont();
            }else{
                limpar_tela();
                cout << TITLE << endl << endl;
                cout << "Funcionário não encontrado!" << endl;
                pressKey2Cont();
            }
            break;
        default:
            limpar_tela();
            cout << TITLE << endl << endl;
            cout << "Busca cancelada!" << endl;
            pressKey2Cont();
            break;
    }
}
template<typename I>
void printCenter_Personalizada(treeNode<funcionario *, I> *root){
    if(root != NULL){
        printCenter_Personalizada(root->left);
        print_funcionario(root->info);
        printCenter_Personalizada(root->right);
    }
}
void printFuncionarios_Main(treeNode<funcionario *, long> * treeMatricula,
    treeNode<funcionario *, string> * treeNome){

    string const TITLE = "-=-=-= IMPRESSÃO DE FUNCIONARIO -=-=-=";

    limpar_tela();
    cout << TITLE << endl << endl;
    int opt;
    cout << "Selecione um Formato de Impressão: " << endl << endl;
    cout << "[1] Por Matricula;" << endl;
    cout << "[2] Por Nome;" << endl;
    cout << "Digite a Opção: ";
    cin >> opt;

    switch(opt){
        case 1:
            limpar_tela();
            cout << TITLE << endl << endl;
            printCenter_Personalizada(treeMatricula);
            pressKey2Cont();
            break;
        case 2:
            limpar_tela();
            cout << TITLE << endl << endl;
            printCenter_Personalizada(treeNome);
            pressKey2Cont();
            break;
        default:
            limpar_tela();
            cout << TITLE << endl << endl;
            cout << "Impressão cancelada!" << endl;
            pressKey2Cont();
            break;
    }

}
void balancearArvores_Main(treeNode<funcionario *, long> * treeMatricula,
    treeNode<funcionario *, string> * treeNome){
    limpar_tela();
    cout << "=-=-=-=-= BALANCEAMENTO DE ARVORES =-=-=-=-=" << endl << endl;
    if(!isBalancedTree(treeMatricula)){
        staticBalanceTree(treeMatricula);
        cout << "A arvore de Matricula foi Balanceada!" << endl;
    }
    if(!isBalancedTree(treeNome)){
        staticBalanceTree(treeNome);
        cout << "A arvore de Nomes foi Balanceada!" << endl;
    }
    pressKey2Cont();
}

//MAIN -----------------------------------------------------

int main(){

    bool continuar = true;
    headerList<funcionario *, int, long, int> * list;
    treeNode<funcionario *, long> * treeMatricula;
    treeNode<funcionario *, string> * treeNome;
    initTree(treeMatricula); initTree(treeNome);
    initList(list); insertListLast(list, 0, 0);

    while(continuar){
        switch(menuHeader()){
            case 1:
                novoFuncionario_Main(list, treeMatricula, treeNome);
                break;
            case 2:
                buscarFuncionario_Main(treeMatricula, treeNome);
                break;
            case 3:
                printFuncionarios_Main(treeMatricula, treeNome);
                break;
            case 4:
                balancearArvores_Main(treeMatricula, treeNome);
                break;
            case 0:
                continuar = false;
                break;
            default:
                break;
        }
    }

    killTree(treeMatricula); killTree(treeNome);
    clearListsMemory(list);
    return 0;
}
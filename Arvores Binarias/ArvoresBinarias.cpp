#include <iostream>
#include <string>

using namespace std;

//Structs
template<typename T, typename I>
struct treeNode{
    T info;
    I key;
    treeNode<T, I> *left, *right;
    int bal;
    bool isAVL; // BSTree e AVL
};

//A função abaixo pode dar erro caso I não seja numérico!
template<typename T, typename I>
int somarKeys(treeNode<T, I> *root){
    if(root == NULL){
        return 0;
    }else{
        return somarKeys(root->left) + somarKeys(root->right) + root->key;
    }
}

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
void init(treeNode<T, I> *&binaryTree){
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
            delete root;
            root = NULL;
        }else if(root->left == NULL){
            treeNode<T, I> * aux = root;
            root = root->right;
            delete aux;
        }else if(root->right == NULL){
            treeNode<T, I> *aux = root;
            root = root->left;
            delete aux;
        }else{
            //No caso em que possui duas folhas, é pegado primeiro a ramificação da esquerda
            treeNode<T, I> *aux = root->left;
            T value = root->info;
            while(aux->right != NULL){
                //Na ramificação da esquerda é feita um busca para achar o maior valor
                aux = aux->right;
            }
            //Esse maior valor é copiado para a raiz atual, pois ele sera a nova raiz
            root->info = aux->info;

            //E então deletamos o valor desejado
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

//--------------------------------------------------------------------------------------------------
//Código para Arvores Avl
template<typename T, typename I>
bool isAvlTree(treeNode<T, I> *root){
    return root->isAVL;
}
template<typename T, typename I>
void rotateRightAVL(treeNode<T, I> *&root){
    treeNode<T, I> *aux;
    aux = root->left;
    root->left = aux->right;
    aux->right = root;
    root = aux;
}
template<typename T, typename I>
void rotateLeftAVL(treeNode<T, I> *&root){
    treeNode<T, I> *aux;
    aux = root->right;
    root->right = aux->left;
    aux->left = root;
    root = aux;
}
template<typename T, typename I>
bool insertAvlTree(treeNode<T, I> *root, T value, I key){
    if(root == NULL){
        root = new treeNode<T, I>;
        root->info = value;
        root->left = root->right = NULL;
        root->key = key;
        root->bal = 0;
        return true;
    }else{
        if(checkKey(root->key, key) == 1){
            if(insertAvlTree(root->left, value)){
                switch(root->bal){
                    case +1: root->bal = 0; return false;
                    case 0: root->bal = -1; return true;
                    case -1:
                        if(root->left->bal == -1) rotateRightAVL(root); // Rotação Simples
                        else{
                            //Rotação Dupla
                            rotateLeftAVL(root->left);
                            rotateRightAVL(root);
                        }
                        root->bal = 0;
                        return false;
                }
            }
        }else{
            if(checkKey(key, root->key) == 1){
                switch(root->bal){
                    case -1: root->bal = 0; return false;
                    case 0: root->bal = +1; return true;
                    case +1:
                        if(root->right->bal == +1) rotateLeftAVL(root); //Rotação Simples
                        else{
                            rotateRightAVL(root->right);
                            rotateLeftAVL(root);
                            root->bal = 0;
                            return false;
                        }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------

int main(){

    treeNode<string, int> *tree, *aux;
    int NUMEROS[] = {1,2,3,4,5,6,7,8,9,10,11};
    string *TESTE = new string[5];
    int TAMANHO_ARRAY_NUMEROS = sizeof(NUMEROS)/sizeof(int);
    init(tree);

    cout << "Inserindo valores do array NUMEROS..." << endl;
    for(int i = 0; i < TAMANHO_ARRAY_NUMEROS; i++){
        if(!insertBSTree(tree, to_string(NUMEROS[i]), NUMEROS[i])){
            cout << "O elemento " << NUMEROS[i] << " já existe!" << endl;
        }
    }
    cout << endl;

    printPre(tree);
    cout << endl;
    printCenter(tree);
    cout << endl;
    printPos(tree);
    cout << endl;

    aux = findNode(tree, 2);
    if(aux != NULL){
        cout << "Teste de Busca: " << aux->key;
    }else{
        cout << "O valor de Busca não foi encontrado!";
    }
    cout << endl;

    cout << "Quantidade de Elementos na Arvore: " << treeLenght(tree);
    cout << endl;

    cout << "Soma dos Elementos na Arvore: " << somarKeys(tree);
    cout << endl;

    cout << "Altura da Arvore: " << treeHeight(tree);
    cout << endl;

    aux = treeMaxKeyValue(tree);
    if(aux != NULL){
        cout << "Maior valor da Arvore: " << aux->key;
    }else{
        cout << "Não foi encontrado um valor máximo!";
    }
    cout << endl;

    aux = treeMinKeyValue(tree);
    if(aux != NULL){
        cout << "Menor valor da Arvore: " << aux->key;
    }else{
        cout << "Não foi encontrado um valor minimo!";
    }
    cout << endl;

    cout << "Removendo o valor 11" << endl;
    removeTreeNode(tree, 11);
    printCenter(tree);
    cout << endl;
    printPre(tree);
    cout<< endl;
    if(isBalancedTree(tree)) cout << "Arvore Balanceda";
    else cout << "Arvore Desbalanceada! Iniciando balanceamento estatico...";
    cout << endl;
    staticBalanceTree(tree);
    cout << "A arvore Balanceada é: ";
    cout << endl;
    printPre(tree);
    cout << endl;
    printCenter(tree);
    cout << endl;

    cout << endl << endl << "Fim da Execução..." << endl;
    return 0;
}

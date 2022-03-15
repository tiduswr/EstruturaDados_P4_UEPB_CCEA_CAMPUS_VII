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
//Funções Principais
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

//Tipo de dados de Funcionário
struct funcionario{
    int mat;
    string nome;
    double salario;
    string funcao;
};

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

//---------------------------------------------Função Personalizada de Soma dos Salaros:
double somarSalarios_Pos(treeNode<funcionario, int> *root){
    if(root != NULL){
        return somarSalarios_Pos(root->left) + somarSalarios_Pos(root->right) + root->info.salario;
    }else return 0;
}
void printTreeNode(treeNode<funcionario, int> *root){
    if(root != NULL){
        cout << "   Matricula=" << root->info.mat << "; Nome=" << 
                root->info.nome << "; Função=" << root->info.funcao << 
                "; Salario=" << root->info.salario << endl;
    }
}
void printTree_Center(treeNode<funcionario, int> *root){
    if(root != NULL){
        printTree_Center(root->left);
        printTreeNode(root);
        printTree_Center(root->right);
    }
}

int main(){

    treeNode<funcionario, int> * tree; init(tree);
    bool continuar = true;

    cout << "-------- ARVORES BINARIAS" << endl << endl;
    cout << "[!] Insira continuamente os dados de funcionarios para popular a tabela Hash!" << endl;
    cout << "[!] Digite 0 na matricula para para o preenchimento!" << endl << endl;
    pressKey2Cont();

    while(continuar){
        limpar_tela();
        cout << "Digite os dados para incluir um Funcionário:" << endl;

        funcionario aux = solicitaDados();
        cout << endl;

        if(aux.mat != 0){
            insertBSTree(tree, aux, aux.mat);
            cout << "Funcionário incluido!" << endl;
            pressKey2Cont();
        }else continuar = false;
    }

    limpar_tela();
    cout << "Imprimindo funcionários:" << endl << endl;
    printTree_Center(tree);
    cout << endl << "Soma dos Salarios de todos os Funcionários: " << somarSalarios_Pos(tree);
    cout << endl;
    pressKey2Cont();

    return 0;
}
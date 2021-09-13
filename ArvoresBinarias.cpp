#include <iostream>

using namespace std;

//Structs
struct dados{
    int key;
};
struct treeNode{
    dados info;
    treeNode *left, *right;
};

//Mude as funções abaixo caso a estrutura dados mude
void printTreeNode(treeNode* node){
    if(node != NULL) cout << node->info.key << " ";
}
int checkKey(dados valueOne, dados valueTwo){
    /* 0 é igual
    *  1 é maior
    *  -1 é menor*/

    if(valueOne.key > valueTwo.key)return 1;
    else if(valueOne.key < valueTwo.key) return -1;
    else if(valueOne.key == valueTwo.key) return 0;
}
int somarKeys(treeNode* root){
    if(root == NULL){
        return 0;
    }else{
        return somarKeys(root->left) + somarKeys(root->right) + root->info.key;
    }
}
//------------------------------------------------------------

//Funções Principais
void init(treeNode*& binaryTree){
    binaryTree = NULL;
}
void printPre(treeNode* root){
    if(root != NULL){
        printTreeNode(root);
        printPre(root->left);
        printPre(root->right);
    }
}
void printCenter(treeNode* root){
    if(root != NULL){
        printCenter(root->left);
        printTreeNode(root);
        printCenter(root->right);
    }
}
void printPos(treeNode* root){
    if(root != NULL){
        printPos(root->left);
        printPos(root->right);
        printTreeNode(root);
    }
}
bool insertBSTree(treeNode*& root, dados value){
    //A função retorna falso caso o valor ja exista na árvore

    if(root == NULL){
        root = new treeNode;
        root->info = value;
        root->left = NULL;
        root->right = NULL;
        return true;
    }
    else if(checkKey(root->info, value) == 1) insertBSTree(root->left, value);
    else if(checkKey(root->info, value) == (-1)) insertBSTree(root->right, value);
    else if(checkKey(root->info, value) == 0) return false;
}
treeNode* findNode(treeNode* root, dados value){
    if(root == NULL || checkKey(root->info, value) == 0) return root;
    else if(checkKey(root->info, value) == 1) return findNode(root->left, value);
    else return findNode(root->right, value);
}
int treeLenght(treeNode* root){
    if(root == NULL){
        return 0;
    }else{
        return treeLenght(root->left) + treeLenght(root->right) + 1;
    }
}

int treeHeight(treeNode* root){
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
treeNode* treeMaxKeyValue(treeNode* root){
    if(root == NULL || root->right == NULL) return root;
    else return treeMaxKeyValue(root->right);
}
treeNode* treeMinKeyValue(treeNode* root){
    if(root == NULL || root->left == NULL) return root;
    else return treeMinKeyValue(root->left);
}
treeNode* removeTreeNode(treeNode* root, dados value){
    //Procura o nó com o valor passado na função
    if(root == NULL) return NULL;
    else if(checkKey(root->info, value) == 1) root->left = removeTreeNode(root->left, value);
    else if(checkKey(root->info, value) == -1) root->right = removeTreeNode(root->right, value);
    else{
        //Verifica qual o caso de exclusão
        if(root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
        }else if(root->left == NULL){
            treeNode * aux = root;
            root = root->right;
            delete aux;
        }else if(root->right == NULL){
            treeNode* aux = root;
            root = root->left;
            delete aux;
        }else{
            //No caso em que possui duas folhas, é pegado primeiro a ramificação da esquerda
            treeNode* aux = root->left;
            while(aux->right != NULL){
                //Na ramificação da esquerda é feita um busca para achar o maior valor
                aux = aux->right;
            }
            //Esse maior valor é copiado para a raiz atual, pois ele sera a nova raiz
            root->info = aux->info;
            //A raiz que possuia o maior valor é então substituida pelo valor que queremos excluir
            aux->info = value;
            //Então pegamos a ramificação da esquerda e excluimos efetivamente o valor procurado
            root->left = removeTreeNode(root->left, value);
        }
    }
    return root;
}
bool isBalancedTree(treeNode* root){
    if(root == NULL) return true;
    else{
        if(abs(treeHeight(root->left) - treeHeight(root->right)) > 1) return false;
        else{
            return isBalancedTree(root->left) && isBalancedTree(root->right);
        }
    }
}
void generateVector(treeNode* root, dados* array, int &i){
    if(root != NULL){
        generateVector(root->left, array, i);
        array[i] = root->info;
        i++;
        generateVector(root->right, array, i);
    }
}

int main(){

    treeNode *tree, *aux;
    int NUMEROS[] = {6, 7, 2, 9, 4, 5};
    dados *TESTE = new dados[5];
    int TAMANHO_ARRAY_NUMEROS = sizeof(NUMEROS)/sizeof(int);
    init(tree);

    cout << "Inserindo valores do array NUMEROS..." << endl;
    for(int i = 0; i < TAMANHO_ARRAY_NUMEROS; i++){
        if(!insertBSTree(tree, dados{NUMEROS[i]})){
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

    aux = findNode(tree, dados{2});
    if(aux != NULL){
        cout << "Teste de Busca: " << aux->info.key;
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
        cout << "Maior valor da Arvore: " << aux->info.key;
    }else{
        cout << "Não foi encontrado um valor máximo!";
    }
    cout << endl;

    aux = treeMinKeyValue(tree);
    if(aux != NULL){
        cout << "Menor valor da Arvore: " << aux->info.key;
    }else{
        cout << "Não foi encontrado um valor minimo!";
    }
    cout << endl;

    cout << "Removendo o valor 2" << endl;
    removeTreeNode(tree, dados{2});
    printCenter(tree);
    cout<< endl;
    if(isBalancedTree(tree)) cout << "Arvore Balanceda";
    else cout << "Arvore Desbalanceada";
    cout << endl;

    int f = 0;
    generateVector(tree, TESTE, f);
    for(int x = 0; x < 5; x++){
        cout << TESTE[x].key << " ";
    }

    cout << endl << endl << "Fim da Execução..." << endl;
    return 0;
}
#include <iostream>

using namespace std;

//Constante
int const ORDEM = 5;

//Struct
template <typename T, typename I>
struct data{
    T key;
    I value;
};
template <typename T, typename I>
struct page{
    data<T, I> r[ORDEM];
    page *p[ORDEM];
    int n;
};

//Funções principais
template <typename T, typename I>
void init(page<T, I> *&root){
    root = NULL;
}

template<typename T, typename I>
data<T, I>* searchBTree(page<T, I> *root, T key){
    if(root == NULL){
        return NULL;
    }else{
        int i = 1;
        while((i < root->n) && (key > root->r[i].key)){
            i++;
            if(key == root->r[i].key) return &(root->r[i]);
            else if(key < root->r[i].key) return searchBTree(root->p[i-1], key);
            else return searchBTree(root->p[i], key);
        }
    }
}

int main(){

    page<int, string>* x;
    init(x);

    cout << endl << endl << "Fim do programa..." << endl;
    return 0;
}
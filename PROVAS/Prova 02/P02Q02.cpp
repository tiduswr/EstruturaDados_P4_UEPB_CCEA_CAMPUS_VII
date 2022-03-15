#include <iostream>
using namespace std;

const int n = 4;

int verticeMaiorAdjacencia(int mat[n][n]){
    int maior = 0;
    int indiceVertice = 0;
    for(int i = 0; i < n; i ++){
        int aux = 0;
        for(int j = 0; j < n; j++){
            if(mat[i][j] > 0) aux ++;
        }
        if(aux > maior) {
            maior = aux; 
            indiceVertice = i;
        }
    }
    return indiceVertice;
}
void criarAdjacencias(int mat[n][n]){
    //Popule o grafo da maneira que você achar necessário
    mat[0][1] = 1;
    mat[1][0] = 1;
    mat[0][3] = 1;
    mat[1][2] = 1;
    mat[1][3] = 1;
    mat[2][3] = 1;
    mat[2][1] = 1;
    mat[3][0] = 1;
    mat[3][1] = 1;
}
int main(){

    int matAdj[n][n]{}; 
    string candidatos[n] = {"Tidus", "Wakka", "Lulu", "Kimahri"};

    criarAdjacencias(matAdj);
    cout << "Matriz de Adjacência:" << endl << endl;
    for(int i = 0; i < n; i ++){
        cout << candidatos[i] << "-> ";
        for(int j = 0; j < n; j++){
            if(matAdj[i][j] > 0) cout << candidatos[j] << ", ";
        }
        cout << endl;
    }

    int indice = verticeMaiorAdjacencia(matAdj);
    cout << endl << "Candidato com maior numero de votos: " << 
            candidatos[indice] << "[Linha da Matriz = " << indice + 1 << "]" << endl << endl;

    return 0;
}
#include <iostream>

using namespace std;

double mediaPonderada(double mediaProvas, double mediaTrabalhos){
    return ((mediaProvas * 7) + (mediaTrabalhos * 3)) / (10);
}

void preencherQuartaColuna(double mat[5][4]){

    for(int i = 0; i < 5; i++){
        mat[i][3] = mediaPonderada(mat[i][1], mat[i][2]);
    }

}

void printMatriz(double mat[5][4]){
    cout << endl << "Matriz de notas:" << endl << endl;
    cout << "MAT | PROVA | TRAB | MEDIA POND" << endl;
    cout << "-------------------------------";
    for(int i = 0; i < 5; i++){
        cout << endl << mat[i][0] << " | " << mat[i][1] << " | " << mat[i][2] << " | " << mat[i][3];
    }
    cout << endl <<endl;
}

int main(){

    double matriz[5][4];

    matriz[0][0] = 1.2;

    for(int i = 0; i < 5; i++){
        matriz[i][0] = 123 * (i + 1);
        matriz[i][1] = (1 + i)*0.83 + 3;
        matriz[i][2] = (1 + i)*0.77 + 5;
        matriz[i][3] = 0;
    }
    
    printMatriz(matriz);
    preencherQuartaColuna(matriz);

    printMatriz(matriz);

    return 0;
}

#include "grafoMatriz.h"
grafoMatriz::grafoMatriz(unsigned int numVertices, unsigned short dir){
    numeroV = numVertices;
    numeroA = 0;
    direcionado = dir;
    tamanhoMatriz = numVertices + 1; //1 coluna a mais (coluna 0) pq vertices comecam a contar do 1
    matrizAdj = vector<vector<int>>(tamanhoMatriz);
            for (int i = 0; i < tamanhoMatriz; i++) {
                matrizAdj[i] = vector<int>(tamanhoMatriz);
                  for (int j = 0; j < tamanhoMatriz; j++)
                        matrizAdj[i][j] = 0;
          }
}
grafoMatriz::~grafoMatriz(){
     for (int i = 0; i < tamanhoMatriz; i++)
        matrizAdj[i].clear();
}
void grafoMatriz::addAresta(unsigned int v1, unsigned int v2){
    if(direcionado == 0){
        matrizAdj[v1][v2] = 1;
        matrizAdj[v2][v1] = 1;
    }
    else{
        matrizAdj[v1][v2] = 1;
    }
    numeroA++;
}
void grafoMatriz::removeAresta(unsigned int v1, unsigned int v2){
    if(direcionado == 0){
        matrizAdj[v1][v2] = 0;
        matrizAdj[v2][v1] = 0;
    }
    else{
        matrizAdj[v1][v2] = 0;
    }
    numeroA--;
}
void grafoMatriz::addVertice(unsigned int v){
    matrizAdj.resize(numeroV+1);
    matrizAdj.push_back(vector<int>(tamanhoMatriz+1));
    int i;
    for (i = 1; i < tamanhoMatriz; i++);
    for (int j = 1; j < tamanhoMatriz; j++){
        matrizAdj[i][j] = 0;
    }
    numeroV++;
    tamanhoMatriz++;
}
void grafoMatriz::removeVertice(unsigned int v){
    numeroV--;
    for (int i = 1; i < tamanhoMatriz; i++){
        matrizAdj[v][i] = -1;
        matrizAdj[i][v] = -1;
    }
}
bool grafoMatriz::verificaAdjacencia(unsigned int v1, unsigned int v2){
    if(direcionado == 0){
        return matrizAdj[v1][v2] || matrizAdj[v2][v1];
    }
    else{
        return matrizAdj[v1][v2];
    }
}
void grafoMatriz::mostraInfo(){
    cout << "Numero de vertices: " << numeroV << endl;
    cout << "Numero de arestas: " << numeroA << endl;
}
void grafoMatriz::imprimeMatriz() {
      for (int i = 1; i < tamanhoMatriz; i++) {
            if(matrizAdj[i][1] != -1){
                  cout << i << ": ";
                  for (int j = 1; j < tamanhoMatriz; j++)
                    if(matrizAdj[1][j] != -1)
                        cout << matrizAdj[i][j] << " ";
                  cout << "\n";
            }
      }
}
unsigned int grafoMatriz::verificaGrau(unsigned int id) {
    unsigned int grau = 0;
    int i = 0;
    for (i = 1; i < tamanhoMatriz; i++){
        if (i == id)
            break;
    }
    for (int j = 1; j < tamanhoMatriz; j++){
        if(matrizAdj[i][j] == 1)
            grau++;
    }
    return grau;
}
#include <iostream>
#include <vector>
using namespace std;
class grafoMatriz{
    private:
        unsigned int numeroV; //Numero de vertices
        unsigned int numeroA; //Numero de arestas
        vector<vector<int>> matrizAdj; //Matriz de adjacencia
        unsigned short direcionado; //Guarda se o grafo é direcionado ou nao
        unsigned int tamanhoMatriz; //Tamanho da matriz de adjacencia
    public:
        grafoMatriz(unsigned int, unsigned short);
        ~grafoMatriz();
        void addAresta(unsigned int,unsigned int);
        void removeAresta(unsigned int,unsigned int);
        void addVertice(unsigned int);
        void removeVertice(unsigned int);
        bool verificaAdjacencia(unsigned int,unsigned int);
        void mostraInfo();
        void imprimeMatriz();
        unsigned int verificaGrau(unsigned int);
};
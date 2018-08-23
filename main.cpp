#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "grafoMatriz.h"
#include "grafoLista.h"

using namespace std;

grafoMatriz* criaGrafoMatriz(string nomeArquivo, unsigned short dir){
    ifstream arquivo(nomeArquivo);
    string linha;
    unsigned int numV, a1, a2 = 0;
    if (arquivo.good()){ //Verifica se o arquivo esta aberto
        arquivo >> numV; //Le a primeira linha com o numero de vertices
        grafoMatriz* g1 = new grafoMatriz(numV,dir);
        getline(arquivo, linha);
        while (getline(arquivo, linha)) //Continua lendo o arquivo
        {
            istringstream iss(linha);
            iss >> a1 >> a2;
            g1->addAresta(a1,a2);
        }
        return g1;
    }
    else{ //Caso o arquivo nao esteja aberto, mostra um erro.
        cout << "Erro ao abrir arquivo do grafo: " << nomeArquivo << endl;
        exit(1);
    }
}

grafoLista* criaGrafoLista(string nomeArquivo, unsigned short dir){
    ifstream arquivo(nomeArquivo);
    string linha;
    unsigned int numV, a1, a2, peso = 0;
    grafoLista* g1 = new grafoLista();
    if (arquivo.good()){ //Verifica se o arquivo esta aberto
        arquivo >> numV; //Le a primeira linha com o numero de vertices
        for (int i = 1; i<=numV; i++){
            g1->adicionaVertice(i); //Adiciona o numero lido de vertices
        }
        getline(arquivo, linha);
        while (getline(arquivo, linha)) //Continua lendo o arquivo
        {
            istringstream iss(linha);
            iss >> a1 >> a2 >> peso;
            g1->adicionaAresta(a1,a2,peso);
        }
        if(peso == 0) //Se o peso for 0 a aresta nao precisa existir em um grafo ponderado
            g1->alteraPonderado(false);
        else
            g1->alteraPonderado(true);
        if(dir)
            g1->alteraDirecionado(true);
        else
            g1->alteraDirecionado(false);
        return g1;
    }
    else{ //Caso o arquivo nao esteja aberto, mostra um erro.
        cout << "Erro ao abrir arquivo do grafo: " << nomeArquivo << endl;
        exit(1);
    }
}

void menuMatriz(grafoMatriz*);
void menuLista(grafoLista*);

int main (int argc, char* argv[]){
    //Confere se o numero de parametros está correto
    if(argc != 2){
        cout << "Número de parâmetros incorreto! Use: "<<argv[0]<<" <arquivo_entrada.txt>" << endl;
        return 0;
    }
    //Guardando o nome do arquivo de entrada
    string nomeEntrada = argv[1];
    unsigned short dir;
    unsigned short modo;
    do{
        cout << "Informe se o grafo e direcionado ou nao (0 = nao direcionado / 1 = direcionado): ";
        cin >> dir;
    }while (dir != 0 && dir != 1);
    do{
        cout << "Informe o modo de representacao (0 = lista de adjacencia / 1 = matriz de adjacencia): ";
        cin >> modo;
    }while (modo != 0 && modo != 1);

    if(dir == 0){
        if(modo == 0){
            cout << "Criando grafo nao direcionado com lista de adjacencia..." << endl;
            grafoLista* gl = criaGrafoLista(nomeEntrada, dir);
            menuLista(gl);
        }
        else{
            cout << "Criando grafo nao direcionado com matriz de adjacencia..." << endl;
            grafoMatriz* gm = criaGrafoMatriz(nomeEntrada, dir);
            menuMatriz(gm);
        }
    }
    else{
        if(modo == 0){
            cout << "Criando grafo direcionado com lista de adjacencia..." << endl;
            grafoLista* gl = criaGrafoLista(nomeEntrada, dir);
            menuLista(gl);
        }
        else{
            cout << "Criando grafo direcionado com matriz de adjacencia..." << endl;
            grafoMatriz* gm = criaGrafoMatriz(nomeEntrada, dir);
            menuMatriz(gm);
        }
    }
    return 0;
}

void menuMatriz(grafoMatriz* g){
    unsigned short menu;
    do{
        cout << endl;
        cout << "--------------------Menu--------------------" << endl;
        cout << "[0]. Sair." << endl;
        cout << "[1]. Apresentar informacoes do grafo." << endl;
        cout << "[2]. Imprimir a matriz de adjacencia." << endl;
        cout << "[3]. Adicionar um vértice." << endl;
        cout << "[4]. Remover um vértice e suas arestas." << endl;
        cout << "[5]. Adicionar uma aresta." << endl;
        cout << "[6]. Remover uma aresta." << endl;
        cout << "[7]. Verificar adjacência de dois vértices." << endl;
        cout << "[8]. Verificar o grau de um vértice." << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Digite a opcão desejada: ";
        cin >> menu;
        switch (menu){
            default:{
                cout << "Opcão inválida!" << endl;
                break;
            }
            case 0:{
                break;
            }
            case 1:{
                g->mostraInfo();
                break;
            }
            case 2:{
                g->imprimeMatriz();
                break;
            }
            case 3:{
                unsigned int ver1;
                cout << "Digite a ID do vértice: ";
                cin >> ver1;
                g->addVertice(ver1);
                break;
            }
            case 4:{
                unsigned int ver1;
                cout << "Digite a ID do vértice: ";
                cin >> ver1;
                g->removeVertice(ver1);
                break;
            }
            case 5:{
                unsigned int ver1, ver2;
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->verificaAdjacencia(ver1,ver2))
                    cout << "Aresta já existe!";
                else
                    g->addAresta(ver1,ver2);
                break;
            }
            case 6:{
                unsigned int ver1, ver2;
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(!g->verificaAdjacencia(ver1,ver2))
                    cout << "Aresta não existe!";
                else
                    g->removeAresta(ver1,ver2);
                break;
            }
            case 7:{
                unsigned int ver1, ver2;
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->verificaAdjacencia(ver1,ver2))
                    cout << "Os vértices são adjacentes.";
                else
                    cout << "Os vértices não são adjacentes.";
                break;
            }
            case 8:{
                unsigned int ver1;
                cout << "Digite a ID do vértice: ";
                cin >> ver1;
                cout << "O grau do vértice é: " << g->verificaGrau(ver1) << endl;
                break;
            }
        }
    }while (menu != 0);
}

void menuLista(grafoLista* g){
    unsigned short menu;
    do{
        cout << endl;
        cout << "--------------------Menu--------------------" << endl;
        cout << "[0]. Sair." << endl;
        cout << "[1]. Apresentar informacoes do grafo." << endl;
        cout << "[2]. Imprimir a lista de adjacencia." << endl;
        cout << "[3]. Adicionar um vértice." << endl;
        cout << "[4]. Remover um vértice e suas arestas." << endl;
        cout << "[5]. Adicionar uma aresta." << endl;
        cout << "[6]. Remover uma aresta." << endl;
        cout << "[7]. Verificar adjacência de dois vértices." << endl;
        cout << "[8]. Verificar o grau de um vértice." << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Digite a opcão desejada: ";
        cin >> menu;
        switch (menu){
            default:{
                cout << "Opcão inválida!" << endl;
                break;
            }
            case 0:{
                break;
            }
            case 1:{
                g->exibeInformacoes();
                break;
            }
            case 2:{
                g->imprimeGrafo();
                break;
            }
            case 3:{
                unsigned int ver1;
                cout << "Digite a ID do vértice: ";
                cin >> ver1;
                g->adicionaVertice(ver1);
                break;
            }
            case 4:{
                unsigned int ver1;
                cout << "Digite a ID do vértice: ";
                cin >> ver1;
                g->removeVertice(ver1);
                break;
            }
            case 5:{
                unsigned int ver1, ver2;
                int peso;
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->verificaAdjacencia(ver1,ver2))
                    cout << "Aresta já existe!";
                else{
                    if(g->getPonderado()){
                        cout << "Digite o peso da aresta: ";
                        cin >> peso;
                        g->adicionaAresta(ver1,ver2,peso);
                    }
                    else{
                        g->adicionaAresta(ver1,ver2,0);
                    }
                }
                break;
            }
            case 6:{
                unsigned int ver1, ver2;
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(!g->verificaAdjacencia(ver1,ver2))
                    cout << "Aresta não existe!";
                else
                    g->removeAresta(ver1,ver2);
                break;
            }
            case 7:{
                unsigned int ver1, ver2;
                cout << "Digite a ID do vértice origem: ";
                cin >> ver1;
                cout << "Digite a ID do vértice destino: ";
                cin >> ver2;
                if(g->verificaAdjacencia(ver1,ver2))
                    cout << "Os vértices são adjacentes.";
                else
                    cout << "Os vértices não são adjacentes.";
                break;
            }
            case 8:{
                unsigned int ver1;
                cout << "Digite a ID do vértice: ";
                cin >> ver1;
                cout << "O grau do vértice é: " << g->verificaGrau(ver1) << endl;
                break;
            }
        }
    }while (menu != 0);
}

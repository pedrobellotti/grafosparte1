#include "grafoLista.h"

grafoLista::grafoLista(){
    primeiro = nullptr;
    numeroV = 0;
    numeroA = 0;
    direcionado = false;
    ponderado = false;
}

grafoLista::~grafoLista(){
    Vertice* aux = primeiro;
    Vertice* prox = nullptr;
    while(aux != nullptr){
        prox = aux->getProximo();
        delete aux;
        aux = prox;
    }
    numeroV = 0;
    numeroA = 0;
    primeiro = nullptr;
}

void grafoLista::alteraPonderado(bool p){
    ponderado = p;
}

void grafoLista::alteraDirecionado(bool d){
    direcionado = d;
}

bool grafoLista::getPonderado(){
    return (ponderado ? true : false);
}

bool grafoLista::getDirecionado(){
    return (direcionado ? true : false);
}

void grafoLista::exibeInformacoes(){
    cout << "Número de vértices: " << numeroV << endl;
    cout << "Número de arestas: " << numeroA << endl;
    cout << "Grafo direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    cout << "Grafo ponderado: " << (ponderado ? "Sim" : "Não") << endl;
}

unsigned int grafoLista::getNumeroV(){
    return numeroV;
}

Vertice* grafoLista::getPrimeiro(){
    return primeiro;
}

//Adiciona um vertice ao grafo
void grafoLista::adicionaVertice(unsigned int idnovo){
    Vertice* novo = new Vertice(idnovo);
    Vertice* v = primeiro;
    if(v == nullptr)
        primeiro = novo;
    else{
        //Chega no ultimo vertice da lista
        for(v; v->getProximo() != nullptr; v=v->getProximo());
        v->setProximo(novo);
    }
    numeroV++;
}

//Adiciona uma aresta ao grafo
void grafoLista::adicionaAresta(unsigned int idorigem, unsigned int iddestino, int peso){
    Vertice* ori = nullptr;
    Vertice* dest = nullptr;
    //Encontrando a id
    for (Vertice* i = primeiro ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == idorigem)
            ori = i;
        else if(i->getId() == iddestino)
            dest = i;
    }
    //Se os vertices foram encontrados, cria a aresta e adiciona no vertice origem
    if(ori != nullptr && dest != nullptr){
        Aresta* nova = new Aresta();
        nova->setDestino(dest);
        nova->setPeso(peso);
        ori->adicionaArestaAux(nova);
        numeroA++;
    }
    else
        cout<<"Erro ao adicionar aresta: algum dos vértices não existe no grafo!"<<endl;
}

//Imprime a lista de adjacencia de cada vertice
/*
*   vO - vértice origem / vD - vértice destino / p - peso
*   O grafo é impresso da segunte forma:
*   Vertice vO-> (p)vD | (p)vD | (p)vD ...
*/
void grafoLista::imprimeGrafo(){
    if (ponderado){ //se for ponderado, imprime com os pesos
        for (Vertice* i = primeiro ; i != nullptr ; i=i->getProximo()){
            cout << "Vertice " << i->getId() << "-> ";
            for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                cout << "(" << a->getPeso() << ")" << a->getDestino()->getId() << " | ";
            cout<<endl;
        }
    }
    else
    {
        for (Vertice* i = primeiro ; i != nullptr ; i=i->getProximo()){
            cout << "Vertice " << i->getId() << "-> ";
            for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                cout << a->getDestino()->getId() << " | ";
            cout<<endl;
        }
    }
}

//Verifica adjacencia entre dois vertices do grafo
bool grafoLista::verificaAdjacencia(unsigned int v1, unsigned int v2){
    for (Vertice* i = primeiro ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == v1){
            for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                if(a->getDestino()->getId() == v2)
                    return true;
        }
        if(i->getId() == v2){
            for (Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima())
                if(a->getDestino()->getId() == v1)
                    return true;
        }
    }
    return false;
    if(direcionado){
        //fazer para grafos direcionados
    }
}

//Verifica se o vertice existe no grafo ou nao
bool grafoLista::verificaId(unsigned int id){
    for (Vertice* i = primeiro ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == id)
            return true;
    }
    return false;
}

//Remove um vertice e suas arestas do grafo
void grafoLista::removeVertice(unsigned int id){
    Vertice* excluir = nullptr;
    Vertice* anterior = nullptr;
    //Removendo o vértice da lista de adjacencia dos outros vertices
    for (Vertice* i = primeiro ; i != nullptr ; i=i->getProximo()){
            for(Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima()){
                if(a->getDestino()->getId() == id){
                    removeAresta(i->getId(),a->getDestino()->getId());
                }
            }
    }
    //Encontrando o vertice
    for (Vertice* i = primeiro ; i != nullptr ; i=i->getProximo()){
        //Se o vertice é o primeiro da lista, já exclui
        if(id == primeiro->getId()){
            excluir = primeiro;
            primeiro = primeiro->getProximo();
            numeroA -= excluir->getGrau();
            delete excluir;
            numeroV--;
            return;
        }
        if(i->getProximo()->getId() == id){
            excluir = i->getProximo();
            anterior = i;
            break;
        }
    }
    //Se o vertice nao foi encontrado, nao faz nada
    if(excluir == nullptr){
        cout << "Vértice não encontrado!" << endl;
        return;
    }
    else{
        anterior->setProximo(excluir->getProximo());
        numeroA -= excluir->getGrau();
        delete excluir;
        numeroV--;
        return;
    }
}

//Remove uma aresta do grafo
void grafoLista::removeAresta(unsigned int v1, unsigned int v2){
    Aresta* excluir = nullptr;
    Aresta* anterior = nullptr;
    Vertice* v = nullptr;
    //Encontrando a aresta
    for (Vertice* i = primeiro ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == v1){
            v = i; //Vertice para diminuir o grau
            for(Aresta* a = i->getPrimeira() ; a != nullptr ; a=a->getProxima()){
                //Se a aresta é a primeira da lista, já exclui
                if(a->getDestino()->getId() == v2){
                    excluir = i->getPrimeira();
                    i->setPrimeira(excluir->getProxima());
                    delete excluir;
                    numeroA--;
                    v->diminuiGrau();
                    return;
                }
                if(a->getProxima()->getDestino()->getId() == v2){
                    excluir = a->getProxima();
                    anterior = a;
                    break;
                }
            }
        }
    }
    //Se a aresta nao foi encontrada, nao faz nada
        if(excluir == nullptr){
        cout << "Aresta não encontrada!" << endl;
        return;
    }
    else{
        anterior->setProxima(excluir->getProxima());
        v->diminuiGrau();
        delete excluir;
        numeroA--;
        return;
    }
}

//Verifica o grau de um vertice
unsigned int grafoLista::verificaGrau(unsigned int g){
    for (Vertice* i = primeiro ; i != nullptr ; i=i->getProximo()){
        if(i->getId() == g)
            return i->getGrau();
    }
}
//---------------------------------------------------------------------------------------------------
// arquivo :    graph.h
// descricao :  cabecalho para grafo direcionado do tp1 de Algoritmos I
// autor :  augusto guerra de lima augustoguerra@dcc.ufmg.br
// historico :  20241102 arquivo criado
//---------------------------------------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include<bits/stdc++.h>
using namespace std;

// classe   : graph_c
// descricao :  modela o problema das cidades utilizando um grafo direcionado
// a escolha de um unordered_map se deve ao fato de os vertices nao serem numericamente indexados
class graph_c
{
    public:
        int V,E;
        string capital;
        unordered_map<string,list<string>>adj;

        graph_c(int _V):V(_V),E(0){}
        ~graph_c(){}

        void add_edge(string& u, string& v);
        void print();

        void determine_capital();
    
    private:
        int bfs(string s);
};

#endif
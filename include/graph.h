//=================================================================
// arquivo  : graph.h
// descricao    : cabecalho da estrutura de grafo direcionado
// autor    : Augusto Guerra de Lima augustoguerra@dcc.ufmg.br
// historico    : ultima atualizacao 20241113
//=================================================================

#ifndef GRAPH_H
#define GRAPH_H

#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;

// classe   : graph_c
// descricao    : armazena a lista de adjacencia bem como informacoes relevantes para o grafo direcionado
// o trabalho foi todo feito utilizando numeros inteiros com um mapeamento de inteiros para o nome dos 
// centros urbanos (strings)
class graph_c
{
    public:
        int V,E;
        
        int capital;
        vector<pair<int,int>>battalions;
        int patrols;

        vector<int>capital_distances; // distancias da capital ate cada vertice
        vector<int>colors;            // colorir e separar  as SCCs do grafo direcionado
        vector<vector<int>>SCC_components;

        unordered_map<string,int>toInt;
        unordered_map<int,string>toString;

        vector<vector<pair<int,int>>>adj;
        vector<pair<int,int>>edges_list; // para cada aresta determina seus vertices (u,v)

        graph_c(int _V);
        ~graph_c(){}

        void add_edge(string&u,string&v);
        void print();

        void determine_capital();
        void determine_battalions();

        void list_battalions();
        void determine_patrols();

    private:
        int bfs(int i, vector<int>&distances);
        
        void dfs(int s,vector<bool>&visit, stack<int>&S);
        void dfs_SCC(int s, vector<bool>&visit, int color, graph_c* G);
        void kosaraju_SCC();
        int bfs_criteria(int s);
        graph_c* transpose();

        void bfs_parentage(int s, vector<pair<int,int>>&P);
        void path_patrol(int s);
};

#endif
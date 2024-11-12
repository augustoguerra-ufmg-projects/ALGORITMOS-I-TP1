#ifndef GRAPH_H
#define GRAPH_H

#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;

class graph_c
{
    public:
        int V,E;
        
        int capital;
        vector<pair<int,int>>battalions;
        int patrols;

        vector<int>capital_distances; // distancia da capital para cada vertice
        vector<int>colors; // cor de cada vertice SCC
        vector<vector<int>>SCC_components; // lista de componentes fortemente conexas do grafo

        unordered_map<string,int>toInt;
        unordered_map<int,string>toString;

        vector<vector<pair<int,int>>>adj;
        vector<pair<int,int>>edges_list; // indice da aresta para o par de vertices que as liga

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
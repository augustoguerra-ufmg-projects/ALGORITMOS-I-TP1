#ifndef GRAPH_H
#define GRAPH_H

#include<bits/stdc++.h>
using namespace std;

class graph_c
{
    public:
        int V,E;
        unordered_map<string,list<string>>adj;

        graph_c(int _V):V(_V),E(0){}
        ~graph_c(){}

        void add_edge(string& u, string& v);
        void print();
};

#endif
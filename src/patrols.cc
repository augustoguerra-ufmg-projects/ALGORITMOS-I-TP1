#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

// metodo   : path_patrol
// descricao    : descreve um circuito nas arestas de uma
// componente conexa
void graph_c::path_patrol(string&s)
{
    vector<string>patrol_path;
    unordered_map<string,bool>visit;

    stack<string>S;
    S.push(s);

    while(!S.empty())
    {
        string u=S.top();
        S.pop();
        patrol_path.push_back(u);

        for(string&v:this->adj[u])
        {
            string edge=u+","+v;

            if(colors[v]==colors[u] and !visit[edge])
            {
                visit[edge]=1;
                S.push(v);
            }
        }
    }
    
    for(size_t i=0; i<patrol_path.size()-1;i++)
    {
        cout<<patrol_path[i]<<" ";
    }
    cout<<endl;
}

// metodo   : determine_patrols
// descricao    : determina para as componentes fortemente conexas seus
// possiveis patrulhamentos
void graph_c::determine_patrols()
{
    cout<<this->patrols<<endl;
    for(size_t i=0; i<battalions.size(); i++)
        if(this->battalions[i].second>1)
        {
            string battalion=this->battalions[i].first;
            path_patrol(battalion);
        }
}
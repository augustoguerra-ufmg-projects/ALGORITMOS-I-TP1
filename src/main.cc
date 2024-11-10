//---------------------------------------------------------------------------------------------------
// arquivo :    main.cc
// descricao :  codigo principal para processamento de entradas do tp1 de Algoritmos I
// autor :  augusto guerra de lima augustoguerra@dcc.ufmg.br
// historico :  20241102 arquivo criado
//---------------------------------------------------------------------------------------------------

#include<bits/stdc++.h>
#include"../include/graph.h"
using namespace std;

int main()
{
    int n,m;cin>>n>>m;

    graph_c G(n);

    string u,v;
    for(int i=0;i<m;i++)
    {
        cin>>u>>v;
        G.add_edge(u,v);
    }

    // G.print();

    G.determine_capital();
    cout<<G.capital<<"\n";

    G.determine_battalions();
    G.list_battalions();

    G.determine_patrols();

    return(0);
}
#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
using namespace std;

class vertex_c
{
	public:
	string name;

	vertex_c(string _name):name(_name){}
	~vertex_c(){}
}

class edge_c
{
	public:
	vertex_c vertex;
	int index;
	edge_c* next;
	
	edge_c(string _name);
	~edge_c();
}

class adj_list_c
{
	public:
	bool capital, battalion;
	edge_c* head;

	adj_list_c();
	~adj_list_c();
}

class graph_c
{
	public:
		int V, E;
		graph(int _V);
		~graph();

		void print();
}

#endif

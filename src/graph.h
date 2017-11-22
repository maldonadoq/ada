#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include "edge.h"

using namespace std;

class graph{ 
public:
	vector<vector<edge>> l_adj;				//list of adj
    unsigned Vcnt, Ecnt; 
    bool digraph;

	graph(unsigned V, bool digraph = false){ 
		this->Vcnt = V;
		this->Ecnt = 0;
		this->digraph = digraph;
		this->l_adj.resize(V);
    }

	unsigned V() const{	return this->Vcnt;	}
	unsigned E() const{	return this->Ecnt;	}
	bool directed() const{	return this->digraph;	}
	bool edge_(unsigned _w, unsigned _v){	
		for(unsigned i=0; i<this->l_adj[_w].size(); i++)
			if(this->l_adj[_w][i].v == _v)	return true;
		return false;	
	}

	void insert(edge_tmp a){
		this->l_adj[a.w].push_back(edge(a.v,a.p));
		Ecnt++;
	}

	~graph(){		}
};

#endif
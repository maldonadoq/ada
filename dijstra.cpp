#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;


class Edge{
public:
	int w,v,p;
	Edge(int _w, int _v, int _p){
		this->w = _w;
		this->v = _v;
		this->p = _p;
	}
};

class GRAPH{ 
public:
	vector <vector<int>> adj;
    int Vcnt, Ecnt; 
    bool digraph;

	GRAPH(int V, bool digraph = false) : adj(V), Vcnt(V), Ecnt(0), digraph(digraph) { 
		for (int i = 0; i < V; i++) 
			adj[i].assign(V,0);
    }

	~GRAPH();
	int V() const{	return this->Vcnt;	}
	int E() const{	return this->Ecnt;	}
	bool directed() const{	return this->digraph;	}

	void insert(Edge a){
		this->adj[a.w][a.v] = a.p;
		Ecnt++;
	}

	bool edge(int _w, int _v){
		return (this->adj[_w][_w] == 0)?	false: true;
	}

    class adjIterator{
	const GRAPH &G;
		int i, v;
	public:
		adjIterator(const GRAPH &G, int v) :  G(G), v(v), i(-1) { }
		int beg() { i = -1; return nxt(); }
	  	int nxt() {
			for (i++; i < G.V(); i++)
				if (G.adj[v][i] != 0) return i;
	      	return -1;
    	}
  		bool end() { return i >= G.V(); }
    };
};


template <class Graph> 
vector<Edge> edges(Graph &G){ 
	int E = 0;
    vector <Edge> a(G.E());
    for (int v = 0; v < G.V(); v++){
        typename Graph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt()) 
			if (G.directed() || v < w)
			a[E++] = Edge(v, w);
	}
    return a;
}

template <class Graph> 
void show(const Graph &G){ 
	for (int s = 0; s < G.V(); s++){
		cout.width(2); cout << s << ":";
		typename Graph::adjIterator A(G, s);
		for (int t = A.beg(); !A.end(); t = A.nxt()){
			cout.width(2); cout << t << " ";
		}
        cout << endl;
	}
}

GRAPH * scan(){
	int v, e;
	cin >> v >> e;
	
	GRAPH *a = new GRAPH(v,true);
	int x,y,z;
	for(int i=0; i<e; i++){
		cin >> x >> y >> z;
		a->insert(Edge(x,y,z));
	}

	return a;
}

int main(int argc, char const *argv[]){	
	GRAPH *a = scan();
	show(*a);

	return 0;
}

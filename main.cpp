#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <list>
#include <queue>

#define infty 10000000

using namespace std;

// cola de prioridad
template<class T>
class prqueue{
public:
	list<T> a;
	typedef typename list<T>::iterator	niterator;
	
	prqueue(){	};
	prqueue(T w){	this->end = w;	}

	void push(T x){
		niterator it = a.begin();
		for(; it!=a.end(); it++)
			if(x.second<=(*it).second)	break;
		a.insert(it, x);
	}

	void pop(){	a.pop_front();	}

	T top(){
		niterator it = a.begin();
		return *it;
	}

	bool empty(){	return	a.empty();	}
	unsigned size(){	return a.size();	}
};


class edge{
public:
	int w,v,p;
	bool m_v;
	edge(int _w, int _v, int _p){
		this->w = _w;
		this->v = _v;
		this->p = _p;
		this->m_v = false;
	}
};

class graph{ 
public:
	vector<vector<int>> m_adj;				//matriz of adj
	vector<vector<edge>> l_adj;				//list of adj
	vector<pair<unsigned,unsigned>> m_v;	//priority queue node
    int Vcnt, Ecnt; 
    bool digraph;

	graph(int V, bool digraph = false) : m_adj(V), Vcnt(V), Ecnt(0), digraph(digraph) { 
		for (int i = 0; i < V; i++){
			this->m_adj[i].assign(V,0);
			this->m_v.push_back(pair<unsigned,unsigned>(i,infty));
		}
		this->l_adj.resize(V);
    }

	~graph();
	int V() const{	return this->Vcnt;	}
	int E() const{	return this->Ecnt;	}
	bool directed() const{	return this->digraph;	}
	bool edge_(int _w, int _v){	return (this->m_adj[_w][_w] == 0)?	false: true;	}
	void pull();
	void dijkstra(int,int);
	void reset(){
		for(unsigned i=0; i<this->m_v.size(); i++){
			this->m_v[i] = pair<unsigned,unsigned>(i,infty);
			for(unsigned j=0; j<this->l_adj[i].size(); j++)
				this->l_adj[i][j].m_v = false;
		}
	}

	void insert(edge a){
		this->m_adj[a.w][a.v] = a.p;
		Ecnt++;
	}

    class adjIterator{
    private:
		const graph &G;
		int i, v;
	public:
		adjIterator(const graph &G, int v) :  G(G), v(v), i(-1) { }
		int beg(){ i = -1; return nxt(); }
	  	int nxt(){
			for (i++; i < G.V(); i++)
				if (G.m_adj[v][i] != 0) return i;
	      	return -1;
    	}
  		bool end() { return i >= G.V(); }
    };
};

void graph::pull(){
	for(unsigned i=0; i<Vcnt; i++){
		for(unsigned j=0; j<Vcnt; j++)
			if(this->m_adj[i][j] != 0)
				this->l_adj[i].push_back(edge(i,j,this->m_adj[i][j]));
	}
}

void graph::dijkstra(int a, int b){
	if(a>=this->Vcnt or a==b){
		cout << "doesn't exist road [" << a << "->" << b << "]" << endl;
		return;
	}

	this->m_v[a].second = 0;
	prqueue<pair<unsigned,unsigned>> pq;
	pq.push(this->m_v[a]);
	pair<unsigned,unsigned> tmp;
	unsigned j;

	//l_adj para no hacer preguntas de más en m_adj!!
	vector<vector<int>> m_road(this->Vcnt);
	vector<int> cam_m(infty);
	while(!pq.empty()){
		tmp = pq.top();	pq.pop();
		for(int i=0; i<this->l_adj[tmp.first].size(); i++){
			j = this->l_adj[tmp.first][i].v;
			if(!this->l_adj[tmp.first][i].m_v and 
				(this->m_v[j].second >= (this->m_v[tmp.first].second + this->l_adj[tmp.first][i].p))){

				m_road[j] = m_road[tmp.first];
				m_road[j].push_back(j);

				if(j == b and cam_m.size()>m_road[j].size())	cam_m = m_road[j];

				this->m_v[j].second = this->m_v[tmp.first].second + this->l_adj[tmp.first][i].p;
				this->l_adj[tmp.first][i].m_v = true;
				pq.push(this->m_v[j]);
			}
		}
	}

	if(cam_m.size() == infty){
		cout << "doesn't exist road [" << a << "->" << b << "]" << endl;
		return;
	}

	cout << a;
	for(unsigned k=0; k<cam_m.size(); k++)
		cout << " " << cam_m[k];
	cout << endl;
	m_road.clear();
	cam_m.clear();
}


template <class graph> 
vector<edge> edges(graph &G){ 
	int E = 0;
    vector <edge> a(G.E());
    for (int v = 0; v < G.V(); v++){
        typename graph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt()) 
			if (G.directed() || v < w)
			a[E++] = edge(v, w);
	}
    return a;
}

template<class graph> 
void show(const graph &G){ 
	for (int s = 0; s < G.V(); s++){
		cout.width(2); cout << s << ":";
		typename graph::adjIterator A(G, s);
		for (int t = A.beg(); !A.end(); t = A.nxt()){
			cout.width(2); cout << t << " ";
		}
        cout << endl;
	}
}

template<class graph>
void print(const graph &G){
	for(int i=0; i<G.l_adj.size(); i++){
		cout << i << ":	";
		for(int j=0; j<G.l_adj[i].size(); j++)
			cout << G.l_adj[i][j].v << "|" << G.l_adj[i][j].p << "\t";
		cout << endl;
	}
}

graph * scan(){
	int v, e, rd, b, c;
	cin >> v >> e;
	
	graph *a = new graph(v,false);
	int x,y,z;
	for(int i=0; i<e; i++){
		cin >> x >> y >> z;
		a->insert(edge(x,y,z));
	}

	cin >> rd;
	a->pull();
	for(int i=0; i<rd; i++){
		cin >> b >> c;
		a->reset();
		a->dijkstra(b,c);
	}

	return a;
}

int main(int argc, char const *argv[]){	
	graph *a = scan();
	print(*a);
	return 0;
}

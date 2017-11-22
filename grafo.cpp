#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <map>
#include <unistd.h>
#include <sys/time.h>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <fstream>

#define infty 99999.9

using namespace std;

class cedge{
public:
	unsigned v,w;
	double p;
	cedge(unsigned _v, unsigned _w, double _p){
		this->v = _v;
		this->w = _w;
		this->p = _p;
	}
};

class cgrafo{
private:
	vector<map<int, double>>	m_list_adj;
	int vcnt;
	int ecnt;
public:
	cgrafo(int n_v){
		m_list_adj = vector<map<int, double>>(n_v);
		vcnt = n_v;
		ecnt = 0;
	}
	void insert(cedge e){
		m_list_adj[e.v][e.w] = e.p;
		ecnt++;
	}

	void remove(int u, int v){
		m_list_adj[u].erase(v);
		ecnt--;
	}

	double edge(int u, int v){
		return (m_list_adj[u].find(v) != m_list_adj[u].end())? m_list_adj[u][v]: infty;
	}

	vector<int> edgev(int a){
		vector<int> n;
		for (auto it = m_list_adj[a].begin(); it!=m_list_adj[a].end(); ++it)
			n.push_back(it->first);

		return n;
	}
	int V() const{ return vcnt; }
	int E() const{ return ecnt; }
};


void dijkstra(cgrafo &graph, int a, vector<double> &dist, vector<int> &pred){
	typedef pair<double, int> distance;

	priority_queue<distance,vector<distance>,greater<distance>> pq;
	distance x;
	vector<bool> vist(graph.V(), false);

	dist = vector<double>(graph.V(), infty);
	pred = vector<int>(graph.V(), -1);
	dist[a] = 0;

	pq.push(distance(dist[a], a));

	vector<int> vec;
	int y;

	while (!pq.empty()){
		x = pq.top();
		if (vist[x.second] == false){
			vec = graph.edgev(x.second);
			for (int i = 0; i < vec.size(); ++i){
				y = vec[i];
				if (vist[y] == false and graph.edge(x.second, y) > 0 and dist[x.second] + graph.edge(x.second, y) < dist[y]){
					dist[y] = dist[x.second] + graph.edge(x.second, y);
					pred[y] = x.second;
					pq.push(distance(dist[y], y));
				}
			}
			vist[x.second] = true;
		}
		pq.pop();
	}
}

void path(vector<int> &pred, int start, int end){
	if (pred[end] == -1){
		cout << "doesn't exist path" << endl;
		return;
	}
	else{
		while (end != start){
			cout << end << " ";
			end = pred[end];
		}
		cout << end << endl;
	}
}

void scan(bool rw, unsigned qu){
	int v,e,a,b;
	double p;
	vector<double> dist;
	vector<int> pred;

	cin >> v >> e;

	cgrafo graph(v);

	for (int i = 0; i < e; ++i){
		cin >> a >> b >> p;
		graph.insert(cedge(a, b, p));
	}

	string name = "path.bin";
	struct timeval ti, tf;
	double ttime;

	if(rw){
		ofstream wfile(name, ios::out | ios::binary);
		wfile.seekp(0);
		gettimeofday(&ti, NULL);

		for (unsigned i=0; i<v; i++){
			dijkstra(graph, i, dist, pred);
			wfile.write(reinterpret_cast<const char*>(&pred[0]), v*sizeof(int));
		}

		gettimeofday(&tf, NULL);
		ttime = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
		printf("dijkstra %d :  %.10f s\n",v,ttime/1000);
		wfile.close();
	}
	else{
		ifstream rfile(name, ios::in | ios::binary);
		gettimeofday(&ti, NULL);
		srand(time(NULL));
		for(unsigned j=0; j<qu; j++){
			int start = rand()%v, end = rand()%v;
			rfile.seekg(sizeof(int)*start*v);
			vector<int> rpred(v);
			rfile.read(reinterpret_cast<char*>(&rpred[0]), v*sizeof(int));
			path(rpred, start, end);
		}

		gettimeofday(&tf, NULL);
		ttime = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
		printf("%d query's:  %.10f s\n",qu,ttime/1000);

		rfile.close();
	}
}

int main(int argc, char const *argv[]){
	if(argc>2)
		scan(stoi(argv[1]),stoi(argv[2]));
	else cout << "wrong args" << endl;
	return 0;
}

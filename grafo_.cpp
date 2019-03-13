#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <list>
#include <queue>
#include <vector>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <algorithm>
#include "src/grafo.h"
#include "src/traits.h"

#define infty 1<<15

using namespace std;

typedef traits<int,float> shell;
// creación de binario 38 GB
void create_binary(string name, unsigned t){
	ofstream cfile(name, ios::binary);	cfile.close();

	ofstream file(name, ios::in | ios::binary);
	int a = -1;
	file.seekp(0, ios::end);
	for(unsigned i=0; i<t; i++){
		for(unsigned j=0; j<t; j++){
			file.write((char *)&a,sizeof(int));
		}
	}
	
	file.close();
}

void update(ofstream &file, vector<unsigned> &v, unsigned s, unsigned e, unsigned ver){
	unsigned st = s;
	if(v.size()==0){
		int tmp = -2;
		file.seekp(sizeof(int)*((st*ver)+e), ios::beg);
		file.write((char*)&tmp,sizeof(int));
	}
	else{
		for(unsigned i=0; i<v.size(); i++){
			file.seekp(sizeof(int)*((st*ver)+e), ios::beg);
			file.write((char*)&v[i],sizeof(int));
			st = v[i];
		}
	}
}

int get(ifstream &file, unsigned f){
	int a;
	file.seekg(sizeof(int)*f, ios::beg);
	file.read((char*)(&a),sizeof(int));
	return a;
}

void print(unsigned a, vector<unsigned> &v){
	if(v.size()==0){
		cout << "doesn't exist path" << endl;
		return;
	}
	cout << a << " ";
	for(unsigned j=0; j<v.size(); j++)
		cout << v[j] << " ";
	cout << endl << endl;
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

void scan(bool rw, unsigned t){
	cgrafo<shell> *gr = new cgrafo<shell>();

	unsigned v,e,a,b,i,j,k;
	int u,bl;
	float p;
	cin >> v >> e;
	for(i=0; i<v; i++)
		gr->insert_node(i);

	for(i=0; i<e; i++){
		cin >> a >> b >> p;
		gr->insert_edge(p,a,b,0);
	}

	srand(time(NULL));
	struct timeval ti, tf;
	double ttime;
	string name;

	name = "path.bin";
    if(rw){		
    	create_binary(name,v);
    	vector<vector<unsigned>> tmp;
    	ifstream ifile(name, ios::binary | ios::app);
    	ofstream ofile(name, ios::in | ios::binary);
	    gettimeofday(&ti, NULL);
		for(unsigned i=0; i<v; i++){
			bl = get(ifile,(v*a)+b);
			if(bl == -1){
				tmp = gr->dijkstra(a);
				for(unsigned j=0; j<v; j++)
					update(ofile,tmp[j],a,j,v);
	        }
		}

		gettimeofday(&tf, NULL);
		ttime = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
		printf("dijkstra:  %.10f s\n",ttime/(1000));
	}
	else{
		ifstream rfile(name, ios::in | ios::binary);
		gettimeofday(&ti, NULL);
		srand(time(NULL));
		for(unsigned j=0; j<t; j++){
			int start = rand()%v, end = rand()%v;
			rfile.seekg(sizeof(int)*start*v);
			vector<int> rpred(v);
			rfile.read(reinterpret_cast<char*>(&rpred[0]), v*sizeof(int));
			path(rpred, start, end);
		}

		gettimeofday(&tf, NULL);
		ttime = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
		printf("%d query's:  %.10f s\n",t,ttime/1000);

		rfile.close();
	}
	delete gr;
}

int main(int argc, char const *argv[]){
	if(argc>2)
		scan(stoi(argv[1]),stoi(argv[2]));
	else cout << "wrong args" << endl;
    return 0;
}
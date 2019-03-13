#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include "src/grafo.h"
#include "src/traits.h"

const bool pr = true;

using namespace std;

typedef traits<int,float> shell;

void create_binary(string name, unsigned t){
	ofstream cfile(name, ios::binary);	cfile.close();
	ofstream file(name, ios::in | ios::binary);

	int a = -1;
	file.seekp(0, ios::end);
	for(unsigned i=0; i<t; i++)
		for(unsigned j=0; j<t; j++)
			file.write((char *)&a,sizeof(int));
	
	file.close();
}

void update(string name, vector<unsigned> &v, unsigned s, unsigned e, unsigned ver){
	ofstream file(name, ios::in | ios::binary);
	unsigned st = s;
	for(unsigned i=0; i<v.size(); i++){
		file.seekp(sizeof(int)*((st*ver)+e), ios::beg);
		file.write((char*)&v[i],sizeof(int));
		st = v[i];
	}
	file.close();
}

int get(string name, unsigned f){
	ifstream file(name, ios::binary | ios::app);
	int a;
	file.seekg(sizeof(int)*f, ios::beg);
	file.read((char*)(&a),sizeof(int));
	file.close();
	return a;
}

void print(vector<vector<unsigned>> &v){
	for(unsigned i=0; i<v.size(); i++){
		for(unsigned j=0; j<v[i].size(); j++)
			cout << v[i][j] << " ";
		cout << endl;
	}
}

void search_dikjstra(cgrafo<shell> *a, unsigned s, vector<vector<unsigned>> *v){
	*v = a->dijkstra(s);
}

void scan(){
	cgrafo<shell> *gr1 = new cgrafo<shell>();
	cgrafo<shell> *gr2 = new cgrafo<shell>();
	cgrafo<shell> *gr3 = new cgrafo<shell>();
	cgrafo<shell> *gr4 = new cgrafo<shell>();

	unsigned v,e,a,b,i,j,k;
	int u;
	float p;
	cin >> v >> e;
	for(i=0; i<v; i++){
		gr1->insert_node(i);
		gr2->insert_node(i);
		gr3->insert_node(i);
		gr4->insert_node(i);
	}

	for(i=0; i<e; i++){
		cin >> a >> b >> p;
		gr1->insert_edge(p,a,b,0);
		gr2->insert_edge(p,a,b,0);
		gr3->insert_edge(p,a,b,0);
		gr4->insert_edge(p,a,b,0);
	}

	//csearch<shell> *yas = new csearch<shell>(gr);

	srand(time(NULL));
	unsigned t = 10;
	struct timeval ti, tf;
	double time;
	string name;

	name = "pred.bin";

	if(!pr){
		gettimeofday(&ti, NULL);
		create_binary(name,v);
		gettimeofday(&tf, NULL);

		time = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
		printf("create binary:  %.10f s\n",time/1000);

		gettimeofday(&ti, NULL);
		vector<vector<unsigned>> tmp1, tmp2, tmp3, tmp4;

		unsigned tw;
		for(i=0; i<v/4; i++){
			thread t1(&search_dikjstra,gr1,i*4,&tmp1);
			thread t2(&search_dikjstra,gr2,(i*4)+1,&tmp2);
			thread t3(&search_dikjstra,gr3,(i*4)+2,&tmp3);
			thread t4(&search_dikjstra,gr4,(i*4)+3,&tmp4);
			t1.join();	t2.join();	t3.join();	t4.join();

			for(j=0; j<v; j++){
				tw = i*4;
				if(get(name,(tw*v)+j) == -1)
					update(name,tmp1[j],tw,j,v);
				if(get(name,((tw+1)*v)+j) == -1)
					update(name,tmp2[j],tw+1,j,v);
				if(get(name,((tw+2)*v)+j) == -1)
					update(name,tmp3[j],tw+2,j,v);
				if(get(name,((tw+3)*v)+j) == -1)
					update(name,tmp4[j],tw+3,j,v);
			}

		}

		gettimeofday(&tf, NULL);
		time = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
		printf("dijkstra:  %.10f\n",time/1000);
	}
	
	else{
		gettimeofday(&ti, NULL);
		for(i=0; i<t; i++){
			//a = rand()%v;	b = rand()%v;
			if(get(name,(v*a)+b) == -1){
				cout << "doesn't exist path" << endl;
				continue;
			}
			cout << a << " ";
			u = a;
			while(u!=b){
				u = get(name,(u*v)+b);
				cout << u << " ";
			}
			cout << endl;
		}

		gettimeofday(&tf, NULL);
		time = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
		printf("\n%d query's:  %.10f\n",t,time/1000);
	}

	delete gr1;
	delete gr2;
	delete gr3;
	delete gr4;
}

int main(int argc, char const *argv[]){
	scan();
    return 0;
}
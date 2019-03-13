#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <utility>
#include <time.h>
//#include "src/graph.h"
//#include "src/edge.h"

#define infty 10000000.0
static unsigned zp;

using namespace std;

/*No uso el grafo, bueno si, pero lo saqué, por que al final
no lo uso, solo defrente cargo mi matriz en floy warshall*/

class floyd_warshall{
public:
	float **W;
	float **P;
	unsigned size;

	floyd_warshall(unsigned _size){
		this->size = _size;
		this->W = new float*[this->size];
		this->P = new float*[this->size];

		for(unsigned i=0; i<this->size; i++){
			this->W[i] = new float[this->size];
			this->P[i] = new float[this->size];
			for(unsigned j=0; j<this->size; j++){
				this->W[i][j] = infty;
				this->P[i][j] = -1;
			}
			this->W[i][i] = 0;
		}
	}

	void insert(unsigned a, unsigned b, float p){
		this->W[a][b] = p;
		this->P[a][b] = b;
	}

	void execute(){
	    for(unsigned k=0; k<this->size; k++){
	        for(unsigned i=0; i<this->size; i++){
	            for(unsigned j=0; j<this->size; j++){
	                if(this->W[i][k] + this->W[k][j] < this->W[i][j]){
	                    this->W[i][j] = this->W[i][k] + this->W[k][j];
	                    this->P[i][j] = this->P[i][k];
	                }
	            }
	        }
	    }
	}

	void all_path(){
		for(unsigned i=0; i<this->size; i++){
			for(unsigned j=0; j<this->size; j++)
				this->find(i,j);
			cout << endl;
		}
	}

	void print_predecesor(){
		for(unsigned i=0; i<this->size; i++){
			for(unsigned j=0; j<this->size; j++)
				cout << this->P[i][j] << " ";
			cout << endl;
		}
	}

	void find(unsigned a, unsigned b){
		if(this->P[a][b] == -1){
			cout << "doesn't exist road [" << a << "," << b << "]" << endl;
			return;
		}

		unsigned u = a;
		cout << "[" << a << "," << b << "]: " << this->W[a][b] << "\t" << u << " ";
		while(u!=b){
			u = this->P[u][b];
			cout << u << " ";
		}
		cout << endl;
	}
};

void scan(){
	unsigned v, e, b, c, nq, i, sq, j;
	struct timeval ti, tf;
	float p;
	double tim;

	cin >> v >> e;
	floyd_warshall fw(v);

	for(i=0; i<e; i++){
		cin >> b >> c >> p;
		fw.insert(b,c,p);
	}

	gettimeofday(&ti, NULL);
	
	fw.execute();
	
	gettimeofday(&tf, NULL);
	tim = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
	printf("floyd warshall time:\t%.8lf s\n",tim/1000);


	fw.print_predecesor();
	fw.find(9,7);
	fw.find(1,8);

	/*srand(time(NULL));
	sq = v/10;
	for(j=1; j<=10; j++){
		nq = j*sq;
		gettimeofday(&ti, NULL);

		for(i=0; i<nq; i++)	fw.find(rand()%v, rand()%v);
		
		gettimeofday(&tf, NULL);
	    tim = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
	    printf("%d\t%.8lf\n", nq,tim);
	}*/
}

int main(int argc, char const *argv[]){	
	scan();
	return 0;
}
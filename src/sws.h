#ifndef _SWS_H_
#define _SWS_H_

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>

using namespace std;

bool linear_search(int *a, int t, int x){
    for(int i=0; i<t; i++)
        if(*(a+i) == x) return true;
    return false;
}

double time(int *a, int t, void (*p)(int *, int)){
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    p(a, t);
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    return tiempo;
}

void dat_t(FILE *a, int *A, int t, void (*p)(int *, int)){
    double tim = (double)(time(A, t,p)/1000);
    fprintf(a, "%lf\t", tim);
}

void rand_(int *a, int t){
	srand(time(NULL));
	for(int i=0; i<t; i++)	*(a+i) = rand()%(2*t);
}

void min_to_max(int *a, int t){
	for(int i=0; i<t; i++)	*(a+i) = i;
}

void max_to_min(int *a, int t){
	for(int i=0; i<t; i++)	*(a+i) = t-i-1;
}

void swap_(int *a, int *b){
	int r = *a;
	*a = *b;
	*b = r;
}

void print_(int *a, int t){
    for(int i=0; i<t; i++)  cout << *(a+i) << " ";
    cout << endl;
}

template<class T>
void print(vector<T> const &v){
    if(v.empty())   cout << "this vector is empty!";
    for(unsigned i=0; i<v.size(); i++)  cout << v[i] << " ";
    cout << endl;
}

template<class T>
void print_twod(vector<T> &v){
    if(v.empty())   cout << "this vector is empty!";
    for(unsigned i=0; i<v.size(); i++){
        for(unsigned j=0; j<v[i].size(); j++)
            cout << v[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

template<class T>
void print_graph(const T &G){
    for(int i=0; i<G.l_adj.size(); i++){
        cout << i << ": ";
        for(int j=0; j<G.l_adj[i].size(); j++)
            cout << G.l_adj[i][j].v << "|" << G.l_adj[i][j].p << "\t";
        cout << endl;
    }
}

#endif

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

static unsigned nc=0, nc1=0;

template<class T>
void swap1 (T &a, T &b){
	T tm = a;
	a = b;
	b = tm;
}

int random(int i, int s){
	return (rand()%(s-i))+i;
}

template<class T>
int wp_(vector<T> &v, int i, int f){
	int idx = i;
	for(int k=i+1; k<f; k++){
		if(v[idx]>v[k]){
			idx = k;
		}
	}
	return idx;
} 

template <class T>
void quick_sort(vector<T> &v, int iz, int de){
	int i,j,x;
    i = iz; 
    j = de; 
    //x = v[(iz+de)/2];
    //x = v[random(iz,de)];
    x = v[wp_(v,iz,de)];

    while(i<=j){
        while((v[i]<x) and (j<=de)){	i++;	nc++;	}
        while((x<v[j]) and (j>iz)){	j--;	nc++;	}
 
        if(i<=j){ 
            swap1(v[i], v[j]);
            i++;  j--; 
        }
         
    }
    
    if(iz<j)  quick_sort(v, iz, j); 
    if(i<de)  quick_sort(v, i, de);
}

template <class T>
void quick(vector<T> &v, int iz, int de){
	int i,j,x;
    i = iz; 
    j = de; 
    x = v[random(iz,de)];
    while(i<=j){
        while((v[i]<x) and (j<=de)){	i++;	nc1++;	}
        while((x<v[j]) and (j>iz)){	j--;	nc1++;	}
 
        if(i<=j){ 
            swap1(v[i], v[j]);
            i++;  j--; 
        }        
    }
    
    if(iz<j)  quick(v, iz, j); 
    if(i<de)  quick(v, i, de);
}


template<class T>
void print_(vector<T> v){
	for(unsigned i=0; i<v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

int main(int argc, char const *argv[]){
	vector<int> v, w;
	unsigned nt = 50000;
	int rd;
	srand(time(NULL));
	for(unsigned t = 1000; t<=nt; t+=1000){
		for(unsigned i=0; i<t; i++){
			rd = rand()%t;
			v.push_back(rd);
			w.push_back(rd);
		}
		quick_sort(v,0,t-1);
		quick(w,0,t-1);
		v.clear();	w.clear();
		cout << t << "\t" << nc << "\t" << nc1 << endl;
		nc = 0;	nc1 = 0;
	}
	return 0;
}
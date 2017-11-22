#include <iostream>
#include <stdio.h>
#include "src/sws.h"
#include <vector>
#include <stack>

using namespace std;

unsigned furthest(vector<int> &v, unsigned cl, unsigned r){
	unsigned idx;
	//if((v[cl+1]-v[cl]) > r)	return 0;
	//for(idx=cl; idx<v.size() and (v[idx+1]-v[cl]) <= r; idx++);
	(cl+r > v.size())? idx=v.size()-1: idx=cl+r;
	for(; idx<v.size() and (v[idx]-v[cl])>r ; idx--);
	return idx;
}

vector<int> frog_hopp(vector<int> &v, unsigned r, unsigned n){
	vector<int> h;
	unsigned cl = 0, nl;

	h.push_back(v[0]);
	while(cl<v.size() and v[cl]!=n){
		nl = furthest(v,cl,r);
		if(nl==0){	h.clear();	return h;	}
		h.push_back(v[nl]);
		cl = nl;
	}

	return h;
}

vector<int> scan(){
	int n, r, nl, xd;
	cin >> r >> n >> nl;
	vector<int> v;
	for(int i=0; i<nl; i++){
		cin >> xd;
		v.push_back(xd);
	}

	return frog_hopp(v,r,n);
}

int main(int argc, char const *argv[]){
	//vector<int> v = scan();
	//print(v);
	cout << sizeof(int) << endl;
	cout << sizeof(float) << endl;
	cout << sizeof(double) << endl;
	return 0;
}

//0 1 _ 3 4 _ 6 7 8 _ 10 11 12 13 
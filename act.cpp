#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>
#include "src/sort.h"

using namespace std;

class act{
public:
	double st, et, lg;
	act(){		};
	act(double _st, double _et){
		this->st = _st;
		this->et = _et;
		this->lg = this->et-this->st;
	}
	friend bool operator<(const act &a, const act &b){	return (a.et<b.et)? true: false;	}
	friend bool operator>(const act &a, const act &b){	return (a.st<b.st)? true: false;	}
	friend ostream& operator<< (ostream & out, const act &c){
       out << "[" << c.st << "," << c.et << "]";	
       return out;
   	}
	~act(){		}
};

bool w1(const act &a, const act &b){	return (a.st<b.st)? true: false;	}
bool w2(const act &a, const act &b){	return (a.lg<b.lg)? true: false;	}
bool w3(const act &a, const act &b){	return (a.et<b.et)? true: false;	}


template <class T>
void quick_sort(vector<T> &v, int iz, int de, bool (*p)(const act &a, const act &b)){
	int i,j;
    i = iz; 
    j = de; 
    T x = v[(iz+de)/2];
    while(i<=j){
        while(p(v[i],x) and (j<=de))	i++;
        while(p(x,v[j]) and (j>iz))	j--;
 
        if(i<=j){ 
            swap1(v[i], v[j]);
            i++;  j--; 
        }        
    }
    
    if(iz<j)  quick_sort(v, iz, j,p); 
    if(i<de)  quick_sort(v, i, de,p);
}

template<class T>
vector<T> act_sel(vector<T> &v){
	vector<T> s;	list<T> q;
	for(unsigned i=0; i<v.size(); i++)	q.push_back(v[i]);
	T tm;

	typename list<T>::iterator it;
	while(!q.empty()){
		tm = q.front();	s.push_back(tm);
    	q.pop_front();
    	for(it = q.begin(); it!=q.end() ; it++){
    		if((*it).st < tm.et){
    			q.erase(it);
    			it--;
    		}
    	}
    }
	return s;
}

vector<act> scan(){
	int n;
	double st, et;
	cin >> n;
	vector<act> v;
	for(int i=0; i<n; i++){
		cin >> st >> et;
		v.push_back(act(st,et));
	}
	return v;
}

int main(int argc, char const *argv[]){
	vector<act> v = scan();
	quick_sort(v,0,v.size()-1,w1);	print(v);
	print(act_sel(v));
	quick_sort(v,0,v.size()-1,w2);	print(v);
	print(act_sel(v));
	quick_sort(v,0,v.size()-1,w3);	print(v);
	print(act_sel(v));
	return 0;
}
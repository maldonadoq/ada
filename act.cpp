#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>
#include "src/sort.h"

using namespace std;

class act{
public:
	double st, et, lg, wt;
	act(){		};
	act(double _st, double _et, double _wt){
		this->st = _st;
		this->et = _et;
		this->wt = _wt;
		this->lg = this->et-this->st;
	}
	friend ostream& operator<< (ostream & out, const act &c){
       out << "[" << c.st << "," << c.et << "," << c.wt << "]";	
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


// greddy O(N^2)
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


// greddy O(N)
template<class T>
vector<T> act_sel_n(vector<T> &v){
	vector<T> s;
	unsigned i=0,j;
	s.push_back(v[i]);
	for(j=1; j<v.size(); j++){
		if(v[j].st >= v[i].et){
			s.push_back(v[j]);
			i=j;
		}
	}
	return s;
}

template<class T>
vector<act> activ_value(vector<T> &v){
	double dp[v.size()];
	unsigned n = v.size(),i,j;
	double mxt=-1;
	vector<act> s;
	for(int i=0; i<n; i++)	dp[i]=v[i].wt;
    
    for(i=1; i<n; i++){
        for(j=0; j<i; j++){
            if(v[j].et<=v[i].st)
                dp[i]=max(dp[i], dp[j]+v[i].wt);
            mxt=max(dp[i], mxt);
        }
    }

    for(int i=n-1; i>=0; i--){
        if(dp[i]==mxt){
            mxt-=v[i].wt;
            s.push_back(v[i]);
        }
    }

    return s;
}

vector<act> scan(){
	int n;
	double st, et, wt;
	cin >> n;
	vector<act> v;
	for(int i=0; i<n; i++){
		cin >> st >> et >> wt;
		v.push_back(act(st,et,wt));
	}
	return v;
}

//w1	start time
//w2	length time
//w3	end time

int main(int argc, char const *argv[]){
	vector<act> v = scan();
	quick_sort(v,0,v.size()-1,w3);	print(v);
	print(act_sel_n(v));
	print(activ_value(v));
	return 0;
}
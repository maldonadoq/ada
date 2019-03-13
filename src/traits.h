#ifndef _TRAITS_H_
#define _TRAITS_H_

#include <iostream>
#include <math.h>

using namespace std;

template<class _N, class _E>
class traits{
public:
    typedef traits<_N,_E> self;
    typedef _N N;
    typedef _E E;
    typedef cgrafo<self>   grafo;
    typedef cnode<self>   node;
    typedef cedge<self>   edge;
    typedef typename list<node *>::iterator niterator;
    typedef typename list<edge *>::iterator eiterator;
};

class cord{
public:
    int x, y;
    cord(int _x=0, int _y=0){
        this->x = _x;
        this->y = _y;
    }
    friend bool operator==(const cord &a, const cord &b){
       	if(a.x == b.x && a.y == b.y) return true;
		return false;
   	}
   	friend bool operator!=(const cord &a, const cord &b){
       	if(a.x != b.x || a.y != b.y) return true;
		return false;
   	}
    friend ostream& operator<< (ostream & out, const cord &c){
       out << "(" << c.x << "," << c.y << ")";	
       return out;
   	}
   	double distance(cord a){
   		return sqrt(pow(this->x -a.x,2)+pow(this->y -a.y,2));
   	}
   	~cord(){	};
};

#endif
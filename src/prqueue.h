#ifndef _PRQUEUE_H_
#define _PRQUEUE_H_

#include <iostream>
#include <list>

using namespace std;

template<class T>
class prqueue{
public:
	list<T> a;
	typedef typename list<T>::iterator	niterator;
	
	prqueue(){	};
	prqueue(T w){	this->end = w;	}

	void push(T x){
		niterator it = a.begin();
		for(; it!=a.end(); it++)
			if(x.second<=(*it).second)	break;
		a.insert(it, x);
	}

	void pop(){	a.pop_front();	}

	T top(){
		niterator it = a.begin();
		return *it;
	}

	bool empty(){	return	a.empty();	}
	unsigned size(){	return a.size();	}
};

#endif
#ifndef _PRQUEUE_H_
#define _PRQUEUE_H_

#include <iostream>
#include <list>

template<class G>
class prqueue{
public:
	typedef typename G::node		node;
	typedef typename G::niterator	niterator;
	list<node *> a;
	node *end;
	prqueue(){	};
	prqueue(node *w){	this->end = w;	}

	void push(node* x){
		niterator it = a.begin();
		for(; it!=a.end(); it++)
			if(x->m_acum<=(*it)->m_acum)	break;
		a.insert(it, x);
	}

	void pushd(node* x){
		niterator it = a.begin();
		for(; it!=a.end(); it++)
			if(x->m_dato.distance(end->m_dato)<=(*it)->m_dato.distance(end->m_dato))	break;
		a.insert(it,x);
	}

	void pop(){	a.pop_front();	}

	node* top(){
		niterator it = a.begin();
		return *it;
	}

	bool empty(){	return	a.empty();	}
};

#endif
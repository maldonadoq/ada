#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "cmp.h"
#include "btree.h"
#include <thread>

template<class G>
class csearch{
public:
	typedef	typename G::grafo		grafo;
	typedef typename G::N			N;
	typedef typename G::eiterator	eiterator;
	typedef typename G::niterator	niterator;
	typedef typename G::node 		node;

	grafo *M;
	btree<unsigned,cml<unsigned>> *tree;
	unsigned source;
	vector<vector<unsigned>> m_road;
	csearch(grafo *cr){	this->M = cr;	}

	void Thread(unsigned a){
		this->tree = new btree<unsigned,cml<unsigned>>();
	}

};

#endif
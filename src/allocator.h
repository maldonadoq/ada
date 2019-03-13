#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <list>
#include <iostream>

using namespace std;

template<class T>
class F{
public:
	inline unsigned operator()(T *a){
		unsigned sum = 0;
		for(unsigned i=0; a->m_name[i]!='\0'; i++)
			sum+=(a->m_name[i]-'A');
		return sum;
	}
};

template<class T>
class Alist{
public:
	list<T*> a;
	typename list<T*>::iterator it;
	Alist(){	};

	bool ins(T *x){
		if(fin(x))	return false;
		a.push_back(x);
		return true;
	}

	bool rem(T *x){
		if(!fin(x))	return false;
		a.erase(it);
	}

	bool fin(T *x){
		for(it=a.begin(); it!=a.end(); it++)
			if((*it)->m_name == x->m_name)	return true;
		return false;
	}

	void pri(){
		for(it=a.begin(); it!=a.end(); it++)	(*it)->print();
		cout << endl << endl;			
	}

	unsigned size(){	return a.size();	}
};

#endif
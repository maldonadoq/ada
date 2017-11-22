#ifndef _EDGE_H_
#define _EDGE_H_

class edge_tmp{
public:
	unsigned w,v;
	double p;
	edge_tmp(unsigned _w, unsigned _v, double _p){
		this->w = _w;
		this->v = _v;
		this->p = _p;
	}
};

class edge{
public:
	unsigned v;
	double p;
	edge(unsigned _v, double _p){
		this->v = _v;
		this->p = _p;
	}
};

template<class G>
class cedge{
public:
    typedef typename G::E E;
    typedef typename G::node node;
    node* m_nodes[2];
    E m_dato;
    bool m_dir;
    bool m_vst;
    cedge(E x, bool d){
        this->m_dato = x;
        this->m_dir = d;
        this->m_vst = false;
    }
    ~cedge(){   };
};

#endif	
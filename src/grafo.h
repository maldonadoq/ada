#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <vector>
#include <list>
#include <queue>
#include <vector>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <algorithm>
#include <stdlib.h>

#define infty 1<<15

#include "node.h"
#include "edge.h"
#include "prqueue.h"
#include "search.h"

using namespace std;

template<class G>
class cgrafo{
public:
    typedef typename G::N N;
    typedef typename G::E E;
    typedef typename G::node node;
    typedef typename G::edge edge;
    typedef typename G::niterator niterator;
    typedef typename G::eiterator eiterator;
    unsigned ne, nn;
    string m_name;
    vector<node *> m_nodes;
    
    cgrafo(string name){
        this->ne = 0; this->nn = 0;
        this->m_name = name;   
    }
    cgrafo(){    this->ne = 0; this->nn = 0;    }

    void info(){
        cout << "-----------------------------------" << endl;
        cout << "   " << this->m_name << "   nodos: " << nn << "    aristas: " << ne << endl;
        cout << "-----------------------------------" << endl;  
    }
    
    bool insert_node(N x){
        node *tr = new node(x,nn++);
        m_nodes.push_back(tr);
        return true;
    }
    
    bool insert_edge(E x, unsigned a, unsigned b, bool d){
        edge *c = new edge(x,d);
        m_nodes[a]->m_edges.push_back(c);
        m_nodes[b]->m_edges.push_back(c);
        c->m_nodes[0] = m_nodes[a];
        c->m_nodes[1] = m_nodes[b];
        this->ne++;
        return true;
    }
    
    bool remove_edge(N a, N b){
    	unsigned p,q;
    	if(!(find(a,p) and find(b,q)))	return false;
    	m_nodes[p]->remove_edge(m_nodes[q]);
    	this->ne--;
        return true;
    }
    
    bool remove_node(N x){
        unsigned p;
        if(!find(x,p))   return false;
        this->ne -= m_nodes[p]->m_edges.size();
        m_nodes[p]->remove_edges();
        delete m_nodes[p];
        m_nodes.erase(m_nodes.begin()+p);
        return true;
    }
    
    void print(){
    	info();
        unsigned wq = (m_nodes.size()/10 == 0)? 1: m_nodes.size()/10;
        for(unsigned i=0; i<m_nodes.size(); i+=wq)  
            m_nodes[i]->print();
    }

    void fn(node *a, E ed, E ac, vector<unsigned> &road){
        if((ac+ed)<a->m_acum){
            a->m_acum = ac+ed;
            a->m_road = road;
            a->m_road.push_back(a->m_id);
        }
    }

    vector<vector<unsigned>> dijkstra(unsigned a){
        this->pull();
        prqueue<G> pq;
        pq.push(m_nodes[a]);
        eiterator it;
        node *t;
        m_nodes[a]->m_acum = 0;
        while(!pq.empty()){
            t = pq.top();   pq.pop();
            for(it=t->m_edges.begin(); it!=t->m_edges.end(); it++){
                if(!(*it)->m_vst){
                    if(((*it)->m_nodes[1]->m_dato!=t->m_dato)){
                        (*it)->m_vst = true;
                        fn((*it)->m_nodes[1], (*it)->m_dato, t->m_acum,(*it)->m_nodes[0]->m_road);  
                        pq.push((*it)->m_nodes[1]);   
                    }
                }
            }
        }
        /*cout << m_nodes[b]->m_acum << "\t" << a << " ";
        for(unsigned i=0; i<m_nodes[b]->m_road.size(); i++)
            cout << m_nodes[b]->m_road[i] << " ";
        cout << endl;*/
        vector<vector<unsigned>> v;
        for(unsigned i=0; i<m_nodes.size(); i++)
            v.push_back(m_nodes[i]->m_road);
        return v;
    }

    void pull(){
        eiterator it;
        for(unsigned i=0; i<m_nodes.size(); i++){
            m_nodes[i]->m_road.clear();
            m_nodes[i]->m_acum = infty;
            for(it=m_nodes[i]->m_edges.begin(); it!=m_nodes[i]->m_edges.end(); it++)
                (*it)->m_vst = false;
        }
    }

    virtual ~cgrafo(){ 
        node *t;
        while(m_nodes.size()!=0){
            t = m_nodes[0];
            m_nodes.erase(m_nodes.begin());
            delete t;
        }
    };
};

#endif
#include <iostream>
#include <queue>
 
using namespace std;

class sws{
public:
    unsigned a,b;
    sws(unsigned _a, unsigned _b){
        this->a = _a;
        this->b = _b;
    }
};

class compare{
public:
    bool operator()(sws a, sws b){
        return a.a < b.a;
    }
};
 
void showpq(priority_queue <sws> gq){
    priority_queue <sws> g = gq;
    while (!g.empty()){
        cout << '\t' << (g.top()).a;
        g.pop();
    }
    cout << '\n';
}
 
int main ()
{
    priority_queue <sws> gquiz;
    gquiz.push(sws(10,2));
    gquiz.push(sws(30,1));
    gquiz.push(sws(20,3));
    gquiz.push(sws(5,4));
    gquiz.push(sws(1,4));
 
    cout << "The priority queue gquiz is : ";
    showpq(gquiz);
 
    cout << "\ngquiz.size() : " << gquiz.size();
    return 0;
}
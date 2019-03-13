#include <iostream>
#include <math.h>
#include "src/sws.h"

static int n=10;

using namespace std;

double factorial(double t){
	double r = 1;
	for(int i=1; i<=t; i++)	r*=i;
	return r;
}

double exponencial(int a){
	double r = 0;
	for(int i=0; i<n; i++)
		r += pow(a,i)/factorial(i);
	return r;
}

double sin_(double a){
	double r=0;
	for(int i=0; i<n; i++){
		if(i%2 == 0)	r += ((double)pow(a,(2*i) + 1)/factorial((2*i)+1));
		else	r -= ((double)pow(a,(2*i) + 1)/factorial((2*i)+1));
	}
	return r;
}

double ln(float a){
	double r=0;
	for(int i=0; i<n; i++){
		if(i%2 == 0)	r+=(pow(a-1,i+1)/(i+1));
		else	r-=(pow(a-1,i+1)/(i+1));
	}
	return r;
}


class A{
private:
	int a;
protected:
	int c;
public:
	int b;
	A(){
		this->a = 0;
		this->b = 0;
	}
	virtual void f()=0;
	virtual ~A(){	}
};


class B:public A{
	void f(){
		this->b++;
		this->c++;
	}
};

int main(int argc, char const *argv[]){
	A &a = *(new B());
	a.f();
	delete &a;
	return 0;
}
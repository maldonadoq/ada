#ifndef _SORT_H_
#define _SORT_H_

#include <vector>
#include "sws.h"
#include <iostream>

using namespace std;

template<class T>
void swap1 (T &a, T &b){
	T tm = a;
	a = b;
	b = tm;
}


#endif
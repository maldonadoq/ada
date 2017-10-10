#include <iostream>
#include <stdio.h>
#include "src/sws.h"

static unsigned long long s;

using namespace std;

bool comp(int a, int b){
	s++;
	return a<b;
}

void insert_sort(int *a, int t, bool (*p)(int, int)){
	int j;
	for(int i=0; i<t; i++){
		j = i;
		while(j>0 and p(*(a+j),*(a+j-1))){
			swap_((a+j), (a+j-1));
			j--;
		}
	}
}


void merge_sort(int *a, int izq, int der, bool (*p)(int, int)){
	if(izq == der) return;

	int t = der-izq+1;
	int piv = ((izq+der)>>1);

	merge_sort(a,izq,piv,p);
	merge_sort(a,piv+1,der,p);

	int *b = new int[t];
	for(int i=0; i<t; i++)	*(b+i) = *(a+izq+i);
	
	int j = 0;
	int k = piv-izq+1;

	for(int i=0; i<t; i++){
		if(k<=der-izq){
			if(j <= piv-izq){
				if(p(*(b+k),*(b+j))){	*(a+i+izq) = *(b+k);	k++;	}
				else{	*(a+i+izq) = *(b+j);	j++;	}
			}
			else{	*(a+i+izq) = *(b+k);	k++;	}
		}
		else{	*(a+i+izq) = *(b+j); j++;	}
	}
	delete b;
}

int main(int argc, char const *argv[]){
	int n = 20, ju = 10000;
	for(int i=0, in=ju; i<n; i++, in+=ju){
		int *a = new int[in];
		int *b = new int[in];
		
		rand_(a,in);
		rand_(b,in);

		cout << in << "\t";	s=0;
		merge_sort(a,0,in-1,comp);	
		cout << s << "\t";	s=0;
		insert_sort(b,in,comp);
		cout << s << "\n";
		delete a;	delete b;
	}
	return 0;
}
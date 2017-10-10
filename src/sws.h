#ifndef _SWS_H_
#define _SWS_H_

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>

using namespace std;

bool linear_search(int *a, int t, int x){
    for(int i=0; i<t; i++)
        if(*(a+i) == x) return true;
    return false;
}

double time(int *a, int t, void (*p)(int *, int)){
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    p(a, t);
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    return tiempo;
}

void dat_t(FILE *a, int *A, int t, void (*p)(int *, int)){
    double tim = (double)(time(A, t,p)/1000);
    fprintf(a, "%lf\t", tim);
}

void rand_(int *a, int t){
	srand(time(NULL));
	for(int i=0; i<t; i++)	*(a+i) = rand()%(2*t);
}

void min_to_max(int *a, int t){
	for(int i=0; i<t; i++)	*(a+i) = i;
}

void max_to_min(int *a, int t){
	for(int i=0; i<t; i++)	*(a+i) = t-i-1;
}

void swap_(int *a, int *b){
	int r = *a;
	*a = *b;
	*b = r;
}

void print_(int *a, int t){
    for(int i=0; i<t; i++)  cout << *(a+i) << " ";
    cout << endl;
}

#endif
